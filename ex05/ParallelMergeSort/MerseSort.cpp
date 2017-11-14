#include "main.h"

void merge(int* array, int start, int end) {
    int middle = (start + end) / 2;
    int temp_index = 0;

    /* create a temporary array */
    int *temp = new int[sizeof(int) * (end - start + 1)];

    /* merge in sorted data from the 2 halves */
    int left = start;
    int right = middle + 1;

    /* while both halves have data */
    while((left <= middle) && (right <= end)) {
        /* if the left half value is less than right */
        if (array[left] < array[right]) {
            /* take from left */
            temp[temp_index] = array[left];
            temp_index++;
            left++;
        }
        else {
            /* take from right */
            temp[temp_index] = array[right];
            temp_index++;
            right++;
        }
    }

    /* add the remaining elements from the left half */
    while(left <= middle) {
        temp[temp_index] = array[left];
        temp_index++;
        left++;
    }

    /* add the remaining elements from the right half */
    while(right <= end) {
        temp[temp_index] = array[right];
        temp_index++;
        right++;
    }

    /* move from temp array to the original array */
    int i;
    for(i = start; i <= end; i++) {
        array[i] = temp[i - start];
    }

    /* delete temporary array */
    delete temp;
}

void mergeSort(int* array, int start, int end) {
    if(start < end) {

        int middle = (start + end) / 2;

        /* sort both halves in parallel sections */
#pragma omp parallel sections
        {
#pragma omp section
            {
                mergeSort(array, start, middle);
            }
#pragma omp section
            {
                mergeSort(array, middle + 1, end);
            }
        }

        /* merge the two halves */
        merge(array, start, end);
    }
}