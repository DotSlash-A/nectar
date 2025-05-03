// File: matrix_utils.c
#include "matrix_utils.h"
#include <stdio.h>
#include <stdlib.h> // For malloc, free, exit
#include <string.h> // For memcpy, memset, snprintf
#include <math.h>   // For fabs, pow
#include <stdbool.h>

// --- Matrix Creation/Destruction ---

MatrixC* create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return NULL; // Invalid dimensions
    }

    // Allocate memory for the MatrixC struct itself
    MatrixC* matrix = (MatrixC*)malloc(sizeof(MatrixC));
    if (!matrix) {
        return NULL; // Failed to allocate struct
    }
    matrix->rows = rows;
    matrix->cols = cols;

    // Allocate memory for the array of row pointers (double**)
    matrix->data = (double**)malloc(rows * sizeof(double*));
    if (!matrix->data) {
        free(matrix); // Free the struct if row pointer allocation fails
        return NULL;
    }

    // Allocate memory for each row (double*) and initialize to 0.0
    for (int i = 0; i < rows; ++i) {
        matrix->data[i] = (double*)malloc(cols * sizeof(double));
        if (!matrix->data[i]) {
            // Allocation failed for a row: cleanup previously allocated rows and the row pointer array
            for (int k = 0; k < i; ++k) {
                free(matrix->data[k]);
            }
            free(matrix->data);
            free(matrix);
            return NULL;
        }
        // Initialize elements to 0.0
        memset(matrix->data[i], 0, cols * sizeof(double));
        // Alternative: loop and assign 0.0 if memset isn't preferred
        // for (int j = 0; j < cols; ++j) matrix->data[i][j] = 0.0;
    }

    return matrix;
}

void destroy_matrix(MatrixC* matrix) {
    if (!matrix) {
        return; // Nothing to free
    }
    if (matrix->data) {
        // Free each row
        for (int i = 0; i < matrix->rows; ++i) {
            free(matrix->data[i]); // Safe to free NULL, but rows should be allocated if data isn't NULL
        }
        // Free the array of row pointers
        free(matrix->data);
    }
    // Free the struct itself
    free(matrix);
}

// --- Validation and Helper Functions ---

int matrix_is_valid(const MatrixC* matrix, int* rows, int* cols) {
    if (!matrix || !matrix->data || matrix->rows <= 0 || matrix->cols <= 0) {
        if(rows) *rows = 0;
        if(cols) *cols = 0;
        return 0; // false (invalid)
    }
    // Basic check: Assume if struct/data ptr is valid, internal structure is too
    // (More robust checks could verify each matrix->data[i] is not NULL)
    if(rows) *rows = matrix->rows;
    if(cols) *cols = matrix->cols;
    return 1; // true (valid)
}

int matrix_is_square(const MatrixC* matrix, int* n) {
    int rows, cols;
    if (!matrix_is_valid(matrix, &rows, &cols) || rows != cols) {
         if(n) *n = 0;
         return 0; // false (not valid or not square)
    }
    if(n) *n = rows; // Dimension
    return 1; // true (is square)
}

int matrix_get_dimension_string(const MatrixC* matrix, char* buffer, size_t buffer_size) {
    if (!buffer || buffer_size == 0) return MATRIX_ERR_INVALID_ARG;
    int rows, cols;
    if (matrix_is_valid(matrix, &rows, &cols)) {
        snprintf(buffer, buffer_size, "%dx%d", rows, cols);
    } else {
        snprintf(buffer, buffer_size, "Invalid");
    }
    buffer[buffer_size - 1] = '\0'; // Ensure null termination
    return MATRIX_SUCCESS;
}

