// src/main/java/michu/fr/polynomials/PolynomialExamples.java
package michu.fr.polynomials;

import michu.fr.polynomials.models.FormedPolynomial;
import michu.fr.polynomials.models.PolynomialDivisionResult;
import michu.fr.polynomials.models.QuadraticSolution;
import michu.fr.polynomials.models.RootsCoefficientsRelation;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class PolynomialExamples {
    public static void main(String[] args) {
        System.out.println("--- Polynomial Examples ---");

        // 1. Formatting and Evaluation
        List<Double> p1Coeffs = Arrays.asList(2.0, -3.0, 0.0, 5.0); // 2x^3 - 3x^2 + 5
        String p1Str = PolynomialUtils.formatPolynomialToString(p1Coeffs, "x");
        System.out.println("P1(x) = " + p1Str);
        System.out.println("P1(2) = " + PolynomialUtils.evaluatePolynomial(p1Coeffs, 2.0)); // 2(8) - 3(4) + 5 = 16 - 12 + 5 = 9

        List<Double> pConstCoeffs = Arrays.asList(7.0); // P(x) = 7
        System.out.println("P_const(x) = " + PolynomialUtils.formatPolynomialToString(pConstCoeffs, "x"));
        System.out.println("P_const(3) = " + PolynomialUtils.evaluatePolynomial(pConstCoeffs, 3.0));

        List<Double> pZeroCoeffs = Arrays.asList(0.0, 0.0, 0.0); // P(x) = 0
        System.out.println("P_zero(x) = " + PolynomialUtils.formatPolynomialToString(pZeroCoeffs, "x"));


        // 2. Polynomial Division
        List<Double> dividend = Arrays.asList(1.0, -5.0, 6.0);    // x^2 - 5x + 6
        List<Double> divisor  = Arrays.asList(1.0, -2.0);       // x - 2
        PolynomialDivisionResult divResult = PolynomialUtils.polynomialDivision(dividend, divisor);
        System.out.println("\nDivision: " + divResult); // Should be (x-3) remainder 0

        List<Double> dividend2 = Arrays.asList(1.0, 0.0, 0.0, -1.0); // x^3 - 1
        List<Double> divisor2  = Arrays.asList(1.0, -1.0);      // x - 1
        PolynomialDivisionResult divResult2 = PolynomialUtils.polynomialDivision(dividend2, divisor2);
        System.out.println("Division 2: " + divResult2); // Should be (x^2+x+1) remainder 0

        List<Double> dividend3 = Arrays.asList(2.0, 3.0, 1.0);    // 2x^2 + 3x + 1
        List<Double> divisor3  = Arrays.asList(1.0, 2.0, 1.0); // x^2 + 2x + 1
        PolynomialDivisionResult divResult3 = PolynomialUtils.polynomialDivision(dividend3, divisor3);
        System.out.println("Division 3: " + divResult3); // Should be Q=2, R=-x-1


        // 3. Quadratic Equation Solving
        System.out.println("\n--- Quadratic Equation Examples ---");
        QuadraticSolution sol1 = QuadraticEquationUtils.solveQuadraticEquation(1, -5, 6); // (x-2)(x-3)=0, roots 2,3
        System.out.println(sol1);

        QuadraticSolution sol2 = QuadraticEquationUtils.solveQuadraticEquation(1, -4, 4); // (x-2)^2=0, root 2 (repeated)
        System.out.println(sol2);

        QuadraticSolution sol3 = QuadraticEquationUtils.solveQuadraticEquation(1, 2, 5); // x^2+2x+5=0, complex roots -1 +/- 2i
        System.out.println(sol3);

        QuadraticSolution solLinear = QuadraticEquationUtils.solveQuadraticEquation(0, 2, -4); // 2x-4=0, root 2
        System.out.println(solLinear);

        QuadraticSolution solIdentity = QuadraticEquationUtils.solveQuadraticEquation(0, 0, 0); // 0=0
        System.out.println(solIdentity);

         QuadraticSolution solContradiction = QuadraticEquationUtils.solveQuadraticEquation(0, 0, 5); // 0= -5
        System.out.println(solContradiction);


        // 4. Rational Roots
        System.out.println("\n--- Rational Roots Examples ---");
        List<Double> polyForRationalRoots1 = Arrays.asList(1.0, -6.0, 11.0, -6.0); // (x-1)(x-2)(x-3) = x^3 - 6x^2 + 11x - 6
        System.out.println("Roots for P(x)=" + PolynomialUtils.formatPolynomialToString(polyForRationalRoots1, "x") + ": " + PolynomialUtils.findRationalRoots(polyForRationalRoots1));

        List<Double> polyForRationalRoots2 = Arrays.asList(2.0, -1.0, -2.0, 1.0); // (2x-1)(x-1)(x+1) = 2x^3 - x^2 - 2x + 1 -> Roots 0.5, 1, -1
        System.out.println("Roots for P(x)=" + PolynomialUtils.formatPolynomialToString(polyForRationalRoots2, "x") + ": " + PolynomialUtils.findRationalRoots(polyForRationalRoots2));
        
        List<Double> polyWithZeroRoot = Arrays.asList(1.0, -1.0, -2.0, 0.0); // x^3 - x^2 - 2x = x(x-2)(x+1) -> Roots 0, 2, -1
        System.out.println("Roots for P(x)=" + PolynomialUtils.formatPolynomialToString(polyWithZeroRoot, "x") + ": " + PolynomialUtils.findRationalRoots(polyWithZeroRoot));


        // 5. Roots-Coefficients Relations
        System.out.println("\n--- Roots-Coefficients Relation Examples ---");
        List<Double> quadraticCoeffs = Arrays.asList(1.0, -7.0, 10.0); // x^2 - 7x + 10 = 0, roots 2, 5
        RootsCoefficientsRelation qcRelation = PolynomialUtils.relationRootsCoefficientsQuadratic(quadraticCoeffs);
        System.out.println(qcRelation);

        List<Double> cubicCoeffs = Arrays.asList(1.0, -6.0, 11.0, -6.0); // x^3 - 6x^2 + 11x - 6 = 0, roots 1, 2, 3
        RootsCoefficientsRelation cubicRelation = PolynomialUtils.relationRootsCoefficientsCubic(cubicCoeffs);
        System.out.println(cubicRelation);

        // 6. Form Polynomial from Roots
        System.out.println("\n--- Form Polynomial from Roots Examples ---");
        List<Double> rootsToForm = Arrays.asList(1.0, 2.0, 3.0);
        FormedPolynomial formed1 = PolynomialUtils.formPolynomialFromRoots(rootsToForm, 1.0, "y");
        System.out.println(formed1); // Should be y^3 - 6y^2 + 11y - 6

        List<Double> rootsToForm2 = Arrays.asList(2.0, 2.0); // (x-2)(x-2) = x^2 - 4x + 4
        FormedPolynomial formed2 = PolynomialUtils.formPolynomialFromRoots(rootsToForm2, 2.0, "z"); // 2(z^2 - 4z + 4) = 2z^2 - 8z + 8
        System.out.println(formed2);

        FormedPolynomial formed3 = PolynomialUtils.formPolynomialFromRoots(Collections.singletonList(5.0), -1.0, "x"); // -1(x-5) = -x+5
        System.out.println(formed3);
    }
}