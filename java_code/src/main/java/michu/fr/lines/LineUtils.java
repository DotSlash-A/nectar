package michu.fr.lines;

// Make sure imports point to the classes in michu.fr.lines.models
import michu.fr.lines.models.Coordinates;
import michu.fr.lines.models.GeneralLineInput;
import michu.fr.lines.models.LineEquationResult;
import michu.fr.lines.models.SlopeInput;

// import java.util.Map;
import java.util.Objects;

public class LineUtils {

    private static final double EPSILON = 1e-9; // Small value for float comparison

    public static double calculateSlope(Coordinates p1, Coordinates p2) {
        Objects.requireNonNull(p1, "Point 1 cannot be null");
        Objects.requireNonNull(p2, "Point 2 cannot be null");

        // Use getters
        if (Math.abs(p2.getX() - p1.getX()) < EPSILON) {
            throw new IllegalArgumentException("Cannot calculate slope for a vertical line (x1 == x2).");
        }
        // Use getters
        return (p2.getY() - p1.getY()) / (p2.getX() - p1.getX());
    }

    public static double findMissingSlopeVariable(String variableToFind, SlopeInput input) {
        Objects.requireNonNull(variableToFind, "variableToFind cannot be null");
        Objects.requireNonNull(input, "SlopeInput cannot be null");

        // Use getters
        Double x1 = input.getX1();
        Double y1 = input.getY1();
        Double x2 = input.getX2();
        Double y2 = input.getY2();
        Double m = input.getM(); // Assumed to be the tangent value directly

        if (m == null && !variableToFind.equals("m")) {
             throw new IllegalArgumentException("Error: Slope 'm' is required unless finding 'm'.");
        }

        try {
            switch (variableToFind) {
                case "x2":
                    if (y2 == null || y1 == null || x1 == null || m == null) throw new IllegalArgumentException("Missing required values (y2, y1, x1, m) to find 'x2'.");
                    if (Math.abs(m) < EPSILON) throw new IllegalArgumentException("Cannot solve for x2 with zero slope (horizontal line).");
                    return x1 + (y2 - y1) / m;
                case "x1":
                     if (y2 == null || y1 == null || x2 == null || m == null) throw new IllegalArgumentException("Missing required values (y2, y1, x2, m) to find 'x1'.");
                    if (Math.abs(m) < EPSILON) throw new IllegalArgumentException("Cannot solve for x1 with zero slope (horizontal line).");
                    return x2 - (y2 - y1) / m;
                case "y2":
                    if (x2 == null || y1 == null || x1 == null || m == null) throw new IllegalArgumentException("Missing required values (x2, y1, x1, m) to find 'y2'.");
                    return y1 + m * (x2 - x1);
                case "y1":
                    if (x2 == null || y2 == null || x1 == null || m == null) throw new IllegalArgumentException("Missing required values (x2, y2, x1, m) to find 'y1'.");
                    return y2 - m * (x2 - x1);
                case "m":
                    if (x1 == null || y1 == null || x2 == null || y2 == null) throw new IllegalArgumentException("Missing required values (x1, y1, x2, y2) to find 'm'.");
                    if (Math.abs(x2 - x1) < EPSILON) throw new IllegalArgumentException("Cannot calculate slope 'm' when x1 and x2 are equal (vertical line).");
                    return (y2 - y1) / (x2 - x1);
                default:
                    throw new IllegalArgumentException("Invalid value for 'variableToFind'. Must be one of 'x1', 'y1', 'x2', 'y2', 'm'.");
            }
        } catch (ArithmeticException e) {
             throw new IllegalArgumentException("Calculation resulted in division by zero. Check inputs.", e);
        }
     }
    

