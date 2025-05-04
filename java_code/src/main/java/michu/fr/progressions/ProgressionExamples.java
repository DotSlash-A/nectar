package michu.fr.progressions;

// Import the utility classes
import michu.fr.progressions.ArithmeticProgressionUtils;
import michu.fr.progressions.GeometricProgressionUtils;

// Import the model classes
import michu.fr.progressions.models.*;

/**
 * A class demonstrating solutions to sample Arithmetic and Geometric Progression problems
 * using the utility classes.
 */
public class ProgressionExamples {

    public static void main(String[] args) {

        System.out.println("--- Solving Sample Progression Problems ---");
        System.out.println("=========================================");

        try { // Wrap examples in a try-catch for robustness

            // --- Arithmetic Progression Examples ---
            System.out.println("\n--- Arithmetic Progression (AP) Examples ---");

            // Example 1: Find nth term and sum of an AP
            System.out.println("\nExample 1: Find the 15th term and sum of the AP: 5, 8, 11, ...");
            double a1 = 5.0;
            double d1 = 8.0 - 5.0; // Calculate common difference
            int n1 = 15;
            System.out.printf("  Inputs: a = %.2f, d = %.2f, n = %d%n", a1, d1, n1);
            APResult result1 = ArithmeticProgressionUtils.calculateAPTermAndSum(a1, d1, n1);
            System.out.printf("  Solution: 15th Term (T15) = %.2f, Sum of first 15 terms (S15) = %.2f%n",
                              result1.getNthTerm(), result1.getSumNTerms());
            // Verification: T15 = 5 + (15-1)*3 = 5 + 14*3 = 5 + 42 = 47. S15 = 15/2 * (2*5 + (15-1)*3) = 7.5 * (10 + 42) = 7.5 * 52 = 390.
            // Note: The previous tester example used different inputs (a=2, d=3, n=10 -> T10=29, S10=155)

            // Example 2: Find nth term from the end
            System.out.println("\nExample 2: An AP starts at 4, has d=5, and ends at 99. Find the 4th term from the end.");
            double l2 = 99.0;
            double d2 = 5.0;
            int nFromEnd2 = 4;
            System.out.printf("  Inputs: last term (l) = %.2f, d = %.2f, term from end (n) = %d%n", l2, d2, nFromEnd2);
            double result2 = ArithmeticProgressionUtils.calculateNthTermFromLast(l2, d2, nFromEnd2);
            System.out.printf("  Solution: The 4th term from the end is = %.2f%n", result2);
             // Verification: The sequence is 4, 9, 14, ..., 89, 94, 99. 4th from end is 89. Calculation: 99 - (4-1)*5 = 99 - 3*5 = 99 - 15 = 84. Let's recheck the tester example: l=29, d=3, n=3 -> 29-(3-1)*3 = 29-6=23. Seems correct. Sequence: 2, 5, 8, 11, 14, 17, 20, 23, 26, 29. 3rd from end is 23. The example here l=99, d=5, n=4 -> 99-(4-1)*5 = 99-15 = 84. Yes, 84 is correct.

            // Example 3: Find middle terms
            System.out.println("\nExample 3: Find the middle term(s) of the AP: 3, 7, 11, ..., 79.");
            double a3 = 3.0;
            double d3 = 7.0 - 3.0;
            double lastTerm3 = 79.0;
            System.out.printf("  Inputs: a = %.2f, d = %.2f, lastTerm = %.2f%n", a3, d3, lastTerm3);
            APMiddleTermResult result3 = ArithmeticProgressionUtils.findMiddleTermsAP(a3, d3, lastTerm3);
            System.out.printf("  Solution: Number of terms = %d%n", result3.getNumberOfTerms());
            if (result3.getMiddleValues().size() == 1) {
                System.out.printf("            There is 1 middle term (Term %d) with value = %.2f%n",
                                  result3.getMiddleIndices().get(0), result3.getMiddleValues().get(0));
            } else {
                 System.out.printf("            There are 2 middle terms (Terms %d and %d) with values = %.2f and %.2f%n",
                                  result3.getMiddleIndices().get(0), result3.getMiddleIndices().get(1),
                                  result3.getMiddleValues().get(0), result3.getMiddleValues().get(1));
            }
             // Verification: n = (79-3)/4 + 1 = 76/4 + 1 = 19 + 1 = 20 terms (Even).
             // Middle terms are n/2 = 10th and n/2+1 = 11th.
             // T10 = 3 + (10-1)*4 = 3 + 9*4 = 3 + 36 = 39.
             // T11 = 3 + (11-1)*4 = 3 + 10*4 = 3 + 40 = 43.
             // The code should return {numberOfTerms=20, middleIndices=[10, 11], middleValues=[39.0, 43.0]}. Let's run and see.


            // --- Geometric Progression Examples ---
            System.out.println("\n\n--- Geometric Progression (GP) Examples ---");

            // Example 4: Find nth term and sum of a GP
            System.out.println("\nExample 4: Find the 6th term and sum of the GP: 2, 6, 18, ...");
            double a4 = 2.0;
            double r4 = 6.0 / 2.0; // Calculate common ratio
            int n4 = 6;
            System.out.printf("  Inputs: a = %.2f, r = %.2f, n = %d%n", a4, r4, n4);
            GPResult result4 = GeometricProgressionUtils.calculateGPTermAndSum(a4, r4, n4);
             System.out.printf("  Solution: 6th Term (T6) = %.2f, Sum of first 6 terms (S6) = %.2f%n",
                              result4.getNthTerm(), result4.getSumNTerms());
            // Verification: T6 = 2 * 3^(6-1) = 2 * 3^5 = 2 * 243 = 486.
            // S6 = 2 * (3^6 - 1) / (3 - 1) = 2 * (729 - 1) / 2 = 728.

            // Example 5: Find sum to infinity
            System.out.println("\nExample 5: Find the sum to infinity of the GP: 27, 9, 3, ...");
            double a5 = 27.0;
            double r5 = 9.0 / 27.0; // Common ratio = 1/3
            System.out.printf("  Inputs: a = %.2f, r = %.4f%n", a5, r5);
            double result5 = GeometricProgressionUtils.calculateSumToInfinity(a5, r5);
            System.out.printf("  Solution: Sum to Infinity (S_inf) = %.2f%n", result5);
            // Verification: S_inf = a / (1 - r) = 27 / (1 - 1/3) = 27 / (2/3) = 27 * 3 / 2 = 81 / 2 = 40.5.

            // Example 6: Find geometric mean
            System.out.println("\nExample 6: Find the geometric mean (GM) between 5 and 45.");
            double num1_6 = 5.0;
            double num2_6 = 45.0;
            System.out.printf("  Inputs: num1 = %.2f, num2 = %.2f%n", num1_6, num2_6);
            double result6 = GeometricProgressionUtils.calculateGeometricMean(num1_6, num2_6);
            System.out.printf("  Solution: Geometric Mean (GM) = %.2f%n", result6);
            // Verification: GM = sqrt(5 * 45) = sqrt(225) = 15.

            // Example 7: Insert geometric means
            System.out.println("\nExample 7: Insert 4 geometric means between 1/3 and 81.");
            // Use double for 1/3
            double a7 = 1.0 / 3.0;
            double b7 = 81.0;
            int k7 = 4;
            System.out.printf("  Inputs: a = %.4f, b = %.2f, k = %d%n", a7, b7, k7);
            GPInsertMeansResult result7 = GeometricProgressionUtils.insertGeometricMeans(a7, b7, k7);
            System.out.printf("  Solution: Common ratio found = %.2f%n", result7.getCommonRatio());
            System.out.println("            The 4 geometric means are: " + result7.getGeometricMeans());
            // Verification: We need to insert 4 means, so total terms = 4+2=6.
            // b = a * r^(k+1) => 81 = (1/3) * r^(4+1) => 81 = (1/3) * r^5
            // r^5 = 81 * 3 = 243. Since 3^5 = 243, r = 3.
            // Means are: a*r, a*r^2, a*r^3, a*r^4
            // (1/3)*3 = 1
            // (1/3)*3^2 = (1/3)*9 = 3
            // (1/3)*3^3 = (1/3)*27 = 9
            // (1/3)*3^4 = (1/3)*81 = 27
            // Means should be [1.0, 3.0, 9.0, 27.0].

        } catch (Exception e) {
            // Catch any unexpected exceptions during solving valid problems
             System.err.println("\nAn unexpected error occurred while solving the examples: " + e.getMessage());
             e.printStackTrace(); // Print stack trace for debugging unexpected errors
        }

        System.out.println("\n=========================================");
        System.out.println("--- Example Problems Solved ---");
    }
}