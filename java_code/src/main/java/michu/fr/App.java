// File: src/main/java/michu/fr/App.java
package michu.fr;

// Ensure imports point to the classes in michu.fr.lines.models
import michu.fr.lines.LineUtils;
import michu.fr.lines.models.Coordinates;
import michu.fr.lines.models.GeneralLineInput;
import michu.fr.lines.models.LineEquationResult;
import michu.fr.lines.models.SlopeInput;
import michu.fr.matrix.models.AdjInvResponse;
import michu.fr.matrix.models.ConstructedMatrixResponse;
import michu.fr.matrix.models.DetInput;
import michu.fr.matrix.models.DeterminantResponseAPI;
import michu.fr.matrix.models.MatrixEqualityResponse;
import michu.fr.matrix.models.MatrixFormulaInput;
import michu.fr.matrix.models.MatrixInputAPI;
import michu.fr.matrix.models.MatrixResponse;
import michu.fr.matrix.models.MinorsCofactorsResponse;
import michu.fr.matrix.models.TwoMatrixInput;
import michu.fr.circles.CircleUtils;
import michu.fr.circles.models.*;
// import michu.fr.lines.models.Coordinates; // Reusing Coordinates
// import michu.fr.lines.models.GeneralLineInput; // Reusing GeneralLineInput
import michu.fr.limits.LimitUtils;
import michu.fr.limits.models.LimitRequest;
import michu.fr.limits.models.LimitResponse;
import michu.fr.matrix.MatrixUtils;
// import michu.fr.matrix.models.*;

import java.util.Arrays;
import java.util.List;
// import java.util.ArrayList;


// import java.util.HashMap;