     // Overload using angle needs similar getter changes for input
     public static double findMissingSlopeVariableWithAngle(String variableToFind, SlopeInput input) {
          Objects.requireNonNull(variableToFind, "variableToFind cannot be null");
          Objects.requireNonNull(input, "SlopeInput cannot be null");
          // Use getter for m
          if (input.getM() == null && !variableToFind.equals("m")) {
               throw new IllegalArgumentException("Error: Slope angle 'm' is required unless finding 'm'.");
          }

          Double tangentM = null;
          // Use getter for m
          if (input.getM() != null) {
              double angleRad = Math.toRadians(input.getM());
              if (Math.abs(Math.cos(angleRad)) < EPSILON) {
                  if (variableToFind.equals("y1") || variableToFind.equals("y2")) {
                      throw new IllegalArgumentException("Cannot solve for y1 or y2 for a vertical line (angle 90/-90 deg).");
                  }
                  tangentM = Double.POSITIVE_INFINITY;
              } else {
                  tangentM = Math.tan(angleRad);
              }
          }

          // Use getters for x1, y1, x2, y2 when creating tangentInput
          SlopeInput tangentInput = new SlopeInput(input.getX1(), input.getY1(), input.getX2(), input.getY2(), tangentM);

          // Vertical line handling - use getters
          if (tangentM != null && Double.isInfinite(tangentM)) {
               Double x1 = input.getX1(); Double x2 = input.getX2();
               // ... rest of vertical line logic ...
                switch(variableToFind) {
                    case "x1":
                        if (x2 == null) throw new IllegalArgumentException("Missing x2 for vertical line case.");
                        return x2; // x1 must equal x2
                    case "x2":
                        if (x1 == null) throw new IllegalArgumentException("Missing x1 for vertical line case.");
                        return x1; // x2 must equal x1
                    case "y1":
                    case "y2":
                        throw new IllegalArgumentException("Cannot solve for y for a vertical line using this method structure easily.");
                    case "m":
                         if (x1 == null || x2 == null) throw new IllegalArgumentException("Missing x1 or x2 to determine vertical line slope.");
                         if (Math.abs(x1-x2) < EPSILON) return Double.POSITIVE_INFINITY; // Or throw? Representing infinite slope.
                         else throw new IllegalArgumentException("Points do not form a vertical line, cannot return infinite slope."); // Should have finite tangent
                    default: throw new IllegalArgumentException("Invalid variableToFind.");
                }
          }

         // If not vertical or finding m when not vertical - use getters
         if (variableToFind.equals("m")) {
              if (input.getX1() == null || input.getY1() == null || input.getX2() == null || input.getY2() == null) {
                  throw new IllegalArgumentException("Missing required values (x1, y1, x2, y2) to find 'm'.");
              }
               if (Math.abs(input.getX2() - input.getX1()) < EPSILON) {
                    throw new IllegalArgumentException("Vertical line slope calculation results in undefined tangent.");
               }
               double slope = (input.getY2() - input.getY1()) / (input.getX2() - input.getX1());
               return Math.toDegrees(Math.atan(slope));
         } else {
             return findMissingSlopeVariable(variableToFind, tangentInput);
         }
     }

    public static LineEquationResult calculateSlopeInterceptForm(Coordinates p1, Coordinates p2, Double slope) {
        double m, b;

        if (slope == null) {
            Objects.requireNonNull(p1, "Point 1 is required when slope is null.");
            Objects.requireNonNull(p2, "Point 2 is required when slope is null.");
            // Use getters
            if (Math.abs(p2.getX() - p1.getX()) < EPSILON) {
                throw new IllegalArgumentException("Cannot determine slope-intercept form for a vertical line.");
            }
            m = calculateSlope(p1, p2);
        } else {
            Objects.requireNonNull(p1, "At least one point (p1) is required when slope is provided.");
            m = slope;
        }

        // Calculate y-intercept - use getters
        b = p1.getY() - m * p1.getX();

        String equation = formatSlopeInterceptEquation(m, b);
        return new LineEquationResult(m, b, equation);
    }

     public static LineEquationResult calculatePerpendicularLine(double newYIntercept, Coordinates p1, Coordinates p2, Double originalSlope) {
          double m_orig;
           if (originalSlope == null) {
               Objects.requireNonNull(p1, "Point 1 is required when originalSlope is null.");
               Objects.requireNonNull(p2, "Point 2 is required when originalSlope is null.");
               // Use getters
               if (Math.abs(p2.getX() - p1.getX()) < EPSILON) {
                   double perpSlope = 0.0;
                   String equation = String.format("y = %.2f", newYIntercept);
                   return new LineEquationResult(perpSlope, newYIntercept, equation);
               }
               m_orig = calculateSlope(p1, p2);
           } else {
               m_orig = originalSlope;
           }

            if (Math.abs(m_orig) < EPSILON) {
                throw new IllegalArgumentException("Original line is horizontal (slope=0), perpendicular line is vertical and cannot be represented in y=mx+b form with a standard y-intercept.");
            }

           double perpSlope = -1.0 / m_orig;
           String equation = formatSlopeInterceptEquation(perpSlope, newYIntercept);
           return new LineEquationResult(perpSlope, newYIntercept, equation);
     }


    public static String getPointSlopeForm(Coordinates point, double slope) {
        Objects.requireNonNull(point, "Point cannot be null.");
        // Use getters
        return String.format("y - %.2f = %.2f(x - %.2f)", point.getY(), slope, point.getX());
    }

    public static String getTwoPointForm(Coordinates p1, Coordinates p2) {
        Objects.requireNonNull(p1, "Point 1 cannot be null.");
        Objects.requireNonNull(p2, "Point 2 cannot be null.");
        double slope = calculateSlope(p1, p2);
        // Use getters for p1
        return String.format("y - %.2f = %.2f(x - %.2f)", p1.getY(), slope, p1.getX());
    }

    public static String getInterceptForm(double xIntercept, double yIntercept) {
        if (Math.abs(xIntercept) < EPSILON || Math.abs(yIntercept) < EPSILON) {
            throw new IllegalArgumentException("Intercepts cannot be zero for the standard intercept form x/a + y/b = 1.");
        }
        return String.format("x / %.2f + y / %.2f = 1", xIntercept, yIntercept);
    }