MatrixC* matrix_get_submatrix(const MatrixC* matrix, int skip_row, int skip_col) {
    int n;
    if (!matrix_is_square(matrix, &n) || n <= 1 || skip_row < 0 || skip_row >= n || skip_col < 0 || skip_col >= n) {
        return NULL; // Invalid input or 1x1 matrix
    }

    MatrixC* sub = create_matrix(n - 1, n - 1);
    if (!sub) return NULL; // Memory allocation failed

    int sub_r = 0;
    for (int r = 0; r < n; ++r) {
        if (r == skip_row) continue;
        int sub_c = 0;
        for (int c = 0; c < n; ++c) {
            if (c == skip_col) continue;
            sub->data[sub_r][sub_c] = matrix->data[r][c];
            sub_c++;
        }
        sub_r++;
    }
    return sub;
}

void matrix_print(const char* title, const MatrixC* matrix) {
    printf("%s:\n", title);
    int rows, cols;
     if (!matrix_is_valid(matrix, &rows, &cols)) {
        printf("  [Invalid or Empty Matrix]\n");
        return;
    }
    for (int i = 0; i < rows; ++i) {
        printf("  [");
        for (int j = 0; j < cols; ++j) {
            printf("%.4f%s", matrix->data[i][j], (j == cols - 1) ? "" : ", ");
        }
        printf("]\n");
    }
}


// --- Core Calculation Functions ---

int matrix_determinant_recursive(const MatrixC* matrix, double* result) {
    if (!result) return MATRIX_ERR_INVALID_ARG;
    int n;
    if (!matrix_is_square(matrix, &n)) return MATRIX_ERR_DIMENSION;

    if (n == 0) { *result = 1.0; return MATRIX_SUCCESS; } // Convention for 0x0
    if (n == 1) { *result = matrix->data[0][0]; return MATRIX_SUCCESS; }
    if (n == 2) {
        *result = matrix->data[0][0] * matrix->data[1][1] - matrix->data[0][1] * matrix->data[1][0];
        return MATRIX_SUCCESS;
    }

    double det = 0.0;
    for (int j = 0; j < n; ++j) { // Expand along first row
        MatrixC* sub = matrix_get_submatrix(matrix, 0, j);
        if (!sub) return MATRIX_ERR_MEMORY; // Failed to create submatrix

        double minor;
        int status = matrix_determinant_recursive(sub, &minor);
        destroy_matrix(sub); // Free the temporary submatrix
        if (status != MATRIX_SUCCESS) return status; // Propagate error

        double sign = (j % 2 == 0) ? 1.0 : -1.0;
        det += sign * matrix->data[0][j] * minor;
    }
    *result = det;
    return MATRIX_SUCCESS;
}

int matrix_transpose(const MatrixC* input, MatrixC** result_ptr) {
    if (!result_ptr) return MATRIX_ERR_INVALID_ARG;
    *result_ptr = NULL; // Ensure result is NULL initially
    int rows, cols;
    if (!matrix_is_valid(input, &rows, &cols)) return MATRIX_ERR_INVALID_ARG;

    MatrixC* transposed = create_matrix(cols, rows);
    if (!transposed) return MATRIX_ERR_MEMORY;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed->data[j][i] = input->data[i][j];
        }
    }
    *result_ptr = transposed;
    return MATRIX_SUCCESS;
}

int matrix_add(const MatrixC* a, const MatrixC* b, MatrixC** result_ptr) {
     if (!result_ptr) return MATRIX_ERR_INVALID_ARG;
     *result_ptr = NULL;
     int rA, cA, rB, cB;
     if (!matrix_is_valid(a, &rA, &cA) || !matrix_is_valid(b, &rB, &cB)) return MATRIX_ERR_INVALID_ARG;
     if (rA != rB || cA != cB) return MATRIX_ERR_DIMENSION;

     MatrixC* result = create_matrix(rA, cA);
     if (!result) return MATRIX_ERR_MEMORY;

     for(int i=0; i<rA; ++i) {
         for(int j=0; j<cA; ++j) {
             result->data[i][j] = a->data[i][j] + b->data[i][j];
         }
     }
     *result_ptr = result;
     return MATRIX_SUCCESS;
}

