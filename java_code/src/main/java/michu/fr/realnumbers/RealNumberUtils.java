package michu.fr.realnumbers;

import michu.fr.realnumbers.models.*;



import java.util.*;


/**
 * Utility class for calculations related to Real Numbers concepts
 * from NCERT Class 10.
 */
public final class RealNumberUtils {

    // Private constructor to prevent instantiation
    private RealNumberUtils() {
        throw new UnsupportedOperationException("This is a utility class and cannot be instantiated");
    }

    /**
     * Applies Euclid's Division Lemma: dividend = divisor * quotient + remainder.
     *
     * @param dividend The number to be divided.
     * @param divisor  The number by which to divide (must be non-zero).
     * @return EuclidLemmaResult containing quotient, remainder, and the equation.
     * @throws IllegalArgumentException if divisor is zero.
     */
    public static EuclidLemmaResult euclidsDivisionLemma(int dividend, int divisor) {
        if (divisor == 0) {
            throw new IllegalArgumentException("Divisor cannot be zero.");
        }
        int quotient = dividend / divisor;
        int remainder = dividend % divisor;
        return new EuclidLemmaResult(dividend, divisor, quotient, remainder);
    }

    /**
     * Calculates the Highest Common Factor (HCF/GCD) of two numbers using Euclid's Algorithm.
     *
     * @param n1 First integer.
     * @param n2 Second integer.
     * @return HCFResult containing the two numbers and their HCF.
     * @throws IllegalArgumentException if HCF(0,0) is attempted.
     */
    public static HCFResult euclidsAlgorithmHCF(int n1, int n2) {
        if (n1 == 0 && n2 == 0) {
            throw new IllegalArgumentException("HCF(0, 0) is undefined. At least one number must be non-zero.");
        }
        int num1 = Math.abs(n1);
        int num2 = Math.abs(n2);

        int dividend = Math.max(num1, num2);
        int divisor = Math.min(num1, num2);

        if (divisor == 0) { // handles cases like HCF(5,0) = 5
             return new HCFResult(n1, n2, dividend);
        }

        int remainder;
        while (divisor != 0) {
            remainder = dividend % divisor;
            dividend = divisor;
            divisor = remainder;
        }
        return new HCFResult(n1, n2, dividend);
    }

    /**
     * Computes the prime factorization of a positive integer n.
     *
     * @param n The integer to factorize.
     * @return PrimeFactorizationResult containing the number and its prime factors (prime -> exponent).
     * @throws IllegalArgumentException if n <= 1.
     */
    public static PrimeFactorizationResult getPrimeFactorization(int n) {
        if (n <= 1) {
            throw new IllegalArgumentException("Number must be greater than 1 for prime factorization.");
        }

        Map<Integer, Integer> factors = new HashMap<>();
        int num = n;

        // Count divisions by 2
        while (num % 2 == 0) {
            factors.put(2, factors.getOrDefault(2, 0) + 1);
            num /= 2;
        }

        // Check for odd factors from 3 upwards
        for (int i = 3; i * i <= num; i += 2) {
            while (num % i == 0) {
                factors.put(i, factors.getOrDefault(i, 0) + 1);
                num /= i;
            }
        }

        // If num is still greater than 1, it must be a prime
        if (num > 1) {
            factors.put(num, factors.getOrDefault(num, 0) + 1);
        }
        return new PrimeFactorizationResult(n, factors);
    }

