package michu.fr.progressions;

// Import the utility classes
// import michu.fr.progressions.ArithmeticProgressionUtils;
// import michu.fr.progressions.GeometricProgressionUtils;

// Import the model classes (using wildcard for convenience)
import michu.fr.progressions.models.*;

/**
 * A class with a main method to test the progression utility functions.
 */
public class ProgressionTester {

    public static void main(String[] args) {

        System.out.println("--- Testing Progression Utils ---");
        System.out.println("=================================");

        // --- Arithmetic Progression Tests ---
        System.out.println("\n--- Arithmetic Progression (AP) Tests ---");

        // 1. Test calculateAPTermAndSum
        try {
            double a1 = 2.0;
            double d1 = 3.0;
            int n1 = 10;
            System.out.printf("Testing AP Basic: a=%.2f, d=%.2f, n=%d%n", a1, d1, n1);
            APResult result1 = ArithmeticProgressionUtils.calculateAPTermAndSum(a1, d1, n1);
            System.out.println("  Result: " + result1);
            // Expected: APResult{nthTerm=29.0, sumNTerms=155.0}

            // Test edge case n=1
            APResult result1_edge = ArithmeticProgressionUtils.calculateAPTermAndSum(5.0, 10.0, 1);
            System.out.println("Testing AP Basic (n=1): a=5.0, d=10.0, n=1");
            System.out.println("  Result: " + result1_edge);
             // Expected: APResult{nthTerm=5.0, sumNTerms=5.0}

        } catch (IllegalArgumentException e) {
            System.err.println("  Error in calculateAPTermAndSum: " + e.getMessage());
        }
         try { // Test invalid n
             System.out.println("\nTesting AP Basic with invalid n=0:");
             ArithmeticProgressionUtils.calculateAPTermAndSum(1.0, 1.0, 0);
         } catch (IllegalArgumentException e) {
             System.err.println("  Caught expected error: " + e.getMessage());
         }


        // 2. Test calculateNthTermFromLast
        try {
            double l2 = 29.0;
            double d2 = 3.0;
            int n2 = 3;
            System.out.printf("\nTesting AP Nth Term From Last: l=%.2f, d=%.2f, n=%d (3rd term from end)%n", l2, d2, n2);
            double result2 = ArithmeticProgressionUtils.calculateNthTermFromLast(l2, d2, n2);
            System.out.println("  Result: " + result2);
            // Expected: 23.0

             // Test n=1 (last term)
             double result2_edge = ArithmeticProgressionUtils.calculateNthTermFromLast(50.0, 5.0, 1);
             System.out.println("Testing AP Nth Term From Last (n=1): l=50.0, d=5.0, n=1");
             System.out.println("  Result: " + result2_edge);
             // Expected: 50.0

        } catch (IllegalArgumentException e) {
            System.err.println("  Error in calculateNthTermFromLast: " + e.getMessage());
        }
         try { // Test invalid n
             System.out.println("\nTesting AP Nth Term From Last with invalid n=0:");
             ArithmeticProgressionUtils.calculateNthTermFromLast(10.0, 2.0, 0);
         } catch (IllegalArgumentException e) {
             System.err.println("  Caught expected error: " + e.getMessage());
         }

        // 3. Test findMiddleTermsAP
        try {
            // Case 1: Even number of terms
            double a3_1 = 2.0;
            double d3_1 = 3.0;
            double last3_1 = 29.0; // n=10 terms
            System.out.printf("\nTesting AP Middle Terms (Even): a=%.2f, d=%.2f, lastTerm=%.2f%n", a3_1, d3_1, last3_1);
            APMiddleTermResult result3_1 = ArithmeticProgressionUtils.findMiddleTermsAP(a3_1, d3_1, last3_1);
            System.out.println("  Result: " + result3_1);
            // Expected: APMiddleTermResult{numberOfTerms=10, middleIndices=[5, 6], middleValues=[14.0, 17.0]}

            // Case 2: Odd number of terms
            double a3_2 = 1.0;
            double d3_2 = 2.0;
            double last3_2 = 9.0; // n=5 terms
            System.out.printf("\nTesting AP Middle Terms (Odd): a=%.2f, d=%.2f, lastTerm=%.2f%n", a3_2, d3_2, last3_2);
            APMiddleTermResult result3_2 = ArithmeticProgressionUtils.findMiddleTermsAP(a3_2, d3_2, last3_2);
            System.out.println("  Result: " + result3_2);
            // Expected: APMiddleTermResult{numberOfTerms=5, middleIndices=[3], middleValues=[5.0]}

            // Case 3: Single term
            double a3_3 = 7.0;
            double d3_3 = 5.0; // d doesn't matter here if a == lastTerm
            double last3_3 = 7.0; // n=1 term
            System.out.printf("\nTesting AP Middle Terms (Single): a=%.2f, d=%.2f, lastTerm=%.2f%n", a3_3, d3_3, last3_3);
            APMiddleTermResult result3_3 = ArithmeticProgressionUtils.findMiddleTermsAP(a3_3, d3_3, last3_3);
            System.out.println("  Result: " + result3_3);
            // Expected: APMiddleTermResult{numberOfTerms=1, middleIndices=[1], middleValues=[7.0]}

        } catch (IllegalArgumentException e) {
            System.err.println("  Error in findMiddleTermsAP: " + e.getMessage());
        }
         try { // Test invalid d=0, a!=last
             System.out.println("\nTesting AP Middle Terms with invalid input (d=0, a!=last):");
             ArithmeticProgressionUtils.findMiddleTermsAP(1.0, 0.0, 5.0);
         } catch (IllegalArgumentException e) {
             System.err.println("  Caught expected error: " + e.getMessage());
         }
          try { // Test invalid - unreachable last term
             System.out.println("\nTesting AP Middle Terms with invalid input (unreachable last term):");
             ArithmeticProgressionUtils.findMiddleTermsAP(1.0, 2.0, 10.0); // 1, 3, 5, 7, 9, 11... 10 is not reachable
         } catch (IllegalArgumentException e) {
             System.err.println("  Caught expected error: " + e.getMessage());
         }

        // --- Geometric Progression Tests ---
        System.out.println("\n\n--- Geometric Progression (GP) Tests ---");

        // 4. Test calculateGPTermAndSum
        try {
            double a4 = 3.0;
            double r4 = 2.0;
            int n4 = 5;
            System.out.printf("\nTesting GP Basic: a=%.2f, r=%.2f, n=%d%n", a4, r4, n4);
            GPResult result4 = GeometricProgressionUtils.calculateGPTermAndSum(a4, r4, n4);
            System.out.println("  Result: " + result4);
            // Expected: GPResult{nthTerm=48.0, sumNTerms=93.0}

            // Test r=1
             double a4_r1 = 5.0;
             double r4_r1 = 1.0;
             int n4_r1 = 4;
             System.out.printf("Testing GP Basic (r=1): a=%.2f, r=%.2f, n=%d%n", a4_r1, r4_r1, n4_r1);
             GPResult result4_r1 = GeometricProgressionUtils.calculateGPTermAndSum(a4_r1, r4_r1, n4_r1);
             System.out.println("  Result: " + result4_r1);
             // Expected: GPResult{nthTerm=5.0, sumNTerms=20.0}

            // Test a=0
            double a4_a0 = 0.0;
            double r4_a0 = 10.0;
            int n4_a0 = 5;
            System.out.printf("Testing GP Basic (a=0): a=%.2f, r=%.2f, n=%d%n", a4_a0, r4_a0, n4_a0);
            GPResult result4_a0 = GeometricProgressionUtils.calculateGPTermAndSum(a4_a0, r4_a0, n4_a0);
            System.out.println("  Result: " + result4_a0);
            // Expected: GPResult{nthTerm=0.0, sumNTerms=0.0}

            // Test fractional r
             double a4_frac = 8.0;
             double r4_frac = 0.5;
             int n4_frac = 4;
             System.out.printf("Testing GP Basic (fractional r): a=%.2f, r=%.2f, n=%d%n", a4_frac, r4_frac, n4_frac);
             GPResult result4_frac = GeometricProgressionUtils.calculateGPTermAndSum(a4_frac, r4_frac, n4_frac);
             System.out.println("  Result: " + result4_frac);
              // Expected: GPResult{nthTerm=1.0, sumNTerms=15.0} (8+4+2+1 = 15)

        } catch (IllegalArgumentException | ArithmeticException e) {
            System.err.println("  Error in calculateGPTermAndSum: " + e.getMessage());
        }
        try { // Test invalid n
             System.out.println("\nTesting GP Basic with invalid n=0:");
             GeometricProgressionUtils.calculateGPTermAndSum(1.0, 2.0, 0);
         } catch (IllegalArgumentException e) {
             System.err.println("  Caught expected error: " + e.getMessage());
         }


        // 5. Test calculateSumToInfinity
        try {
            double a5 = 10.0;
            double r5 = 0.5;
            System.out.printf("\nTesting GP Sum to Infinity: a=%.2f, r=%.2f%n", a5, r5);
            double result5 = GeometricProgressionUtils.calculateSumToInfinity(a5, r5);
            System.out.println("  Result: " + result5);
            // Expected: 20.0

            double a5_neg = 6.0;
            double r5_neg = -0.5;
             System.out.printf("Testing GP Sum to Infinity (neg r): a=%.2f, r=%.2f%n", a5_neg, r5_neg);
            double result5_neg = GeometricProgressionUtils.calculateSumToInfinity(a5_neg, r5_neg);
            System.out.println("  Result: " + result5_neg);
             // Expected: 4.0 (6 / (1 - (-0.5)) = 6 / 1.5 = 4)

        } catch (IllegalArgumentException | ArithmeticException e) {
            System.err.println("  Error in calculateSumToInfinity: " + e.getMessage());
        }
        try { // Test invalid r >= 1
             System.out.println("\nTesting GP Sum to Infinity with invalid r=1.5:");
             GeometricProgressionUtils.calculateSumToInfinity(10.0, 1.5);
         } catch (IllegalArgumentException e) {
             System.err.println("  Caught expected error: " + e.getMessage());
         }
        try { // Test invalid r = -1
             System.out.println("\nTesting GP Sum to Infinity with invalid r=-1:");
             GeometricProgressionUtils.calculateSumToInfinity(10.0, -1.0);
         } catch (IllegalArgumentException e) {
             System.err.println("  Caught expected error: " + e.getMessage());
         }

        // 6. Test calculateGeometricMean
        try {
            double num1_6 = 4.0;
            double num2_6 = 9.0;
            System.out.printf("\nTesting Geometric Mean: num1=%.2f, num2=%.2f%n", num1_6, num2_6);
            double result6 = GeometricProgressionUtils.calculateGeometricMean(num1_6, num2_6);
            System.out.println("  Result: " + result6);
            // Expected: 6.0

             double num1_6z = 0.0;
             double num2_6z = 10.0;
             System.out.printf("Testing Geometric Mean (one zero): num1=%.2f, num2=%.2f%n", num1_6z, num2_6z);
             double result6z = GeometricProgressionUtils.calculateGeometricMean(num1_6z, num2_6z);
             System.out.println("  Result: " + result6z);
             // Expected: 0.0

        } catch (IllegalArgumentException e) {
            System.err.println("  Error in calculateGeometricMean: " + e.getMessage());
        }
         try { // Test invalid negative input
             System.out.println("\nTesting Geometric Mean with negative input:");
             GeometricProgressionUtils.calculateGeometricMean(-4.0, 9.0);
         } catch (IllegalArgumentException e) {
             System.err.println("  Caught expected error: " + e.getMessage());
         }

        // 7. Test insertGeometricMeans
        try {
            double a7 = 2.0;
            double b7 = 162.0;
            int k7 = 3;
            System.out.printf("\nTesting GP Insert Means: a=%.2f, b=%.2f, k=%d%n", a7, b7, k7);
            GPInsertMeansResult result7 = GeometricProgressionUtils.insertGeometricMeans(a7, b7, k7);
            System.out.println("  Result: " + result7);
            // Expected: GPInsertMeansResult{commonRatio=3.0, geometricMeans=[6.0, 18.0, 54.0]}

             // Test negative ratio case (odd root)
             double a7_neg = 1.0;
             double b7_neg = -8.0;
             int k7_neg = 2; // r^3 = -8 => r = -2
             System.out.printf("Testing GP Insert Means (negative r): a=%.2f, b=%.2f, k=%d%n", a7_neg, b7_neg, k7_neg);
             GPInsertMeansResult result7_neg = GeometricProgressionUtils.insertGeometricMeans(a7_neg, b7_neg, k7_neg);
             System.out.println("  Result: " + result7_neg);
             // Expected: GPInsertMeansResult{commonRatio=-2.0, geometricMeans=[-2.0, 4.0]}

              // Test b=0 case
             double a7_b0 = 10.0;
             double b7_b0 = 0.0;
             int k7_b0 = 2; // r^3 = 0 => r = 0
             System.out.printf("Testing GP Insert Means (b=0): a=%.2f, b=%.2f, k=%d%n", a7_b0, b7_b0, k7_b0);
             GPInsertMeansResult result7_b0 = GeometricProgressionUtils.insertGeometricMeans(a7_b0, b7_b0, k7_b0);
             System.out.println("  Result: " + result7_b0);
             // Expected: GPInsertMeansResult{commonRatio=0.0, geometricMeans=[0.0, 0.0]}


        } catch (IllegalArgumentException | ArithmeticException e) {
            System.err.println("  Error in insertGeometricMeans: " + e.getMessage());
        }
         try { // Test invalid k=0
             System.out.println("\nTesting GP Insert Means with invalid k=0:");
             GeometricProgressionUtils.insertGeometricMeans(1.0, 10.0, 0);
         } catch (IllegalArgumentException e) {
             System.err.println("  Caught expected error: " + e.getMessage());
         }
         try { // Test invalid a=0, b!=0
             System.out.println("\nTesting GP Insert Means with invalid a=0, b!=0:");
             GeometricProgressionUtils.insertGeometricMeans(0.0, 10.0, 2);
         } catch (IllegalArgumentException e) {
             System.err.println("  Caught expected error: " + e.getMessage());
         }
         try { // Test invalid - even root of negative
             System.out.println("\nTesting GP Insert Means with invalid input (even root of negative):");
             GeometricProgressionUtils.insertGeometricMeans(1.0, -16.0, 3); // r^4 = -16, no real root
         } catch (IllegalArgumentException e) {
             System.err.println("  Caught expected error: " + e.getMessage());
         }

        System.out.println("\n=================================");
        System.out.println("--- Testing Complete ---");
    }
}