int matrix_multiply_scalar(const MatrixC* matrix, double scalar, MatrixC** result_ptr) {
     if (!result_ptr) return MATRIX_ERR_INVALID_ARG;
     *result_ptr = NULL;
     int rows, cols;
      if (!matrix_is_valid(matrix, &rows, &cols)) return MATRIX_ERR_INVALID_ARG;

      MatrixC* result = create_matrix(rows, cols);
      if (!result) return MATRIX_ERR_MEMORY;

      for(int i=0; i<rows; ++i) {
         for(int j=0; j<cols; ++j) {
             result->data[i][j] = matrix->data[i][j] * scalar;
         }
     }
     *result_ptr = result;
     return MATRIX_SUCCESS;
}

int matrix_multiply_matrices(const MatrixC* a, const MatrixC* b, MatrixC** result_ptr) {
     if (!result_ptr) return MATRIX_ERR_INVALID_ARG;
     *result_ptr = NULL;
     int rA, cA, rB, cB;
     if (!matrix_is_valid(a, &rA, &cA) || !matrix_is_valid(b, &rB, &cB)) return MATRIX_ERR_INVALID_ARG;
     if (cA != rB) return MATRIX_ERR_DIMENSION;

     MatrixC* result = create_matrix(rA, cB); // Dimensions of result are rowsA x colsB
     if (!result) return MATRIX_ERR_MEMORY;

      for(int i=0; i<rA; ++i) {
         for(int j=0; j<cB; ++j) {
             // result[i][j] is already 0.0 due to create_matrix
             for(int k=0; k<cA; ++k) { // cA == rB
                result->data[i][j] += a->data[i][k] * b->data[k][j];
             }
         }
     }
     *result_ptr = result;
     return MATRIX_SUCCESS;
}

int matrix_cofactor_matrix(const MatrixC* input, MatrixC** result_ptr) {
     if (!result_ptr) return MATRIX_ERR_INVALID_ARG;
     *result_ptr = NULL;
     int n;
     if (!matrix_is_square(input, &n)) return MATRIX_ERR_DIMENSION;

     MatrixC* cofactors = create_matrix(n, n);
     if (!cofactors) return MATRIX_ERR_MEMORY;

     int status = MATRIX_SUCCESS; // Track errors during sub-calculations
     for(int r=0; r<n; ++r) {
         for(int c=0; c<n; ++c) {
            MatrixC* sub = matrix_get_submatrix(input, r, c);
            if (!sub) { status = MATRIX_ERR_MEMORY; goto cleanup_cofactor; }

            double minor;
            status = matrix_determinant_recursive(sub, &minor);
            destroy_matrix(sub); // Free temp submatrix
            if (status != MATRIX_SUCCESS) goto cleanup_cofactor;

            double sign = ((r + c) % 2 == 0) ? 1.0 : -1.0;
            cofactors->data[r][c] = sign * minor;
         }
     }

cleanup_cofactor:
    if (status != MATRIX_SUCCESS) {
        destroy_matrix(cofactors);
        *result_ptr = NULL;
    } else {
        *result_ptr = cofactors;
    }
    return status;
}

int matrix_adjoint_matrix(const MatrixC* input, MatrixC** result_ptr) {
    if (!result_ptr) return MATRIX_ERR_INVALID_ARG;
    *result_ptr = NULL;
    MatrixC* cofactors = NULL;
    int status = matrix_cofactor_matrix(input, &cofactors);
    if (status != MATRIX_SUCCESS) return status;

    status = matrix_transpose(cofactors, result_ptr);
    destroy_matrix(cofactors); // Free intermediate cofactor matrix
    return status;
}