     public static String getSymmetricForm(double thetaDegrees, Coordinates p1, Coordinates p2) {
         Objects.requireNonNull(p1, "Point 1 cannot be null.");
         Objects.requireNonNull(p2, "Point 2 cannot be null.");

         double thetaRad = Math.toRadians(thetaDegrees);
         double cosTheta = Math.cos(thetaRad);
         double sinTheta = Math.sin(thetaRad);

         if (Math.abs(cosTheta) < EPSILON || Math.abs(sinTheta) < EPSILON) {
              throw new IllegalArgumentException("Symmetric form is ill-defined for horizontal or vertical lines (theta = 0, 90, 180, etc.).");
         }

         // Use getters for distance calculation
         double distance = Math.sqrt(Math.pow(p2.getX() - p1.getX(), 2) + Math.pow(p2.getY() - p1.getY(), 2));

         // Use getters for point coordinates in format string
         return String.format("(x - %.2f) / %.3f = (y - %.2f) / %.3f (= +/-%.2f)",
                              p1.getX(), cosTheta, p1.getY(), sinTheta, distance);
     }

     public static String getNormalForm(double alphaDegrees, Double p, Coordinates pointOnLine) {
         double pValue;
         double alphaRad = Math.toRadians(alphaDegrees);
         double cosAlpha = Math.cos(alphaRad);
         double sinAlpha = Math.sin(alphaRad);

         if (p == null) {
             Objects.requireNonNull(pointOnLine, "pointOnLine is required if p is null.");
             // Calculate p using getters
             pValue = pointOnLine.getX() * cosAlpha + pointOnLine.getY() * sinAlpha;
             if (pValue < -EPSILON) {
                  System.err.println("Warning: Calculated 'p' is negative. Standard normal form requires p >= 0. Adjust alpha accordingly if needed.");
             } else if (Math.abs(pValue) < EPSILON) {
                 pValue = 0.0;
             }
         } else {
             if (p < -EPSILON) {
                 throw new IllegalArgumentException("Distance 'p' in normal form must be non-negative.");
             }
              pValue = p;
         }

         return String.format("x * cos(%.1f°) + y * sin(%.1f°) = %.3f", alphaDegrees, alphaDegrees, pValue);
     }

      public static String transformGeneralToSlopeIntercept(GeneralLineInput input) {
          Objects.requireNonNull(input, "GeneralLineInput cannot be null.");
          // Use getters
          double a = input.getA();
          double b = input.getB();
          double c = input.getC();

          if (Math.abs(b) < EPSILON) {
              if (Math.abs(a) < EPSILON) {
                   return (Math.abs(c) < EPSILON) ? "Degenerate line (0 = 0)" : "Invalid line (non-zero constant = 0)";
              }
              return String.format("Vertical line: x = %.2f", -c / a);
          }

          double m = -a / b;
          double yIntercept = -c / b;
          return formatSlopeInterceptEquation(m, yIntercept);
      }

       public static String transformGeneralToInterceptForm(GeneralLineInput input) {
           Objects.requireNonNull(input, "GeneralLineInput cannot be null.");
           // Use getters
           double a = input.getA();
           double b = input.getB();
           double c = input.getC();

           if (Math.abs(c) < EPSILON) {
               throw new IllegalArgumentException("Line passes through the origin (C=0), intercept form x/a + y/b = 1 is undefined.");
           }
           if (Math.abs(a) < EPSILON || Math.abs(b) < EPSILON) {
                throw new IllegalArgumentException("Line is parallel to an axis (A=0 or B=0), intercept form x/a + y/b = 1 is undefined.");
           }

           double xIntercept = -c / a;
           double yIntercept = -c / b;
           return getInterceptForm(xIntercept, yIntercept);
       }

    // --- Helper Method (no changes needed here) ---
    private static String formatSlopeInterceptEquation(double m, double b) {
        // ... (same as before) ...
        String slopeTerm;
        String interceptTerm;

        // Format slope (m)
        if (Math.abs(m) < EPSILON) {
            slopeTerm = ""; // Horizontal line
        } else if (Math.abs(m - 1.0) < EPSILON) {
            slopeTerm = "x";
        } else if (Math.abs(m + 1.0) < EPSILON) {
            slopeTerm = "-x";
        } else {
            slopeTerm = String.format("%.2fx", m);
        }

        // Format intercept (b)
        if (Math.abs(b) < EPSILON) {
            interceptTerm = "";
        } else {
            interceptTerm = String.format("%s %.2f", (b > 0 ? "+ " : "- "), Math.abs(b));
        }

        // Combine terms
        if (slopeTerm.isEmpty() && interceptTerm.isEmpty()) {
            return "y = 0"; // Should only happen if m=0 and b=0
        } else if (slopeTerm.isEmpty()) {
             return String.format("y = %.2f", b); // Direct formatting of b handles sign
        } else if (interceptTerm.isEmpty()) {
            return "y = " + slopeTerm;
        } else {
            return "y = " + slopeTerm + " " + interceptTerm;
        }
    }
}