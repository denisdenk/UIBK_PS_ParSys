#include <iostream>
#include <vector>
#include <algorithm>
#include "chrono_timer.h"

using namespace std;

// solves the n Queens Problem
int main(int argc, char** argv){

    ChronoTimer t("n Queens");
    int n = atoi(argv[1]);          // number of Queens, must be even (no check)
    int solutions = 0;              // number of solutions

    // even n
    if (n%2 == 0){
    // loop through half of first column
        for (int i=1; i<=n/2; i++ ){
            // some vectors for looping
            vector<int> counts(n - 2);
            vector<int> ycoords;

            // coordinate of the first column y value
            ycoords.push_back(i);
            // set index for second column to zero if not allowed
            int firstsize = n - 2;
            if (1 <= i - 1){firstsize -= 1;}
           
            while (counts[0]<=firstsize){
                if (ycoords.size() == n - 1){
                    vector<int> indices;
                        for (int q=1; q<=n; q++){
                        indices.push_back(q);
                    }
                    for (int k=0; k<n - 1; k++){

                        if (ycoords[k] + n - 1 - k <= n){indices[ycoords[k] + n - 1 - k - 1] = 0;}
                        if (1 <= ycoords[k] - n + 1 + k){indices[ycoords[k] - n + 1 + k - 1] = 0;}
                        indices[ycoords[k] - 1] = 0;
                    }
                    // delete disallowed indices
                    indices.erase(remove(indices.begin(), indices.end(), 0), indices.end());
                    if (indices.size() >= 1){solutions += 1;}
                    ycoords.pop_back();

                }

                else {

                    int j = ycoords.size();
                    vector<int> indices;
                        for (int q=1; q<=n; q++){
                        indices.push_back(q);
                    }
                    for (int k=0; k<j; k++){

                        if (ycoords[k] + j - k <= n){indices[ycoords[k] + j - k - 1] = 0;}
                        if (1 <= ycoords[k] - j + k){indices[ycoords[k] - j + k - 1] = 0;}
                        indices[ycoords[k] - 1] = 0;
                
                    }
                    
                    // delete disallowed indices
                    indices.erase(remove(indices.begin(), indices.end(), 0), indices.end());
                    if (indices.size()<=counts[j - 1]){
                        
                        if (j == 1){counts[0] += 1;}
                        else {ycoords.pop_back(); counts[j - 1]=0;}

                    }

                    else{ycoords.push_back(indices[counts[j - 1]]); counts[j - 1] += 1;}
                }
            }
        }

        cout << "The " << n << " Queens Problem has " << 2 * solutions << " solutions." << endl;

    }

    // odd n
    else {

        // first loop through even indices
        for (int i=1; i<=(n-1)/2; i++ ){
            // some vectors for looping
            vector<int> counts(n - 2);
            vector<int> ycoords;

            // coordinate of the first column y value
            ycoords.push_back(i);

            // set index for second column to zero if not allowed
            int firstsize = n - 2;
            if (1 <= i - 1){firstsize -= 1;}

            // loop through second column
            while (counts[0]<=firstsize){
                if (ycoords.size() == n - 1){

                    vector<int> indices;
                    for (int q=1; q<=n; q++){
                    indices.push_back(q);
                    }

                    for (int k=0; k<n - 1; k++){

                        if (ycoords[k] + n - 1 - k <= n){indices[ycoords[k] + n - 1 - k - 1] = 0;}
                        if (1 <= ycoords[k] - n + 1 + k){indices[ycoords[k] - n + 1 + k - 1] = 0;}
                        indices[ycoords[k] - 1] = 0;
                    }

                    // delete disallowed indices
                    indices.erase(remove(indices.begin(), indices.end(), 0), indices.end());
                    if (indices.size() >= 1){solutions += 1;}
                    ycoords.pop_back();

                }

                else {

                    int j = ycoords.size();
                    vector<int> indices;
                    for (int q=1; q<=n; q++){
                    indices.push_back(q);
                    }

                    for (int k=0; k<j; k++){

                        if (ycoords[k] + j - k <= n){indices[ycoords[k] + j - k - 1] = 0;}
                        if (1 <= ycoords[k] - j + k){indices[ycoords[k] - j + k - 1] = 0;}
                        indices[ycoords[k] - 1] = 0;
                
                    }
                    
                    // delete disallowed indices
                    indices.erase(remove(indices.begin(), indices.end(), 0), indices.end());
                    if (indices.size()<=counts[j - 1]){
                        
                        if (j == 1){counts[0] += 1;}
                        else {ycoords.pop_back(); counts[j - 1]=0;}

                    }

                    else{ycoords.push_back(indices[counts[j - 1]]); counts[j - 1] += 1;}
                }
            }
        }

        // solutions are symmetric
        solutions *= 2;

        // find solutions for middle of the column
        int i = (n + 1)/2;
        // some vectors for looping
        vector<int> counts(n - 2);
        vector<int> ycoords;

        // coordinate of the first column y value
        ycoords.push_back(i);

        // set index for second column to zero if not allowed
        int firstsize = n - 2;
        if (1 <= i - 1){firstsize -= 1;}

        // loop through second column
        while (counts[0]<=firstsize){

            if (ycoords.size() == n - 1){

                vector<int> indices;
                for (int q=1; q<=n; q++){
                indices.push_back(q);
                }

                for (int k=0; k<n - 1; k++){

                    if (ycoords[k] + n - 1 - k <= n){indices[ycoords[k] + n - 1 - k - 1] = 0;}
                    if (1 <= ycoords[k] - n + 1 + k){indices[ycoords[k] - n + 1 + k - 1] = 0;}
                    indices[ycoords[k] - 1] = 0;
                }

                // delete disallowed indices
                indices.erase(remove(indices.begin(), indices.end(), 0), indices.end());

                if (indices.size() >= 1){solutions += 1;}
                ycoords.pop_back();

            }

            else {

                int j = ycoords.size();
                vector<int> indices;
                for (int q=1; q<=n; q++){
                indices.push_back(q);
                }

                for (int k=0; k<j; k++){

                    if (ycoords[k] + j - k <= n){indices[ycoords[k] + j - k - 1] = 0;}
                    if (1 <= ycoords[k] - j + k){indices[ycoords[k] - j + k - 1] = 0;}
                    indices[ycoords[k] - 1] = 0;
            
                }
                
                // delete disallowed indices
                indices.erase(remove(indices.begin(), indices.end(), 0), indices.end());

                if (indices.size()<=counts[j - 1]){
                    
                    if (j == 1){counts[0] += 1;}
                    else {ycoords.pop_back(); counts[j - 1]=0;}

                }

                else{ycoords.push_back(indices[counts[j - 1]]); counts[j - 1] += 1;}
            }
        }

        cout << "The " << n << " Queens Problem has " << solutions << " solutions." << endl;

    }
        
   
      
    return 0;
    }

   

    
    



    