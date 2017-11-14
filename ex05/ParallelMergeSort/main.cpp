#include <iostream>

#include "main.h"

int main(int argc, char** argv) {

    // Checking arguments
    if (argc != 2) return EXIT_FAILURE;
    int num = atoi(argv[1]);
    if (num == 0) return EXIT_FAILURE;

    int A[num], i;
    UniformDistribution dist;


    /* put in random numbers */
    for(i = 0; i < num; i++) {
        A[i] = dist.sample();
    }

    {
        cout << "Array size: " << num << endl;
        ChronoTimer t("Multiplication");
        mergeSort(A, 0, num-1);
    }


    return 0;
}