    /**
     * Calculates HCF from two prime factorization maps.
     *
     * @param factors1 Prime factorization of the first number.
     * @param factors2 Prime factorization of the second number.
     * @return The HCF.
     */
    public static int hcfFromPrimeFactorization(Map<Integer, Integer> factors1, Map<Integer, Integer> factors2) {
        int hcf = 1;
        for (Map.Entry<Integer, Integer> entry : factors1.entrySet()) {
            int prime = entry.getKey();
            if (factors2.containsKey(prime)) {
                int power = Math.min(entry.getValue(), factors2.get(prime));
                hcf *= Math.pow(prime, power);
            }
        }
        return hcf;
    }
     /**
     * Calculates LCM from two prime factorization maps.
     *
     * @param factors1 Prime factorization of the first number.
     * @param factors2 Prime factorization of the second number.
     * @return The LCM.
     */
    public static long lcmFromPrimeFactorization(Map<Integer, Integer> factors1, Map<Integer, Integer> factors2) {
        long lcm = 1L;
        Map<Integer, Integer> allPrimesWithMaxPower = new HashMap<>(factors1);

        for (Map.Entry<Integer, Integer> entry : factors2.entrySet()) {
            allPrimesWithMaxPower.put(entry.getKey(),
                Math.max(entry.getValue(), allPrimesWithMaxPower.getOrDefault(entry.getKey(), 0))
            );
        }
        
        for (Map.Entry<Integer, Integer> entry : allPrimesWithMaxPower.entrySet()) {
            lcm *= Math.pow(entry.getKey(), entry.getValue());
             if (lcm < 0) { // Overflow check for long
                 throw new ArithmeticException("LCM calculation resulted in overflow.");
             }
        }
        return lcm;
    }


    /**
     * Calculates the Least Common Multiple (LCM) of two numbers using the formula LCM(a,b) = |a*b| / HCF(a,b).
     *
     * @param n1 First integer.
     * @param n2 Second integer.
     * @return The LCM as a long (to prevent overflow).
     * @throws IllegalArgumentException if both n1 and n2 are zero.
     * @throws ArithmeticException if HCF is zero (should not happen if inputs are handled).
     */
    public static long calculateLCM(int n1, int n2) {
        if (n1 == 0 && n2 == 0) {
            throw new IllegalArgumentException("LCM(0,0) is undefined. At least one number must be non-zero.");
        }
        if (n1 == 0 || n2 == 0) {
            return 0; // Conventionally LCM(a,0) = 0
        }
        int hcf = euclidsAlgorithmHCF(n1, n2).getHcf();
        if (hcf == 0) { // Should not be reached if n1 or n2 is non-zero
            throw new ArithmeticException("HCF is zero, cannot calculate LCM.");
        }
        // Use long for product to prevent overflow before division
        return Math.abs((long) n1 * n2) / hcf;
    }

    /**
     * Combines HCF and LCM calculation, also returning prime factorizations.
     * @param num1 First integer (>1).
     * @param num2 Second integer (>1).
     * @return HCFAndLCMResult object.
     */
    public static HCFAndLCMResult getHCFAndLCMDetails(int num1, int num2) {
        if (num1 <= 1 || num2 <= 1) {
            throw new IllegalArgumentException("Numbers must be greater than 1 for this detailed HCF/LCM via prime factorization.");
        }
        PrimeFactorizationResult pf1 = getPrimeFactorization(num1);
        PrimeFactorizationResult pf2 = getPrimeFactorization(num2);
        
        int hcf = hcfFromPrimeFactorization(pf1.getFactors(), pf2.getFactors());
        long lcm = calculateLCM(num1, num2); // Or use lcmFromPrimeFactorization

        return new HCFAndLCMResult(num1, num2, pf1.getFactors(), pf2.getFactors(), hcf, lcm);
    }


