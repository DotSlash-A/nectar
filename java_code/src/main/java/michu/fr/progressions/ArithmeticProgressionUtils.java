// src/main/java/michu/fr/progressions/ArithmeticProgressionUtils.java
package michu.fr.progressions;

import michu.fr.progressions.models.APMiddleTermResult;
import michu.fr.progressions.models.APResult;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Utility class for calculations related to Arithmetic Progressions (AP).
 */
public final class ArithmeticProgressionUtils {

    private static final double EPSILON = 1e-9; // For floating point comparisons

    // Private constructor to prevent instantiation
    private ArithmeticProgressionUtils() {
        throw new UnsupportedOperationException("This is a utility class and cannot be instantiated");
    }

    /**
     * Calculates the nth term and the sum of the first n terms of an AP.
     *
     * @param a The first term of the AP.
     * @param d The common difference of the AP.
     * @param n The number of terms (must be a positive integer).
     * @return An APResult object containing the nth term and the sum of the first n terms.
     * @throws IllegalArgumentException if n is not positive.
     */
    public static APResult calculateAPTermAndSum(double a, double d, int n) {
        if (n <= 0) {
            throw new IllegalArgumentException("Number of terms (n) must be a positive integer.");
        }

        // Calculate nth term: T_n = a + (n - 1) * d
        double nthTerm = a + (n - 1) * d;

        // Calculate sum of first n terms: S_n = (n / 2) * (2a + (n - 1) * d)
        // Use n / 2.0 to ensure floating point division
        double sumNTerms = (n / 2.0) * (2 * a + (n - 1) * d);

        return new APResult(nthTerm, sumNTerms);
    }

    /**
     * Calculates the nth term from the end of an AP.
     *
     * @param l The last term of the AP.
     * @param d The common difference of the AP.
     * @param n Which term from the end (e.g., n=1 is the last term, n=2 is second last). Must be positive.
     * @return The value of the nth term from the end.
     * @throws IllegalArgumentException if n is not positive.
     */
    public static double calculateNthTermFromLast(double l, double d, int n) {
        if (n <= 0) {
            throw new IllegalArgumentException("Term number from end (n) must be a positive integer.");
        }

        // Calculate nth term from the last term: T_n_from_end = l - (n - 1) * d
        return l - (n - 1) * d;
    }

    /**
     * Calculates the middle term(s) of an AP defined by its first term, common difference, and last term.
     *
     * @param a         The first term of the AP.
     * @param d         The common difference of the AP.
     * @param lastTerm The value of the last term in the AP.
     * @return An APMiddleTermResult containing the number of terms, indices (1-based), and values of the middle term(s).
     * @throws IllegalArgumentException if the progression is invalid (e.g., d=0 and a != lastTerm, or lastTerm is not reachable).
     */
    public static APMiddleTermResult findMiddleTermsAP(double a, double d, double lastTerm) {
        int n; // Number of terms

        if (Math.abs(d) < EPSILON) {
            // Case: Common difference is zero
            if (Math.abs(a - lastTerm) < EPSILON) {
                 // Constant sequence, a = lastTerm. Technically infinite terms if viewed as a limit,
                 // but defined by 'a' and 'lastTerm', it implies only 1 term if they are equal.
                 n = 1;
            } else {
                // d is 0 but first and last terms differ - impossible progression
                throw new IllegalArgumentException("Invalid progression: d is 0 but first and last terms differ.");
            }
        } else {
            // Case: Common difference is non-zero
            // Calculate the number of terms n from a_n = a + (n-1)d => n = (a_n - a)/d + 1
            if ((lastTerm - a) / d < -EPSILON) { // last term is before first term with positive d, or vice versa
                 throw new IllegalArgumentException("Last term is not reachable from the first term with the given common difference direction.");
            }

            double n_float = (lastTerm - a) / d + 1.0;

            // Check if n_float is close to a positive integer
            if (n_float < (1.0 - EPSILON)) { // Check if n is less than 1
                 throw new IllegalArgumentException("Invalid progression parameters leading to non-positive number of terms.");
            }
             if (Math.abs(n_float - Math.round(n_float)) > EPSILON) {
                 throw new IllegalArgumentException("The provided last term is not part of the arithmetic progression defined by 'a' and 'd' (non-integer number of terms).");
            }
            n = (int) Math.round(n_float);
             if (n <= 0) { // Should be caught above, but double check
                throw new IllegalArgumentException("Invalid progression parameters leading to non-positive number of terms.");
            }
        }

        // Calculate middle term(s)
        List<Integer> middleIndices = new ArrayList<>();
        List<Double> middleValues = new ArrayList<>();

        if (n % 2 == 1) { // Odd number of terms
            int middleIndex = (n + 1) / 2;
            // Value: a + (middleIndex - 1) * d
            double middleTermValue = a + (middleIndex - 1) * d;
            middleIndices.add(middleIndex);
            middleValues.add(middleTermValue);
        } else { // Even number of terms
            int middleIndex1 = n / 2;
            int middleIndex2 = n / 2 + 1;
            // Value 1: a + (middleIndex1 - 1) * d
            double middleTerm1Value = a + (middleIndex1 - 1) * d;
            // Value 2: a + (middleIndex2 - 1) * d
            double middleTerm2Value = a + (middleIndex2 - 1) * d;
            middleIndices.add(middleIndex1);
            middleIndices.add(middleIndex2);
            middleValues.add(middleTerm1Value);
            middleValues.add(middleTerm2Value);
        }

        return new APMiddleTermResult(n, Collections.unmodifiableList(middleIndices), Collections.unmodifiableList(middleValues));
    }
}