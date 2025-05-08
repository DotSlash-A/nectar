package michu.fr.linearequations;

import michu.fr.linearequations.models.ConsistencyCheckResult;
import michu.fr.linearequations.models.EquationCoefficients;
import michu.fr.linearequations.models.ReducibleSolutionResult;
import michu.fr.linearequations.models.SolutionResult;

import org.apache.commons.math3.linear.Array2DRowRealMatrix;
import org.apache.commons.math3.linear.DecompositionSolver;
import org.apache.commons.math3.linear.LUDecomposition;
import org.apache.commons.math3.linear.RealMatrix;
import org.apache.commons.math3.linear.RealVector;
import org.apache.commons.math3.linear.ArrayRealVector;
import org.apache.commons.math3.linear.SingularMatrixException;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Utility class for operations on pairs of linear equations in two variables.
 * Equations are generally in the form:
 * a1x + b1y = c1
 * a2x + b2y = c2
 *
 * For cross-multiplication, the form a1x + b1y + c1 = 0 is used.
 */
public final class LinearEquationUtils {

    private static final double EPSILON = 1e-9; // For floating point comparisons

    public static final String CONSISTENT_UNIQUE = "CONSISTENT_UNIQUE";
    public static final String CONSISTENT_INFINITE = "CONSISTENT_INFINITE";
    public static final String INCONSISTENT_PARALLEL = "INCONSISTENT_PARALLEL";

    private LinearEquationUtils() {
        throw new UnsupportedOperationException("This is a utility class and cannot be instantiated");
    }

    /**
     * Checks the consistency of a pair of linear equations.
     * a1x + b1y = c1
     * a2x + b2y = c2
     */
    public static ConsistencyCheckResult checkConsistency(double a1, double b1, double c1, double a2, double b2, double c2) {
        EquationCoefficients coeffs = new EquationCoefficients(a1, b1, c1, a2, b2, c2);
        Map<String, String> ratioStrings = new HashMap<>();
        
        // Calculate ratios for description
        ratioStrings.put("a1/a2", (a2 != 0) ? String.format("%.4f", a1/a2) : (a1 == 0 ? "0/0" : "undef (a1/0)"));
        ratioStrings.put("b1/b2", (b2 != 0) ? String.format("%.4f", b1/b2) : (b1 == 0 ? "0/0" : "undef (b1/0)"));
        ratioStrings.put("c1/c2", (c2 != 0) ? String.format("%.4f", c1/c2) : (c1 == 0 ? "0/0" : "undef (c1/0)"));

        String consistencyType;
        String description;
        String graphicalInterpretation;

        double determinant = a1 * b2 - a2 * b1;

        if (Math.abs(determinant) > EPSILON) {
            consistencyType = CONSISTENT_UNIQUE;
            description = String.format("System has a unique solution (intersecting lines) because a1*b2 - a2*b1 = %.4f != 0.", determinant);
            graphicalInterpretation = "Lines intersect at a single point.";
        } else {
            // Determinant is zero, so lines are parallel or coincident
            // Check a1/a2 = b1/b2 != c1/c2 (parallel) or a1/a2 = b1/b2 = c1/c2 (coincident)
            // Using cross-products to avoid division by zero issues:
            // a1*c2 - a2*c1 (for comparing a1/a2 with c1/c2, effectively Dx of Cramer's rule if constants were on other side)
            // b1*c2 - b2*c1 (for comparing b1/b2 with c1/c2, effectively Dy of Cramer's rule)

            if (Math.abs(a1 * c2 - a2 * c1) > EPSILON || Math.abs(b1 * c2 - b2 * c1) > EPSILON) {
                // This means that (a1/a2 = b1/b2) but this common ratio is NOT equal to (c1/c2)
                // Or one of (a1,b1,c1) is 0 making one set of ratios 0, while others are non-zero/undefined.
                // Special check: if 0x + 0y = C (C!=0), then inconsistent.
                if ((Math.abs(a1) < EPSILON && Math.abs(b1) < EPSILON && Math.abs(c1) > EPSILON) ||
                    (Math.abs(a2) < EPSILON && Math.abs(b2) < EPSILON && Math.abs(c2) > EPSILON)) {
                    consistencyType = INCONSISTENT_PARALLEL;
                    description = "System is inconsistent (parallel lines). One equation is of the form 0x + 0y = C (C!=0).";
                } else {
                     consistencyType = INCONSISTENT_PARALLEL;
                     description = "System is inconsistent (parallel lines). Ratios a1/a2 = b1/b2 != c1/c2 (or equivalent if denominators are zero).";
                }
                graphicalInterpretation = "Lines are parallel and distinct.";
            } else {
                // Determinant is zero, and a1*c2 = a2*c1, and b1*c2 = b2*c1
                // This implies a1/a2 = b1/b2 = c1/c2 (if denominators are non-zero)
                // This covers 0x+0y=0 as well, which leads to infinite solutions.
                consistencyType = CONSISTENT_INFINITE;
                description = "System has infinitely many solutions (coincident lines). Ratios a1/a2 = b1/b2 = c1/c2 (or equivalent).";
                graphicalInterpretation = "Lines are coincident (overlap completely).";
            }
        }
        description += String.format(" Ratios: a1/a2=%s, b1/b2=%s, c1/c2=%s.",
                ratioStrings.get("a1/a2"), ratioStrings.get("b1/b2"), ratioStrings.get("c1/c2"));

        return new ConsistencyCheckResult(coeffs, consistencyType, description, ratioStrings, graphicalInterpretation);
    }

