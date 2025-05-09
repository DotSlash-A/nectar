package michu.fr.threedgeometry;

import michu.fr.threedgeometry.models.*; // Import all models

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public final class ThreeDGeometryUtils {

    private static final double EPSILON = 1e-9; // For floating point comparisons

    private ThreeDGeometryUtils() {
        throw new UnsupportedOperationException("This is a utility class and cannot be instantiated");
    }

    // --- 23. ALGEBRA OF VECTORS ---

    public static Vector3D addVectors(Vector3D v1, Vector3D v2) {
        return v1.add(v2);
    }

    public static Vector3D subtractVectors(Vector3D v1, Vector3D v2) {
        return v1.subtract(v2);
    }

    public static Vector3D scalarMultiplyVector(double scalar, Vector3D v) {
        return v.scalarMultiply(scalar);
    }

    public static MagnitudeResult vectorMagnitude(Vector3D v) {
        return new MagnitudeResult(v, v.magnitude());
    }

    public static Vector3D unitVector(Vector3D v) {
        try {
            return v.normalize();
        } catch (ArithmeticException e) {
            throw new IllegalArgumentException("Cannot compute unit vector for a zero vector.", e);
        }
    }

    public static Vector3D vectorFromTwoPoints(Point3D p1, Point3D p2) {
        return new Vector3D(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
    }

    public static Point3D sectionFormula(Point3D p1, Point3D p2, double m, double n, boolean internal) {
        if (internal) {
            if (Math.abs(m + n) < EPSILON) throw new IllegalArgumentException("Sum of ratios m+n cannot be zero for internal division.");
            double x = (n * p1.x + m * p2.x) / (m + n);
            double y = (n * p1.y + m * p2.y) / (m + n);
            double z = (n * p1.z + m * p2.z) / (m + n);
            return new Point3D(x, y, z);
        } else { // external
            if (Math.abs(m - n) < EPSILON) throw new IllegalArgumentException("Ratios m and n cannot be equal for external division.");
            double x = (m * p2.x - n * p1.x) / (m - n);
            double y = (m * p2.y - n * p1.y) / (m - n);
            double z = (m * p2.z - n * p1.z) / (m - n);
            return new Point3D(x, y, z);
        }
    }

    // Collinearity, etc. would also go here.

    // --- 24. SCALAR OR DOT PRODUCT ---

    public static DotProductResult dotProduct(Vector3D v1, Vector3D v2) {
        double dp = v1.dot(v2);
        double mag1 = v1.magnitude();
        double mag2 = v2.magnitude();
        Double angleRad = null;
        Double angleDeg = null;

        if (Math.abs(mag1) > EPSILON && Math.abs(mag2) > EPSILON) {
            double cosTheta = dp / (mag1 * mag2);
            cosTheta = Math.max(-1.0, Math.min(1.0, cosTheta)); // Clamp
            angleRad = Math.acos(cosTheta);
            angleDeg = Math.toDegrees(angleRad);
        }
        return new DotProductResult(v1, v2, dp, angleRad, angleDeg);
    }
    
    // ProjectionResult model would be needed
    // public static ProjectionResult projectionVectorOnVector(Vector3D a, Vector3D b) { ... }


    // --- 25. VECTOR OR CROSS PRODUCT ---

    public static CrossProductResult crossProduct(Vector3D v1, Vector3D v2) {
        Vector3D cp = v1.cross(v2);
        return new CrossProductResult(v1, v2, cp, cp.magnitude());
    }

    public static AreaTriangleResult areaTriangleVectors(Vector3D v1, Vector3D v2) {
        CrossProductResult cpRes = crossProduct(v1, v2);
        double area = 0.5 * cpRes.getMagnitudeOfCrossProduct();
        // For the result object, you might want to indicate how the area was derived
        Map<String, String> context = new HashMap<>();
        context.put("method", "0.5 * |v1 x v2|");
        context.put("v1", v1.toString());
        context.put("v2", v2.toString());
        return new AreaTriangleResult(area, context); // AreaTriangleResult needs to be defined
    }

    public static AreaTriangleResult areaTrianglePoints(Point3D p1, Point3D p2, Point3D p3) {
        Vector3D v12 = vectorFromTwoPoints(p1, p2);
        Vector3D v13 = vectorFromTwoPoints(p1, p3);
        return areaTriangleVectors(v12, v13);
    }

    // ScalarTripleProductResult model would be needed
    // public static ScalarTripleProductResult scalarTripleProduct(Vector3D a, Vector3D b, Vector3D c) {
    //     return new ScalarTripleProductResult(a,b,c, a.dot(b.cross(c)));
    // }


    // --- 26. DIRECTION COSINES AND DIRECTION RATIOS ---

    public static DirectionRatios directionRatiosFromVector(Vector3D v) {
        return new DirectionRatios(v.x, v.y, v.z);
    }

    public static DirectionRatios directionRatiosFromPoints(Point3D p1, Point3D p2) {
        Vector3D v = vectorFromTwoPoints(p1, p2);
        return new DirectionRatios(v.x, v.y, v.z);
    }

    public static DirectionCosines directionCosinesFromRatios(DirectionRatios dr) {
        double magSq = dr.a * dr.a + dr.b * dr.b + dr.c * dr.c;
        if (Math.abs(magSq) < EPSILON) {
            return new DirectionCosines(0, 0, 0, false); // Or throw error
        }
        double mag = Math.sqrt(magSq);
        return new DirectionCosines(dr.a / mag, dr.b / mag, dr.c / mag);
    }

    public static DirectionCosines directionCosinesFromVector(Vector3D v) {
        if (v.isZeroVector(EPSILON)) {
             return new DirectionCosines(0, 0, 0, false);
        }
        Vector3D unitV = v.normalize();
        return new DirectionCosines(unitV.x, unitV.y, unitV.z);
    }

    // --- 27. STRAIGHT LINE IN SPACE ---
    public static LineEquationResult lineEqVectorForm(Point3D point, Vector3D directionVector) {
        String eqStr = String.format("r = %s + λ%s", point.toString(), directionVector.toString());
        return new LineEquationResult("vector_form", eqStr, point, directionVector);
    }

    public static LineEquationResult lineEqCartesianSymmetric(Point3D point, DirectionRatios dr) {
        StringBuilder sb = new StringBuilder();
        boolean first = true;

        if (Math.abs(dr.a) > EPSILON) {
            sb.append(String.format("(x - %.2f)/%.2f", point.x, dr.a));
            first = false;
        } else {
            // Append x = x0 later if other terms exist
        }

        if (Math.abs(dr.b) > EPSILON) {
            if (!first) sb.append(" = ");
            sb.append(String.format("(y - %.2f)/%.2f", point.y, dr.b));
            first = false;
        } else {
            // Append y = y0 later
        }

        if (Math.abs(dr.c) > EPSILON) {
            if (!first) sb.append(" = ");
            sb.append(String.format("(z - %.2f)/%.2f", point.z, dr.c));
            first = false;
        } else {
            // Append z = z0 later
        }
        
        List<String> fixedCoords = new ArrayList<>();
        if (Math.abs(dr.a) < EPSILON) fixedCoords.add(String.format("x = %.2f", point.x));
        if (Math.abs(dr.b) < EPSILON) fixedCoords.add(String.format("y = %.2f", point.y));
        if (Math.abs(dr.c) < EPSILON) fixedCoords.add(String.format("z = %.2f", point.z));

        if (!fixedCoords.isEmpty()) {
            if (sb.length() > 0) sb.append("; ");
            sb.append(String.join(", ", fixedCoords));
        }
        
        if (sb.length() == 0 && fixedCoords.size() == 3) { // All DRs are zero - it's a point
             return new LineEquationResult("point_form (invalid line)", point.toString(), point, new Vector3D(0,0,0));
        }


        return new LineEquationResult("cartesian_symmetric_form", sb.toString(), point, new Vector3D(dr.a, dr.b, dr.c));
    }
    
    public static double angleBetweenLines(Vector3D dir1, Vector3D dir2) { // Returns angle in radians
        DotProductResult dpRes = dotProduct(dir1, dir2);
        if (dpRes.getAngleRadians() == null) {
            throw new IllegalArgumentException("Cannot calculate angle with zero vector(s).");
        }
        return dpRes.getAngleRadians();
    }
    
    // ShortestDistanceResult, LinesRelationshipResult models would be needed
    // public static ShortestDistanceResult shortestDistanceSkewLines(Point3D p1, Vector3D d1, Point3D p2, Vector3D d2) { ... }
    // public static LinesRelationshipResult linesRelationship(Point3D p1, Vector3D d1, Point3D p2, Vector3D d2) { ... }


    // --- 28. THE PLANE ---
    public static PlaneEquationResult planeEqVectorNormalForm(Vector3D unitNormal, double distanceFromOrigin) {
        if (! (Math.abs(unitNormal.magnitude() - 1.0) < EPSILON) ) {
            // If not unit vector, normalize it, adjust distance accordingly.
            // Or strictly require unitNormal as input. For now, assume it's unit.
            // throw new IllegalArgumentException("Normal vector provided must be a unit vector for this form.");
        }
        // Ensure distance is positive for standard form by potentially flipping normal
        Vector3D nEff = unitNormal;
        double dEff = distanceFromOrigin;
        if (dEff < 0) {
            dEff = -dEff;
            nEff = unitNormal.scalarMultiply(-1);
        }
        String eqStr = String.format("r . %s = %.2f", nEff.toString(), dEff);
        return new PlaneEquationResult("vector_normal_form", eqStr, nEff, dEff, null);
    }

    public static PlaneEquationResult planeEqCartesianFromNormalPoint(Vector3D normal, Point3D point) {
        // A(x-x0) + B(y-y0) + C(z-z0) = 0 => Ax + By + Cz - (Ax0+By0+Cz0) = 0
        // So D_lhs = -(A*x0 + B*y0 + C*z0)
        double A = normal.x;
        double B = normal.y;
        double C = normal.z;
        double D_lhs = - (A * point.x + B * point.y + C * point.z);
        
        Map<String, Double> coeffs = new HashMap<>();
        coeffs.put("A", A); coeffs.put("B", B); coeffs.put("C", C); coeffs.put("D", D_lhs);

        String eqStr = String.format("%.2fx + %.2fy + %.2fz + %.2f = 0", A, B, C, D_lhs);
        return new PlaneEquationResult("cartesian_form", eqStr, normal, null, coeffs);
    }

    public static PlaneEquationResult planeEqFromThreePoints(Point3D p1, Point3D p2, Point3D p3) {
        Vector3D v12 = vectorFromTwoPoints(p1, p2);
        Vector3D v13 = vectorFromTwoPoints(p1, p3);
        Vector3D normal = v12.cross(v13);

        if (normal.isZeroVector(EPSILON)) {
            throw new IllegalArgumentException("The three points are collinear and do not define a unique plane.");
        }
        return planeEqCartesianFromNormalPoint(normal, p1); // Use p1 as a point on the plane
    }
    
    // AngleBetweenPlanesResult, AngleLinePlaneResult, DistancePointPlaneResult, etc. models needed
    // public static double angleBetweenPlanes(Vector3D n1, Vector3D n2) { ... }
    // public static double angleLinePlane(Vector3D lineDir, Vector3D planeNormal) { ... }
    // public static DistancePointPlaneResult distancePointPlane(Point3D point, PlaneEquationResult plane) { ... }
    // public static IntersectionLinePlaneResult intersectionLinePlane(...) { ... }
    // public static IntersectionTwoPlanesResult intersectionTwoPlanes(...) { ... }

}