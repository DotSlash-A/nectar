package michu.fr.threedgeometry;

import michu.fr.threedgeometry.models.*;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public final class ThreeDGeometryUtils {

    private static final double EPSILON = 1e-9; // For floating point comparisons

    private ThreeDGeometryUtils() {
        throw new UnsupportedOperationException("This is a utility class and cannot be instantiated");
    }

    // --- Helper for formatting doubles in strings ---
    private static String f(double val) {
        if (Math.abs(val - Math.round(val)) < EPSILON) {
            return String.format("%d", Math.round(val));
        }
        return String.format("%.3f", val); // Consistent precision
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

    public static UnitVectorResult unitVector(Vector3D v) {
        try {
            return new UnitVectorResult(v, v.normalize());
        } catch (ArithmeticException e) {
            throw new IllegalArgumentException("Cannot compute unit vector for a zero vector.", e);
        }
    }

    public static Vector3D vectorFromTwoPoints(Point3D p1, Point3D p2) {
        return new Vector3D(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
    }

    public static SectionFormulaResult sectionFormula(Point3D p1, Point3D p2, double m, double n, boolean internal) {
        Point3D resultingPoint;
        String divisionType;
        if (internal) {
            if (Math.abs(m + n) < EPSILON) throw new IllegalArgumentException("Sum of ratios m+n cannot be zero for internal division.");
            double x = (n * p1.x + m * p2.x) / (m + n);
            double y = (n * p1.y + m * p2.y) / (m + n);
            double z = (n * p1.z + m * p2.z) / (m + n);
            resultingPoint = new Point3D(x, y, z);
            divisionType = "internal";
        } else { // external
            if (Math.abs(m - n) < EPSILON) throw new IllegalArgumentException("Ratios m and n cannot be equal for external division.");
            double x = (m * p2.x - n * p1.x) / (m - n);
            double y = (m * p2.y - n * p1.y) / (m - n);
            double z = (m * p2.z - n * p1.z) / (m - n);
            resultingPoint = new Point3D(x, y, z);
            divisionType = "external";
        }
        return new SectionFormulaResult(resultingPoint, p1, p2, m, n, divisionType);
    }
    
    public static CollinearityResult checkCollinearityPoints(List<Point3D> points) {
        if (points == null || points.size() < 2) {
            return new CollinearityResult(true, "Less than 2 points are trivially collinear.", points != null ? points : Collections.emptyList());
        }
        if (points.size() == 2) {
            return new CollinearityResult(true, "Two points are always collinear.", points);
        }

        Point3D p0 = points.get(0);
        Vector3D v1 = vectorFromTwoPoints(p0, points.get(1));

        if (v1.isZeroVector(EPSILON) && points.size() > 2) { // First two points are same
             // Check if all points are the same as p0
            for (int i = 2; i < points.size(); i++) {
                if (vectorFromTwoPoints(p0, points.get(i)).magnitude() > EPSILON) {
                     return new CollinearityResult(false, "Points are not collinear; first two are coincident, but others differ.", points);
                }
            }
            return new CollinearityResult(true, "All points are coincident.", points);
        }


        for (int i = 2; i < points.size(); i++) {
            Vector3D vCurrent = vectorFromTwoPoints(p0, points.get(i));
            if (vCurrent.isZeroVector(EPSILON)) continue; // This point is same as p0

            // Check if vCurrent is parallel to v1 (cross product is zero vector)
            if (v1.isZeroVector(EPSILON)) { // If p0 and p1 were the same, v1 is zero. Now check vCurrent against next non-zero vector.
                // This case becomes complex if multiple initial points are coincident.
                // For simplicity, if v1 is zero, we need a non-zero reference vector.
                // Let's assume v1 is non-zero due to the check above or the list having distinct points.
                 return new CollinearityResult(false, "Initial reference vector P0P1 is zero, ambiguity in direction.", points);
            }

            Vector3D crossProd = v1.cross(vCurrent);
            if (crossProd.magnitude() > EPSILON) {
                return new CollinearityResult(
                    false,
                    "Vector from point 0 to point " + i + " is not parallel to vector from point 0 to point 1.",
                    points
                );
            }
        }
        return new CollinearityResult(
            true,
            "All vectors formed from the first point to other points are parallel (or points are coincident).",
            points
        );
    }


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
    
    public static ProjectionResult projectionVectorOnVector(Vector3D vectorA, Vector3D vectorB) {
        double magB = vectorB.magnitude();
        if (Math.abs(magB) < EPSILON) {
            throw new IllegalArgumentException("Cannot project onto a zero vector (vector B).");
        }
        double scalarProj = vectorA.dot(vectorB) / magB;
        Vector3D unitB = vectorB.normalize(); // Safe due to magB check
        Vector3D vectorProj = unitB.scalarMultiply(scalarProj);
        return new ProjectionResult(vectorA, vectorB, scalarProj, vectorProj);
    }


    // --- 25. VECTOR OR CROSS PRODUCT ---

    public static CrossProductResult crossProduct(Vector3D v1, Vector3D v2) {
        Vector3D cp = v1.cross(v2);
        return new CrossProductResult(v1, v2, cp, cp.magnitude());
    }

    public static AreaTriangleResult areaTriangleVectors(Vector3D adjacentSide1, Vector3D adjacentSide2) {
        CrossProductResult cpRes = crossProduct(adjacentSide1, adjacentSide2);
        double area = 0.5 * cpRes.getMagnitudeOfCrossProduct();
        Map<String, String> context = new HashMap<>();
        context.put("method", "0.5 * |side1 x side2|");
        context.put("side1", adjacentSide1.toString());
        context.put("side2", adjacentSide2.toString());
        return new AreaTriangleResult(area, context);
    }

    public static AreaTriangleResult areaTrianglePoints(Point3D p1, Point3D p2, Point3D p3) {
        Vector3D v12 = vectorFromTwoPoints(p1, p2);
        Vector3D v13 = vectorFromTwoPoints(p1, p3);
        Map<String, String> context = new HashMap<>();
        context.put("method", "0.5 * |(P2-P1) x (P3-P1)|");
        context.put("P1", p1.toString());
        context.put("P2", p2.toString());
        context.put("P3", p3.toString());
        // Get area from vectors and then update context
        AreaTriangleResult areaResVec = areaTriangleVectors(v12, v13);
        return new AreaTriangleResult(areaResVec.getArea(), context);
    }

    public static ScalarTripleProductResult scalarTripleProduct(Vector3D a, Vector3D b, Vector3D c) {
        double stp = a.dot(b.cross(c));
        boolean areCoplanar = Math.abs(stp) < EPSILON;
        return new ScalarTripleProductResult(a, b, c, stp, areCoplanar);
    }


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
        if (Math.abs(magSq) < EPSILON) { // Zero vector case
            return new DirectionCosines(0, 0, 0, false);
        }
        double mag = Math.sqrt(magSq);
        return new DirectionCosines(dr.a / mag, dr.b / mag, dr.c / mag);
    }

    public static DirectionCosines directionCosinesFromVector(Vector3D v) {
        if (v.isZeroVector(EPSILON)) {
             return new DirectionCosines(0, 0, 0, false);
        }
        try {
            Vector3D unitV = v.normalize();
            return new DirectionCosines(unitV.x, unitV.y, unitV.z);
        } catch (ArithmeticException e) { // Should be caught by isZeroVector
            return new DirectionCosines(0,0,0, false);
        }
    }

    // --- 27. STRAIGHT LINE IN SPACE ---
    public static LineEquationResult lineEqVectorForm(Point3D point, Vector3D directionVector) {
        if (directionVector.isZeroVector(EPSILON)) {
            throw new IllegalArgumentException("Direction vector for a line cannot be a zero vector.");
        }
        String eqStr = String.format("r = %s + λ%s", point.toString(), directionVector.toString());
        return new LineEquationResult("vector_form", eqStr, point, directionVector);
    }

    public static LineEquationResult lineEqCartesianSymmetric(Point3D point, DirectionRatios dr) {
         if (Math.abs(dr.a) < EPSILON && Math.abs(dr.b) < EPSILON && Math.abs(dr.c) < EPSILON) {
            // All DRs are zero - it's a point, not a line.
            return new LineEquationResult("point_form (not a line)",
                String.format("Point: %s", point.toString()), point, new Vector3D(0,0,0));
        }

        List<String> parts = new ArrayList<>();
        if (Math.abs(dr.a) > EPSILON) parts.add(String.format("(x - %s)/%s", f(point.x), f(dr.a)));
        if (Math.abs(dr.b) > EPSILON) parts.add(String.format("(y - %s)/%s", f(point.y), f(dr.b)));
        if (Math.abs(dr.c) > EPSILON) parts.add(String.format("(z - %s)/%s", f(point.z), f(dr.c)));
        
        String mainEq = String.join(" = ", parts);

        List<String> fixedCoords = new ArrayList<>();
        if (Math.abs(dr.a) < EPSILON) fixedCoords.add(String.format("x = %s", f(point.x)));
        if (Math.abs(dr.b) < EPSILON) fixedCoords.add(String.format("y = %s", f(point.y)));
        if (Math.abs(dr.c) < EPSILON) fixedCoords.add(String.format("z = %s", f(point.z)));

        String fullEqStr = mainEq;
        if (!fixedCoords.isEmpty()) {
            if (!fullEqStr.isEmpty()) fullEqStr += "; ";
            fullEqStr += String.join(", ", fixedCoords);
        }
        
        return new LineEquationResult("cartesian_symmetric_form", fullEqStr, point, new Vector3D(dr.a, dr.b, dr.c));
    }

    public static List<LineEquationResult> lineEqFromTwoPoints(Point3D p1, Point3D p2) {
        Vector3D dirVec = vectorFromTwoPoints(p1, p2);
        if (dirVec.isZeroVector(EPSILON)) {
            throw new IllegalArgumentException("The two points are coincident, cannot define a unique line.");
        }
        DirectionRatios dr = directionRatiosFromVector(dirVec);
        List<LineEquationResult> results = new ArrayList<>();
        results.add(lineEqVectorForm(p1, dirVec)); // Use p1 as the point
        results.add(lineEqCartesianSymmetric(p1, dr));
        return results;
    }
    
    public static AngleBetweenLinesResult angleBetweenLines(Vector3D dir1, Vector3D dir2) {
        if (dir1.isZeroVector(EPSILON) || dir2.isZeroVector(EPSILON)) {
            throw new IllegalArgumentException("Direction vectors cannot be zero for angle calculation.");
        }
        DotProductResult dpRes = dotProduct(dir1, dir2); // dotProduct handles normalization for angle
        if (dpRes.getAngleRadians() == null) { // Should not happen if vectors are non-zero
             throw new ArithmeticException("Could not compute angle, check vector magnitudes.");
        }
        return new AngleBetweenLinesResult(dir1, dir2, dpRes.getAngleRadians(), dpRes.getAngleDegrees());
    }
    
    public static ShortestDistanceResult shortestDistanceBetweenLines(Point3D p1, Vector3D d1, Point3D p2, Vector3D d2) {
        if (d1.isZeroVector(EPSILON) || d2.isZeroVector(EPSILON)) {
            throw new IllegalArgumentException("Direction vectors for lines cannot be zero.");
        }
        LineEquationResult line1Def = lineEqVectorForm(p1, d1);
        LineEquationResult line2Def = lineEqVectorForm(p2, d2);

        Vector3D p2_minus_p1 = vectorFromTwoPoints(p1, p2);
        Vector3D d1_cross_d2 = d1.cross(d2);
        double dist;
        String relationship;
        Point3D ptOnL1 = null, ptOnL2 = null; // For skew lines, points of shortest distance

        if (d1_cross_d2.magnitude() < EPSILON) { // Lines are parallel
            relationship = "parallel";
            // Distance between parallel lines = |(p2 - p1) x d1| / |d1|
            dist = p2_minus_p1.cross(d1).magnitude() / d1.magnitude();
            if (dist < EPSILON) { // Check if also collinear
                 relationship = "collinear (same line)";
            } else {
                 relationship = "parallel_distinct";
            }
        } else { // Lines are skew or intersecting
            // SD = | (p2 - p1) . (d1 x d2) | / |d1 x d2 |
            dist = Math.abs(p2_minus_p1.dot(d1_cross_d2)) / d1_cross_d2.magnitude();
            if (dist < EPSILON) {
                relationship = "intersecting";
                // To find intersection point, solve p1 + t*d1 = p2 + s*d2 for t or s
                // One way: t = ((p2-p1) x d2) . (d1 x d2) / |d1 x d2|^2
                double t = (p2_minus_p1.cross(d2)).dot(d1_cross_d2) / Math.pow(d1_cross_d2.magnitude(), 2);
                ptOnL1 = p1.toVector3D().add(d1.scalarMultiply(t)).toPoint3D(); // Intersection point
                // Similarly for s for verification: s = ((p1-p2) x d1) . (d2 x d1) / |d2 x d1|^2 - note d2xd1 = -d1xd2
                // s = ((p2-p1) x d1) . (d1 x d2) / Math.pow(d1_cross_d2.magnitude(), 2); // Check this formula
                // ptOnL2 = p2.toVector3D().add(d2.scalarMultiply(s)).toPoint3D();
            } else {
                relationship = "skew";
                // Points for shortest distance segment:
                // t = [(p2-p1).d1 * d2.d2 - (p2-p1).d2 * d1.d2] / [ (d1.d1)(d2.d2) - (d1.d2)^2 ]
                // s = [(p2-p1).d1 * d1.d2 - (p2-p1).d2 * d1.d1] / [ (d1.d2)^2 - (d1.d1)(d2.d2) ] (Denominator flipped)
                double d1d1 = d1.dot(d1);
                double d2d2 = d2.dot(d2);
                double d1d2 = d1.dot(d2);
                double p21d1 = p2_minus_p1.dot(d1);
                double p21d2 = p2_minus_p1.dot(d2);

                double den = d1d1 * d2d2 - d1d2 * d1d2;
                if (Math.abs(den) > EPSILON) { // Avoid division by zero if d1, d2 are parallel (already handled)
                    double t = (p21d1 * d2d2 - p21d2 * d1d2) / den;
                    double s = (p21d1 * d1d2 - p21d2 * d1d1) / (-den); // Denominator is -(d1d1*d2d2 - d1d2*d1d2)

                    ptOnL1 = p1.toVector3D().add(d1.scalarMultiply(t)).toPoint3D();
                    ptOnL2 = p2.toVector3D().add(d2.scalarMultiply(s)).toPoint3D();
                }
            }
        }
        return new ShortestDistanceResult(line1Def, line2Def, dist, relationship, ptOnL1, ptOnL2);
    }
    
    // LinesRelationshipResult will be similar to ShortestDistanceResult or can be combined

    public static DistancePointLineResult distancePointLine(Point3D point, Point3D linePoint, Vector3D lineDir) {
        if (lineDir.isZeroVector(EPSILON)) {
            throw new IllegalArgumentException("Line direction vector cannot be zero.");
        }
        Vector3D ap = vectorFromTwoPoints(linePoint, point); // Vector from point on line to the given point
        Vector3D crossProd = ap.cross(lineDir);
        double distance = crossProd.magnitude() / lineDir.magnitude();

        // Foot of perpendicular (M) on line: M = linePoint + t * lineDir
        // t = (AP . lineDir) / |lineDir|^2
        double t = ap.dot(lineDir) / Math.pow(lineDir.magnitude(), 2);
        Point3D foot = linePoint.toVector3D().add(lineDir.scalarMultiply(t)).toPoint3D();
        
        return new DistancePointLineResult(point, lineEqVectorForm(linePoint, lineDir), distance, foot);
    }

    // --- 28. THE PLANE ---
    public static PlaneEquationResult planeEqVectorNormalForm(Vector3D normalVector, double distanceFromOrigin) {
        if (normalVector.isZeroVector(EPSILON)) {
            throw new IllegalArgumentException("Normal vector for a plane cannot be zero.");
        }
        Vector3D unitNormal = normalVector.normalize(); // Will throw if normal is zero vector
        
        Vector3D nEff = unitNormal;
        double dEff = distanceFromOrigin;
        // Standard form usually has d >= 0. If d < 0, flip normal and d.
        if (dEff < 0) {
            dEff = -dEff;
            nEff = unitNormal.scalarMultiply(-1);
        }
        String eqStr = String.format("r . %s = %s", nEff.toString(), f(dEff));
        Map<String, Double> coeffs = new HashMap<>();
        coeffs.put("A", nEff.x); coeffs.put("B", nEff.y); coeffs.put("C", nEff.z);
        coeffs.put("D", -dEff); // For Ax+By+Cz+D=0 form, D = -distance_from_origin_for_unit_normal

        return new PlaneEquationResult("vector_normal_form", eqStr, nEff, dEff, coeffs);
    }

    public static PlaneEquationResult planeEqCartesianFromNormalPoint(Vector3D normal, Point3D pointOnPlane) {
        if (normal.isZeroVector(EPSILON)) {
            throw new IllegalArgumentException("Normal vector for a plane cannot be zero.");
        }
        // A(x-x0) + B(y-y0) + C(z-z0) = 0  => Ax + By + Cz - (A*x0 + B*y0 + C*z0) = 0
        // So D_lhs = -(A*x0 + B*y0 + C*z0)
        double A = normal.x;
        double B = normal.y;
        double C = normal.z;
        double D_lhs = -(A * pointOnPlane.x + B * pointOnPlane.y + C * pointOnPlane.z);
        
        Map<String, Double> coeffsMap = new HashMap<>();
        coeffsMap.put("A", A); coeffsMap.put("B", B); coeffsMap.put("C", C); coeffsMap.put("D", D_lhs);

        String eqStr = String.format("%sx + %sy + %sz + %s = 0", f(A), f(B), f(C), f(D_lhs));
        return new PlaneEquationResult("cartesian_form_normal_point", eqStr, normal, null, coeffsMap);
    }
    
    public static PlaneEquationResult planeEqFromCoefficients(PlaneEquationCoefficients coeffs) {
        Vector3D normal = new Vector3D(coeffs.a, coeffs.b, coeffs.c);
        if (normal.isZeroVector(EPSILON)) {
             throw new IllegalArgumentException("Coefficients A,B,C for normal vector cannot all be zero.");
        }
        double dLhs = coeffs.getDForAxByCzPlusDlhsEqualsZero();
        String eqStr = String.format("%sx + %sy + %sz + %s = 0", f(coeffs.a), f(coeffs.b), f(coeffs.c), f(dLhs));
        
        Map<String, Double> coeffsMap = new HashMap<>();
        coeffsMap.put("A", coeffs.a); coeffsMap.put("B", coeffs.b); coeffsMap.put("C", coeffs.c);
        coeffsMap.put("D", dLhs);
        
        double distFromOrigin = Math.abs(dLhs) / normal.magnitude();

        return new PlaneEquationResult("cartesian_form_coeffs", eqStr, normal, distFromOrigin, coeffsMap);
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
    
    public static AngleBetweenPlanesResult angleBetweenPlanes(PlaneEquationResult plane1, PlaneEquationResult plane2) {
        if (plane1.getNormalVector() == null || plane2.getNormalVector() == null) {
            throw new IllegalArgumentException("Plane definitions must include normal vectors.");
        }
        Vector3D n1 = plane1.getNormalVector();
        Vector3D n2 = plane2.getNormalVector();
        AngleBetweenLinesResult angleLines = angleBetweenLines(n1, n2); // Angle between normals
        return new AngleBetweenPlanesResult(plane1, plane2, angleLines.getAngleRadians(), angleLines.getAngleDegrees());
    }

// ... (previous methods from ThreeDGeometryUtils.java) ...

public static AngleLinePlaneResult angleLinePlane(LineEquationResult line, PlaneEquationResult plane) {
    if (line.getDirectionVector() == null || plane.getNormalVector() == null) {
        throw new IllegalArgumentException("Line and Plane definitions must include direction/normal vectors.");
    }
    Vector3D lineDir = line.getDirectionVector();
    Vector3D planeNormal = plane.getNormalVector();

    if (lineDir.isZeroVector(EPSILON) || planeNormal.isZeroVector(EPSILON)) {
        throw new IllegalArgumentException("Direction/normal vector(s) cannot be zero for angle calculation.");
    }

    // Angle θ between line direction and plane normal:
    DotProductResult dpRes = dotProduct(lineDir, planeNormal);
    if (dpRes.getAngleRadians() == null) {
         throw new ArithmeticException("Could not compute angle theta between line direction and plane normal.");
    }
    double theta = dpRes.getAngleRadians(); // Angle between lineDir and planeNormal

    // Angle α between line and plane is |π/2 - θ|
    // Or, sin(α) = |cos(θ)| = |(lineDir . planeNormal) / (|lineDir| * |planeNormal|)|
    double sinAlpha = Math.abs(lineDir.dot(planeNormal) / (lineDir.magnitude() * planeNormal.magnitude()));
    sinAlpha = Math.max(-1.0, Math.min(1.0, sinAlpha)); // Clamp due to precision
    double alphaRadians = Math.asin(sinAlpha);
    double alphaDegrees = Math.toDegrees(alphaRadians);

    return new AngleLinePlaneResult(line, plane, alphaRadians, alphaDegrees);
}

public static DistancePointPlaneResult distancePointPlane(Point3D point, PlaneEquationCoefficients planeCoeffs) {
    double A = planeCoeffs.a;
    double B = planeCoeffs.b;
    double C = planeCoeffs.c;
    double D_lhs = planeCoeffs.getDForAxByCzPlusDlhsEqualsZero(); // Ax+By+Cz+D_lhs = 0

    Vector3D normal = new Vector3D(A,B,C);
    if (normal.isZeroVector(EPSILON)) {
        throw new IllegalArgumentException("Plane normal vector (A,B,C) derived from coefficients is zero, plane is ill-defined.");
    }

    // Distance = |Ax0 + By0 + Cz0 + D_lhs| / sqrt(A^2 + B^2 + C^2)
    double numerator = Math.abs(A * point.x + B * point.y + C * point.z + D_lhs);
    double denominator = normal.magnitude();
    
    double dist = numerator / denominator;

    // Foot of perpendicular: P_foot = Point - t * Normal_unit_vector
    // where t = signed_distance = (A*x0 + B*y0 + C*z0 + D_lhs) / sqrt(A^2+B^2+C^2)
    double signedDistance = (A * point.x + B * point.y + C * point.z + D_lhs) / denominator;
    Vector3D unitNormal = normal.normalize();
    Point3D foot = point.toVector3D().subtract(unitNormal.scalarMultiply(signedDistance)).toPoint3D();
    
    // Create a PlaneEquationResult from coefficients for the return object
    PlaneEquationResult planeDef = planeEqFromCoefficients(planeCoeffs);

    return new DistancePointPlaneResult(point, planeDef, dist, foot);
}

public static RelationshipLinePlaneResult relationshipLinePlane(LineEquationResult line, PlaneEquationCoefficients planeCoeffs) {
    Vector3D lineDir = line.getDirectionVector();
    Point3D linePoint = line.getPointOnLine();
    Vector3D planeNormal = new Vector3D(planeCoeffs.a, planeCoeffs.b, planeCoeffs.c);
    double D_lhs = planeCoeffs.getDForAxByCzPlusDlhsEqualsZero();

    if (lineDir == null || linePoint == null || planeNormal.isZeroVector(EPSILON)) {
        throw new IllegalArgumentException("Invalid line or plane definition provided.");
    }
    PlaneEquationResult planeDef = planeEqFromCoefficients(planeCoeffs);


    double N_dot_d = planeNormal.dot(lineDir);

    if (Math.abs(N_dot_d) < EPSILON) { // Line direction is perpendicular to plane normal => Line is parallel to plane
        // Check if point on line lies on the plane
        double valAtPoint = planeNormal.dot(linePoint.toVector3D()) + D_lhs;
        if (Math.abs(valAtPoint) < EPSILON) {
            return new RelationshipLinePlaneResult(line, planeDef, "line_lies_in_plane", null, 0.0);
        } else {
            double dist = Math.abs(valAtPoint) / planeNormal.magnitude();
            return new RelationshipLinePlaneResult(line, planeDef, "line_parallel_to_plane_distinct", null, dist);
        }
    } else { // Line intersects the plane
        // λ * (N·d) = -(N·p + D_lhs)
        double lambda = -(planeNormal.dot(linePoint.toVector3D()) + D_lhs) / N_dot_d;
        Point3D intersectionPoint = linePoint.toVector3D().add(lineDir.scalarMultiply(lambda)).toPoint3D();
        return new RelationshipLinePlaneResult(line, planeDef, "line_intersects_plane", intersectionPoint, null);
    }
}


public static IntersectionLinePlaneResult intersectionLinePlane(LineEquationResult line, PlaneEquationCoefficients planeCoeffs) {
    RelationshipLinePlaneResult rel = relationshipLinePlane(line, planeCoeffs);
    boolean intersects = false;
    Point3D intersectionPoint = null;
    String message = rel.getRelationship();

    if ("line_intersects_plane".equals(rel.getRelationship())) {
        intersects = true;
        intersectionPoint = rel.getIntersectionPoint();
    } else if ("line_lies_in_plane".equals(rel.getRelationship())) {
        intersects = true; // Infinitely many intersection points
        message = "Line lies in the plane (infinite intersection points).";
    }
    PlaneEquationResult planeDef = planeEqFromCoefficients(planeCoeffs);
    return new IntersectionLinePlaneResult(line, planeDef, intersects, intersectionPoint, message);
}

public static IntersectionTwoPlanesResult intersectionTwoPlanes(PlaneEquationCoefficients p1Coeffs, PlaneEquationCoefficients p2Coeffs) {
    Vector3D n1 = new Vector3D(p1Coeffs.a, p1Coeffs.b, p1Coeffs.c);
    double d1Lhs = p1Coeffs.getDForAxByCzPlusDlhsEqualsZero();
    PlaneEquationResult plane1Def = planeEqFromCoefficients(p1Coeffs);

    Vector3D n2 = new Vector3D(p2Coeffs.a, p2Coeffs.b, p2Coeffs.c);
    double d2Lhs = p2Coeffs.getDForAxByCzPlusDlhsEqualsZero();
    PlaneEquationResult plane2Def = planeEqFromCoefficients(p2Coeffs);

    if (n1.isZeroVector(EPSILON) || n2.isZeroVector(EPSILON)) {
        throw new IllegalArgumentException("Normal vector from plane coefficients cannot be zero.");
    }

    Vector3D lineDir = n1.cross(n2);

    if (lineDir.isZeroVector(EPSILON)) { // Planes are parallel
        // Check if they are the same plane:
        // A point on plane1 is (x0, y0, z0). If n1. (x0,y0,z0) + d1 = 0
        // Check if this point lies on plane2: n2 . (x0,y0,z0) + d2 = 0
        // A robust check: Are (A1,B1,C1,D1) proportional to (A2,B2,C2,D2)?
        // For example, if A2 != 0, k = A1/A2. Then check B1=k*B2, C1=k*C2, D1=k*D2.
        // This needs careful handling of zero coefficients.

        // A simpler approach for parallel planes: check distance between them.
        // Pick an arbitrary point on plane 1 (e.g., by setting y=0, z=0 if A1!=0)
        Point3D pointOnPlane1 = null;
        if (Math.abs(p1Coeffs.a) > EPSILON) pointOnPlane1 = new Point3D(-d1Lhs / p1Coeffs.a, 0, 0);
        else if (Math.abs(p1Coeffs.b) > EPSILON) pointOnPlane1 = new Point3D(0, -d1Lhs / p1Coeffs.b, 0);
        else if (Math.abs(p1Coeffs.c) > EPSILON) pointOnPlane1 = new Point3D(0, 0, -d1Lhs / p1Coeffs.c);
        else if (Math.abs(d1Lhs) < EPSILON) { // 0x+0y+0z+0=0, essentially all space
            // If plane2 is also 0x+0y+0z+0=0, then coincident.
            if (n2.isZeroVector(EPSILON) && Math.abs(d2Lhs) < EPSILON) {
                 return new IntersectionTwoPlanesResult(plane1Def, plane2Def, true, null, "Planes are coincident (0x+0y+0z+0=0 for both).");
            } else { // Plane1 is trivial, Plane2 is not. They are not the same unless Plane2 is also trivial.
                // This case is tricky. "Parallel" is still true.
                 return new IntersectionTwoPlanesResult(plane1Def, plane2Def, false, null, "Planes are parallel (Plane1 is 0x+0y+0z+0=0).");
            }
        } else { // 0x+0y+0z+D1=0 (D1!=0) -> no points satisfy plane1
             return new IntersectionTwoPlanesResult(plane1Def, plane2Def, false, null, "Plane 1 is inconsistent (0x+0y+0z+D=0, D!=0).");
        }


        if (pointOnPlane1 != null) {
            double valOnPlane2 = n2.dot(pointOnPlane1.toVector3D()) + d2Lhs;
            if (Math.abs(valOnPlane2) < EPSILON) {
                return new IntersectionTwoPlanesResult(plane1Def, plane2Def, true, null, "Planes are coincident (same plane).");
            }
        }
        // If pointOnPlane1 was null due to A1=B1=C1=0 but D1!=0, then plane1 is inconsistent.
        // If pointOnPlane1 was found and it's not on plane2, then parallel and distinct.
        return new IntersectionTwoPlanesResult(plane1Def, plane2Def, false, null, "Planes are parallel and distinct.");
    }

    // Planes intersect in a line. Find a point on this line.
    // Set one coordinate to 0 (e.g., z=0) and solve the 2D system for x, y:
    // A1x + B1y = -d1Lhs
    // A2x + B2y = -d2Lhs
    Point3D pointOnLine = null;
    double det_xy = p1Coeffs.a * p2Coeffs.b - p2Coeffs.a * p1Coeffs.b;
    double det_yz = p1Coeffs.b * p2Coeffs.c - p2Coeffs.b * p1Coeffs.c;
    double det_zx = p1Coeffs.c * p2Coeffs.a - p2Coeffs.c * p1Coeffs.a;

    if (Math.abs(det_xy) > EPSILON) { // Try setting z=0
        double x = (-d1Lhs * p2Coeffs.b - (-d2Lhs) * p1Coeffs.b) / det_xy;
        double y = (p1Coeffs.a * (-d2Lhs) - p2Coeffs.a * (-d1Lhs)) / det_xy;
        pointOnLine = new Point3D(x, y, 0);
    } else if (Math.abs(det_yz) > EPSILON) { // Try setting x=0
        double y = (-d1Lhs * p2Coeffs.c - (-d2Lhs) * p1Coeffs.c) / det_yz;
        double z = (p1Coeffs.b * (-d2Lhs) - p2Coeffs.b * (-d1Lhs)) / det_yz;
        pointOnLine = new Point3D(0, y, z);
    } else if (Math.abs(det_zx) > EPSILON) { // Try setting y=0
        double z = (-d1Lhs * p2Coeffs.a - (-d2Lhs) * p1Coeffs.a) / det_zx;
        double x = (p1Coeffs.c * (-d2Lhs) - p2Coeffs.c * (-d1Lhs)) / det_zx;
        pointOnLine = new Point3D(x, 0, z);
    } else {
        // This means all 2x2 sub-determinants of (n1, n2) are zero,
        // which implies n1 and n2 are parallel. This case should have been caught by lineDir.isZeroVector().
        // If it reaches here, there might be an issue or a very specific alignment.
        return new IntersectionTwoPlanesResult(plane1Def, plane2Def, true, null, // Still true because lineDir was non-zero
            "Planes intersect, but finding a specific point on the line failed (possible numerical instability or edge case).");
    }

    LineEquationResult lineOfIntersection = lineEqVectorForm(pointOnLine, lineDir);
    return new IntersectionTwoPlanesResult(plane1Def, plane2Def, true, lineOfIntersection, "Planes intersect in a line.");
}

public static CoplanarityLinesResult checkCoplanarityLines(LineEquationResult line1, LineEquationResult line2) {
    Point3D p1 = line1.getPointOnLine(); Vector3D d1 = line1.getDirectionVector();
    Point3D p2 = line2.getPointOnLine(); Vector3D d2 = line2.getDirectionVector();

    if (p1 == null || d1 == null || p2 == null || d2 == null || d1.isZeroVector(EPSILON) || d2.isZeroVector(EPSILON)) {
        throw new IllegalArgumentException("Valid line definitions (point and non-zero direction vector) are required.");
    }

    Vector3D p1p2 = vectorFromTwoPoints(p1, p2);
    // Lines are coplanar if the scalar triple product [P1P2 d1 d2] = 0
    ScalarTripleProductResult stpRes = scalarTripleProduct(p1p2, d1, d2);
    
    PlaneEquationResult planeContaining = null;
    String reason;

    if (stpRes.areCoplanar()) {
        // If coplanar, they are either parallel or intersecting.
        Vector3D d1xd2 = d1.cross(d2);
        if (d1xd2.isZeroVector(EPSILON)) { // Parallel
            reason = "Lines are parallel and coplanar.";
            // Plane containing them: normal = (P1P2 x d1), point = p1
            Vector3D planeNormal = p1p2.cross(d1);
             if (!planeNormal.isZeroVector(EPSILON)) { // If P1P2 is not parallel to d1
                planeContaining = planeEqCartesianFromNormalPoint(planeNormal, p1);
            } else { // P1P2 is parallel to d1 -> lines are collinear (same line)
                reason = "Lines are collinear (same line).";
                // Infinitely many planes contain them. We can pick one.
                // e.g. normal perpendicular to d1, e.g. if d1=(a,b,c), normal=(-b,a,0) if a or b != 0
                Vector3D arbitraryNormal;
                if(Math.abs(d1.x) > EPSILON || Math.abs(d1.y) > EPSILON) arbitraryNormal = new Vector3D(-d1.y, d1.x, 0);
                else arbitraryNormal = new Vector3D(0, -d1.z, d1.y); // If d1 is along z-axis
                
                if (!arbitraryNormal.isZeroVector(EPSILON)) {
                     planeContaining = planeEqCartesianFromNormalPoint(arbitraryNormal.normalize(), p1);
                } else {
                     reason += " Cannot define a unique plane easily (d1 might be zero or aligned with axis in a specific way).";
                }
            }
        } else { // Intersecting
            reason = "Lines are intersecting and coplanar.";
            // Plane containing them: normal = (d1 x d2), point = p1 (or p2)
            planeContaining = planeEqCartesianFromNormalPoint(d1xd2, p1);
        }
        return new CoplanarityLinesResult(line1, line2, true, planeContaining, reason);
    } else {
        reason = "Lines are skew (not coplanar).";
        return new CoplanarityLinesResult(line1, line2, false, null, reason);
    }
}

public static ImagePointInLineResult imageOfPointInLine(Point3D point, LineEquationResult line) {
    Point3D linePoint = line.getPointOnLine();
    Vector3D lineDir = line.getDirectionVector();
    if (linePoint == null || lineDir == null || lineDir.isZeroVector(EPSILON)) {
        throw new IllegalArgumentException("Valid line definition required.");
    }

    DistancePointLineResult distRes = distancePointLine(point, linePoint, lineDir);
    Point3D foot = distRes.getFootOfPerpendicular();

    // Image P' = Foot + (Foot - P) = 2*Foot - P
    Vector3D imageVec = foot.toVector3D().scalarMultiply(2.0).subtract(point.toVector3D());
    Point3D imagePoint = imageVec.toPoint3D();

    return new ImagePointInLineResult(point, line, imagePoint, foot);
}



}