#include <iostream>
#include <random>
#include "chrono.h"


using namespace std;

// power function for int

int raise(int n, int p){

        if (p == 0){return 1;}
        else {return n * raise(n, p - 1);}

}
// updates for heat propagation and stationary heat equation
// update the array with values, a copy of the array is needed and also the bulk indices and the dimension
// as well as the linear size of the grid

void update_propagation(double *array1, double *array2, int *indices, int dimension, int size, double diff){

  // loop through all indices in the bulk and update the first array based on the values in the second

  for (int i = 0; i < raise(size - 2, dimension); i++){

    // update based on nerest neighbors in each dimension
    // 1d

    if (dimension == 1){

      array1[indices[i]] = (1. - 2. * diff) * array2[indices[i]] + diff * (array2[indices[i] + 1] + array2[indices[i] - 1]);

    }

    // 2d

    else if (dimension == 2){

      array1[indices[i]] = (1. - 4. * diff) * array2[indices[i]] + diff * (array2[indices[i] + 1] + array2[indices[i] - 1] + array2[indices[i] + size] + array2[indices[i] - size]);

    }

    // 3d

    else {

      array1[indices[i]] = array1[indices[i]] = (1. - 6. * diff) * array2[indices[i]] + diff * (array2[indices[i] + 1] + array2[indices[i] - 1] + array2[indices[i] + size] + array2[indices[i] - size] + array2[indices[i] + size * size] + array2[indices[i] - size * size]);

    }
  }

}

void update_stationary(double *array1, double *array2, int *indices, int dimension, int size, double diff){

  // loop through all indices in the bulk and update the first array based on the values in the second

  for (int i = 0; i < raise(size - 2, dimension); i++){

    // update based on nerest neighbors in each dimension
    // 1d

    if (dimension == 1){

      array1[indices[i]] =  (1./(2. * diff)) * (array2[indices[i] + 1] + array2[indices[i] - 1]);

    }

    // 2d

    else if (dimension == 2){

      array1[indices[i]] = (1./(4. * diff))  * (array2[indices[i] + 1] + array2[indices[i] - 1] + array2[indices[i] + size] + array2[indices[i] - size]);

    }

    // 3d

    else {

      array1[indices[i]] = (1./(6. * diff)) * (array2[indices[i] + 1] + array2[indices[i] - 1] + array2[indices[i] + size] + array2[indices[i] - size] + array2[indices[i] + size * size] + array2[indices[i] - size * size]);

    }
  }

}

void parallel_update_stationary(double *array1, double *array2, int *indices, int dimension, int size, double diff){

  // loop through all indices in the bulk and update the first array based on the values in the second

  #pragma omp parallel for shared(array1, array2, indices, dimension, size, diff)

  for (int i = 0; i < raise(size - 2, dimension); i++){

    // update based on nerest neighbors in each dimension
    // 1d

    if (dimension == 1){

      array1[indices[i]] =  (1./(2. * diff)) * (array2[indices[i] + 1] + array2[indices[i] - 1]);

    }

    // 2d

    else if (dimension == 2){

      array1[indices[i]] = (1./(4. * diff))  * (array2[indices[i] + 1] + array2[indices[i] - 1] + array2[indices[i] + size] + array2[indices[i] - size]);

    }

    // 3d

    else {

      array1[indices[i]] = (1./(6. * diff)) * (array2[indices[i] + 1] + array2[indices[i] - 1] + array2[indices[i] + size] + array2[indices[i] - size] + array2[indices[i] + size * size] + array2[indices[i] - size * size]);

    }
  }

}

// calculate the overall change (sum of individual changes) on the grid
// needs updated array, previous array, size of arrays

double total_change(double *array1, double *array2, int size){

  double delta = 0.;
  for (int i = 0; i < size; i++){delta += array1[i] - array2[i];}

  return delta;
}

double parallel_total_change(double *array1, double *array2, int size){

  double delta = 0.;

  #pragma omp parallel for reduction(+: delta) shared(array1, array2)
  for (int i = 0; i < size; i++){delta += array1[i] - array2[i];}

  return delta;
}