int matrix_inverse_matrix(const MatrixC* input, MatrixC** result_ptr) {
     if (!result_ptr) return MATRIX_ERR_INVALID_ARG;
     *result_ptr = NULL;

     double det;
     int status = matrix_determinant_recursive(input, &det);
     if (status != MATRIX_SUCCESS) return status;

     if (fabs(det) < MATRIX_C_EPSILON) {
         return MATRIX_ERR_MATH; // Singular matrix, no inverse
     }

     MatrixC* adj = NULL;
     status = matrix_adjoint_matrix(input, &adj);
     if (status != MATRIX_SUCCESS) return status;

     status = matrix_multiply_scalar(adj, 1.0 / det, result_ptr);
     destroy_matrix(adj); // Free intermediate adjoint matrix
     return status;
}


// --- "API"-like Functions ---

int matrix_calculate_determinant(const MatrixInputC* input, DeterminantResponseC* response) {
    if (!input || !input->matrix || !response) return MATRIX_ERR_INVALID_ARG;
    return matrix_determinant_recursive(input->matrix, &response->determinant);
}

int matrix_compare_matrices(const TwoMatrixInputC* input, MatrixEqualityResponseC* response) {
    if (!input || !input->matrix_a || !input->matrix_b || !response) return MATRIX_ERR_INVALID_ARG;

    response->are_equal = false; // Default to not equal
    matrix_get_dimension_string(input->matrix_a, response->dimensions_a, sizeof(response->dimensions_a));
    matrix_get_dimension_string(input->matrix_b, response->dimensions_b, sizeof(response->dimensions_b));

    int rA, cA, rB, cB;
    if (!matrix_is_valid(input->matrix_a, &rA, &cA) || !matrix_is_valid(input->matrix_b, &rB, &cB)) {
        snprintf(response->reason, sizeof(response->reason), "One or both inputs are not valid matrices.");
        return MATRIX_SUCCESS; // Return success code, but are_equal is false
    }
    if (rA != rB || cA != cB) {
        snprintf(response->reason, sizeof(response->reason), "Matrices have different dimensions.");
        return MATRIX_SUCCESS;
    }

    for (int i = 0; i < rA; ++i) {
        for (int j = 0; j < cA; ++j) {
            if (fabs(input->matrix_a->data[i][j] - input->matrix_b->data[i][j]) > MATRIX_C_EPSILON) {
                 snprintf(response->reason, sizeof(response->reason),
                          "Element mismatch at row %d, column %d (%.4f != %.4f).",
                          i, j, input->matrix_a->data[i][j], input->matrix_b->data[i][j]);
                 return MATRIX_SUCCESS;
            }
        }
    }

    response->are_equal = true;
    snprintf(response->reason, sizeof(response->reason), "Matrices are identical.");
    return MATRIX_SUCCESS;
}

int matrix_add_api(const TwoMatrixInputC* input, MatrixResponseC* response) {
    if (!input || !response) return MATRIX_ERR_INVALID_ARG;
    response->result_matrix = NULL;
    return matrix_add(input->matrix_a, input->matrix_b, &response->result_matrix);
}

int matrix_multiply_scalar_api(const MatrixInputC* matrixInput, double scalar, MatrixResponseC* response) {
    if (!matrixInput || !response) return MATRIX_ERR_INVALID_ARG;
     response->result_matrix = NULL;
    return matrix_multiply_scalar(matrixInput->matrix, scalar, &response->result_matrix);
}

int matrix_multiply_matrices_api(const TwoMatrixInputC* input, MatrixResponseC* response) {
     if (!input || !response) return MATRIX_ERR_INVALID_ARG;
     response->result_matrix = NULL;
    return matrix_multiply_matrices(input->matrix_a, input->matrix_b, &response->result_matrix);
}

int matrix_transpose_api(const MatrixInputC* input, MatrixResponseC* response) {
    if (!input || !response) return MATRIX_ERR_INVALID_ARG;
     response->result_matrix = NULL;
    return matrix_transpose(input->matrix, &response->result_matrix);
}

