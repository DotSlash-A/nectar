// File: matrix_utils.cc
#include "matrix_utils.h"
#include <vector>
#include <stdexcept>
#include <cmath>    // For std::fabs, std::pow
#include <limits>   // For numeric_limits
#include <sstream>  // For dimension string formatting
#include <iomanip>  // For setting precision in output (optional)

namespace MatrixUtils {

    // --- Validation and Helper Functions ---

    bool isValidMatrix(const Matrix& matrix, int& rows, int& cols) {
        if (matrix.empty()) {
            rows = 0;
            cols = 0;
            return false; // Must have at least one row
        }
        rows = matrix.size();
        if (matrix[0].empty()) {
            cols = 0;
            return false; // Rows cannot be empty
        }
        cols = matrix[0].size();

        // Check if all rows have the same number of columns
        for (size_t i = 1; i < rows; ++i) {
            if (matrix[i].size() != cols) {
                return false; // Inconsistent column count
            }
        }
        return true;
    }

    bool isSquareMatrix(const Matrix& matrix, int& n) {
        int rows, cols;
        if (!isValidMatrix(matrix, rows, cols)) {
            n = 0;
            return false;
        }
        if (rows != cols) {
            n = 0;
            return false;
        }
        n = rows; // Dimension of the square matrix
        return true;
    }

     std::string getDimensionString(const Matrix& matrix) {
         int rows, cols;
         if (isValidMatrix(matrix, rows, cols)) {
             return std::to_string(rows) + "x" + std::to_string(cols);
         } else {
             return "Invalid";
         }
     }

    Matrix getSubmatrix(const Matrix& matrix, int skip_row, int skip_col) {
        int n = matrix.size();
        if (n <= 1) {
            return Matrix(); // Return empty matrix for base case or error
        }
        Matrix submatrix(n - 1, std::vector<double>(n - 1));
        int sub_r = 0;
        for (int r = 0; r < n; ++r) {
            if (r == skip_row) continue;
            int sub_c = 0;
            for (int c = 0; c < n; ++c) {
                if (c == skip_col) continue;
                submatrix[sub_r][sub_c] = matrix[r][c];
                sub_c++;
            }
            sub_r++;
        }
        return submatrix;
    }

    // --- Core Calculation Functions ---

    double calculateDeterminantRecursive(const Matrix& matrix) {
        int n;
        if (!isSquareMatrix(matrix, n)) {
            throw std::invalid_argument("Determinant requires a square matrix.");
        }

        if (n == 0) {
            return 1.0; // Convention: det(0x0 matrix) = 1 (minor of 1x1)
        }
        if (n == 1) {
            return matrix[0][0];
        }
        if (n == 2) {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        }

        double det = 0.0;
        // Laplace expansion along the first row (row 0)
        for (int j = 0; j < n; ++j) { // Column index j
            Matrix sub = getSubmatrix(matrix, 0, j);
            double minor = calculateDeterminantRecursive(sub);
            // Cofactor sign = (-1)^(0+j)
            double sign = (j % 2 == 0) ? 1.0 : -1.0;
            det += sign * matrix[0][j] * minor;
        }
        return det;
    }

