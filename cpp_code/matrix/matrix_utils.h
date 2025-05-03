// File: matrix_utils.h
#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include "matrix_types.h" // Include the structures defined above
#include <vector>
#include <string>
#include <stdexcept> // For standard exceptions

// Define a small tolerance for floating-point comparisons
const double MATRIX_EPSILON = 1e-9;

namespace MatrixUtils {

    // --- Validation and Helper Functions ---
    bool isValidMatrix(const Matrix& matrix, int& rows, int& cols);
    bool isSquareMatrix(const Matrix& matrix, int& n);
    std::string getDimensionString(const Matrix& matrix);
    Matrix getSubmatrix(const Matrix& matrix, int skip_row, int skip_col);

    // --- Core Calculation Functions ---
    double calculateDeterminantRecursive(const Matrix& matrix); // Internal recursive helper
    Matrix transposeMatrix(const Matrix& matrix);
    Matrix addMatrices(const Matrix& matrix_a, const Matrix& matrix_b);
    Matrix multiplyMatrixByScalar(const Matrix& matrix, double scalar);
    Matrix multiplyMatrices(const Matrix& matrix_a, const Matrix& matrix_b);
    Matrix calculateCofactorMatrix(const Matrix& matrix); // Helper needed for adj/inv
    Matrix calculateAdjointMatrix(const Matrix& matrix); // Helper needed for inv

    // --- "API"-like Functions (matching Python endpoints where possible) ---

    DeterminantResponse calculateDeterminant(const MatrixInput& input);
    MatrixEqualityResponse compareMatrices(const TwoMatrixInput& input);
    MatrixResponse addMatricesAPI(const TwoMatrixInput& input);
    MatrixResponse multiplyMatrixByScalarAPI(const MatrixInput& matrixInput, double scalar);
    MatrixResponse multiplyMatricesAPI(const TwoMatrixInput& input);
    MatrixResponse transposeMatrixAPI(const MatrixInput& input);
    MinorsCofactorsResponse calculateMinorsAndCofactors(const MatrixInput& input);
    AdjInvResponse calculateAdjointAndInverse(const MatrixInput& input);

    // NOTE: construct_matrix_from_formula is omitted due to complexity without external libraries.

} // namespace MatrixUtils

#endif // MATRIX_UTILS_H