int matrix_calculate_minors_cofactors(const MatrixInputC* input, MinorsCofactorsResponseC* response) {
     if (!input || !input->matrix || !response) return MATRIX_ERR_INVALID_ARG;
     // Initialize response pointers to NULL
     response->matrix_of_minors = NULL;
     response->matrix_of_cofactors = NULL;
     response->determinant = 0.0; // Or NaN?
     response->dimensions[0] = '\0';


     int n;
     int status = matrix_is_square(input->matrix, &n);
     if (status == 0) return MATRIX_ERR_DIMENSION; // Use the return code convention

     matrix_get_dimension_string(input->matrix, response->dimensions, sizeof(response->dimensions));

     status = matrix_cofactor_matrix(input->matrix, &response->matrix_of_cofactors);
     if (status != MATRIX_SUCCESS) return status;

     // Calculate minors separately for the response
     response->matrix_of_minors = create_matrix(n, n);
     if (!response->matrix_of_minors) {
         destroy_matrix(response->matrix_of_cofactors); // Clean up already created cofactor matrix
         response->matrix_of_cofactors = NULL;
         return MATRIX_ERR_MEMORY;
     }

     status = MATRIX_SUCCESS;
      for(int r=0; r<n; ++r) {
         for(int c=0; c<n; ++c) {
            MatrixC* sub = matrix_get_submatrix(input->matrix, r, c);
             if (!sub) { status = MATRIX_ERR_MEMORY; goto cleanup_minors; }
            double minor_val;
            int det_status = matrix_determinant_recursive(sub, &minor_val);
            destroy_matrix(sub);
             if (det_status != MATRIX_SUCCESS) { status = det_status; goto cleanup_minors; }
             response->matrix_of_minors->data[r][c] = minor_val;
         }
     }

     // Calculate determinant
     status = matrix_determinant_recursive(input->matrix, &response->determinant);
     if (status != MATRIX_SUCCESS) goto cleanup_minors;


     return MATRIX_SUCCESS;

 cleanup_minors:
    // Clean up if minor calculation failed after cofactor was created
    destroy_matrix(response->matrix_of_minors);
    response->matrix_of_minors = NULL;
    destroy_matrix(response->matrix_of_cofactors);
    response->matrix_of_cofactors = NULL;
    return status;

}

int matrix_calculate_adjoint_inverse(const MatrixInputC* input, AdjInvResponseC* response) {
    if (!input || !input->matrix || !response) return MATRIX_ERR_INVALID_ARG;
    // Initialize response pointers
    response->adjoint_matrix = NULL;
    response->inverse_matrix = NULL;
    response->is_invertible = false;
    response->determinant = 0.0;
    response->dimensions[0] = '\0';


    matrix_get_dimension_string(input->matrix, response->dimensions, sizeof(response->dimensions));

    int status = matrix_adjoint_matrix(input->matrix, &response->adjoint_matrix);
    if (status != MATRIX_SUCCESS) return status;

    status = matrix_determinant_recursive(input->matrix, &response->determinant);
    if (status != MATRIX_SUCCESS) {
        destroy_matrix(response->adjoint_matrix); // Clean up adjoint if det fails
        response->adjoint_matrix = NULL;
        return status;
    }

    if (fabs(response->determinant) > MATRIX_C_EPSILON) {
        response->is_invertible = true;
        // Calculate inverse: (1/det) * adj
        status = matrix_multiply_scalar(response->adjoint_matrix, 1.0 / response->determinant, &response->inverse_matrix);
        if (status != MATRIX_SUCCESS) {
             destroy_matrix(response->adjoint_matrix); // Clean up adjoint if inverse fails
             response->adjoint_matrix = NULL;
             response->is_invertible = false; // Mark as not invertible if calc failed
             return status;
        }
    } else {
        response->is_invertible = false;
        response->inverse_matrix = NULL; // Explicitly NULL
    }

    return MATRIX_SUCCESS;
}