int main(){

    int dim = 2;        // dimension of grid, must be 1, 2 , 3
    int N = 200;         // lenght odf single dimension
    double D = 1.;     // effective diffusion constant
    double eps = 0.00001;  // precison criteria
    double amp = 3.0;         // amplitude of initial distribuntion
    double bc[2 * dim] = {0.}; // boundary conditions
    double seed = 22.;        // seed for random numbers

    bc[0] = 0.;
    bc[1] = 0.;
    bc[2] = 0.;
    bc[3] = 0.;
    // bc[4] = 9.;
    // bc[5] = -5.;

    default_random_engine generator;
    generator.seed(seed);
    uniform_real_distribution<double> distribution(0.0, amp);

    if (dim != 1 ^ dim != 2 ^ dim != 3){cout << "dimension error: dim = " << dim << " must be 1, 2 or 3" << endl; }
    else {



            double grid[raise(N, dim)] = {0.};     // holds values of the heat amplitude
            int index[raise(N - 2, dim)];           // holds indices of sites in bulk (without boundary)

            // fill initial array with random values (later set boundary)

            for (int n = 0; n < sizeof(grid)/sizeof(double); n++){

                grid[n] = distribution(generator);
            }

            // fill indices (hard code)

            // 1d

            if (dim == 1){

              for (int i = 0; i < N - 2; i ++){index[i] = i + 1;}

            }

            // 2d

            else if (dim == 2){

              for (int i = 0; i < N - 2; i++){
                for (int j = 0; j < N - 2; j++){

                  index[i + j * (N - 2)] = (i + 1) + (j + 1) * N;

                }
              }
            }

            // 3d

            else {

              for (int i = 0; i < N - 2; i++){
                for (int j = 0; j < N - 2; j++){
                  for (int k = 0; k < N - 2; k++){

                    index[i + j * (N - 2) + k * (N - 2) * (N - 2)] = (i + 1) + (j + 1) * N + (k + 1) * N * N;

                  }
                }
              }

            }



            // set boundary condition (hard code)

            // 1d

            if (dim == 1){grid[0] = bc[0]; grid[N - 1] = bc[1];}

            // 2d

            else if (dim == 2){

              // corners

              grid[0] = 0.5 * (bc[0] + bc[1]);                // upper left
              grid[N - 1] = 0.5 * (bc[0] + bc[3]);            // upper right
              grid[N * (N - 1)] = 0.5 * (bc[1] + bc[2]);      // lower left
              grid[N * N - 1] = 0.5 * (bc[2] + bc[3]);        // lower right

              // edges (without corners)

              for (int i = 1; i <= N - 2; i++){

                grid[i] = bc[0];    // top edge
                grid[i * N] = bc[1];    // left edge
                grid[N * (N - 1) + i] = bc[2];    // bottom edge
                grid[(N - 1) + i * N] = bc[3];    // right edge

              }
            }

             // 3d

             else {

               // corners

               grid[0] = (bc[0] + bc[1] + bc[2])/3.0;                             // edge between faces 1, 2, 3
               grid[N * (N - 1)] = (bc[0] + bc[1] + bc[3])/3.0;                   // edge between faces 1, 2, 4
               grid[N - 1] = (bc[0] + bc[2] + bc[4])/3.0;                         // edge between faces 1, 3, 5
               grid[N * N - 1] = (bc[0] + bc[3] + bc[4])/3.0;                     // edge between faces 1, 4, 5
               grid[N * N * (N - 1)] = (bc[1] + bc[2] + bc[5])/3.0;               // edge between faces 2, 3, 6
               grid[N * (N * N - 1)] = (bc[1] + bc[3] + bc[5])/3.0;               // edge between faces 2, 4, 6
               grid[(N - 1) * (N * N + 1)] = (bc[2] + bc[4] + bc[5])/3.0;         // edge between faces 3, 5, 6
               grid[N * N * N - 1] = (bc[3] + bc[4] + bc[5])/3.0;                 // edge between faces 4, 5, 6

               // edges (without corners)

               for (int i = 1; i <= N - 2; i++){

                 grid[i * N] = 0.5 * (bc[0] + bc[1]);                             // edge between faces 1, 2
                 grid[i] = 0.5 * (bc[0] + bc[2]);                                 // edge between faces 1, 3
                 grid[N * (N - 1) + i] = 0.5 * (bc[0] + bc[3]);                   // edge between faces 1, 4
                 grid[(N - 1) + i * N] = 0.5 * (bc[0] + bc[4]);                   // edge between faces 1, 5
                 grid[i * N * N] = 0.5 * (bc[1] + bc[2]);                         // edge between faces 2, 3
                 grid[N * (N - 1) + i * N * N] = 0.5 * (bc[1] + bc[3]);           // edge between faces 2, 4
                 grid[N * N * (N - 1) + i * N] = 0.5 * (bc[1] + bc[5]);           // edge between faces 2, 6
                 grid[(N - 1) + i * N * N] = 0.5 * (bc[2] + bc[4]);               // edge between faces 3, 5
                 grid[N * N * (N - 1) + i] = 0.5 * (bc[2] + bc[5]);               // edge between faces 3, 6
                 grid[(N * N - 1) + i * N * N] = 0.5 * (bc[3] + bc[4]);           // edge between faces 4, 5
                 grid[N * (N * N - 1) + i] = 0.5 * (bc[3] + bc[5]);               // edge between faces 4, 6
                 grid[(N - 1) * (N * N + 1) + i * N] = 0.5 * (bc[4] + bc[5]);     // edge between faces 5, 6

               }

               // faces (without edges and corners)

               for (int i = 1; i <= N - 2; i++){
                 for (int j = 1; j <= N - 2; j++){

                   grid[i + j * N] = bc[0];                         // face 1
                   grid[i * N + j * N * N] = bc[1];                 // face 2
                   grid[i + j * N * N] = bc[2];                     // face 3
                   grid[N * (N - 1) + i + j * N * N] = bc[3];       // face 4
                   grid[(N - 1) + i * N + j * N * N] = bc[4];       // face 5
                   grid[N * N * (N - 1) + i + j * N] = bc[5];       // face 6

                 }
               }
             }

             // update until overall change is leq epsilon (square since change can be negative)

             int count = 0;
             double change = 1.0;

        {
            ChronoTimer t("Parallel Stencil");
            while ((change * change) > (eps * eps)) {

                // create copy of grid

                double gridcopy[raise(N, dim)] = {0.};
                for (int i = 0; i < raise(N, dim); i++){

                    gridcopy[i] = grid[i];

                }

                // update the original grid

                parallel_update_stationary(grid, gridcopy, index, dim, N, D);

                // get total change

                change = parallel_total_change(grid, gridcopy, raise(N, dim));

                // count steps

                count++;

            }

        }




            cout << "delta h = " << change << endl;
            cout << count << "  steps" << endl;


    //         for (int i = 0; i < raise(N, dim); i++){
    //
    //           cout << grid[i] << "  ";
    //
    //         }
    //         cout << endl;
    //
    }
}
