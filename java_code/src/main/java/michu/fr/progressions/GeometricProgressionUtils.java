// src/main/java/michu/fr/progressions/GeometricProgressionUtils.java
package michu.fr.progressions;

import michu.fr.progressions.models.GPInsertMeansResult;
import michu.fr.progressions.models.GPResult;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Utility class for calculations related to Geometric Progressions (GP).
 */
public final class GeometricProgressionUtils {

    private static final double EPSILON = 1e-9; // For floating point comparisons

    // Private constructor to prevent instantiation
    private GeometricProgressionUtils() {
        throw new UnsupportedOperationException("This is a utility class and cannot be instantiated");
    }

    /**
     * Calculates the nth term and the sum of the first n terms of a GP.
     *
     * @param a The first term of the GP.
     * @param r The common ratio of the GP.
     * @param n The number of terms (must be a positive integer).
     * @return A GPResult object containing the nth term and the sum of the first n terms.
     * @throws IllegalArgumentException if n is not positive, or for ambiguous cases like a=0, r=0, n>1.
     */
    public static GPResult calculateGPTermAndSum(double a, double r, int n) {
        if (n <= 0) {
            throw new IllegalArgumentException("Number of terms (n) must be a positive integer.");
        }
         if (Math.abs(a) < EPSILON && Math.abs(r) < EPSILON && n > 1) {
             // Sequence is 0, 0, 0... but 0^0 is involved in formula for T1 if n=1 (pow(0,0)=1),
             // and potentially for Sn formula depending on implementation.
             // Let's return 0,0 for simplicity as the sequence is all zeros after T1.
             // Python example threw error, let's be consistent:
              throw new IllegalArgumentException("Ambiguous case: a=0, r=0, n>1. Sequence is 0, 0,... but formulas can lead to 0^0.");
         }
        if (Math.abs(a) < EPSILON) { // If a=0, all terms are 0
             return new GPResult(0.0, 0.0);
         }


        // Calculate nth term: T_n = a * r^(n-1)
        // Math.pow handles 0^0 correctly (returns 1.0), so T1 for r=0 works.
        double nthTerm = a * Math.pow(r, n - 1);
         if (Double.isInfinite(nthTerm) || Double.isNaN(nthTerm)) {
              throw new ArithmeticException("Calculation of nth term resulted in overflow or undefined value.");
         }


        // Calculate sum of first n terms: S_n
        double sumNTerms;
        if (Math.abs(r - 1.0) < EPSILON) { // Check if r is very close to 1
            sumNTerms = n * a;
        } else {
            // S_n = a * (r^n - 1) / (r - 1)  or  a * (1 - r^n) / (1 - r)
            double numerator = a * (Math.pow(r, n) - 1.0);
            double denominator = r - 1.0;
             if (Math.abs(denominator) < EPSILON * EPSILON) { // Avoid division by almost zero, tighter tolerance
                 // This case should ideally be caught by the |r-1| check, but for safety.
                 // Could happen if r is extremely close to 1 but not caught by EPSILON.
                 // Treat as r=1 case.
                  sumNTerms = n * a;
                  System.err.println("Warning: Common ratio 'r' is extremely close to 1. Treating as r=1 for sum calculation.");
             } else {
                 sumNTerms = numerator / denominator;
             }
        }
        if (Double.isInfinite(sumNTerms) || Double.isNaN(sumNTerms)) {
             throw new ArithmeticException("Calculation of sum resulted in overflow or undefined value.");
        }


        return new GPResult(nthTerm, sumNTerms);
    }

    /**
     * Calculates the sum to infinity of a GP.
     *
     * @param a The first term of the GP.
     * @param r The common ratio of the GP.
     * @return The sum to infinity.
     * @throws IllegalArgumentException if the absolute value of r (|r|) is not less than 1.
     */
    public static double calculateSumToInfinity(double a, double r) {
        if (Math.abs(r) >= 1.0 - EPSILON) { // Check |r| >= 1
            throw new IllegalArgumentException("Sum to infinity exists only if the absolute value of the common ratio |r| is less than 1.");
        }

        // Formula: S_inf = a / (1 - r)
        double denominator = 1.0 - r;
         if (Math.abs(denominator) < EPSILON * EPSILON) { // Should not happen if |r|<1 but safety check
             throw new ArithmeticException("Denominator (1-r) is too close to zero.");
         }

        double sum = a / denominator;
         if (Double.isInfinite(sum) || Double.isNaN(sum)) {
             throw new ArithmeticException("Calculation of sum to infinity resulted in overflow or undefined value.");
         }
         return sum;
    }

