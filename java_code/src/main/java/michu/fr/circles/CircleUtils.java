package michu.fr.circles;

import michu.fr.circles.models.*;
import michu.fr.lines.models.Coordinates; // Reusing Coordinates
import michu.fr.lines.models.GeneralLineInput; // Reusing GeneralLineInput

import java.util.Objects;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class CircleUtils {

    private static final double EPSILON = 1e-9; // Tolerance for floating-point comparisons

    /**
     * Calculates the standard and general equations of a circle given its center and radius.
     *
     * @param input CircleGeneralInput containing center (h, k) and radius (r).
     * @return CircleEqnResponse with standard and general forms, center, radius, and coefficients.
     * @throws IllegalArgumentException if radius is negative or inputs are null.
     */
    public static CircleEqnResponse getCircleEquationsFromCenterRadius(CircleGeneralInput input) {
        Objects.requireNonNull(input, "Input cannot be null.");
        Objects.requireNonNull(input.getH(), "Center h cannot be null.");
        Objects.requireNonNull(input.getK(), "Center k cannot be null.");
        Objects.requireNonNull(input.getR(), "Radius r cannot be null.");

        double h = input.getH();
        double k = input.getK();
        double r = input.getR();

        if (r < 0) {
            throw new IllegalArgumentException("Radius cannot be negative.");
        }

        double rSquared = r * r;

        // Standard Form: (x - h)^2 + (y - k)^2 = r^2
        String standardForm = String.format("(x - %.4f)^2 + (y - %.4f)^2 = %.4f", h, k, rSquared)
                                    .replace("- -", "+ "); // Clean up double negatives

        // General Form: x^2 + y^2 + Cx + Dy + E = 0
        // C = -2h
        // D = -2k
        // E = h^2 + k^2 - r^2
        double coeffC = -2 * h;
        double coeffD = -2 * k;
        double coeffE = h * h + k * k - rSquared;

        String generalForm = formatGeneralEquation(1, 1, coeffC, coeffD, coeffE); // A=1, B=1

        return new CircleEqnResponse(standardForm, generalForm, h, k, r, 1, 1, coeffC, coeffD, coeffE);
    }

     /**
      * Extracts coefficients A, B, C, D, E from a general circle equation string.
      * WARNING: This parsing is basic and relies on specific formatting.
      * Assumes terms like Ax^2, By^2, Cx, Dy, E separated by '+' or '-'.
      * Handles implicit coefficients (e.g., x^2, -y, +x).
      *
      * @param equationString The equation string (e.g., "x^2+y^2-4x+6y-12=0").
      * @return A double array [A, B, C, D, E].
      * @throws IllegalArgumentException if parsing fails or equation is invalid.
      */
     private static double[] parseGeneralCircleEquation(String equationString) {
        Objects.requireNonNull(equationString, "Equation string cannot be null.");
        String eq = equationString.replaceAll("\\s+", "").replace("=0", ""); // Remove spaces, "=0"
        eq = eq.replace("^-", "^NEG"); // Temp handle negative exponents if needed (not typical for circle)
        eq = eq.replace("-", "+-"); // Ensure all terms are separated by '+'
        if (eq.startsWith("+-")) {
            eq = eq.substring(1); // Remove leading '+' if it resulted from "+-"
        }

        double a = 0, b = 0, c = 0, d = 0, e = 0;
        // Regex patterns (simplified)
        Pattern x2Pattern = Pattern.compile("([+-]?(?:\\d*\\.?\\d+)?)\\*?x\\^2");
        Pattern y2Pattern = Pattern.compile("([+-]?(?:\\d*\\.?\\d+)?)\\*?y\\^2");
        Pattern xPattern  = Pattern.compile("([+-]?(?:\\d*\\.?\\d+)?)\\*?x(?!\\^)"); // x not followed by ^
        Pattern yPattern  = Pattern.compile("([+-]?(?:\\d*\\.?\\d+)?)\\*?y(?!\\^)"); // y not followed by ^
        // Constant term is harder with regex alone, often easier to remove other terms and parse what's left

         // Simplified extraction - find terms and parse coefficient
        String remainingEq = eq;
        Matcher m;

        m = x2Pattern.matcher(remainingEq);
        if (m.find()) { a = parseCoefficient(m.group(1)); remainingEq = m.replaceAll(""); }
        m = y2Pattern.matcher(remainingEq);
        if (m.find()) { b = parseCoefficient(m.group(1)); remainingEq = m.replaceAll(""); }
        m = xPattern.matcher(remainingEq);
         if (m.find()) { c = parseCoefficient(m.group(1)); remainingEq = m.replaceAll(""); }
         m = yPattern.matcher(remainingEq);
         if (m.find()) { d = parseCoefficient(m.group(1)); remainingEq = m.replaceAll(""); }

         // Parse remaining constant term(s)
         remainingEq = remainingEq.replace("++", "+").replace("--", "+");
         if (!remainingEq.isEmpty() && !remainingEq.equals("+")) {
             try {
                 // Sum up any remaining constants
                 String[] constantTerms = remainingEq.split("\\+");
                 for (String term : constantTerms) {
                     if (!term.trim().isEmpty()) {
                          e += Double.parseDouble(term.trim());
                     }
                 }
             } catch (NumberFormatException ex) {
                 throw new IllegalArgumentException("Could not parse constant term(s) in: '" + remainingEq + "' from equation '" + equationString +"'");
             }
         }


        return new double[]{a, b, c, d, e};
     }

      // Helper to parse coefficient string (handles "+", "-", "+1", "-1", "+2.5", etc.)
     private static double parseCoefficient(String coeffStr) {
         if (coeffStr == null || coeffStr.isEmpty() || coeffStr.equals("+")) return 1.0;
         if (coeffStr.equals("-")) return -1.0;
         return Double.parseDouble(coeffStr);
     }


    /**
     * Calculates the center (h, k) and radius (r) of a circle from its
     * general form equation (Ax^2 + By^2 + Cx + Dy + E = 0).
     * Uses basic string parsing - see limitations on parseGeneralCircleEquation.
     *
     * @param data CircleGeneralFormInput containing the equation string.
     * @return CircleDetailsResponse containing center coordinates and radius.
     * @throws IllegalArgumentException if the equation is invalid or does not represent a real circle.
     */
    public static CircleDetailsResponse getCircleDetailsFromGeneralForm(CircleGeneralFormInput data) {
        Objects.requireNonNull(data, "Input data cannot be null.");
        String inputEqStr = data.getEquation();

        try {
            double[] coeffs = parseGeneralCircleEquation(inputEqStr);
            double A = coeffs[0];
            double B = coeffs[1];
            double C = coeffs[2];
            double D = coeffs[3];
            double E = coeffs[4];

            // --- Validate if it's a circle ---
            if (Math.abs(A) < EPSILON || Math.abs(B) < EPSILON) {
                throw new IllegalArgumentException("Not a valid circle/ellipse equation (A or B is zero).");
            }
            if (Math.abs(A - B) > EPSILON) {
                throw new IllegalArgumentException(
                    String.format("Not a circle equation (coefficient of x^2 (%.4f) != coefficient of y^2 (%.4f)).", A, B)
                );
            }

            // --- Normalize coefficients (divide by A if A is not 1) ---
            String normalizedEqStr = null;
            if (Math.abs(A - 1.0) > EPSILON) {
                C = C / A;
                D = D / A;
                E = E / A;
                normalizedEqStr = formatGeneralEquation(1, 1, C, D, E); // A=1, B=1 now
                A = 1.0; // A and B are now effectively 1
                B = 1.0;
            } else {
                 normalizedEqStr = formatGeneralEquation(A, B, C, D, E); // Already normalized or A=1
            }


            // --- Calculate center (h, k) ---
            // h = -C / (2*A) -> h = -C / 2 (since A=1 now)
            // k = -D / (2*B) -> k = -D / 2 (since B=1 now)
            double h = -C / 2.0;
            double k = -D / 2.0;

            // --- Calculate radius (r) ---
            // r^2 = h^2 + k^2 - E/A -> r^2 = h^2 + k^2 - E (since A=1 now)
            double radiusSquared = h * h + k * k - E;

            if (radiusSquared < -EPSILON) { // Allow for small negative due to precision
                throw new IllegalArgumentException(
                    String.format("Not a real circle (radius squared = %.4f is negative).", radiusSquared)
                );
            }
             if (radiusSquared < 0) {
                 radiusSquared = 0; // Treat very small negative as zero radius
             }

            double r = Math.sqrt(radiusSquared);

            return new CircleDetailsResponse(h, k, r, inputEqStr, normalizedEqStr);

        } catch (Exception e) {
            // Catch parsing errors or validation errors
            throw new IllegalArgumentException("Invalid equation or not a valid circle: " + e.getMessage(), e);
        }
    }


    /**
     * Calculates the 3x3 determinant of a matrix represented by its elements row by row.
     */
    private static double determinant3x3(double a1, double a2, double a3,
                                         double b1, double b2, double b3,
                                         double c1, double c2, double c3) {
        return a1 * (b2 * c3 - b3 * c2)
             - a2 * (b1 * c3 - b3 * c1)
             + a3 * (b1 * c2 - b2 * c1);
    }

    /**
     * Calculate the equation of a circle given three non-collinear points on its circumference.
     * Uses the determinant method based on the general form Ax^2+Ay^2+Dx+Ey+F=0.
     *
     * @param data Input containing the three Coordinates p, q, r.
     * @return CircleEquationOnlyResponse containing the general form equation string.
     * @throws IllegalArgumentException if points are collinear or input is invalid.
     */
    public static CircleEquationOnlyResponse getCircleFromThreePoints(CircleWThreePointsInput data) {
        Objects.requireNonNull(data, "Input data cannot be null.");
        Coordinates p = data.getP();
        Coordinates q = data.getQ();
        Coordinates r = data.getR();

        double x1 = p.getX(), y1 = p.getY();
        double x2 = q.getX(), y2 = q.getY();
        double x3 = r.getX(), y3 = r.getY();

        // Calculate terms needed for determinants
        double c1 = -(x1 * x1 + y1 * y1);
        double c2 = -(x2 * x2 + y2 * y2);
        double c3 = -(x3 * x3 + y3 * y3);

        // Calculate determinants for coefficients of general form:
        // A_det*(x^2+y^2) + B_det*x + C_det*y + D_det = 0
        double aDet = determinant3x3(x1, y1, 1, x2, y2, 1, x3, y3, 1);
        double bDet = determinant3x3(c1, y1, 1, c2, y2, 1, c3, y3, 1);
        double cDet = determinant3x3(x1, c1, 1, x2, c2, 1, x3, c3, 1);
        double dDet = determinant3x3(x1, y1, c1, x2, y2, c2, x3, y3, c3);

        if (Math.abs(aDet) < EPSILON) {
            throw new IllegalArgumentException("Points are collinear, cannot form a unique circle.");
        }

        // Coefficients for Ax^2 + Ay^2 + Dx + Ey + F = 0
        double coeffA = aDet; // Coeff for x^2 and y^2
        double coeffD = bDet; // Coeff for x
        double coeffE = cDet; // Coeff for y
        double coeffF = dDet; // Constant term

        // Optional: Simplify coefficients by dividing by coeffA (or GCD if integer math was used)
        double normD = coeffD / coeffA;
        double normE = coeffE / coeffA;
        double normF = coeffF / coeffA;

        String equation = formatGeneralEquation(1, 1, normD, normE, normF);

        return new CircleEquationOnlyResponse(equation);
    }

     /**
      * Finds the equation of the circle passing through points p and q
      * with its center on the line Ax + By + C = 0.
      * Solves a 3x3 system of linear equations for g, f, c in x^2+y^2+2gx+2fy+c=0.
      *
      * @param p    First point on the circle.
      * @param q    Second point on the circle.
      * @param line GeneralLineInput (A, B, C) for the line containing the center.
      * @return CircleEquationOnlyResponse containing the circle equation string.
      * @throws IllegalArgumentException if points are identical, solution is not unique, or inputs are invalid.
      */
     public static CircleEquationOnlyResponse getCircleCenterOnLine(Coordinates p, Coordinates q, GeneralLineInput line) {
         Objects.requireNonNull(p, "Point p cannot be null.");
         Objects.requireNonNull(q, "Point q cannot be null.");
         Objects.requireNonNull(line, "Line input cannot be null.");

         double x1 = p.getX(), y1 = p.getY();
         double x2 = q.getX(), y2 = q.getY();
         double A = line.getA(), B = line.getB(), C = line.getC();

         if (Math.abs(x1 - x2) < EPSILON && Math.abs(y1 - y2) < EPSILON) {
             throw new IllegalArgumentException("Points p and q cannot be the same.");
         }

         // System of equations for g, f, c:
         // (Eq1) 2*x1*g + 2*y1*f + c = -(x1^2 + y1^2)
         // (Eq2) 2*x2*g + 2*y2*f + c = -(x2^2 + y2^2)
         // (Eq3) -A*g   - B*f      = -C

         // Solve using Cramer's Rule (or Gaussian elimination)
         // Coefficient matrix M:
         // [ 2*x1, 2*y1, 1 ]
         // [ 2*x2, 2*y2, 1 ]
         // [ -A,   -B,   0 ]
         double detM = determinant3x3(2*x1, 2*y1, 1, 2*x2, 2*y2, 1, -A, -B, 0);

         if (Math.abs(detM) < EPSILON) {
             throw new IllegalArgumentException("Could not find a unique solution. Check points and line (e.g., line might be perpendicular bisector).");
         }

         // Constants vector K:
         // [ -(x1^2 + y1^2) ]
         // [ -(x2^2 + y2^2) ]
         // [ -C             ]
         double k1 = -(x1*x1 + y1*y1);
         double k2 = -(x2*x2 + y2*y2);
         double k3 = -C;

         // Determinant for g (replace g column in M with K)
         double detMg = determinant3x3(k1, 2*y1, 1, k2, 2*y2, 1, k3, -B, 0);
         // Determinant for f (replace f column in M with K)
         double detMf = determinant3x3(2*x1, k1, 1, 2*x2, k2, 1, -A, k3, 0);
          // Determinant for c (replace c column in M with K)
         double detMc = determinant3x3(2*x1, 2*y1, k1, 2*x2, 2*y2, k2, -A, -B, k3);

         double g = detMg / detM;
         double f = detMf / detM;
         double c = detMc / detM;

         // Equation: x^2 + y^2 + 2gx + 2fy + c = 0
         String equation = formatGeneralEquation(1, 1, 2 * g, 2 * f, c);

         return new CircleEquationOnlyResponse(equation);
     }


    /**
     * Calculates the parametric equations of a circle given its general form equation string.
     *
     * @param data EquationInput containing the general form equation string.
     * @return ParametricCircleResponse containing x(t), y(t), center, and radius.
     * @throws IllegalArgumentException if parsing fails or equation is invalid.
     */
    public static ParametricCircleResponse getCircleParametric(EquationInput data) {
        Objects.requireNonNull(data, "Input data cannot be null.");

        // 1. Find center (h, k) and radius (r) from the general equation
        // Reuse the logic from getCircleDetailsFromGeneralForm
        CircleDetailsResponse details = getCircleDetailsFromGeneralForm(new CircleGeneralFormInput(data.getEquation()));
        double h = details.getCenterH();
        double k = details.getCenterK();
        double r = details.getRadius();

        // 2. Generate parametric equation strings
        String xParamStr = String.format("%.4f + %.4f*cos(t)", h, r).replace("+ -", "- ");
        String yParamStr = String.format("%.4f + %.4f*sin(t)", k, r).replace("+ -", "- ");;

        return new ParametricCircleResponse(xParamStr, yParamStr, h, k, r);
    }


    /**
     * Calculates the equation of a circle given the two endpoints of a diameter.
     * Uses the formula (x - x1)(x - x2) + (y - y1)(y - y2) = 0.
     *
     * @param p First endpoint of the diameter.
     * @param q Second endpoint of the diameter.
     * @return CircleEquationOnlyResponse containing the general form equation string.
     * @throws NullPointerException if points are null.
     */
    public static CircleEquationOnlyResponse getCircleFromDiameter(Coordinates p, Coordinates q) {
        Objects.requireNonNull(p, "Point p cannot be null.");
        Objects.requireNonNull(q, "Point q cannot be null.");

        double x1 = p.getX(), y1 = p.getY();
        double x2 = q.getX(), y2 = q.getY();

        // Expand (x - x1)(x - x2) + (y - y1)(y - y2) = 0
        // x^2 - x*x2 - x*x1 + x1*x2 + y^2 - y*y2 - y*y1 + y1*y2 = 0
        // x^2 + y^2 - (x1+x2)x - (y1+y2)y + (x1*x2 + y1*y2) = 0
        double coeffC = -(x1 + x2);
        double coeffD = -(y1 + y2);
        double coeffE = (x1 * x2) + (y1 * y2);

        String equation = formatGeneralEquation(1, 1, coeffC, coeffD, coeffE);
        return new CircleEquationOnlyResponse(equation);
    }

     /**
      * Determines the position of a point relative to a circle given its general equation.
      *
      * @param data EquationInput containing the circle's general equation string.
      * @param point The Coordinates of the point to check.
      * @return PointPositionResponse indicating "inside", "on", or "outside".
      * @throws IllegalArgumentException if parsing fails or equation is invalid.
      */
     public static PointPositionResponse getPointPositionRelativeToCircle(EquationInput data, Coordinates point) {
        Objects.requireNonNull(data, "Equation input cannot be null.");
        Objects.requireNonNull(point, "Point cannot be null.");

        // 1. Find center (h, k) and radius (r)
        CircleDetailsResponse details = getCircleDetailsFromGeneralForm(new CircleGeneralFormInput(data.getEquation()));
        double h = details.getCenterH();
        double k = details.getCenterK();
        double r = details.getRadius();
        double rSquared = r * r;

        // 2. Calculate squared distance from center to the point
        double px = point.getX();
        double py = point.getY();
        double distSq = (px - h) * (px - h) + (py - k) * (py - k);

        // 3. Compare squared distance with squared radius (using tolerance)
        if (Math.abs(distSq - rSquared) < EPSILON) {
            return new PointPositionResponse("on");
        } else if (distSq < rSquared) {
            return new PointPositionResponse("inside");
        } else {
            return new PointPositionResponse("outside");
        }
     }

    // --- Helper Method for Formatting Equations ---

    /**
     * Formats a general equation string Ax^2 + By^2 + Cx + Dy + E = 0 nicely.
     * Assumes A and B are non-zero for circle/ellipse context.
     * Handles zero coefficients and coefficients of 1 or -1.
     *
     * @param A Coefficient of x^2
     * @param B Coefficient of y^2
     * @param C Coefficient of x
     * @param D Coefficient of y
     * @param E Constant term
     * @return Formatted equation string ending in " = 0".
     */
    private static String formatGeneralEquation(double A, double B, double C, double D, double E) {
        StringBuilder sb = new StringBuilder();

        // x^2 term
        if (Math.abs(A) > EPSILON) {
            if (Math.abs(A + 1.0) < EPSILON) sb.append("-");
            else if (Math.abs(A - 1.0) > EPSILON) sb.append(String.format("%.4f*", A));
            sb.append("x^2");
        }

        // y^2 term
        if (Math.abs(B) > EPSILON) {
            appendTerm(sb, B, "y^2");
        }

        // x term
        if (Math.abs(C) > EPSILON) {
             appendTerm(sb, C, "x");
        }

        // y term
        if (Math.abs(D) > EPSILON) {
            appendTerm(sb, D, "y");
        }

        // Constant term
        if (Math.abs(E) > EPSILON) {
            appendTerm(sb, E, "");
        }

        if (sb.length() == 0) {
            return "0 = 0"; // Degenerate case
        }

        // Remove leading " + " if present
        if (sb.toString().startsWith(" + ")) {
             sb.delete(0, 3);
        }

        sb.append(" = 0");
        return sb.toString();
    }

    /** Helper to append a term (e.g., + 5x, - y, - 3.2) to a StringBuilder */
    private static void appendTerm(StringBuilder sb, double coeff, String variable) {
        String sign = (coeff < 0) ? " - " : " + ";
        double absCoeff = Math.abs(coeff);

        if (sb.length() > 0) { // Add sign only if not the first term
             sb.append(sign);
        } else if (coeff < 0) { // Handle negative first term
            sb.append("-");
        }


        boolean coeffIsOne = Math.abs(absCoeff - 1.0) < EPSILON;

        if (!variable.isEmpty()) { // If it's a variable term (x, y, x^2, ...)
            if (!coeffIsOne) {
                sb.append(String.format("%.4f*", absCoeff));
            }
             sb.append(variable);
        } else { // If it's a constant term
            sb.append(String.format("%.4f", absCoeff));
        }
    }
}