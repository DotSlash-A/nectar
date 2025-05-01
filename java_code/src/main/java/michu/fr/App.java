// File: src/main/java/michu/fr/App.java
package michu.fr;

// Ensure imports point to the classes in michu.fr.lines.models
import michu.fr.lines.LineUtils;
import michu.fr.lines.models.Coordinates;
import michu.fr.lines.models.GeneralLineInput;
import michu.fr.lines.models.LineEquationResult;
import michu.fr.lines.models.SlopeInput;

import michu.fr.circles.CircleUtils;
import michu.fr.circles.models.*;
import michu.fr.lines.models.Coordinates; // Reusing Coordinates
import michu.fr.lines.models.GeneralLineInput; // Reusing GeneralLineInput



import java.util.HashMap;
import java.util.Map;

public class App {
    public static void main(String[] args) {
        System.out.println("--- Line Calculations ---");

        Coordinates p1 = new Coordinates(1, 2);
        Coordinates p2 = new Coordinates(4, 8);
        try {
            double slope = LineUtils.calculateSlope(p1, p2);
            // toString() method handles printing p1, p2 nicely
            System.out.printf("Slope between %s and %s: %.2f%n", p1, p2, slope);
        } catch (IllegalArgumentException e) {
            System.err.println("Error calculating slope: " + e.getMessage());
        }
         Coordinates p3 = new Coordinates(1, 5);
         try {
             LineUtils.calculateSlope(p1, p3);
         } catch (IllegalArgumentException e) {
              System.err.println("Error calculating slope: " + e.getMessage());
         }

        SlopeInput input = new SlopeInput(1.0, 2.0, 4.0, null, 2.0); // Find y2
        try {
            double y2 = LineUtils.findMissingSlopeVariable("y2", input);
            // Use getters for printing input values
            System.out.printf("Find y2: Given x1=%.1f, y1=%.1f, x2=%.1f, m=%.1f -> y2 = %.2f%n",
                              input.getX1(), input.getY1(), input.getX2(), input.getM(), y2);
        } catch (IllegalArgumentException e) {
             System.err.println("Error finding variable: " + e.getMessage());
        }

        try {
            LineEquationResult result = LineUtils.calculateSlopeInterceptForm(p1, p2, null);
             // Use getter for equation; toString() handles printing p1, p2
            System.out.printf("Slope-Intercept from %s and %s: %s%n", p1, p2, result.getEquation());
        } catch (IllegalArgumentException | NullPointerException e) {
            System.err.println("Error getting slope-intercept: " + e.getMessage());
        }

        try {
            String twoPointEq = LineUtils.getTwoPointForm(p1, p2);
             // toString() handles printing p1, p2
            System.out.printf("Two-Point form for %s and %s: %s%n", p1, p2, twoPointEq);
        } catch (IllegalArgumentException | NullPointerException e) {
             System.err.println("Error getting two-point form: " + e.getMessage());
        }

         try {
              LineEquationResult perpResult = LineUtils.calculatePerpendicularLine(5.0, p1, p2, null);
              // Use getter for equation; toString() handles printing p1, p2
              System.out.printf("Perpendicular to line through %s, %s with y-int=5: %s%n", p1, p2, perpResult.getEquation());
         } catch (IllegalArgumentException | NullPointerException e) {
              System.err.println("Error getting perpendicular line: " + e.getMessage());
         }

        GeneralLineInput generalInput = new GeneralLineInput(2, 4, -8);
        String slopeInterceptEq = LineUtils.transformGeneralToSlopeIntercept(generalInput);
         // toString() handles printing generalInput
        System.out.printf("General %s to Slope-Intercept: %s%n", generalInput, slopeInterceptEq);

         try {
            String interceptEq = LineUtils.transformGeneralToInterceptForm(generalInput);
             // toString() handles printing generalInput
             System.out.printf("General %s to Intercept: %s%n", generalInput, interceptEq);
         } catch (IllegalArgumentException e) {
              System.err.println("Error transforming to intercept form: " + e.getMessage());
         }

        String normalEq = LineUtils.getNormalForm(53.1, 2.0, null);
        System.out.printf("Normal Form (alpha=53.1, p=2): %s%n", normalEq);


         // --- Circle Calculations ---
         System.out.println("\n--- Circle Calculations ---");

         // Example C1: Circle Eq from Center/Radius
         try {
             CircleGeneralInput circleInput = new CircleGeneralInput(2.0, -3.0, 5.0); // h=2, k=-3, r=5
             CircleEqnResponse circleEqs = CircleUtils.getCircleEquationsFromCenterRadius(circleInput);
             System.out.println("Circle from h=2, k=-3, r=5:");
             System.out.println("  Standard Form: " + circleEqs.getStandardForm());
             // Expected: (x - 2.0000)^2 + (y + 3.0000)^2 = 25.0000
             System.out.println("  General Form: " + circleEqs.getGeneralForm());
             // Expected: x^2 + y^2 - 4.0000*x + 6.0000*y - 12.0000 = 0
             System.out.println("  Coeffs (A,B,C,D,E): " + String.format("%.1f, %.1f, %.1f, %.1f, %.1f",
                 circleEqs.getCoeffA(), circleEqs.getCoeffB(), circleEqs.getCoeffC(), circleEqs.getCoeffD(), circleEqs.getCoeffE()));
         } catch (IllegalArgumentException e) {
             System.err.println("Error C1: " + e.getMessage());
         }
 
         // Example C2: Circle Details from General Form
         try {
             // String eqStr = "x^2 + y^2 - 4*x + 6*y - 12 = 0";
              String eqStr = "2x^2 + 2y^2 + 8x - 12y + 6 = 0"; // Test normalization
             CircleDetailsResponse details = CircleUtils.getCircleDetailsFromGeneralForm(new CircleGeneralFormInput(eqStr));
             System.out.printf("Circle Details from '%s':%n", eqStr);
             System.out.printf("  Center (h, k): (%.4f, %.4f)%n", details.getCenterH(), details.getCenterK());
             // Expected for normalized: (-2, 3)
             System.out.printf("  Radius r: %.4f%n", details.getRadius());
             // Expected for normalized: r^2 = (-2)^2 + 3^2 - 3 = 4+9-3=10 => r=sqrt(10) approx 3.1623
             System.out.println("  Normalized Eq: " + details.getNormalizedEquation());
              // Expected: x^2 + y^2 + 4.0000*x - 6.0000*y + 3.0000 = 0
         } catch (IllegalArgumentException e) {
              System.err.println("Error C2: " + e.getMessage());
         }
 
         // Example C3: Circle from 3 Points
         try {
             Coordinates c3p1 = new Coordinates(1, 1);
             Coordinates c3p2 = new Coordinates(2, 4);
             Coordinates c3p3 = new Coordinates(5, 3);
             CircleWThreePointsInput threePoints = new CircleWThreePointsInput(c3p1, c3p2, c3p3);
             CircleEquationOnlyResponse eq3pts = CircleUtils.getCircleFromThreePoints(threePoints);
             System.out.printf("Circle from %s, %s, %s:%n  %s%n", c3p1, c3p2, c3p3, eq3pts.getCircleEquation());
              // Expected: x^2 + y^2 - 6.0000*x - 2.0000*y + 5.0000 = 0 (Center 3,1 Radius sqrt(5))
         } catch (IllegalArgumentException e) {
              System.err.println("Error C3: " + e.getMessage());
         }
 
         // Example C4: Circle from Diameter Endpoints
         try {
             Coordinates diamP1 = new Coordinates(1, 2);
             Coordinates diamP2 = new Coordinates(5, 6);
             CircleEquationOnlyResponse eqDiam = CircleUtils.getCircleFromDiameter(diamP1, diamP2);
             System.out.printf("Circle with diameter %s to %s:%n  %s%n", diamP1, diamP2, eqDiam.getCircleEquation());
              // Expected: (x-1)(x-5) + (y-2)(y-6) = 0 => x^2-6x+5 + y^2-8y+12 = 0 => x^2 + y^2 - 6x - 8y + 17 = 0
              // Output: x^2 + y^2 - 6.0000*x - 8.0000*y + 17.0000 = 0
         } catch (NullPointerException e) {
             System.err.println("Error C4: " + e.getMessage());
         }
 
         // Example C5: Parametric Equations from General Form
         try {
             EquationInput eqnInput = new EquationInput("x^2 + y^2 - 6x - 2y + 5 = 0"); // Center (3,1), r=sqrt(5)
             ParametricCircleResponse paraResp = CircleUtils.getCircleParametric(eqnInput);
             System.out.printf("Parametric for '%s':%n", eqnInput.getEquation());
             System.out.println("  x(t) = " + paraResp.getParametricX()); // Expected: 3.0000 + 2.2361*cos(t)
             System.out.println("  y(t) = " + paraResp.getParametricY()); // Expected: 1.0000 + 2.2361*sin(t)
         } catch (IllegalArgumentException e) {
             System.err.println("Error C5: " + e.getMessage());
         }
 
          // Example C6: Point Position Relative to Circle
          try {
              EquationInput circleEqForPos = new EquationInput("x^2 + y^2 - 4x = 0"); // Center (2,0), r=2
              Coordinates pointInside = new Coordinates(1, 0);
              Coordinates pointOn = new Coordinates(4, 0);
              Coordinates pointOutside = new Coordinates(5, 5);
              PointPositionResponse posIn = CircleUtils.getPointPositionRelativeToCircle(circleEqForPos, pointInside);
              PointPositionResponse posOn = CircleUtils.getPointPositionRelativeToCircle(circleEqForPos, pointOn);
              PointPositionResponse posOut = CircleUtils.getPointPositionRelativeToCircle(circleEqForPos, pointOutside);
              System.out.printf("Point %s relative to %s: %s%n", pointInside, circleEqForPos.getEquation(), posIn.getPosition()); // Expected: inside
              System.out.printf("Point %s relative to %s: %s%n", pointOn, circleEqForPos.getEquation(), posOn.getPosition());     // Expected: on
              System.out.printf("Point %s relative to %s: %s%n", pointOutside, circleEqForPos.getEquation(), posOut.getPosition());// Expected: outside
          } catch (IllegalArgumentException e) {
              System.err.println("Error C6: " + e.getMessage());
          }
 
          // Example C7: Circle Center On Line
          try {
             Coordinates p_c7 = new Coordinates(1, 0);
             Coordinates q_c7 = new Coordinates(3, 0); // Points on x-axis
             GeneralLineInput line_c7 = new GeneralLineInput(0, 1, -2); // Line y=2 (0x + 1y - 2 = 0)
             // Center must be (2, y_c). Line says y_c = 2. Center (2, 2).
             // Radius = distance from (2,2) to (1,0) = sqrt((2-1)^2 + (2-0)^2) = sqrt(1+4) = sqrt(5)
             // Eq: (x-2)^2 + (y-2)^2 = 5 => x^2-4x+4 + y^2-4y+4 = 5 => x^2 + y^2 - 4x - 4y + 3 = 0
             CircleEquationOnlyResponse resp_c7 = CircleUtils.getCircleCenterOnLine(p_c7, q_c7, line_c7);
             System.out.printf("Circle through %s, %s with center on y=2:%n  %s%n", p_c7, q_c7, resp_c7.getCircleEquation());
             // Expected: x^2 + y^2 - 4.0000*x - 4.0000*y + 3.0000 = 0
          } catch (IllegalArgumentException e) {
              System.err.println("Error C7: " + e.getMessage());
          }
 
    }
}