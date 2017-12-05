// use 5 point stencil with the given parameters

#include <iostream>
#include <random>


using namespace std;

int main(){

    int N = 512;         // lenght odf single dimension
    double eps = 20.0;  // precision criteria
    double amp = 3.0;         // amplitude of initial distribuntion
    double bc[4] = {1.0, -0.5, 0.0, 0.5}; // boundary conditions
    double seed = 42;        // seed for random numbers

    default_random_engine generator;
    generator.seed(seed);
    uniform_real_distribution<double> distribution(0.0, amp);


    double grid[N * N][2] = {0.};     // holds values of the heat amplitude
    int index[(N - 2) * (N - 2)];           // holds indices of sites in bulk (without boundary)
    

    // fill initial array with random values (later set boundary)

    for (int n = 0; n < N * N; n++){

        grid[n][0] = distribution(generator);
        grid[n][1] = distribution(generator);
    }
   

    // fill indices (hard code)

    for (int i = 0; i < N - 2; i++){
        for (int j = 0; j < N - 2; j++){

        index[i + j * (N - 2)] = (i + 1) + (j + 1) * N;

        }
    }
    


    // set boundary condition (hard code)

    // edges (without corners)

    for (int i = 1; i <= N - 2; i++){

    grid[i][0] = bc[0];    // top edge
    grid[i][1] = bc[0];

    
    grid[i * N][0] = bc[1];    // left edge
    grid[i * N][1] = bc[1];  

    grid[N * (N - 1) + i][0] = bc[2];    // bottom edge
    grid[N * (N - 1) + i][1] = bc[2];   

    grid[(N - 1) + i * N][0] = bc[3];    // right edge
    grid[(N - 1) + i * N][1] = bc[3];    

    }
    
    

    // update until overall change is leq epsilon (square since change can be negative)

    int count = 0;              // count the number of updates
    double change = 100.0;        // first change to compare eps to
    int a = 0;                  //  indicates which array (grid[...][a]) is the input
    
  
    while ((change * change) > (eps * eps)) {
        
        change = 0.0;
        for (int i = 0; i < (N - 2) * (N - 2); i++){
            
            int k = index[i];

           // update the output array based on the 5 point stencil

            grid[k][1 - a] = 0.2 * (grid[k][a] + grid[k + 1][a] + 
            grid[k - 1][a] + grid[k + N][a] + grid[k - N][a]); 

            change += grid[k][1 - a] - grid[k][a];

        }
    
        a = 1 - a;          // switch input and output array
        count++;
        
    }


    cout << "delta h = " << change << endl;
    cout << count << "  steps" << endl;


    // for (int i = 0; i < N * N; i++){

    //     cout << grid[i][0] << "  ";

    // }
    // cout << endl;

    return 0;
}