    Matrix transposeMatrix(const Matrix& matrix) {
        int rows, cols;
        if (!isValidMatrix(matrix, rows, cols)) {
            // Return empty or throw, depending on desired behavior
            return Matrix();
        }
        if (rows == 0 || cols == 0) return Matrix();

        Matrix transposed(cols, std::vector<double>(rows));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                transposed[j][i] = matrix[i][j];
            }
        }
        return transposed;
    }

    Matrix addMatrices(const Matrix& matrix_a, const Matrix& matrix_b) {
        int rows_a, cols_a, rows_b, cols_b;
        if (!isValidMatrix(matrix_a, rows_a, cols_a) || !isValidMatrix(matrix_b, rows_b, cols_b)) {
            throw std::invalid_argument("Invalid input matrices for addition.");
        }
        if (rows_a != rows_b || cols_a != cols_b) {
            throw std::invalid_argument("Matrices must have the same dimensions for addition.");
        }

        Matrix result(rows_a, std::vector<double>(cols_a));
        for (int i = 0; i < rows_a; ++i) {
            for (int j = 0; j < cols_a; ++j) {
                result[i][j] = matrix_a[i][j] + matrix_b[i][j];
            }
        }
        return result;
    }

    Matrix multiplyMatrixByScalar(const Matrix& matrix, double scalar) {
        int rows, cols;
        if (!isValidMatrix(matrix, rows, cols)) {
            // Return empty or throw
             return Matrix();
        }
        Matrix result(rows, std::vector<double>(cols));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result[i][j] = matrix[i][j] * scalar;
            }
        }
        return result;
    }

    Matrix multiplyMatrices(const Matrix& matrix_a, const Matrix& matrix_b) {
        int rows_a, cols_a, rows_b, cols_b;
        if (!isValidMatrix(matrix_a, rows_a, cols_a) || !isValidMatrix(matrix_b, rows_b, cols_b)) {
            throw std::invalid_argument("Invalid input matrices for multiplication.");
        }
        if (cols_a != rows_b) {
            throw std::invalid_argument("Incompatible dimensions for matrix multiplication (A.cols != B.rows).");
        }

        Matrix result(rows_a, std::vector<double>(cols_b, 0.0)); // Initialize with zeros
        for (int i = 0; i < rows_a; ++i) {
            for (int j = 0; j < cols_b; ++j) {
                for (int k = 0; k < cols_a; ++k) { // cols_a is same as rows_b
                    result[i][j] += matrix_a[i][k] * matrix_b[k][j];
                }
            }
        }
        return result;
    }

    Matrix calculateCofactorMatrix(const Matrix& matrix) {
        int n;
        if (!isSquareMatrix(matrix, n)) {
            throw std::invalid_argument("Cofactor matrix requires a square matrix.");
        }
        Matrix cofactors(n, std::vector<double>(n));
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                Matrix sub = getSubmatrix(matrix, r, c);
                double minor = calculateDeterminantRecursive(sub);
                double sign = ((r + c) % 2 == 0) ? 1.0 : -1.0;
                cofactors[r][c] = sign * minor;
            }
        }
        return cofactors;
    }

    Matrix calculateAdjointMatrix(const Matrix& matrix) {
        Matrix cofactor_matrix = calculateCofactorMatrix(matrix); // Handles square check
        return transposeMatrix(cofactor_matrix);
    }

    // --- "API"-like Functions ---

    DeterminantResponse calculateDeterminant(const MatrixInput& input) {
        // calculateDeterminantRecursive already validates squareness
        double det = calculateDeterminantRecursive(input.matrix);
        return {input.matrix, det};
    }

    MatrixEqualityResponse compareMatrices(const TwoMatrixInput& input) {
        int rows_a, cols_a, rows_b, cols_b;
        bool valid_a = isValidMatrix(input.matrix_a, rows_a, cols_a);
        bool valid_b = isValidMatrix(input.matrix_b, rows_b, cols_b);
        std::string dim_a_str = valid_a ? (std::to_string(rows_a) + "x" + std::to_string(cols_a)) : "Invalid";
        std::string dim_b_str = valid_b ? (std::to_string(rows_b) + "x" + std::to_string(cols_b)) : "Invalid";

        if (!valid_a || !valid_b) {
            return {false, "One or both inputs are not valid matrices.", dim_a_str, dim_b_str};
        }
        if (rows_a != rows_b || cols_a != cols_b) {
            return {false, "Matrices have different dimensions.", dim_a_str, dim_b_str};
        }

        // Element-wise comparison with tolerance
        for (int i = 0; i < rows_a; ++i) {
            for (int j = 0; j < cols_a; ++j) {
                if (std::fabs(input.matrix_a[i][j] - input.matrix_b[i][j]) > MATRIX_EPSILON) {
                     std::ostringstream reason_ss;
                     reason_ss << "Element mismatch at row " << i << ", column " << j
                               << " (" << input.matrix_a[i][j] << " != " << input.matrix_b[i][j] << ").";
                    return {false, reason_ss.str(), dim_a_str, dim_b_str};
                }
            }
        }
        return {true, "Matrices are identical.", dim_a_str, dim_b_str};
    }

    MatrixResponse addMatricesAPI(const TwoMatrixInput& input) {
        // addMatrices performs validation
        Matrix result = addMatrices(input.matrix_a, input.matrix_b);
        return {result};
    }

    MatrixResponse multiplyMatrixByScalarAPI(const MatrixInput& matrixInput, double scalar) {
         // multiplyMatrixByScalar performs basic validation
        Matrix result = multiplyMatrixByScalar(matrixInput.matrix, scalar);
        return {result};
    }

    MatrixResponse multiplyMatricesAPI(const TwoMatrixInput& input) {
        // multiplyMatrices performs validation
        Matrix result = multiplyMatrices(input.matrix_a, input.matrix_b);
        return {result};
    }

    MatrixResponse transposeMatrixAPI(const MatrixInput& input) {
        // transposeMatrix performs validation
        Matrix result = transposeMatrix(input.matrix);
        return {result};
    }

     MinorsCofactorsResponse calculateMinorsAndCofactors(const MatrixInput& input) {
         int n;
         if (!isSquareMatrix(input.matrix, n)) {
             throw std::invalid_argument("Minors/Cofactors require a square matrix.");
         }
         // Calculate cofactors (which internally calculates minors via determinants)
         Matrix cofactors = calculateCofactorMatrix(input.matrix);
         Matrix minors(n, std::vector<double>(n));

         // Re-calculate minors explicitly for the response structure
         // or modify calculateCofactorMatrix to return both if performance is critical
         for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                 Matrix sub = getSubmatrix(input.matrix, r, c);
                 minors[r][c] = calculateDeterminantRecursive(sub);
            }
         }

         double det = calculateDeterminantRecursive(input.matrix); // Recalculate determinant

         return {
             input.matrix,
             getDimensionString(input.matrix),
             minors,
             cofactors,
             det
         };
     }

      AdjInvResponse calculateAdjointAndInverse(const MatrixInput& input) {
            int n;
            if (!isSquareMatrix(input.matrix, n)) {
                throw std::invalid_argument("Adjoint/Inverse require a square matrix.");
            }

            Matrix adj = calculateAdjointMatrix(input.matrix); // Handles internal checks
            double det = calculateDeterminantRecursive(input.matrix);

            bool invertible = std::fabs(det) > MATRIX_EPSILON;
            std::optional<Matrix> inv_opt = std::nullopt; // std::nullopt represents absence of value

            if (invertible) {
                inv_opt = multiplyMatrixByScalar(adj, 1.0 / det);
            }

            return {
                input.matrix,
                getDimensionString(input.matrix),
                det,
                invertible,
                adj,
                inv_opt // Assign the optional containing the matrix or nullopt
            };
      }


} // namespace MatrixUtils



