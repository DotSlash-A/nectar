package michu.fr.matrix;

import michu.fr.matrix.models.*; // Import all models from the subpackage

import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;
import javax.script.Bindings;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class MatrixUtils {

    private static final double EPSILON = 1e-9; // Tolerance for float comparison

    // --- Validation and Conversion Helpers ---

    /**
     * Validates if the input List of Lists represents a valid matrix (rectangular, non-empty, numeric).
     * Converts it to a double[][] array.
     *
     * @param matrixList Input matrix as List<List<Double>>.
     * @return The matrix as double[][].
     * @throws IllegalArgumentException If validation fails.
     */
    private static double[][] validateAndConvertMatrix(List<List<Double>> matrixList) {
        if (matrixList == null || matrixList.isEmpty()) {
            throw new IllegalArgumentException("Matrix input cannot be null or empty.");
        }

        int rows = matrixList.size();
        List<Double> firstRow = matrixList.get(0);
        if (firstRow == null || firstRow.isEmpty()) {
            throw new IllegalArgumentException("Matrix rows cannot be null or empty.");
        }
        int cols = firstRow.size();

        double[][] matrixArray = new double[rows][cols];

        for (int i = 0; i < rows; i++) {
            List<Double> currentRow = matrixList.get(i);
            if (currentRow == null) {
                 throw new IllegalArgumentException("Matrix row " + i + " cannot be null.");
            }
            if (currentRow.size() != cols) {
                throw new IllegalArgumentException("Matrix rows have inconsistent lengths (row " + i + " has " + currentRow.size() + ", expected " + cols + ").");
            }
            for (int j = 0; j < cols; j++) {
                Double element = currentRow.get(j);
                 if (element == null) {
                     throw new IllegalArgumentException("Matrix element at [" + i + "][" + j + "] cannot be null.");
                 }
                matrixArray[i][j] = element; // Auto-unboxing
            }
        }
        return matrixArray;
    }

    /**
     * Validates if the input List of Lists represents a valid SQUARE matrix.
     * Converts it to a double[][] array.
     *
     * @param matrixList Input matrix as List<List<Double>>.
     * @param requiredDimension The expected dimension n for the square matrix. If <= 0, dimension is inferred.
     * @return The square matrix as double[][].
     * @throws IllegalArgumentException If validation fails (not square, wrong dimension, etc.).
     */
    private static double[][] validateAndConvertSquareMatrix(List<List<Double>> matrixList, int requiredDimension) {
        double[][] matrix = validateAndConvertMatrix(matrixList); // Basic validation first
        int rows = matrix.length;
        int cols = matrix[0].length;

        if (rows != cols) {
            throw new IllegalArgumentException("Matrix must be square, but got " + rows + "x" + cols + ".");
        }
        if (requiredDimension > 0 && rows != requiredDimension) {
            throw new IllegalArgumentException("Matrix has dimension " + rows + ", but expected " + requiredDimension + ".");
        }
         if (rows == 0) {
              throw new IllegalArgumentException("Matrix cannot be 0x0.");
         }
        return matrix;
    }

    /**
     * Converts a double[][] array back to List<List<Double>>.
     */
    private static List<List<Double>> convertMatrixToList(double[][] matrixArray) {
        if (matrixArray == null) return null;
        List<List<Double>> matrixList = new ArrayList<>();
        for (double[] rowArray : matrixArray) {
            List<Double> rowList = new ArrayList<>();
            for (double element : rowArray) {
                rowList.add(element);
            }
            matrixList.add(rowList);
        }
        return matrixList;
    }

     /** Gets dimensions as a string "rows x cols" or "Invalid". */
     private static String getDimensionString(List<List<Double>> matrixList) {
         if (matrixList == null || matrixList.isEmpty() || matrixList.get(0) == null) {
             return "Invalid";
         }
         int rows = matrixList.size();
         int cols = matrixList.get(0).size();
         // Quick check for consistency - full validation is elsewhere
         for(int i=1; i<rows; ++i) {
             if(matrixList.get(i) == null || matrixList.get(i).size() != cols) return "Invalid";
         }
         return rows + "x" + cols;
     }


    // --- Core Matrix Operations (Implementations without NumPy) ---

    /**
     * Creates a submatrix by excluding a specified row and column.
     */
    private static double[][] getSubmatrix(double[][] matrix, int excludingRow, int excludingCol) {
        int n = matrix.length;
        if (n <= 1) {
            return new double[0][0]; // Or throw error? Submatrix of 1x1 is tricky.
        }
        double[][] submatrix = new double[n - 1][n - 1];
        int rSub = 0;
        for (int r = 0; r < n; r++) {
            if (r == excludingRow) continue; // Skip the excluded row
            int cSub = 0;
            for (int c = 0; c < n; c++) {
                if (c == excludingCol) continue; // Skip the excluded column
                submatrix[rSub][cSub] = matrix[r][c];
                cSub++;
            }
            rSub++;
        }
        return submatrix;
    }

    /**
     * Calculates the determinant of a square matrix using Laplace (cofactor) expansion.
     */
    private static double calculateDeterminantRecursive(double[][] matrix) {
        int n = matrix.length;
        if (n == 0) {
            return 1; // Determinant of 0x0 matrix (minor of 1x1) is often defined as 1
        }
        if (n == 1) {
            return matrix[0][0];
        }
        if (n == 2) {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        }

        double det = 0;
        // Expand along the first row (row index 0)
        for (int j = 0; j < n; j++) { // j is the column index
            double[][] submatrix = getSubmatrix(matrix, 0, j);
            double minor = calculateDeterminantRecursive(submatrix);
            double cofactor = Math.pow(-1, 0 + j) * minor; // Sign = (-1)^(row+col)
            det += matrix[0][j] * cofactor;
        }
        return det;
    }

    /**
     * Transposes a matrix.
     */
    private static double[][] transposeMatrix(double[][] matrix) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) {
            return new double[0][0]; // Handle empty matrix
        }
        int rows = matrix.length;
        int cols = matrix[0].length;
        double[][] transposed = new double[cols][rows];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                transposed[j][i] = matrix[i][j];
            }
        }
        return transposed;
    }

    /**
     * Adds two matrices element-wise. Assumes dimensions are compatible.
     */
    private static double[][] addMatrices(double[][] matrixA, double[][] matrixB) {
        int rows = matrixA.length;
        int cols = matrixA[0].length;
        double[][] result = new double[rows][cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result[i][j] = matrixA[i][j] + matrixB[i][j];
            }
        }
        return result;
    }

    /**
     * Multiplies a matrix by a scalar.
     */
    private static double[][] multiplyMatrixByScalar(double[][] matrix, double scalar) {
         if (matrix == null || matrix.length == 0 || matrix[0].length == 0) {
             return new double[0][0];
         }
        int rows = matrix.length;
        int cols = matrix[0].length;
        double[][] result = new double[rows][cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result[i][j] = matrix[i][j] * scalar;
            }
        }
        return result;
    }

    /**
     * Multiplies two matrices (A * B). Assumes dimensions are compatible (A.cols == B.rows).
     */
    private static double[][] multiplyMatrices(double[][] matrixA, double[][] matrixB) {
        int rowsA = matrixA.length;
        int colsA = matrixA[0].length; // = rowsB
        int colsB = matrixB[0].length;
        double[][] result = new double[rowsA][colsB];

        for (int i = 0; i < rowsA; i++) { // Row index for result
            for (int j = 0; j < colsB; j++) { // Column index for result
                double sum = 0;
                for (int k = 0; k < colsA; k++) { // Inner loop index
                    sum += matrixA[i][k] * matrixB[k][j];
                }
                result[i][j] = sum;
            }
        }
        return result;
    }


    // --- Public API-like Methods ---

    /**
     * API Method: Calculates the determinant of a matrix provided as List<List<Double>>.
     */
    public static DeterminantResponseAPI calculateDeterminant(DetInput input) {
        Objects.requireNonNull(input, "Input data cannot be null.");
        // Validate, convert, and check if square
        double[][] matrix = validateAndConvertSquareMatrix(input.getMatrix(), -1); // -1 infers dimension

        double determinant = calculateDeterminantRecursive(matrix);

        // Optional: Rounding for cleaner output
         if (Math.abs(determinant - Math.round(determinant)) < EPSILON) {
             determinant = Math.round(determinant);
         }

        return new DeterminantResponseAPI(input.getMatrix(), determinant);
    }

    /**
     * API Method: Compares two matrices for equality.
     */
    public static MatrixEqualityResponse compareMatrices(TwoMatrixInput input) {
        Objects.requireNonNull(input, "Input data cannot be null.");
        List<List<Double>> listA = input.getMatrixA();
        List<List<Double>> listB = input.getMatrixB();

        String dimAStr = getDimensionString(listA);
        String dimBStr = getDimensionString(listB);

        double[][] matrixA, matrixB;
        try {
            // Validate individually first
            matrixA = validateAndConvertMatrix(listA);
            matrixB = validateAndConvertMatrix(listB);
        } catch (IllegalArgumentException e) {
            // If conversion fails, they aren't valid/equal matrices
            return new MatrixEqualityResponse(false, "One or both inputs are not valid matrices.", dimAStr, dimBStr);
        }

        int rowsA = matrixA.length;
        int colsA = matrixA[0].length;
        int rowsB = matrixB.length;
        int colsB = matrixB[0].length;

        if (rowsA != rowsB || colsA != colsB) {
            return new MatrixEqualityResponse(false, "Matrices have different dimensions.", dimAStr, dimBStr);
        }

        // Element-wise comparison with tolerance
        for (int i = 0; i < rowsA; i++) {
            for (int j = 0; j < colsA; j++) {
                if (Math.abs(matrixA[i][j] - matrixB[i][j]) > EPSILON) {
                    String reason = String.format("Element mismatch at row %d, column %d (%.4f != %.4f).",
                                                  i, j, matrixA[i][j], matrixB[i][j]);
                    return new MatrixEqualityResponse(false, reason, dimAStr, dimBStr);
                }
            }
        }

        return new MatrixEqualityResponse(true, "Matrices are identical.", dimAStr, dimBStr);
    }


    /**
     * API Method: Constructs a matrix from a formula string using JavaScript engine.
     * WARNING: Potential security risk if formula comes from untrusted input.
     */
    public static ConstructedMatrixResponse constructMatrixFromFormula(MatrixFormulaInput input) {
        Objects.requireNonNull(input, "Input data cannot be null.");
        int m = input.getM();
        int n = input.getN();
        String formula = input.getFormula();

        ScriptEngineManager manager = new ScriptEngineManager();
        ScriptEngine engine = manager.getEngineByName("JavaScript");
        if (engine == null) {
            throw new RuntimeException("JavaScript engine not found. Ensure JDK includes Nashorn or GraalVM JS.");
        }

        double[][] constructedMatrix = new double[m][n];
        Bindings bindings = engine.createBindings();

        try {
            for (int i = 1; i <= m; i++) { // Formula uses 1-based index
                for (int j = 1; j <= n; j++) {
                    bindings.put("i", i);
                    bindings.put("j", j);
                    Object result = engine.eval(formula, bindings);
                    if (!(result instanceof Number)) {
                        throw new IllegalArgumentException("Formula did not evaluate to a number at (" + i + "," + j + ")");
                    }
                    constructedMatrix[i - 1][j - 1] = ((Number) result).doubleValue();
                }
            }
        } catch (ScriptException e) {
            throw new IllegalArgumentException("Invalid formula or error during evaluation: " + e.getMessage(), e);
        } catch (Exception e) { // Catch other potential errors
             throw new RuntimeException("Unexpected error during formula evaluation: " + e.getMessage(), e);
        }

        return new ConstructedMatrixResponse(m, n, formula, convertMatrixToList(constructedMatrix));
    }

     /**
      * API Method: Adds two matrices.
      */
     public static MatrixResponse addMatricesAPI(TwoMatrixInput input) {
         Objects.requireNonNull(input, "Input data cannot be null.");
         double[][] matrixA = validateAndConvertMatrix(input.getMatrixA());
         double[][] matrixB = validateAndConvertMatrix(input.getMatrixB());

         if (matrixA.length != matrixB.length || matrixA[0].length != matrixB[0].length) {
             throw new IllegalArgumentException("Matrices must have the same dimensions for addition.");
         }

         double[][] result = addMatrices(matrixA, matrixB);
         return new MatrixResponse(convertMatrixToList(result));
     }

      /**
       * API Method: Multiplies a matrix by a scalar.
       */
      public static MatrixResponse multiplyMatrixByScalarAPI(MatrixInputAPI matrixInput, double scalar) {
           Objects.requireNonNull(matrixInput, "Matrix input cannot be null.");
           double[][] matrix = validateAndConvertMatrix(matrixInput.getMatrix());
           double[][] result = multiplyMatrixByScalar(matrix, scalar);
           return new MatrixResponse(convertMatrixToList(result));
      }

       /**
        * API Method: Multiplies two matrices (A * B).
        */
       public static MatrixResponse multiplyMatricesAPI(TwoMatrixInput input) {
            Objects.requireNonNull(input, "Input data cannot be null.");
            double[][] matrixA = validateAndConvertMatrix(input.getMatrixA());
            double[][] matrixB = validateAndConvertMatrix(input.getMatrixB());

            if (matrixA[0].length != matrixB.length) {
                 throw new IllegalArgumentException("Incompatible dimensions for matrix multiplication (A.cols must equal B.rows).");
            }

            double[][] result = multiplyMatrices(matrixA, matrixB);
            return new MatrixResponse(convertMatrixToList(result));
       }

        /**
         * API Method: Transposes a matrix.
         */
        public static MatrixResponse transposeMatrixAPI(MatrixInputAPI input) {
             Objects.requireNonNull(input, "Matrix input cannot be null.");
             double[][] matrix = validateAndConvertMatrix(input.getMatrix());
             double[][] result = transposeMatrix(matrix);
             return new MatrixResponse(convertMatrixToList(result));
        }

     /**
      * API Method: Calculates Minors and Cofactors.
      */
     public static MinorsCofactorsResponse calculateMinorsAndCofactors(DetInput input) {
        Objects.requireNonNull(input, "Input data cannot be null.");
        double[][] matrix = validateAndConvertSquareMatrix(input.getMatrix(), -1);
        int n = matrix.length;

        if (n == 0) {
            throw new IllegalArgumentException("Cannot calculate minors/cofactors for 0x0 matrix.");
        }

        double[][] minorsMatrix = new double[n][n];
        double[][] cofactorsMatrix = new double[n][n];

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                double[][] submatrix = getSubmatrix(matrix, r, c);
                double minorVal = calculateDeterminantRecursive(submatrix);
                minorsMatrix[r][c] = minorVal;
                cofactorsMatrix[r][c] = Math.pow(-1, r + c) * minorVal;
            }
        }

        // Optionally calculate determinant as well
        Double determinant = (n > 0) ? calculateDeterminantRecursive(matrix) : null;


        return new MinorsCofactorsResponse(
            input.getMatrix(),
            n + "x" + n,
            convertMatrixToList(minorsMatrix),
            convertMatrixToList(cofactorsMatrix),
            determinant
        );
     }


    /**
     * API Method: Calculates Adjoint and Inverse matrix.
     */
    public static AdjInvResponse calculateAdjointAndInverse(MatrixInputAPI input) {
        Objects.requireNonNull(input, "Input data cannot be null.");
        double[][] matrix = validateAndConvertSquareMatrix(input.getMatrix(), -1);
        int n = matrix.length;

        if (n == 0) {
            throw new IllegalArgumentException("Cannot calculate adjoint/inverse for 0x0 matrix.");
        }

        // Calculate Cofactors first
        double[][] cofactorsMatrix = new double[n][n];
         for (int r = 0; r < n; r++) {
             for (int c = 0; c < n; c++) {
                 double[][] submatrix = getSubmatrix(matrix, r, c);
                 double minorVal = calculateDeterminantRecursive(submatrix);
                 cofactorsMatrix[r][c] = Math.pow(-1, r + c) * minorVal;
             }
         }

        // Adjoint is the transpose of the cofactor matrix
        double[][] adjointMatrix = transposeMatrix(cofactorsMatrix);

        // Calculate Determinant
        double determinant = calculateDeterminantRecursive(matrix);

        // Check Invertibility and Calculate Inverse
        boolean isInvertible = Math.abs(determinant) > EPSILON;
        double[][] inverseMatrix = null;
        if (isInvertible) {
            double invScalar = 1.0 / determinant;
            inverseMatrix = multiplyMatrixByScalar(adjointMatrix, invScalar);
        }

        return new AdjInvResponse(
            input.getMatrix(),
            n + "x" + n,
            determinant,
            isInvertible,
            convertMatrixToList(adjointMatrix),
            isInvertible ? convertMatrixToList(inverseMatrix) : null
        );
    }

} // End of MatrixUtils class