    /**
     * Solves a pair of linear equations using a general method (Apache Commons Math).
     * a1x + b1y = c1
     * a2x + b2y = c2
     */
    public static SolutionResult solveGeneral(double a1, double b1, double c1, double a2, double b2, double c2) {
        EquationCoefficients coeffs = new EquationCoefficients(a1, b1, c1, a2, b2, c2);
        ConsistencyCheckResult consistency = checkConsistency(a1, b1, c1, a2, b2, c2);
        List<String> steps = new ArrayList<>();
        steps.add("Attempting solution using matrix method (Apache Commons Math).");

        if (CONSISTENT_UNIQUE.equals(consistency.getConsistencyType())) {
            try {
                RealMatrix coefficientsMatrix = new Array2DRowRealMatrix(new double[][]{{a1, b1}, {a2, b2}}, false);
                DecompositionSolver solver = new LUDecomposition(coefficientsMatrix).getSolver();
                RealVector constantsVector = new ArrayRealVector(new double[]{c1, c2}, false);
                RealVector solutionVector = solver.solve(constantsVector);
                double x = solutionVector.getEntry(0);
                double y = solutionVector.getEntry(1);
                steps.add(String.format("Matrix solved: x = %.4f, y = %.4f", x, y));
                return new SolutionResult(coeffs, consistency.getConsistencyType(), consistency.getDescription(),
                        x, y, "General (Matrix Method)", steps);
            } catch (SingularMatrixException e) {
                // This should be caught by consistency check, but as a fallback
                steps.add("Matrix method failed due to singular matrix, re-evaluating consistency.");
                return new SolutionResult(coeffs, INCONSISTENT_PARALLEL, // Or infinite, but singular usually means no unique.
                                          "Matrix is singular. System likely has no unique solution. " + consistency.getDescription(),
                                          "Error", "Error", "General (Matrix Method)", steps);
            } catch (Exception e) {
                 steps.add("Error during matrix solution: " + e.getMessage());
                 return new SolutionResult(coeffs, "ERROR", "An unexpected error occurred during matrix solution.",
                                          "Error", "Error", "General (Matrix Method)", steps);
            }
        } else if (CONSISTENT_INFINITE.equals(consistency.getConsistencyType())) {
            steps.add("System has infinitely many solutions.");
            return new SolutionResult(coeffs, consistency.getConsistencyType(), consistency.getDescription(),
                                      "Infinite", "Infinite", "General (Analysis)", steps);
        } else { // INCONSISTENT_PARALLEL
            steps.add("System has no solution.");
            return new SolutionResult(coeffs, consistency.getConsistencyType(), consistency.getDescription(),
                                      "None", "None", "General (Analysis)", steps);
        }
    }