// import java.util.Map;

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



           System.out.println("\n--- Matrix Calculations ---");

        // Example M1: Determinant
        try {
            List<List<Double>> matList1 = Arrays.asList(
                Arrays.asList(1.0, 2.0),
                Arrays.asList(3.0, 4.0)
            );
            DetInput detInput = new DetInput(matList1);
            DeterminantResponseAPI detResp = MatrixUtils.calculateDeterminant(detInput);
            System.out.printf("Determinant of %s: %.4f%n", matList1, detResp.getDeterminant()); // Expected: -2.0

            List<List<Double>> matList2 = Arrays.asList(
                Arrays.asList(6.0, 1.0, 1.0),
                Arrays.asList(4.0, -2.0, 5.0),
                Arrays.asList(2.0, 8.0, 7.0)
            );
             DetInput detInput2 = new DetInput(matList2);
            DeterminantResponseAPI detResp2 = MatrixUtils.calculateDeterminant(detInput2);
            System.out.printf("Determinant of %s: %.4f%n", matList2, detResp2.getDeterminant()); // Expected: -306.0
        } catch (IllegalArgumentException e) {
            System.err.println("Error M1: " + e.getMessage());
        }

        // Example M2: Matrix Equality
        try {
            List<List<Double>> matA = Arrays.asList(Arrays.asList(1.0, 0.0), Arrays.asList(0.0, 1.0));
            List<List<Double>> matB = Arrays.asList(Arrays.asList(1.0, 0.0), Arrays.asList(0.0, 1.0));
            List<List<Double>> matC = Arrays.asList(Arrays.asList(1.0, 0.0), Arrays.asList(0.0, 2.0));
             List<List<Double>> matD = Arrays.asList(Arrays.asList(1.0, 0.0)); // Different dims

            TwoMatrixInput inputAB = new TwoMatrixInput(matA, matB);
            TwoMatrixInput inputAC = new TwoMatrixInput(matA, matC);
            TwoMatrixInput inputAD = new TwoMatrixInput(matA, matD);

            MatrixEqualityResponse respAB = MatrixUtils.compareMatrices(inputAB);
            MatrixEqualityResponse respAC = MatrixUtils.compareMatrices(inputAC);
            MatrixEqualityResponse respAD = MatrixUtils.compareMatrices(inputAD);

            System.out.printf("Compare A vs B: %s (%s)%n", respAB.areEqual(), respAB.getReason()); // true
            System.out.printf("Compare A vs C: %s (%s)%n", respAC.areEqual(), respAC.getReason()); // false (mismatch)
            System.out.printf("Compare A vs D: %s (%s)%n", respAD.areEqual(), respAD.getReason()); // false (dims)

        } catch (Exception e) { // Catch broader exceptions if needed
             System.err.println("Error M2: " + e.getMessage());
        }

         // Example M3: Construct from Formula
         try {
             MatrixFormulaInput formulaInput = new MatrixFormulaInput(2, 3, "i + 2*j"); // 2x3 matrix
             ConstructedMatrixResponse formulaResp = MatrixUtils.constructMatrixFromFormula(formulaInput);
             System.out.printf("Matrix from formula '%s' (%dx%d):%n%s%n",
                 formulaResp.getFormulaUsed(), formulaResp.getRows(), formulaResp.getColumns(),
                 formulaResp.getConstructedMatrix());
             // Expected: [[3.0, 5.0, 7.0], [4.0, 6.0, 8.0]]
         } catch ( RuntimeException e) {
             System.err.println("Error M3: " + e.getMessage());
         }

        // Example M4: Addition
        try {
            List<List<Double>> addA = Arrays.asList(Arrays.asList(1.0, 2.0), Arrays.asList(3.0, 4.0));
            List<List<Double>> addB = Arrays.asList(Arrays.asList(5.0, 6.0), Arrays.asList(7.0, 8.0));
            TwoMatrixInput addInput = new TwoMatrixInput(addA, addB);
            MatrixResponse addResp = MatrixUtils.addMatricesAPI(addInput);
            System.out.printf("%s + %s = %s%n", addA, addB, addResp.getResultMatrix());
             // Expected: [[6.0, 8.0], [10.0, 12.0]]
        } catch (IllegalArgumentException e) {
            System.err.println("Error M4: " + e.getMessage());
        }

        // Example M5: Scalar Multiply
        try {
            List<List<Double>> scalarMatList = Arrays.asList(Arrays.asList(1.0, 2.0), Arrays.asList(3.0, 4.0));
            MatrixInputAPI scalarMatInput = new MatrixInputAPI(scalarMatList);
            double scalar = 3.0;
            MatrixResponse scalarResp = MatrixUtils.multiplyMatrixByScalarAPI(scalarMatInput, scalar);
            System.out.printf("%.1f * %s = %s%n", scalar, scalarMatList, scalarResp.getResultMatrix());
            // Expected: [[3.0, 6.0], [9.0, 12.0]]
        } catch (IllegalArgumentException e) {
            System.err.println("Error M5: " + e.getMessage());
        }

        // Example M6: Matrix Multiply
        try {
            List<List<Double>> mulA = Arrays.asList(Arrays.asList(1.0, 2.0)); // 1x2
            List<List<Double>> mulB = Arrays.asList(Arrays.asList(3.0), Arrays.asList(4.0)); // 2x1
            TwoMatrixInput mulInput = new TwoMatrixInput(mulA, mulB);
            MatrixResponse mulResp = MatrixUtils.multiplyMatricesAPI(mulInput);
            System.out.printf("%s * %s = %s%n", mulA, mulB, mulResp.getResultMatrix());
             // Expected: [[1*3 + 2*4]] = [[11.0]]
        } catch (IllegalArgumentException e) {
             System.err.println("Error M6: " + e.getMessage());
        }

        // Example M7: Transpose
        try {
             List<List<Double>> transMatList = Arrays.asList(Arrays.asList(1.0, 2.0, 3.0), Arrays.asList(4.0, 5.0, 6.0)); // 2x3
             MatrixInputAPI transInput = new MatrixInputAPI(transMatList);
             MatrixResponse transResp = MatrixUtils.transposeMatrixAPI(transInput);
             System.out.printf("Transpose of %s is %s%n", transMatList, transResp.getResultMatrix());
             // Expected: [[1.0, 4.0], [2.0, 5.0], [3.0, 6.0]] (3x2)
        } catch (IllegalArgumentException e) {
            System.err.println("Error M7: " + e.getMessage());
        }

         // Example M8: Minors/Cofactors
         try {
            List<List<Double>> minorMatList = Arrays.asList(
                Arrays.asList(1.0, 2.0, 3.0),
                Arrays.asList(0.0, 4.0, 5.0),
                Arrays.asList(1.0, 0.0, 6.0)
            );
            DetInput minorInput = new DetInput(minorMatList);
            MinorsCofactorsResponse minorResp = MatrixUtils.calculateMinorsAndCofactors(minorInput);
            System.out.printf("For Matrix: %s%n", minorMatList);
            System.out.printf("  Minors: %s%n", minorResp.getMatrixOfMinors());
            // Expected Minors: [[24, -5, -4], [12, 3, -2], [-2, 5, 4]]
            System.out.printf("  Cofactors: %s%n", minorResp.getMatrixOfCofactors());
             // Expected Cofactors: [[24, 5, -4], [-12, 3, 2], [-2, -5, 4]]
            System.out.printf("  Determinant: %.4f%n", minorResp.getDeterminant()); // Expected: 22
         } catch (IllegalArgumentException e) {
             System.err.println("Error M8: " + e.getMessage());
         }

          // Example M9: Adjoint/Inverse
          try {
            // Use the same matrix as M8, determinant is 22
            List<List<Double>> invMatList = Arrays.asList(
                 Arrays.asList(1.0, 2.0, 3.0),
                 Arrays.asList(0.0, 4.0, 5.0),
                 Arrays.asList(1.0, 0.0, 6.0)
             );
             MatrixInputAPI invInput = new MatrixInputAPI(invMatList);
             AdjInvResponse invResp = MatrixUtils.calculateAdjointAndInverse(invInput);
             System.out.printf("For Matrix: %s%n", invMatList);
             System.out.printf("  Determinant: %.4f%n", invResp.getDeterminant());
             System.out.printf("  Is Invertible: %s%n", invResp.isInvertible());
             System.out.printf("  Adjoint: %s%n", invResp.getAdjointMatrix());
             // Expected Adjoint (Transpose of Cofactors): [[24, -12, -2], [5, 3, -5], [-4, 2, 4]]
             System.out.printf("  Inverse: %s%n", invResp.getInverseMatrix());
             // Expected Inverse: Adjoint / 22
          } catch (IllegalArgumentException e) {
              System.err.println("Error M9: " + e.getMessage());
          }
          
          System.out.println("--------------------------------------------------");
          System.out.println("\n--- Limit Calculations (Numerical Approximation) ---");

        // Test cases
        runLimitTest("(x^2 - 1)/(x - 1)", "x", "1");       // Expected: 2 (removable discontinuity)
        runLimitTest("sin(x)/x", "x", "0");                // Expected: 1
        runLimitTest("(1 + 1/x)^x", "x", "inf");           // Expected: e (approx 2.71828)
        runLimitTest("1/x", "x", "0");                     // Expected: Does Not Exist (opposite infinities)
        runLimitTest("1/x^2", "x", "0");                   // Expected: Infinity
        runLimitTest("sin(1/x)", "x", "0");                // Expected: Does Not Exist (oscillation)
        runLimitTest("x*sin(1/x)", "x", "0");              // Expected: 0 (Squeeze theorem)
        runLimitTest("abs(x)/x", "x", "0");                // Expected: Does Not Exist (left=-1, right=1)
        runLimitTest("x / sqrt(x**2 + 1)", "x", "inf");    // Expected: 1
        runLimitTest("x / sqrt(x**2 + 1)", "x", "-inf");   // Expected: -1
        runLimitTest("ln(x)", "x", "0");                   // Expected: -Infinity (evaluates right side only effectively)
        runLimitTest("invalid syntax (", "x", "1");       // Expected: Expression Error
        runLimitTest("x", "x", "invalid_limit");           // Expected: Input Error

    } // end main

    public static void runLimitTest(String expr, String var, String tendingTo) {
        System.out.printf("Calculating limit of [%s] as %s -> %s:%n", expr, var, tendingTo);
        try {
            LimitRequest request = new LimitRequest(expr, var, tendingTo);
            LimitResponse response = LimitUtils.calculateLimitApprox(request);
            System.out.printf("  Result: %s (%s)%n", response.getLimitResult(), response.getExplanation());
        } catch (Exception e) { // Catch request creation errors too
             System.err.printf("  ERROR creating request/calculating limit: %s%n", e.getMessage());
        }
         System.out.println("--------------------------------------------------");
 
    }
}