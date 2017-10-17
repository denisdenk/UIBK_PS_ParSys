#include <vector>
#include <cstdlib>

using Matrix = std::vector<std::vector<double>>;

// initializes a square identity matrix of size n x n
Matrix id(unsigned n) {
    Matrix res;
    res.resize(n);
    for(unsigned i=0; i<n; i++) {
        res[i].resize(n);
        for(unsigned j=0; j<n; j++) {
            res[i][j] = (i == j) ? 1 : 0;
        }
    }
    return res;
}

// computes the product of two matrices
Matrix operator*(const Matrix& a, const Matrix& b) {
    unsigned n = a.size();
    Matrix c = id(n);
#pragma omp parallel for
    for(unsigned i=0; i<n; ++i) {
        for(unsigned j=0; j<n; ++j) {
            c[i][j] = 0;
            for(unsigned k=0; k<n; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}


int main(int argc, char** argv) {

    if(argc!=2) return EXIT_FAILURE;
    unsigned n = atoi(argv[1]);
    if(n==0) return EXIT_FAILURE;

    // create two matrices
    auto a = id(n);
    a[0][0] = 42;
    a[0][1] = 43;
    a[0][2] = 43;
    a[0][3] = 43;

    a[1][0] = 41;
    a[1][1] = 44;
    a[1][2] = 44;
    a[1][3] = 44;

    a[2][0] = 41;
    a[2][1] = 44;
    a[2][2] = 44;
    a[2][3] = 44;

    a[3][0] = 41;
    a[3][1] = 44;
    a[3][2] = 44;
    a[3][3] = 44;


    auto b = id(n);
    b[0][0] = 42;
    b[0][1] = 43;
    b[0][2] = 43;
    b[0][3] = 43;

    b[1][0] = 41;
    b[1][1] = 44;
    b[1][2] = 44;
    b[1][3] = 44;

    b[2][0] = 41;
    b[2][1] = 44;
    b[2][2] = 44;
    b[2][3] = 44;

    b[3][0] = 41;
    b[3][1] = 44;
    b[3][2] = 44;
    b[3][3] = 44;

    // compute the product
    auto c = a * b;

    // check that the result is correct
    return (c == a) ? EXIT_SUCCESS : EXIT_FAILURE;
}