    /**
     * Solves by substitution method. (Implementation omitted for brevity in this overview, but would be similar to Python logic)
     * a1x + b1y = c1  (eq1)
     * a2x + b2y = c2  (eq2)
     * This would be a fairly long method to implement with detailed steps.
     */
    public static SolutionResult solveBySubstitution(double a1, double b1, double c1, double a2, double b2, double c2) {
        EquationCoefficients coeffs = new EquationCoefficients(a1, b1, c1, a2, b2, c2);
        ConsistencyCheckResult consistency = checkConsistency(a1, b1, c1, a2, b2, c2);
        List<String> steps = new ArrayList<>();
        steps.add("Method: Substitution");

        if (!CONSISTENT_UNIQUE.equals(consistency.getConsistencyType())) {
            return new SolutionResult(coeffs, consistency.getConsistencyType(), consistency.getDescription(),
                                      consistency.getConsistencyType().equals(CONSISTENT_INFINITE) ? "Infinite" : "None",
                                      consistency.getConsistencyType().equals(CONSISTENT_INFINITE) ? "Infinite" : "None",
                                      "Substitution", steps);
        }

        // Actual substitution logic (simplified example)
        // Try to express x from eq1: x = (c1 - b1y) / a1
        if (Math.abs(a1) > EPSILON) {
            steps.add(String.format("From eq1: %sx = %s - %sy  => x = (%s - %sy) / %s", f(a1), f(c1), f(b1), f(c1), f(b1), f(a1)));
            // Substitute into eq2: a2 * [ (c1 - b1y) / a1 ] + b2y = c2
            // (a1b2 - a2b1)y = a1c2 - a2c1
            double yCoeff = a1 * b2 - a2 * b1;
            double yConst = a1 * c2 - a2 * c1;
            steps.add(String.format("Substitute x into eq2: ... => (%s)y = %s", f(yCoeff), f(yConst)));
            if (Math.abs(yCoeff) > EPSILON) {
                double y = yConst / yCoeff;
                double x = (c1 - b1 * y) / a1;
                steps.add(String.format("Solved: y = %s, x = %s", f(y), f(x)));
                return new SolutionResult(coeffs, CONSISTENT_UNIQUE, "Solved by substitution.", x, y, "Substitution", steps);
            }
        } else if (Math.abs(b1) > EPSILON) { // Try to express y from eq1
            steps.add(String.format("From eq1: %sy = %s - %sx => y = (%s - %sx) / %s", f(b1), f(c1), f(a1), f(c1), f(a1), f(b1)));
            // Substitute into eq2: a2x + b2 * [ (c1 - a1x) / b1 ] = c2
            // (a2b1 - a1b2)x = b1c2 - b2c1
             double xCoeff = a2 * b1 - a1 * b2;
             double xConst = b1 * c2 - b2 * c1;
            steps.add(String.format("Substitute y into eq2: ... => (%s)x = %s", f(xCoeff), f(xConst)));
             if (Math.abs(xCoeff) > EPSILON) {
                double x = xConst / xCoeff;
                double y = (c1 - a1 * x) / b1;
                steps.add(String.format("Solved: x = %s, y = %s", f(x), f(y)));
                return new SolutionResult(coeffs, CONSISTENT_UNIQUE, "Solved by substitution.", x, y, "Substitution", steps);
            }
        }
        // Fallback or more complex cases / if first chosen variable leads to 0 coefficient for the other
        steps.add("Substitution logic for this specific case is complex or leads to indeterminate form, relying on general solver.");
        return solveGeneral(a1,b1,c1,a2,b2,c2); // Fallback
    }