// // ----main function for matices
// // File: main.cc
// #include "matrix_utils.h" // Includes matrix_types.h implicitly
// #include <iostream>
// #include <vector>
// #include <iomanip> // For std::setprecision

// // Helper function to print a matrix
// void printMatrix(const std::string& title, const Matrix& mat) {
//     std::cout << title << ":\n";
//     if (mat.empty() || mat[0].empty()) {
//         std::cout << "  []\n";
//         return;
//     }
//     std::cout << std::fixed << std::setprecision(4); // Set precision for output
//     for (const auto& row : mat) {
//         std::cout << "  [";
//         for (size_t j = 0; j < row.size(); ++j) {
//             std::cout << row[j] << (j == row.size() - 1 ? "" : ", ");
//         }
//         std::cout << "]\n";
//     }
//      std::cout << std::defaultfloat; // Reset precision formatting
// }

// int main() {
//     std::cout << "--- Matrix Calculations (C++) ---" << std::endl;

//     // Example M1: Determinant
//     try {
//         Matrix mat1 = {{1.0, 2.0}, {3.0, 4.0}};
//         MatrixInput input1 = {mat1};
//         DeterminantResponse resp1 = MatrixUtils::calculateDeterminant(input1);
//         printMatrix("Matrix A", resp1.input_matrix);
//         std::cout << "Determinant of A: " << resp1.determinant << std::endl; // Expected: -2.0

//         Matrix mat2 = {{6.0, 1.0, 1.0}, {4.0, -2.0, 5.0}, {2.0, 8.0, 7.0}};
//         MatrixInput input2 = {mat2};
//         DeterminantResponse resp2 = MatrixUtils::calculateDeterminant(input2);
//          printMatrix("Matrix B", resp2.input_matrix);
//         std::cout << "Determinant of B: " << resp2.determinant << std::endl; // Expected: -306.0
//     } catch (const std::exception& e) {
//         std::cerr << "Error M1: " << e.what() << std::endl;
//     }
//     std::cout << std::endl;

//     // Example M2: Compare Matrices
//      try {
//         Matrix matA = {{1.0, 0.0}, {0.0, 1.0}};
//         Matrix matB = {{1.0, 0.0}, {0.0, 1.0}};
//         Matrix matC = {{1.0, 0.0}, {0.0, 2.0}};
//         Matrix matD = {{1.0, 0.0}}; // Different dims

//         TwoMatrixInput inputAB = {matA, matB};
//         TwoMatrixInput inputAC = {matA, matC};
//         TwoMatrixInput inputAD = {matA, matD};

