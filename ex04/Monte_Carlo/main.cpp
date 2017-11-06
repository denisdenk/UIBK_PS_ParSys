#include <iostream>

using namespace std;

int innerCount = 0; // Counter for points inside a circle
double x, y;        // Coordinates
double p;           // Pi

int main(int argc, char** argv) {

    // Checking arguments
    if (argc != 2) return EXIT_FAILURE;
    unsigned n = atoi(argv[1]);
    if (n == 0) return EXIT_FAILURE;

    cout <<"\nNumber of samples to use in the estimation: " << n << endl;

    for(int i = 0; i < n; i++) {

        // Generating random dots "x" and "y"
        x = (double)rand()/RAND_MAX;
        y = (double)rand()/RAND_MAX;

        // If the points are in the circle, we increase the counter
        if(x*x + y*y <= 1) {
            innerCount++;
        }
    }

    // Calculate the number Pi
    p = (double) 4 * innerCount / n;

    cout << "Calculated Pi = " << p << endl;
}