    /**
     * Solves by elimination method. (Implementation details similar to substitution, can be lengthy)
     */
    public static SolutionResult solveByElimination(double a1, double b1, double c1, double a2, double b2, double c2) {
        EquationCoefficients coeffs = new EquationCoefficients(a1, b1, c1, a2, b2, c2);
        ConsistencyCheckResult consistency = checkConsistency(a1, b1, c1, a2, b2, c2);
        List<String> steps = new ArrayList<>();
        steps.add("Method: Elimination");

         if (!CONSISTENT_UNIQUE.equals(consistency.getConsistencyType())) {
            return new SolutionResult(coeffs, consistency.getConsistencyType(), consistency.getDescription(),
                                      consistency.getConsistencyType().equals(CONSISTENT_INFINITE) ? "Infinite" : "None",
                                      consistency.getConsistencyType().equals(CONSISTENT_INFINITE) ? "Infinite" : "None",
                                      "Elimination", steps);
        }
        
        // Attempt to eliminate y: Multiply eq1 by b2, eq2 by b1
        // (a1b2 - a2b1)x = c1b2 - c2b1
        double xCoeff = a1 * b2 - a2 * b1; // This is the determinant
        double xConst = c1 * b2 - c2 * b1; 
        steps.add(String.format("To eliminate y: multiply eq1 by %s, eq2 by %s", f(b2), f(b1)));
        steps.add(String.format("Subtracting results in: (%s)x = %s", f(xCoeff), f(xConst)));

        if (Math.abs(xCoeff) > EPSILON) {
            double x = xConst / xCoeff;
            // Substitute x to find y (e.g., in eq1: a1x + b1y = c1 => b1y = c1 - a1x)
            double y;
            if (Math.abs(b1) > EPSILON) {
                y = (c1 - a1 * x) / b1;
            } else if (Math.abs(b2) > EPSILON) { // Use eq2 if b1 is 0
                y = (c2 - a2 * x) / b2;
            } else {
                // Both b1 and b2 are 0. Lines are vertical.
                // This case should be handled by consistency if xCoeff (determinant) is non-zero.
                // If determinant is non-zero, and b1=b2=0, means a1 != 0 and a2 != 0. System is like a1x=c1, a2x=c2.
                // This implies x = c1/a1 and x = c2/a2. If c1/a1 != c2/a2, inconsistent.
                // If c1/a1 = c2/a2, then infinite solutions (y can be anything).
                // But we are in CONSISTENT_UNIQUE branch.
                steps.add("Cannot find y easily as b1 and b2 are near zero. This case needs more specific handling.");
                 return solveGeneral(a1,b1,c1,a2,b2,c2); // Fallback
            }
            steps.add(String.format("Solved: x = %s, y = %s", f(x), f(y)));
            return new SolutionResult(coeffs, CONSISTENT_UNIQUE, "Solved by elimination.", x, y, "Elimination", steps);
        }
        // If xCoeff is 0, it implies determinant is 0, which contradicts CONSISTENT_UNIQUE.
        // This branch should ideally not be hit if consistency check is correct.
        steps.add("Elimination led to 0*x = C. Re-evaluating based on consistency: " + consistency.getDescription());
        return new SolutionResult(coeffs, consistency.getConsistencyType(), consistency.getDescription(),
                                  consistency.getConsistencyType().equals(CONSISTENT_INFINITE) ? "Infinite" : "None",
                                  consistency.getConsistencyType().equals(CONSISTENT_INFINITE) ? "Infinite" : "None",
                                  "Elimination", steps);
    }


