#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

int n, N;

void check(unsigned int array, unsigned int tree);


int main(int argc, char** argv) {

    // Checking arguments
    if (argc != 2) return EXIT_FAILURE;
    N = atoi(argv[1]);
    if (N == 0) return EXIT_FAILURE;
    /**********************************/

    unsigned int array[N] = {0}, tree[N] = {0};

    // Generating array of numbers between 0 to N
    for (int i = 1; i <= N; i++) {
        array[i] = i;
        tree[i] = i;
    }
    std::random_shuffle(array, array + N);
    std::cout << "Shuffled array: ";
    for (int i = 0; i < N; i++) {
        std::cout << array[i] << " ";
    }

    std::cout << "\r\n";
    std::cout << "Sorted array:   ";

    for (int i = 0; i < N; i++) {
        std::cout << tree[i] << " ";
    }

    check(*array, *tree);


}


void check(unsigned int array, unsigned int tree) {

    std::cout << "\r\nChecking result: ";
    if(array == tree) {
        std::cout << "Ok!" << std::endl;
    } else std::cout << "Error!" << std::endl;
}
