// src/main/java/michu/fr/polynomials/PolynomialUtils.java
package michu.fr.polynomials;

import michu.fr.polynomials.models.FormedPolynomial;
import michu.fr.polynomials.models.PolynomialDivisionResult;
import michu.fr.polynomials.models.RootsCoefficientsRelation;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

/**
 * Utility class for polynomial operations.
 * Coefficients are represented as List<Double> from highest power to constant.
 * e.g., 2x^3 - 4x + 5  => Arrays.asList(2.0, 0.0, -4.0, 5.0)
 */
public final class PolynomialUtils {

    private static final double EPSILON = 1e-9;

    private PolynomialUtils() {
        throw new UnsupportedOperationException("This is a utility class and cannot be instantiated");
    }

    /**
     * Formats a list of polynomial coefficients into a string.
     * @param coeffs List of coefficients (highest power first).
     * @param varSymbol The variable symbol (e.g., "x").
     * @return String representation of the polynomial.
     */
    public static String formatPolynomialToString(List<Double> coeffs, String varSymbol) {
        if (coeffs == null || coeffs.isEmpty()) {
            return "0";
        }

        // Remove leading zeros for correct degree, unless it's just [0.0]
        int firstNonZeroIdx = 0;
        while (firstNonZeroIdx < coeffs.size() - 1 && Math.abs(coeffs.get(firstNonZeroIdx)) < EPSILON) {
            firstNonZeroIdx++;
        }
        List<Double> relevantCoeffs = coeffs.subList(firstNonZeroIdx, coeffs.size());


        StringBuilder sb = new StringBuilder();
        int degree = relevantCoeffs.size() - 1;

        for (int i = 0; i <= degree; i++) {
            double coeff = relevantCoeffs.get(i);
            int power = degree - i;

            if (Math.abs(coeff) < EPSILON) { // Skip zero terms
                continue;
            }

            // Sign handling
            if (sb.length() > 0) { // Not the first term
                if (coeff > 0) {
                    sb.append(" + ");
                } else {
                    sb.append(" - ");
                    coeff = -coeff; // Make coeff positive for printing
                }
            } else { // First term
                if (coeff < 0) {
                    sb.append("-");
                    coeff = -coeff;
                }
            }

            // Coefficient value (print 1 only if it's the constant term or only term)
            boolean coeffIsOne = Math.abs(coeff - 1.0) < EPSILON;
            if (!coeffIsOne || power == 0 || (degree == 0 && coeffIsOne)) {
                if (coeff == (long) coeff) { // Print as integer if it's a whole number
                    sb.append(String.format("%d", (long) coeff));
                } else {
                    sb.append(String.format("%.4f", coeff).replaceAll("\\.?0+$", ""));
                }
            } else if (coeffIsOne && power > 0 && sb.length() > 0 && !sb.toString().endsWith(" ")) {
                // if coeff is 1 for a variable term, and it's not the very first term
                // (like 'x' after '+ '), no number needed.
                // If it *is* the very first term (e.g. "x^2..."), then no number needed.
                // This 'else if' handles cases where '1' might be printed unnecessarily if first.
                if (sb.length() == 0 && coeffIsOne) {
                    // Handled by the previous `if (!coeffIsOne ...)` not being met for first term 1*x^n
                }
            }


            // Variable and power
            if (power > 0) {
                 // Add a space if a coefficient was printed and it wasn't just a sign for the first term
                if (sb.length() > 0 && !coeffIsOne && !sb.toString().endsWith(" ") && !(sb.length() == 1 && sb.charAt(0) == '-')) {
                     // sb.append(" "); // Optional space: e.g., "2 x" vs "2x". Usually no space.
                }
                sb.append(varSymbol);
                if (power > 1) {
                    sb.append("^").append(power);
                }
            }
        }

        if (sb.length() == 0) { // All coefficients were zero or list was empty
            return "0";
        }
        return sb.toString();
    }