    /**
     * Solves by cross-multiplication method.
     * Expects equations in form a1x + b1y + C1 = 0 and a2x + b2y + C2 = 0.
     * The c1_form_axbyc0 and c2_form_axbyc0 are C1 and C2 respectively.
     */
    public static SolutionResult solveByCrossMultiplication(double a1, double b1, double c1_form_axbyc0,
                                                            double a2, double b2, double c2_form_axbyc0) {
        // For consistency check, convert to ax+by=c form: c = -C_form_axbyc0
        EquationCoefficients coeffsForDisplay = new EquationCoefficients(a1, b1, -c1_form_axbyc0, a2, b2, -c2_form_axbyc0);
        ConsistencyCheckResult consistency = checkConsistency(a1, b1, -c1_form_axbyc0, a2, b2, -c2_form_axbyc0);
        List<String> steps = new ArrayList<>();
        steps.add("Method: Cross-Multiplication");
        steps.add(String.format("Equations (form ax+by+c=0): %sx + %sy + %s = 0;  %sx + %sy + %s = 0",
                                f(a1),f(b1),f(c1_form_axbyc0), f(a2),f(b2),f(c2_form_axbyc0)));

        if (!CONSISTENT_UNIQUE.equals(consistency.getConsistencyType())) {
            return new SolutionResult(coeffsForDisplay, consistency.getConsistencyType(), consistency.getDescription(),
                                      consistency.getConsistencyType().equals(CONSISTENT_INFINITE) ? "Infinite" : "None",
                                      consistency.getConsistencyType().equals(CONSISTENT_INFINITE) ? "Infinite" : "None",
                                      "Cross-Multiplication", steps);
        }

        // Formula: x / (b1*C2 - b2*C1) = y / (C1*a2 - C2*a1) = 1 / (a1*b2 - a2*b1)
        double den_x = b1 * c2_form_axbyc0 - b2 * c1_form_axbyc0;
        double den_y = c1_form_axbyc0 * a2 - c2_form_axbyc0 * a1;
        double den_1 = a1 * b2 - a2 * b1; // This is the determinant

        steps.add(String.format("x / (%s*%s - %s*%s) = x / %s", f(b1),f(c2_form_axbyc0),f(b2),f(c1_form_axbyc0), f(den_x)));
        steps.add(String.format("y / (%s*%s - %s*%s) = y / %s", f(c1_form_axbyc0),f(a2),f(c2_form_axbyc0),f(a1), f(den_y)));
        steps.add(String.format("1 / (%s*%s - %s*%s) = 1 / %s", f(a1),f(b2),f(a2),f(b1), f(den_1)));


        if (Math.abs(den_1) > EPSILON) {
            double x = den_x / den_1;
            double y = den_y / den_1;
            steps.add(String.format("x = %s / %s = %s", f(den_x), f(den_1), f(x)));
            steps.add(String.format("y = %s / %s = %s", f(den_y), f(den_1), f(y)));
            return new SolutionResult(coeffsForDisplay, CONSISTENT_UNIQUE, "Solved by cross-multiplication.", x, y, "Cross-Multiplication", steps);
        } else {
            // This case should have been caught by consistency check.
            steps.add("Denominator (a1b2 - a2b1) is zero. Re-evaluating based on consistency: " + consistency.getDescription());
             return new SolutionResult(coeffsForDisplay, consistency.getConsistencyType(), consistency.getDescription(),
                                      consistency.getConsistencyType().equals(CONSISTENT_INFINITE) ? "Infinite" : "None",
                                      consistency.getConsistencyType().equals(CONSISTENT_INFINITE) ? "Infinite" : "None",
                                      "Cross-Multiplication", steps);
        }
    }