//         MatrixEqualityResponse respAB = MatrixUtils::compareMatrices(inputAB);
//         MatrixEqualityResponse respAC = MatrixUtils::compareMatrices(inputAC);
//         MatrixEqualityResponse respAD = MatrixUtils::compareMatrices(inputAD);

//         std::cout << "Compare A vs B: " << (respAB.are_equal ? "true" : "false")
//                   << " (" << respAB.reason << ")" << std::endl;
//         std::cout << "Compare A vs C: " << (respAC.are_equal ? "true" : "false")
//                   << " (" << respAC.reason << ")" << std::endl;
//         std::cout << "Compare A vs D: " << (respAD.are_equal ? "true" : "false")
//                   << " (" << respAD.reason << ")" << std::endl;

//      } catch (const std::exception& e) {
//          std::cerr << "Error M2: " << e.what() << std::endl;
//      }
//      std::cout << std::endl;


//     // Example M4: Addition
//     try {
//         Matrix addA = {{1.0, 2.0}, {3.0, 4.0}};
//         Matrix addB = {{5.0, 6.0}, {7.0, 8.0}};
//         TwoMatrixInput addInput = {addA, addB};
//         MatrixResponse addResp = MatrixUtils::addMatricesAPI(addInput);
//         printMatrix("Add A", addA);
//         printMatrix("Add B", addB);
//         printMatrix("A + B", addResp.result_matrix); // Expected: {{6.0, 8.0}, {10.0, 12.0}}
//     } catch (const std::exception& e) {
//          std::cerr << "Error M4: " << e.what() << std::endl;
//     }
//     std::cout << std::endl;

//     // Example M6: Matrix Multiply
//     try {
//         Matrix mulA = {{1.0, 2.0}}; // 1x2
//         Matrix mulB = {{3.0}, {4.0}}; // 2x1
//         TwoMatrixInput mulInput = {mulA, mulB};
//         MatrixResponse mulResp = MatrixUtils::multiplyMatricesAPI(mulInput);
//         printMatrix("Mul A (1x2)", mulA);
//         printMatrix("Mul B (2x1)", mulB);
//         printMatrix("A * B (1x1)", mulResp.result_matrix); // Expected: {{11.0}}
//     } catch (const std::exception& e) {
//         std::cerr << "Error M6: " << e.what() << std::endl;
//     }
//      std::cout << std::endl;


//     // Example M8: Minors/Cofactors
//     try {
//        Matrix minorMat = {{1.0, 2.0, 3.0}, {0.0, 4.0, 5.0}, {1.0, 0.0, 6.0}};
//        MatrixInput minorInput = {minorMat};
//        MinorsCofactorsResponse minorResp = MatrixUtils::calculateMinorsAndCofactors(minorInput);
//        printMatrix("Input for Min/Cof", minorResp.input_matrix);
//        printMatrix("Minors", minorResp.matrix_of_minors);
//        // Expected Minors: [[24, -5, -4], [12, 3, -2], [-2, 5, 4]]
//        printMatrix("Cofactors", minorResp.matrix_of_cofactors);
//        // Expected Cofactors: [[24, 5, -4], [-12, 3, 2], [-2, -5, 4]]
//        std::cout << "Determinant: " << minorResp.determinant << std::endl; // Expected: 22
//     } catch (const std::exception& e) {
//        std::cerr << "Error M8: " << e.what() << std::endl;
//     }
//     std::cout << std::endl;

//     // Example M9: Adjoint/Inverse
//     try {
//         Matrix invMat = {{1.0, 2.0, 3.0}, {0.0, 4.0, 5.0}, {1.0, 0.0, 6.0}}; // Det=22
//         MatrixInput invInput = {invMat};
//         AdjInvResponse invResp = MatrixUtils::calculateAdjointAndInverse(invInput);
//         printMatrix("Input for Adj/Inv", invResp.input_matrix);
//         std::cout << "Determinant: " << invResp.determinant << std::endl;
//         std::cout << "Is Invertible: " << (invResp.is_invertible ? "true" : "false") << std::endl;
//         printMatrix("Adjoint", invResp.adjoint_matrix);
//         // Expected Adjoint: [[24, -12, -2], [5, 3, -5], [-4, 2, 4]]
//         if (invResp.inverse_matrix.has_value()) {
//              printMatrix("Inverse", invResp.inverse_matrix.value());
//              // Expected Inverse: Adjoint / 22
//         } else {
//              std::cout << "Inverse: Not invertible" << std::endl;
//         }
//     } catch (const std::exception& e) {
//         std::cerr << "Error M9: " << e.what() << std::endl;
//     }
//     std::cout << std::endl;


//     return 0;
// }