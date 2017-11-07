#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// binomial coefficient (adapted from http://www.geeksforgeeks.org/space-and-time-efficient-binomial-coefficient/)
int binomialCoeff(int n, int k)
{
   int res = 1;

   // Since C(n, k) = C(n, n-k)
   if ( k > n - k )
       k = n - k;

   // Calculate value of [n * (n-1) *---* (n-k+1)] / [k * (k-1) *----* 1]
   for (int i = 0; i < k; ++i)
   {
       res *= (n - i);
       res /= (i + 1);
   }

   return res;
}



int main(int argc, char** argv){

    int N = atoi(argv[1]);          // board size (N x N) 
    int n = atoi(argv[2]);          // number of Queens, must be less than N (no check)
    int solutions = 0;  // number of solutions
    int nconfig = binomialCoeff(N, n); // number of configurations

    // create array with configurations

    int config_array[nconfig][n];

    // create list of configurations
    for (int i=1; i<=nconfig; i++){

        int index = i;      // (see documentation)
        int entry = 0;      // ""
        
        for (int j=1; j<=n; j++){

            int count = 1;      // ""
            int test = 0;       // ""
            while (test==0) {

                int compare = binomialCoeff(N - entry - count, n - j);
                
                if (index <= compare){
    
                    config_array[i - 1][j - 1] = entry + count;
                    entry = entry + count;
                    test = 1;
                }

                else {
                    
                    index = index - compare;
                    count += 1;
                
                }
            }

        }

    }

    // test the configurations table
//   for (int m=0; m<nconfig; ++m){
//        for (int q=0; q<n; ++q){

//            cout << config_array[m][q] << "   ";
//        }
//        cout << endl;
//    } 

    // loop trough the configurations

	// configuration of columns on board ( which columns are occupied)
   
	 for (int i=0; i<nconfig; i++){
		
        int xvals[n];
        for (int m=0; m<n; m++){xvals[m]=config_array[i][m];}

	// configurations of rows (which rows are occupied), need to take care of permutations here

        for (int j=0; j<nconfig; j++){
			
            int yvals[n];
            for (int m=0; m<n; m++){yvals[m]=config_array[i][m];}
			
			// test zeroth permutaition

            int diag[n];
            int anti_diag[n];

            for (int q=0; q<n; q++){

                diag[q] = yvals[q] - xvals[q] + N;
                anti_diag[q] = yvals[q] + xvals[q] - 1;

            }

            // look for repeated entries, if none increase number of solutions
            int repetition_counter = 0;

            for (int k=0; k<n-1; k++){
                for(int s=k+1; s<n; s++){

                    if (diag[k]==diag[s] or anti_diag[k]==anti_diag[s]){repetition_counter+=1;}
                   
                }

            }

			if (repetition_counter == 0){solutions += 1;}

			// now the remaining permutations (code modified from https://www.codeguru.com/cpp/cpp/algorithms/article.php/c5123/Permutations-in-C.htm)

			while (next_permutation(yvals, yvals + n)){

            	// set up diagonals

            	int diag2[n];
            	int anti_diag2[n];

            	for (int q=0; q<n; q++){

               	 	diag2[q] = yvals[q] - xvals[q] + N;
                	anti_diag2[q] = yvals[q] + xvals[q] - 1;

            	}


            	// look for repeated entries, if none increase number of solutions
            	int repetitions = 0;

            	for (int k=0; k<n-1; k++){
                	for(int s=k+1; s<n; s++){

                    	if (diag2[k]==diag2[s] or anti_diag2[k]==anti_diag2[s]){repetitions += 1;}
                    	else {}
                	}
				}
				
				if (repetitions == 0){solutions += 1;}
				
			}

            
        }

    }
    
    cout << "The n Queens Problem on an N x N board with n, N = " << n << ", " << N << " has " << solutions << " solutions." << endl;
    return 0;
}