    /**
     * Basic primality test.
     * @param n Integer to test.
     * @return true if n is prime, false otherwise.
     */
    public static boolean isPrimeBasic(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i = i + 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    /**
     * Checks if a non-negative integer N is a perfect square.
     * @param n Integer to check.
     * @return true if n is a perfect square, false otherwise.
     * @throws IllegalArgumentException if n is negative.
     */
    public static boolean isNumberPerfectSquare(int n) {
        if (n < 0) throw new IllegalArgumentException("Input number cannot be negative.");
        if (n == 0) return true;
        int sqrtN = (int) Math.sqrt(n);
        return sqrtN * sqrtN == n;
    }

    /**
     * Checks if the square root of a non-negative integer N is irrational.
     * @param number Non-negative integer N.
     * @return IrrationalityCheckResult.
     */
    public static IrrationalityCheckResult checkSqrtIrrationality(int number) {
        String form = "sqrt(" + number + ")";
        if (number < 0) {
            return new IrrationalityCheckResult(form, false, "sqrt(" + number + ") is a complex number, not a real irrational number.");
        }
        if (isNumberPerfectSquare(number)) {
            return new IrrationalityCheckResult(form, false, "sqrt(" + number + ") = " + (int) Math.sqrt(number) + ", which is rational (an integer).");
        }
        String reason;
        if (isPrimeBasic(number)) {
            reason = number + " is a prime number. The square root of a prime number is irrational.";
        } else {
            reason = number + " is not a perfect square. The square root of a non-perfect square integer is irrational.";
        }
        return new IrrationalityCheckResult(form, true, reason);
    }

    /**
     * Determines if the decimal expansion of a rational number num/den is terminating or non-terminating recurring.
     * @param numerator   Numerator of the fraction.
     * @param denominator Denominator of the fraction (must be non-zero).
     * @return DecimalExpansionResult.
     * @throws IllegalArgumentException if denominator is zero.
     */
    public static DecimalExpansionResult getDecimalExpansionType(int numerator, int denominator) {
        if (denominator == 0) {
            throw new IllegalArgumentException("Denominator cannot be zero.");
        }

        int common = euclidsAlgorithmHCF(Math.abs(numerator), Math.abs(denominator)).getHcf();
        int simplifiedDen = Math.abs(denominator) / common;

        if (simplifiedDen == 0) { // Should not happen if original denominator wasn't 0 and HCF is correct
            return new DecimalExpansionResult(numerator, denominator, "undefined", "Denominator became zero after simplification.");
        }
        if (simplifiedDen == 1) {
            return new DecimalExpansionResult(numerator, denominator, "terminating",
                    "The fraction simplifies to an integer (" + (numerator / common) + "). Denominator is 1.");
        }

        // Prime factorize the simplified denominator
        int tempDen = simplifiedDen;
        boolean only2And5 = true;
        StringBuilder factorsStrBuilder = new StringBuilder();

        int count2 = 0;
        while (tempDen % 2 == 0) {
            tempDen /= 2;
            count2++;
        }
        if (count2 > 0) factorsStrBuilder.append("2^").append(count2).append(" ");

        int count5 = 0;
        while (tempDen % 5 == 0) {
            tempDen /= 5;
            count5++;
        }
        if (count5 > 0) factorsStrBuilder.append("5^").append(count5).append(" ");

        // Check for other prime factors
        for (int i = 3; i * i <= tempDen; i += 2) { // Check odd numbers
            if (tempDen % i == 0) {
                 int countOther = 0;
                 while (tempDen % i == 0) {
                    tempDen /= i;
                    countOther++;
                 }
                 only2And5 = false;
                 factorsStrBuilder.append(i).append("^").append(countOther).append(" ");
            }
        }
        if (tempDen > 1) { // Remaining tempDen is a prime factor other than 2 or 5
             if (tempDen != 2 && tempDen != 5) { // Should be caught by loop if not prime, but safety for prime > sqrt(original tempDen)
                only2And5 = false;
                factorsStrBuilder.append(tempDen).append("^1 ");
            }
        }
        
        String denominatorFactorsStr = factorsStrBuilder.toString().trim();
        if (denominatorFactorsStr.isEmpty() && simplifiedDen == 1) denominatorFactorsStr = "1"; // if it simplified to 1/1
        else if (denominatorFactorsStr.isEmpty()) denominatorFactorsStr = String.valueOf(simplifiedDen);


        String reason;
        String type;
        if (only2And5) {
            type = "terminating";
            reason = "Simplified denominator (" + simplifiedDen + ") has prime factors: " + denominatorFactorsStr + " (only 2s and/or 5s).";
        } else {
            type = "non-terminating recurring";
            reason = "Simplified denominator (" + simplifiedDen + ") has prime factors: " + denominatorFactorsStr + " (includes primes other than 2 and 5).";
        }
        return new DecimalExpansionResult(numerator, denominator, type, reason);
    }

}