    /**
     * Solves equations reducible to linear form.
     * User provides coefficients for the substituted linear equations (in u and v).
     * uCoeff1*u + vCoeff1*v = const1
     * uCoeff2*u + vCoeff2*v = const2
     * And what u and v represent (e.g., u="1/x", v="1/y").
     */
    public static ReducibleSolutionResult solveReducible(
            double uCoeff1, double vCoeff1, double const1,
            double uCoeff2, double vCoeff2, double const2,
            String uRepresents, String vRepresents) {

        EquationCoefficients substitutedEqs = new EquationCoefficients(uCoeff1, vCoeff1, const1, uCoeff2, vCoeff2, const2);
        Map<String, String> substDetails = new HashMap<>();
        substDetails.put("u_represents", uRepresents);
        substDetails.put("v_represents", vRepresents);
        substDetails.put("substituted_eq1", String.format("%su + %sv = %s", f(uCoeff1),f(vCoeff1),f(const1)));
        substDetails.put("substituted_eq2", String.format("%su + %sv = %s", f(uCoeff2),f(vCoeff2),f(const2)));

        // Solve for u and v
        SolutionResult uvSolution = solveGeneral(uCoeff1, vCoeff1, const1, uCoeff2, vCoeff2, const2);

        Double originalX = null; String originalXStr = "N/A";
        Double originalY = null; String originalYStr = "N/A";

        if (CONSISTENT_UNIQUE.equals(uvSolution.getConsistencyType())) {
            Double u = uvSolution.getSolutionX();
            Double v = uvSolution.getSolutionY();
            substDetails.put("solution_u", (u != null) ? f(u) : "Error");
            substDetails.put("solution_v", (v != null) ? f(v) : "Error");

            if (u != null) {
                if ("1/x".equalsIgnoreCase(uRepresents.trim())) {
                    if (Math.abs(u) > EPSILON) { originalX = 1.0 / u; originalXStr = f(originalX); }
                    else { originalXStr = "Error (u=0 for 1/x)"; }
                } else if ("x".equalsIgnoreCase(uRepresents.trim())) {
                     originalX = u; originalXStr = f(originalX);
                } else { originalXStr = "Cannot determine x from u=" + f(u); }
            }

            if (v != null) {
                if ("1/y".equalsIgnoreCase(vRepresents.trim())) {
                    if (Math.abs(v) > EPSILON) { originalY = 1.0 / v; originalYStr = f(originalY); }
                    else { originalYStr = "Error (v=0 for 1/y)"; }
                } else if ("y".equalsIgnoreCase(vRepresents.trim())) {
                    originalY = v; originalYStr = f(originalY);
                } else { originalYStr = "Cannot determine y from v=" + f(v); }
            }
             return new ReducibleSolutionResult(substitutedEqs, uvSolution.getConsistencyType(),
                    "Solved substituted system for u and v. " + uvSolution.getDescription(),
                    u, v, uvSolution.getSolutionXString(), uvSolution.getSolutionYString(),
                    originalX, originalY, originalXStr, originalYStr,
                    "Reducible (General for u,v)", uvSolution.getSteps(), substDetails);

        } else { // Infinite or No solution for u,v
            substDetails.put("solution_u", uvSolution.getSolutionXString());
            substDetails.put("solution_v", uvSolution.getSolutionYString());
            originalXStr = "Derived from u: " + uvSolution.getSolutionXString();
            originalYStr = "Derived from v: " + uvSolution.getSolutionYString();
            
            return new ReducibleSolutionResult(substitutedEqs, uvSolution.getConsistencyType(),
                    "Substituted system for u and v: " + uvSolution.getDescription(),
                    uvSolution.getSolutionXString(), uvSolution.getSolutionYString(), // Pass string solutions for u,v
                    originalXStr, originalYStr,
                    "Reducible (General for u,v)", uvSolution.getSteps(), substDetails);
        }
    }

    // Helper to format doubles nicely
    private static String f(double val) {
        if (Math.abs(val - Math.round(val)) < EPSILON) {
            return String.format("%d", Math.round(val));
        }
        return String.format("%.2f", val); // Adjust precision as needed
    }
}