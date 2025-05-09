package michu.fr.threedgeometry;

import michu.fr.threedgeometry.models.*;

import java.util.ArrayList;
import java.util.List;

public class ThreeDGeometryExamples {
    public static void main(String[] args) {
        System.out.println("--- 3D Geometry Examples (Updated) ---");

        // --- Vector Algebra ---
        System.out.println("\n-- Vector Algebra --");
        Vector3D v1 = new Vector3D(1, 2, 3);
        Vector3D v2 = new Vector3D(4, 5, 6);
        System.out.println("v1 = " + v1);
        System.out.println("v2 = " + v2);
        System.out.println("v1 + v2 = " + ThreeDGeometryUtils.addVectors(v1, v2));
        System.out.println("Magnitude of v1: " + ThreeDGeometryUtils.vectorMagnitude(v1));
        try {
            System.out.println("Unit vector of v1: " + ThreeDGeometryUtils.unitVector(v1));
        } catch (IllegalArgumentException e) { System.out.println("Error: " + e.getMessage()); }

        Point3D pA = new Point3D(1,0,-1);
        Point3D pB = new Point3D(3,2,1);
        System.out.println("Vector from pA to pB: " + ThreeDGeometryUtils.vectorFromTwoPoints(pA, pB));
        System.out.println("Section formula (internal m=2,n=3 for pA,pB): " + ThreeDGeometryUtils.sectionFormula(pA, pB, 2, 3, true));
        
        List<Point3D> collinearPoints = new ArrayList<>();
        collinearPoints.add(new Point3D(1,2,3));
        collinearPoints.add(new Point3D(2,3,4));
        collinearPoints.add(new Point3D(3,4,5));
        System.out.println("Collinearity of (1,2,3),(2,3,4),(3,4,5): " + ThreeDGeometryUtils.checkCollinearityPoints(collinearPoints));
        
        List<Point3D> nonCollinearPoints = new ArrayList<>(collinearPoints);
        nonCollinearPoints.add(new Point3D(3,4,6)); // Changed z
        System.out.println("Collinearity of (1,2,3),(2,3,4),(3,4,5),(3,4,6): " + ThreeDGeometryUtils.checkCollinearityPoints(nonCollinearPoints));


        // --- Dot and Cross Product ---
        System.out.println("\n-- Dot and Cross Product --");
        Vector3D dp_v1 = new Vector3D(1, -1, 2);
        Vector3D dp_v2 = new Vector3D(2, 3, -1);
        System.out.println("Dot product of " + dp_v1 + " and " + dp_v2 + ": " + ThreeDGeometryUtils.dotProduct(dp_v1, dp_v2));
        System.out.println("Projection of " + dp_v1 + " on " + dp_v2 + ": " + ThreeDGeometryUtils.projectionVectorOnVector(dp_v1, dp_v2));

        Vector3D cp_v1 = new Vector3D(2, 1, -1);
        Vector3D cp_v2 = new Vector3D(1, -1, 2);
        System.out.println("Cross product of " + cp_v1 + " and " + cp_v2 + ": " + ThreeDGeometryUtils.crossProduct(cp_v1, cp_v2));

        Point3D t_p1 = new Point3D(1,1,1); Point3D t_p2 = new Point3D(1,2,3); Point3D t_p3 = new Point3D(2,3,1);
        System.out.println("Area of triangle (P1,P2,P3): " + ThreeDGeometryUtils.areaTrianglePoints(t_p1,t_p2,t_p3));
        
        Vector3D stp_a = new Vector3D(1,0,0); Vector3D stp_b = new Vector3D(0,1,0); Vector3D stp_c = new Vector3D(0,0,1);
        System.out.println("Scalar Triple Product of i,j,k: " + ThreeDGeometryUtils.scalarTripleProduct(stp_a,stp_b,stp_c));
        Vector3D stp_c_coplanar = new Vector3D(1,1,0); // a,b,c_coplanar are coplanar
        System.out.println("Scalar Triple Product of i,j,i+j: " + ThreeDGeometryUtils.scalarTripleProduct(stp_a,stp_b,stp_c_coplanar));


        // --- Direction Cosines/Ratios ---
        System.out.println("\n-- Direction Cosines & Ratios --");
        Vector3D dir_v = new Vector3D(1, 2, 2);
        DirectionRatios dr = ThreeDGeometryUtils.directionRatiosFromVector(dir_v);
        System.out.println("DR for " + dir_v + ": " + dr);
        System.out.println("DC for DR " + dr + ": " + ThreeDGeometryUtils.directionCosinesFromRatios(dr));
        System.out.println("DC for vector " + dir_v + ": " + ThreeDGeometryUtils.directionCosinesFromVector(dir_v));

        // --- Straight Line ---
        System.out.println("\n-- Straight Line --");
        Point3D line_p0 = new Point3D(1,2,3); Vector3D line_dir = new Vector3D(2,3,4);
        LineEquationResult lineVecForm = ThreeDGeometryUtils.lineEqVectorForm(line_p0, line_dir);
        System.out.println("Line (Vector Form): " + lineVecForm);
        DirectionRatios line_dr_cart = new DirectionRatios(2,0,4);
        System.out.println("Line (Cartesian Symm Form DR <2,0,4>): " + ThreeDGeometryUtils.lineEqCartesianSymmetric(line_p0, line_dr_cart));
        
        Point3D l2p1 = new Point3D(1,1,0); Point3D l2p2 = new Point3D(2,0,2);
        List<LineEquationResult> lineEqs2pts = ThreeDGeometryUtils.lineEqFromTwoPoints(l2p1, l2p2);
        System.out.println("Line from 2 points (Vector): " + lineEqs2pts.get(0));
        System.out.println("Line from 2 points (Cartesian): " + lineEqs2pts.get(1));

        Vector3D line1_d = new Vector3D(1,1,0); Vector3D line2_d = new Vector3D(1,-1,1);
        System.out.println("Angle between lines with dir " + line1_d + " and " + line2_d + ": " + ThreeDGeometryUtils.angleBetweenLines(line1_d, line2_d));

        Point3D l1_p = new Point3D(1,2,3); Vector3D l1_v = new Vector3D(1,-1,1);
        Point3D l2_p = new Point3D(2,1,0); Vector3D l2_v = new Vector3D(2,1,2); // Skew lines
        System.out.println("Shortest distance L1 & L2 (skew): " + ThreeDGeometryUtils.shortestDistanceBetweenLines(l1_p, l1_v, l2_p, l2_v));
        
        Point3D l3_p = new Point3D(0,0,0); Vector3D l3_v = new Vector3D(1,1,1);
        Point3D l4_p = new Point3D(1,1,1); Vector3D l4_v = new Vector3D(2,2,2); // Parallel
        System.out.println("Shortest distance L3 & L4 (parallel): " + ThreeDGeometryUtils.shortestDistanceBetweenLines(l3_p, l3_v, l4_p, l4_v));

        Point3D distPtLine_pt = new Point3D(1,0,0);
        Point3D distPtLine_linePt = new Point3D(0,0,0); Vector3D distPtLine_lineDir = new Vector3D(0,1,0); // y-axis
        System.out.println("Distance from (1,0,0) to y-axis: " + ThreeDGeometryUtils.distancePointLine(distPtLine_pt, distPtLine_linePt, distPtLine_lineDir));

        // --- Plane ---
        System.out.println("\n-- Plane --");
        Vector3D plane_n_unit = new Vector3D(0,0,1);
        System.out.println("Plane (Vector Normal Form, n=k, d=5): " + ThreeDGeometryUtils.planeEqVectorNormalForm(plane_n_unit, 5));
        
        Vector3D plane_n = new Vector3D(2,-3,4); Point3D plane_p = new Point3D(1,1,1);
        PlaneEquationResult planeCartNormPt = ThreeDGeometryUtils.planeEqCartesianFromNormalPoint(plane_n, plane_p);
        System.out.println("Plane (Cartesian from Normal & Point): " + planeCartNormPt);
        
        PlaneEquationCoefficients planeCoeffs1 = new PlaneEquationCoefficients(2,-3,4, -plane_n.dot(plane_p.toVector3D())); // 2x-3y+4z - 3 = 0
        System.out.println("Plane (from coeffs 2x-3y+4z-3=0): " + ThreeDGeometryUtils.planeEqFromCoefficients(planeCoeffs1));

        Point3D pl_p1=new Point3D(1,0,0); Point3D pl_p2=new Point3D(0,1,0); Point3D pl_p3=new Point3D(0,0,1);
        PlaneEquationResult plane3pts = ThreeDGeometryUtils.planeEqFromThreePoints(pl_p1,pl_p2,pl_p3); // x+y+z-1=0
        System.out.println("Plane (from 3 points P1,P2,P3): " + plane3pts);

        PlaneEquationCoefficients planeCoeffs2 = new PlaneEquationCoefficients(1,1,1, -1); // x+y+z-1=0
        PlaneEquationCoefficients planeCoeffs3 = new PlaneEquationCoefficients(1,0,0, 0);  // x=0 (yz-plane)
        PlaneEquationResult planeYZ = ThreeDGeometryUtils.planeEqFromCoefficients(planeCoeffs3);
        System.out.println("Angle between x+y+z-1=0 and x=0: " + ThreeDGeometryUtils.angleBetweenPlanes(plane3pts, planeYZ));

        LineEquationResult lineForAngle = ThreeDGeometryUtils.lineEqVectorForm(new Point3D(0,0,0), new Vector3D(1,1,1));
        System.out.println("Angle between line r=t(i+j+k) and plane x+y+z-1=0: " + ThreeDGeometryUtils.angleLinePlane(lineForAngle, plane3pts));

        Point3D ptForDistPlane = new Point3D(2,2,2);
        System.out.println("Distance from (2,2,2) to plane x+y+z-1=0: " + ThreeDGeometryUtils.distancePointPlane(ptForDistPlane, planeCoeffs2));
        
        System.out.println("Relationship Line r=t(i+j+k) and Plane x+y+z-1=0: " + ThreeDGeometryUtils.relationshipLinePlane(lineForAngle, planeCoeffs2));
        LineEquationResult lineIntersects = ThreeDGeometryUtils.lineEqVectorForm(new Point3D(0,0,0), new Vector3D(1,0,0)); // x-axis
        System.out.println("Intersection Line r=t(i) and Plane x+y+z-1=0: " + ThreeDGeometryUtils.intersectionLinePlane(lineIntersects, planeCoeffs2));
        
        // ... (previous example code from ThreeDGeometryExamples.java) ...

        PlaneEquationCoefficients planeInter1 = new PlaneEquationCoefficients(1,1,1, -6.0); // x+y+z-6=0
        PlaneEquationCoefficients planeInter2 = new PlaneEquationCoefficients(1,-1,1, -2.0); // x-y+z-2=0
        System.out.println("Intersection of planes x+y+z-6=0 and x-y+z-2=0: \n  " + ThreeDGeometryUtils.intersectionTwoPlanes(planeInter1, planeInter2));

        PlaneEquationCoefficients planeParallel1 = new PlaneEquationCoefficients(1,1,1, -1.0); // x+y+z-1=0
        PlaneEquationCoefficients planeParallel2 = new PlaneEquationCoefficients(2,2,2, -5.0); // 2x+2y+2z-5=0 (Parallel)
        System.out.println("Intersection of planes x+y+z-1=0 and 2x+2y+2z-5=0: \n  " + ThreeDGeometryUtils.intersectionTwoPlanes(planeParallel1, planeParallel2));
        
        PlaneEquationCoefficients planeCoincident1 = new PlaneEquationCoefficients(1,1,1, -3.0); // x+y+z-3=0
        PlaneEquationCoefficients planeCoincident2 = new PlaneEquationCoefficients(3,3,3, -9.0); // 3x+3y+3z-9=0 (Coincident)
        System.out.println("Intersection of planes x+y+z-3=0 and 3x+3y+3z-9=0: \n  " + ThreeDGeometryUtils.intersectionTwoPlanes(planeCoincident1, planeCoincident2));


        // --- Coplanarity of Lines and Image ---
        System.out.println("\n-- Coplanarity and Image --");
        LineEquationResult lineA = ThreeDGeometryUtils.lineEqVectorForm(new Point3D(1,1,0), new Vector3D(1,-1,2));
        LineEquationResult lineB = ThreeDGeometryUtils.lineEqVectorForm(new Point3D(2,0,2), new Vector3D(-1,1,0)); // Intersecting with lineA
        System.out.println("Coplanarity of Line A and Line B (Intersecting): \n  " + ThreeDGeometryUtils.checkCoplanarityLines(lineA, lineB));

        LineEquationResult lineC = ThreeDGeometryUtils.lineEqVectorForm(new Point3D(0,0,0), new Vector3D(1,0,0)); // x-axis
        LineEquationResult lineD = ThreeDGeometryUtils.lineEqVectorForm(new Point3D(0,1,0), new Vector3D(1,0,0)); // Line parallel to x-axis through (0,1,0)
        System.out.println("Coplanarity of Line C and Line D (Parallel): \n  " + ThreeDGeometryUtils.checkCoplanarityLines(lineC, lineD));

        LineEquationResult lineE = ThreeDGeometryUtils.lineEqVectorForm(new Point3D(0,0,0), new Vector3D(1,0,0)); // x-axis
        LineEquationResult lineF = ThreeDGeometryUtils.lineEqVectorForm(new Point3D(0,1,0), new Vector3D(0,0,1)); // Line parallel to z-axis through (0,1,0) - Skew
        System.out.println("Coplanarity of Line E and Line F (Skew): \n  " + ThreeDGeometryUtils.checkCoplanarityLines(lineE, lineF));


        Point3D pointForImageInLine = new Point3D(1, 6, 3);
        LineEquationResult lineForImage = ThreeDGeometryUtils.lineEqCartesianSymmetric(
                new Point3D(0,1,2), new DirectionRatios(1,2,-1) // (x-0)/1 = (y-1)/2 = (z-2)/-1
        );
        System.out.println("Image of point " + pointForImageInLine + " in line " + lineForImage.getEquationStr() + ": \n  " + ThreeDGeometryUtils.imageOfPointInLine(pointForImageInLine, lineForImage));

        
        System.out.println("\n--- End of 3D Geometry Examples ---");
    }
}