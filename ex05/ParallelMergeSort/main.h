//
// Created by anykey on 14.11.17.
//

#ifndef PARALLELMERGESORT_MAIN_H
#define PARALLELMERGESORT_MAIN_H

#include <random>
#include <omp.h>
#include "chrono.h"
#include "UniformDistribution.h"

using namespace std;

void merge(int* array, int start, int end);
void mergeSort(int* array, int start, int end);

#endif //PARALLELMERGESORT_MAIN_H
