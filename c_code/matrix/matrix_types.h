// File: matrix_types.h
#ifndef MATRIX_TYPES_H
#define MATRIX_TYPES_H

#include <stddef.h> // For size_t
#include <stdbool.h> // For bool type

// --- Error Codes ---
#define MATRIX_SUCCESS 0
#define MATRIX_ERR_INVALID_ARG 1 // NULL pointers, invalid dimensions
#define MATRIX_ERR_MEMORY 2      // malloc failed
#define MATRIX_ERR_DIMENSION 3   // Mismatched dimensions for operation
#define MATRIX_ERR_MATH 4        // e.g., singular matrix for inverse

// --- Matrix Structure ---
typedef struct {
    int rows;
    int cols;
    double** data; // Pointer to array of row pointers
} MatrixC; // Added 'C' suffix to avoid potential clashes if mixing with C++

// --- Function to Create/Destroy Matrix ---
// Creates a matrix, initializes elements to 0.0. Returns NULL on failure.
MatrixC* create_matrix(int rows, int cols);
// Frees all memory associated with the matrix. Safe to call with NULL.
void destroy_matrix(MatrixC* matrix);

// --- Input Structures (using pointers to avoid copying) ---
typedef struct {
    const MatrixC* matrix; // Use const for input-only matrices
} MatrixInputC;

typedef struct {
    const MatrixC* matrix_a;
    const MatrixC* matrix_b;
} TwoMatrixInputC;

// --- Output/Response Structures ---
// Note: For matrices returned in response structs, the CALLER is generally
// responsible for calling destroy_matrix() on them unless documented otherwise.

typedef struct {
    // const MatrixC* input_matrix; // Usually not needed to copy input back
    double determinant;
} DeterminantResponseC;

typedef struct {
    bool are_equal;
    char reason[256]; // Fixed-size buffer for reason string
    char dimensions_a[32];
    char dimensions_b[32];
} MatrixEqualityResponseC;

// For operations returning a single matrix result
typedef struct {
    MatrixC* result_matrix; // Caller must free this matrix!
} MatrixResponseC;

typedef struct {
    // const MatrixC* input_matrix;
    char dimensions[32];
    MatrixC* matrix_of_minors;    // Caller must free!
    MatrixC* matrix_of_cofactors; // Caller must free!
    double determinant;
} MinorsCofactorsResponseC;

typedef struct {
    // const MatrixC* input_matrix;
    char dimensions[32];
    double determinant;
    bool is_invertible;
    MatrixC* adjoint_matrix; // Caller must free!
    MatrixC* inverse_matrix; // Caller must free (will be NULL if not invertible)!
} AdjInvResponseC;


#endif // MATRIX_TYPES_H