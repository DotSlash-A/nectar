#include <stdio.h>
#include <cblas.h>

int main() {
    int m = 2, n = 3, k = 4; // Dimensions: A is m x k, B is k x n, C is m x n

    double A[8] = { // 2x4 matrix
        1, 2, 3, 4,
        5, 6, 7, 8
    };
    double B[12] = { // 4x3 matrix
        1, 2, 3,
        4, 5, 6,
        7, 8, 9,
        10, 11, 12
    };
    double C[6] = {0}; // 2x3 matrix for result

    // C = 1.0*A*B + 0.0*C
    cblas_dgemm(
        CblasRowMajor,  // Row major order
        CblasNoTrans,   // Don't transpose A
        CblasNoTrans,   // Don't transpose B
        m, n, k,        // Sizes
        1.0,            // alpha
        A, k,           // A and its leading dimension
        B, n,           // B and its leading dimension
        0.0,            // beta
        C, n            // C and its leading dimension
    );

    printf("Result matrix C:\n");
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++)
            printf("%6.1f ", C[i*n + j]);
        printf("\n");
    }
    return 0;
}