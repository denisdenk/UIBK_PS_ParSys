#include <iostream>
#include <random>
#include <iomanip>

#include "UniformDistribution.h"
#include "main.h"
#include "chrono.h"


int main(int argc, char** argv) {

    // Checking arguments
    if (argc != 2) return EXIT_FAILURE;
    n = atoi(argv[1]);
    if (n == 0) return EXIT_FAILURE;

    cout <<"Number of samples to use in the estimation: " << n << endl;
    {
        ChronoTimer t("Multiplication");
        CalculatingPi();
    }
}

/*
 * The function of counting the number of points within the circle
 */
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

    /*
     *  We use "shared" for number of threads and parts
     *  because we need access to this data from all threads.
     *  In fact, we do not need specify this, since all variables declared before the directive are "shared".
     *
     *  Use the expression reduction.
     *  In this case, each thread will receive its own copy of the "counter" variable,
     *  perform all the necessary actions with it,
     *  and then perform the specified operation to combine the resulting values with the original one.
     */

#pragma omp parallel for shared(thread, part) reduction(+:counter)

        for (int i = 0; i < thread; i++) {
            counter += InsideCircle(part);
        }


        const double p = 4.0 * counter / n;

        cout << "Calculated Pi: " << p << endl;

}
