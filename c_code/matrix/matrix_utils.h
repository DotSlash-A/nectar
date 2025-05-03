// File: matrix_utils.h
#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include "matrix_types.h" // Include the structures and error codes

// Define a small tolerance for floating-point comparisons
#define MATRIX_C_EPSILON 1e-9

// --- Validation and Helper Functions ---
// Checks if matrix pointer and data are valid, gets dimensions.
int matrix_is_valid(const MatrixC* matrix, int* rows, int* cols);
// Checks if matrix is valid and square, gets dimension n.
int matrix_is_square(const MatrixC* matrix, int* n);
// Helper to get dimensions as string (caller provides buffer)
int matrix_get_dimension_string(const MatrixC* matrix, char* buffer, size_t buffer_size);
// Creates a submatrix (caller must free the result)
MatrixC* matrix_get_submatrix(const MatrixC* matrix, int skip_row, int skip_col);
// Prints matrix to stdout (for debugging)
void matrix_print(const char* title, const MatrixC* matrix);


// --- Core Calculation Functions (Internal use or direct call if needed) ---
// These return error codes and output results via pointers.
int matrix_determinant_recursive(const MatrixC* matrix, double* result);
int matrix_transpose(const MatrixC* input, MatrixC** result); // Allocates result
int matrix_add(const MatrixC* a, const MatrixC* b, MatrixC** result); // Allocates result
int matrix_multiply_scalar(const MatrixC* matrix, double scalar, MatrixC** result); // Allocates result
int matrix_multiply_matrices(const MatrixC* a, const MatrixC* b, MatrixC** result); // Allocates result
int matrix_cofactor_matrix(const MatrixC* input, MatrixC** result); // Allocates result
int matrix_adjoint_matrix(const MatrixC* input, MatrixC** result); // Allocates result
int matrix_inverse_matrix(const MatrixC* input, MatrixC** result); // Allocates result (NULL if singular)

// --- "API"-like Functions (matching Python endpoints where possible) ---
// These functions typically allocate memory for the result structure or contained matrices,
// which the caller might need to manage (e.g., free matrices inside response structs).
// Return MATRIX_SUCCESS or an error code.

int matrix_calculate_determinant(const MatrixInputC* input, DeterminantResponseC* response);
int matrix_compare_matrices(const TwoMatrixInputC* input, MatrixEqualityResponseC* response);
int matrix_add_api(const TwoMatrixInputC* input, MatrixResponseC* response); // Response contains matrix to free
int matrix_multiply_scalar_api(const MatrixInputC* matrixInput, double scalar, MatrixResponseC* response); // Response contains matrix to free
int matrix_multiply_matrices_api(const TwoMatrixInputC* input, MatrixResponseC* response); // Response contains matrix to free
int matrix_transpose_api(const MatrixInputC* input, MatrixResponseC* response); // Response contains matrix to free
int matrix_calculate_minors_cofactors(const MatrixInputC* input, MinorsCofactorsResponseC* response); // Response contains matrices to free
int matrix_calculate_adjoint_inverse(const MatrixInputC* input, AdjInvResponseC* response); // Response contains matrices to free

// NOTE: construct_matrix_from_formula is omitted.

#endif // MATRIX_UTILS_H