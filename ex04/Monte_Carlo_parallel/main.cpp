#include <iostream>
#include <random>
#include <iomanip>

#include "UniformDistribution.h"
#include "main.h"


int main(int argc, char** argv) {

    // Checking arguments
    if (argc != 2) return EXIT_FAILURE;
    n = atoi(argv[1]);
    if (n == 0) return EXIT_FAILURE;

    cout <<"Number of samples to use in the estimation: " << n << endl;
    CalculatingPi();
}

int InsideCircle(const int numSamples)
{
    UniformDistribution distribution;

    int counter = 0;
    for (int s = 0; s != numSamples; s++) {
        auto x = distribution.sample();
        auto y = distribution.sample();

        if (x * x + y * y < 1) {
            counter++;
        }
    }
    return counter;
}

double CalculatingPi() {

    int thread = 4;
    int part = n / thread;
    int counter = 0;

#pragma omp parallel for shared(thread, part) reduction(+:counter)

    for (int i = 0; i < thread; i++) {
        counter += InsideCircle(part);
    }

    const double p = 4.0 * counter / n;
    cout << "Calculated Pi: " << p << endl;
}

