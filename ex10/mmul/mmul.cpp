#include <iostream>
#include <mpi.h>
#include <vector>
#include <random>

using namespace std;

int main(int argc, char *argv[]) {

  /* mmul with mpi version 1 */

  int p;                      // number of processes
  int n = atoi(argv[1]);                      // size of matrices (assume square matrices for now)

  // start parallel environment

  MPI_Init(&argc, &argv);

  int id;                                     // id of process
  MPI_Comm_rank(MPI_COMM_WORLD, &id);         // give each process its id
  MPI_Comm_size(MPI_COMM_WORLD, &p);         // get number of processesS

  // each process will compute columns of the resulting matrix (C = A*B )
  // for this it needs the full matrix A and the corresponding column of B

  vector<vector<double>> A (n, vector<double> (n)); 

  // in this example we will make A the identity matrix and B a random matrix

  default_random_engine generator;
  generator.seed(id + 1);
  uniform_real_distribution<double> distribution(-1.0, 1.0);

  // set up A

  for (int i = 0; i < n; i++){A[i][i] = 1.; }

  // loop through the rows of a

  for (int i = 0; i < n; i++){

      // distribute the workload 

      if (i % p == id){

        // create the columns to be computed (usually B would be read from file specified by the id)

        vector<double> B (n);
        vector<double> C (n);
        for (int j = 0; j < n; i++){
              
            B[j] = distribution(generator);
              
            }

        // perform the multiplication

        for (int k = 0; k < n; k++){
            for (int q = 0; q < n; q++){

                C[k] += A[k][q] * B[q];
            }
        }

        // now the column of C is ready to be written to file, to be used for further computations or to be outputted 
        // here we output the difference with B (C - B), which should give zeros

        for (int s = 0; s < n; s++){

            cout << C[s] - B[s] << endl;
        }
      }

  }


  // print if process is finished

  cout << "Process " << id << " is finished." << endl;

  MPI_Finalize();

  return 0;
}