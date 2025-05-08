// src/main/java/michu/fr/polynomials/QuadraticEquationUtils.java
package michu.fr.polynomials;

import michu.fr.polynomials.models.ComplexNumber;
import michu.fr.polynomials.models.QuadraticSolution;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public final class QuadraticEquationUtils {

    private static final double EPSILON = 1e-9;

    private QuadraticEquationUtils() {
         throw new UnsupportedOperationException("This is a utility class and cannot be instantiated");
    }

    /**
     * Solves ax^2 + bx + c = 0.
     * @param a Coefficient of x^2.
     * @param b Coefficient of x.
     * @param c Constant term.
     * @return QuadraticSolution object.
     */
    public static QuadraticSolution solveQuadraticEquation(double a, double b, double c) {
        String equationStr = PolynomialUtils.formatPolynomialToString(Arrays.asList(a, b, c), "x") + " = 0";
        double discriminant = 0; // Initialize
        String natureOfRoots;
        List<Object> roots = new ArrayList<>(); // Store Double or ComplexNumber

        if (Math.abs(a) < EPSILON) { // Linear or trivial equation
            if (Math.abs(b) < EPSILON) { // c = 0
                if (Math.abs(c) < EPSILON) {
                    natureOfRoots = "Identity (0x + 0 = 0)";
                    roots.add("All real numbers");
                } else {
                    natureOfRoots = "Contradiction (0 = non-zero)";
                    // No roots
                }
            } else { // bx + c = 0
                natureOfRoots = "Linear equation";
                roots.add(-c / b);
            }
            // For non-quadratic, discriminant isn't standard, set to NaN or 0, or omit
            discriminant = Double.NaN; 
        } else { // Quadratic
            discriminant = b * b - 4 * a * c;

            if (discriminant > EPSILON) {
                natureOfRoots = "Two distinct real roots";
                double sqrtD = Math.sqrt(discriminant);
                roots.add((-b + sqrtD) / (2 * a));
                roots.add((-b - sqrtD) / (2 * a));
            } else if (Math.abs(discriminant) < EPSILON) { // D is effectively zero
                natureOfRoots = "Two equal real roots (repeated root)";
                roots.add(-b / (2 * a));
                // roots.add(-b / (2 * a)); // Represent as one for list, describe in nature
            } else { // D < 0
                natureOfRoots = "Two complex conjugate roots";
                double sqrtNegD = Math.sqrt(-discriminant);
                double realPart = -b / (2 * a);
                double imagPart = sqrtNegD / (2 * a);
                roots.add(new ComplexNumber(realPart, imagPart));
                roots.add(new ComplexNumber(realPart, -imagPart));
            }
        }
        return new QuadraticSolution(equationStr, a, b, c, discriminant, natureOfRoots, Collections.unmodifiableList(roots));
    }
}