    /**
     * Evaluates P(xVal) using Horner's method.
     * @param coeffs Polynomial coefficients.
     * @param xVal Value at which to evaluate.
     * @return Result of P(xVal).
     */
    public static double evaluatePolynomial(List<Double> coeffs, double xVal) {
        if (coeffs == null || coeffs.isEmpty()) return 0.0;
        double result = 0.0;
        for (double coeff : coeffs) {
            result = result * xVal + coeff;
        }
        return result;
    }

    /**
     * Performs polynomial long division: dividend / divisor.
     * @param dividendCoeffs Coefficients of the dividend.
     * @param divisorCoeffs Coefficients of the divisor.
     * @return PolynomialDivisionResult containing quotient and remainder.
     */
    public static PolynomialDivisionResult polynomialDivision(List<Double> dividendCoeffs, List<Double> divisorCoeffs) {
        if (divisorCoeffs == null || divisorCoeffs.isEmpty() || Math.abs(divisorCoeffs.get(0)) < EPSILON) {
            throw new IllegalArgumentException("Divisor cannot be zero or have a zero leading coefficient.");
        }
        if (dividendCoeffs == null || dividendCoeffs.isEmpty()) {
            List<Double> zero = Collections.singletonList(0.0);
            return new PolynomialDivisionResult(zero, zero, "0", "0", "0 = (divisor) * 0 + 0");
        }

        List<Double> quotient = new ArrayList<>();
        List<Double> remainder = new ArrayList<>(dividendCoeffs); // Work on a copy

        int dividendDegree = dividendCoeffs.size() - 1;
        int divisorDegree = divisorCoeffs.size() - 1;

        if (dividendDegree < divisorDegree) {
            String dividendStr = formatPolynomialToString(dividendCoeffs, "x");
            String divisorStr = formatPolynomialToString(divisorCoeffs, "x");
            String equationStr = String.format("%s = (%s) * 0 + %s", dividendStr, divisorStr, dividendStr);
            return new PolynomialDivisionResult(Collections.singletonList(0.0), dividendCoeffs, "0", dividendStr, equationStr);
        }

        int quotientDegree = dividendDegree - divisorDegree;
        for (int i = 0; i <= quotientDegree; i++) {
            quotient.add(0.0); // Initialize quotient list
        }

        double leadDivisorCoeff = divisorCoeffs.get(0);

        for (int i = 0; i <= quotientDegree; i++) {
            double currentLeadRemainderCoeff = remainder.get(i);
            double currentQuotientCoeff = currentLeadRemainderCoeff / leadDivisorCoeff;
            quotient.set(i, currentQuotientCoeff);

            for (int j = 0; j < divisorCoeffs.size(); j++) {
                remainder.set(i + j, remainder.get(i + j) - currentQuotientCoeff * divisorCoeffs.get(j));
            }
        }

        // Extract the actual remainder part
        List<Double> finalRemainderCoeffs = new ArrayList<>();
        int remainderStartIndex = quotientDegree + 1;
        if (remainderStartIndex < remainder.size()) {
             for(int k=remainderStartIndex; k<remainder.size(); k++){
                 // Only add significant terms to remainder
                 if (Math.abs(remainder.get(k)) > EPSILON || finalRemainderCoeffs.isEmpty() && k == remainder.size()-1){
                      finalRemainderCoeffs.add(remainder.get(k));
                 }
             }
        }
         // Clean up leading zeros in remainder (if any came from exact division part)
         int firstNonZeroRem = 0;
         while(firstNonZeroRem < finalRemainderCoeffs.size() && Math.abs(finalRemainderCoeffs.get(firstNonZeroRem)) < EPSILON) {
             firstNonZeroRem++;
         }
         if(firstNonZeroRem > 0 && firstNonZeroRem == finalRemainderCoeffs.size()){ // all zeros
             finalRemainderCoeffs = Collections.singletonList(0.0);
         } else if (firstNonZeroRem > 0) {
             finalRemainderCoeffs = finalRemainderCoeffs.subList(firstNonZeroRem, finalRemainderCoeffs.size());
         }


        if (finalRemainderCoeffs.isEmpty()) {
            finalRemainderCoeffs.add(0.0);
        }


        String dividendStr = formatPolynomialToString(dividendCoeffs, "x");
        String divisorStr = formatPolynomialToString(divisorCoeffs, "x");
        String quotientStr = formatPolynomialToString(quotient, "x");
        String remainderStr = formatPolynomialToString(finalRemainderCoeffs, "x");
        String equationStr = String.format("(%s) = (%s) * (%s) + (%s)", dividendStr, divisorStr, quotientStr, remainderStr);

        return new PolynomialDivisionResult(quotient, finalRemainderCoeffs, quotientStr, remainderStr, equationStr);
    }


