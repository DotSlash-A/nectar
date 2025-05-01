// File: src/main/java/michu/fr/App.java
package michu.fr;

// Ensure imports point to the classes in michu.fr.lines.models
import michu.fr.lines.LineUtils;
import michu.fr.lines.models.Coordinates;
import michu.fr.lines.models.GeneralLineInput;
import michu.fr.lines.models.LineEquationResult;
import michu.fr.lines.models.SlopeInput;

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
    }
}