// File: matrix_types.h
#ifndef MATRIX_TYPES_H
#define MATRIX_TYPES_H

#include <vector>
#include <string>
#include <optional> // For optional inverse matrix

// Define Matrix type for convenience
using Matrix = std::vector<std::vector<double>>;

// --- Input Structures ---

// For determinant, minors, cofactors, adjoint, inverse
struct MatrixInput {
    Matrix matrix;
};

// For add, multiply, compare
struct TwoMatrixInput {
    Matrix matrix_a;
    Matrix matrix_b;
};

// --- Output/Response Structures ---

struct DeterminantResponse {
    Matrix input_matrix;
    double determinant;
};

struct MatrixEqualityResponse {
    bool are_equal;
    std::string reason;
    std::string dimensions_a; // e.g., "3x4" or "Invalid"
    std::string dimensions_b;
};

struct MatrixResponse { // For simple operations returning one matrix
    Matrix result_matrix;
};

struct MinorsCofactorsResponse {
    Matrix input_matrix;
    std::string dimensions;
    Matrix matrix_of_minors;
    Matrix matrix_of_cofactors;
    double determinant; // Often useful to return alongside
};

struct AdjInvResponse {
    Matrix input_matrix;
    std::string dimensions;
    double determinant;
    bool is_invertible;
    Matrix adjoint_matrix;
    std::optional<Matrix> inverse_matrix; // Use optional for possibly non-existent inverse
};


#endif // MATRIX_TYPES_H