     /**
     * Finds rational roots of a polynomial with integer coefficients.
     * @param coeffs List of coefficients (assumed to be integers or representable as such).
     * @return List of rational roots found.
     */
    public static List<Double> findRationalRoots(List<Double> coeffs) {
        if (coeffs == null || coeffs.isEmpty() || coeffs.size() == 1 && Math.abs(coeffs.get(0)) < EPSILON) { // Constant 0 polynomial
            return Collections.emptyList();
        }
         if (coeffs.size() == 1 && Math.abs(coeffs.get(0)) > EPSILON) { // Non-zero constant has no roots
             return Collections.emptyList();
         }


        // For RRT, coefficients should ideally be integers.
        // We'll round them, assuming they are meant to be integers.
        List<Long> intCoeffs = coeffs.stream()
                                    .map(d -> (long) Math.round(d))
                                    .collect(Collectors.toList());

        long a0 = intCoeffs.get(intCoeffs.size() - 1); // Constant term
        long an = intCoeffs.get(0);                   // Leading coefficient

        if (an == 0) {
            // Leading coefficient is zero, reduce polynomial degree
            if (intCoeffs.size() > 1) {
                return findRationalRoots(coeffs.subList(1, coeffs.size()));
            }
            return Collections.emptyList();
        }
        
        Set<Double> rationalRoots = new HashSet<>();

        if (a0 == 0) { // x=0 is a root
            rationalRoots.add(0.0);
            if (coeffs.size() > 1) { // if it's not just P(x) = 0x + 0
                 List<Double> reducedCoeffs = new ArrayList<>(coeffs.subList(0, coeffs.size() - 1));
                 if (!reducedCoeffs.isEmpty()) { // P(x)/x still has terms
                     rationalRoots.addAll(findRationalRoots(reducedCoeffs));
                 }
            }
             return new ArrayList<>(rationalRoots);
        }


        List<Long> pDivisors = getDivisors(Math.abs(a0));
        List<Long> qDivisors = getDivisors(Math.abs(an));


        for (long p : pDivisors) {
            for (long q : qDivisors) {
                if (q == 0) continue; // Denominator cannot be zero
                double potentialRoot1 = (double) p / q;
                double potentialRoot2 = (double) -p / q;

                if (Math.abs(evaluatePolynomial(coeffs, potentialRoot1)) < EPSILON) {
                    rationalRoots.add(potentialRoot1);
                }
                if (Math.abs(evaluatePolynomial(coeffs, potentialRoot2)) < EPSILON) {
                    rationalRoots.add(potentialRoot2);
                }
            }
        }
        List<Double> sortedRoots = new ArrayList<>(rationalRoots);
        Collections.sort(sortedRoots);
        return sortedRoots;
    }