    /**
     * Calculates the geometric mean (GM) of two non-negative numbers.
     *
     * @param num1 The first number (must be non-negative).
     * @param num2 The second number (must be non-negative).
     * @return The geometric mean.
     * @throws IllegalArgumentException if either number is negative.
     */
    public static double calculateGeometricMean(double num1, double num2) {
        if (num1 < -EPSILON || num2 < -EPSILON) { // Allow for small tolerance around zero
            throw new IllegalArgumentException("Geometric Mean is typically defined for non-negative numbers.");
        }
         // Handle cases where one or both numbers are effectively zero
         if (Math.abs(num1) < EPSILON || Math.abs(num2) < EPSILON) {
             return 0.0;
         }

        // GM = sqrt(num1 * num2)
        return Math.sqrt(num1 * num2);
    }

    /**
     * Inserts 'k' geometric means between two numbers 'a' and 'b'.
     * Forms a GP: a, G1, G2, ..., Gk, b.
     *
     * @param a The first number (start of the sequence).
     * @param b The last number (end of the sequence).
     * @param k The number of geometric means to insert (must be a positive integer).
     * @return A GPInsertMeansResult containing the common ratio used and a list of the geometric means.
     * @throws IllegalArgumentException if k is not positive, if a is zero and b is non-zero,
     *                                  or if a real common ratio cannot be found (e.g., even root of a negative number).
     */
    public static GPInsertMeansResult insertGeometricMeans(double a, double b, int k) {
        if (k <= 0) {
            throw new IllegalArgumentException("Number of means to insert (k) must be a positive integer.");
        }

        if (Math.abs(a) < EPSILON) {
            if (Math.abs(b) < EPSILON) {
                // Means between 0 and 0 are all 0
                List<Double> means = new ArrayList<>(Collections.nCopies(k, 0.0));
                // Common ratio is technically undefined or could be anything, let's use 0
                return new GPInsertMeansResult(0.0, Collections.unmodifiableList(means));
            } else { // a=0, b!=0
                throw new IllegalArgumentException("Cannot insert geometric means starting from 0 to a non-zero number (requires infinite or zero ratio).");
            }
        }

        // If a != 0
        // Sequence: a, G1, ..., Gk, b (total k + 2 terms)
        // b = a * r^(k+1) => r^(k+1) = b / a
        double ratio_power_k_plus_1 = b / a;
        int rootIndex = k + 1;

        // Check for complex roots needed for real means
        if (ratio_power_k_plus_1 < -EPSILON && rootIndex % 2 == 0) {
            throw new IllegalArgumentException(
                String.format("Cannot compute real geometric means: requires taking an even root (%d) of a negative number (%.4f).",
                              rootIndex, ratio_power_k_plus_1)
            );
        }

        double r; // Common ratio
        try {
             if (Math.abs(ratio_power_k_plus_1) < EPSILON) { // b is zero, a is non-zero
                 r = 0.0;
             } else if (ratio_power_k_plus_1 < 0) { // Negative base, rootIndex must be odd (checked above)
                r = -Math.pow(Math.abs(ratio_power_k_plus_1), 1.0 / rootIndex);
            } else { // Positive base
                r = Math.pow(ratio_power_k_plus_1, 1.0 / rootIndex);
            }
        } catch (Exception e) { // Catch potential issues from Math.pow, though less common
            throw new ArithmeticException("Error calculating common ratio: " + e.getMessage());
        }
        if (Double.isInfinite(r) || Double.isNaN(r)) {
             throw new ArithmeticException("Calculated common ratio is invalid (Infinite or NaN). Check input values.");
        }

        // Calculate the means: G_i = a * r^i for i = 1, 2, ..., k
        List<Double> means = new ArrayList<>(k);
        double currentTerm = a;
        for (int i = 0; i < k; i++) {
            currentTerm *= r;
             if (Double.isInfinite(currentTerm) || Double.isNaN(currentTerm)) {
                 throw new ArithmeticException(String.format("Calculation of mean %d resulted in overflow or undefined value.", i+1));
             }
            means.add(currentTerm);
        }

        return new GPInsertMeansResult(r, Collections.unmodifiableList(means));
    }
}