    private static List<Long> getDivisors(long n) {
        Set<Long> divisors = new HashSet<>();
        if (n == 0) return Collections.singletonList(0L); // Should not happen if a0!=0
        for (long i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                divisors.add(i);
                divisors.add(n / i);
            }
        }
        List<Long> sortedDivs = new ArrayList<>(divisors);
        Collections.sort(sortedDivs);
        return sortedDivs;
    }

    public static RootsCoefficientsRelation relationRootsCoefficientsQuadratic(List<Double> coeffs) {
        if (coeffs == null || coeffs.size() != 3) {
            throw new IllegalArgumentException("Quadratic polynomial must have 3 coefficients (ax^2+bx+c).");
        }
        double a = coeffs.get(0);
        double b = coeffs.get(1);
        double c = coeffs.get(2);

        if (Math.abs(a) < EPSILON) {
            throw new IllegalArgumentException("Leading coefficient 'a' cannot be zero for a quadratic.");
        }

        Map<String, Object> relations = new HashMap<>();
        relations.put("sum_of_roots (alpha + beta)", -b / a);
        relations.put("product_of_roots (alpha * beta)", c / a);

        String polyStr = formatPolynomialToString(coeffs, "x");
        return new RootsCoefficientsRelation(polyStr, 2, relations, "For ax^2+bx+c=0: Sum (α+β) = -b/a, Product (αβ) = c/a.");
    }

    public static RootsCoefficientsRelation relationRootsCoefficientsCubic(List<Double> coeffs) {
         if (coeffs == null || coeffs.size() != 4) {
             throw new IllegalArgumentException("Cubic polynomial must have 4 coefficients (ax^3+bx^2+cx+d).");
         }
         double a = coeffs.get(0);
         double b = coeffs.get(1);
         double c = coeffs.get(2);
         double d = coeffs.get(3);

         if (Math.abs(a) < EPSILON) {
             throw new IllegalArgumentException("Leading coefficient 'a' cannot be zero for a cubic.");
         }

         Map<String, Object> relations = new HashMap<>();
         relations.put("sum_of_roots (α+β+γ)", -b / a);
         relations.put("sum_of_products_pairwise (αβ+βγ+γα)", c / a);
         relations.put("product_of_roots (αβγ)", -d / a);

         String polyStr = formatPolynomialToString(coeffs, "x");
         return new RootsCoefficientsRelation(polyStr, 3, relations, "For ax^3+bx^2+cx+d=0: Sum (α+β+γ) = -b/a, Sum pairwise (αβ+βγ+γα) = c/a, Product (αβγ) = -d/a.");
     }

     /**
     * Multiplies two polynomials.
     * @param poly1Coeffs Coefficients of the first polynomial.
     * @param poly2Coeffs Coefficients of the second polynomial.
     * @return List of coefficients of the resulting polynomial.
     */
    public static List<Double> multiplyPolynomials(List<Double> poly1Coeffs, List<Double> poly2Coeffs) {
        if (poly1Coeffs == null || poly1Coeffs.isEmpty() || poly2Coeffs == null || poly2Coeffs.isEmpty()) {
            return Collections.singletonList(0.0); // Or throw error
        }

        int deg1 = poly1Coeffs.size() - 1;
        int deg2 = poly2Coeffs.size() - 1;
        int resultDeg = deg1 + deg2;
        
        List<Double> resultCoeffs = new ArrayList<>(Collections.nCopies(resultDeg + 1, 0.0));

        for (int i = 0; i <= deg1; i++) {
            for (int j = 0; j <= deg2; j++) {
                resultCoeffs.set(i + j, resultCoeffs.get(i + j) + poly1Coeffs.get(i) * poly2Coeffs.get(j));
            }
        }
        return resultCoeffs;
    }

    public static FormedPolynomial formPolynomialFromRoots(List<Double> roots, double leadingCoefficient, String varSymbol) {
        if (roots == null || roots.isEmpty()) {
            // Polynomial is just the leading coefficient (constant)
            List<Double> coeffs = Collections.singletonList(leadingCoefficient);
            return new FormedPolynomial(coeffs, formatPolynomialToString(coeffs, varSymbol), roots, leadingCoefficient);
        }

        List<Double> currentCoeffs = Collections.singletonList(leadingCoefficient);

        for (double root : roots) {
            // Factor (x - root) has coefficients [1.0, -root]
            List<Double> factorCoeffs = Arrays.asList(1.0, -root);
            currentCoeffs = multiplyPolynomials(currentCoeffs, factorCoeffs);
        }
         String polyStr = formatPolynomialToString(currentCoeffs, varSymbol);
        return new FormedPolynomial(currentCoeffs, polyStr, new ArrayList<>(roots), leadingCoefficient);
    }
}