#include "three_d_utils.h"
#include <stdexcept> // For std::invalid_argument, std::runtime_error
#include <vector>
#include <string>
#include <cmath>     // For std::abs, std::sqrt, std::pow, M_PI
#include <algorithm> // For std::min, std::max
#include <iomanip>   // For std::fixed, std::setprecision
#include <sstream>   // For std::ostringstream

// Define M_PI if not available (e.g., on MSVC without _USE_MATH_DEFINES)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace michu_fr {
namespace three_d_geometry {

// --- Epsilon for floating point comparisons ---
const double EPSILON = 1e-9;

// --- Helper for formatting doubles in strings for equations ---
static std::string f_eq(double val, int precision = 2) {
    std::ostringstream oss;
    // Check if it's very close to an integer
    if (std::abs(val - std::round(val)) < EPSILON / 1000.0) { // Tighter epsilon for integer check
        oss << static_cast<long long>(std::round(val));
    } else {
        oss << std::fixed << std::setprecision(precision) << val;
    }
    return oss.str();
}


// --- Helper for converting degrees to radians and vice-versa ---
double toRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

double toDegrees(double radians) {
    return radians * 180.0 / M_PI;
}

// --- 23. ALGEBRA OF VECTORS ---
Vector3D addVectors(const Vector3D& v1, const Vector3D& v2) {
    return v1.add(v2);
}

Vector3D subtractVectors(const Vector3D& v1, const Vector3D& v2) {
    return v1.subtract(v2);
}

Vector3D scalarMultiplyVector(double scalar, const Vector3D& v) {
    return v.scalarMultiply(scalar);
}

MagnitudeResult vectorMagnitude(const Vector3D& v) {
    return MagnitudeResult(v, v.magnitude());
}

UnitVectorResult unitVector(const Vector3D& v) {
    try {
        return UnitVectorResult(v, v.normalize());
    } catch (const std::runtime_error& e) {
        throw std::invalid_argument("Cannot compute unit vector for a zero vector.");
    }
}

Vector3D vectorFromTwoPoints(const Point3D& p1, const Point3D& p2) {
    return Vector3D(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
}

SectionFormulaResult sectionFormula(const Point3D& p1, const Point3D& p2, double m, double n, bool internal) {
    Point3D resultingPoint;
    std::string divisionType;
    if (internal) {
        if (std::abs(m + n) < EPSILON) {
            throw std::invalid_argument("Sum of ratios m+n cannot be zero for internal division.");
        }
        double x = (n * p1.x + m * p2.x) / (m + n);
        double y = (n * p1.y + m * p2.y) / (m + n);
        double z = (n * p1.z + m * p2.z) / (m + n);
        resultingPoint = Point3D(x, y, z);
        divisionType = "internal";
    } else { // external
        if (std::abs(m - n) < EPSILON) {
            throw std::invalid_argument("Ratios m and n cannot be equal for external division.");
        }
        double x = (m * p2.x - n * p1.x) / (m - n);
        double y = (m * p2.y - n * p1.y) / (m - n);
        double z = (m * p2.z - n * p1.z) / (m - n);
        resultingPoint = Point3D(x, y, z);
        divisionType = "external";
    }
    return SectionFormulaResult(resultingPoint, p1, p2, m, n, divisionType);
}

CollinearityResult checkCollinearityPoints(const std::vector<Point3D>& points) {
    if (points.size() < 2) {
        return CollinearityResult(true, "Less than 2 points are trivially collinear.", points);
    }
    if (points.size() == 2) {
        return CollinearityResult(true, "Two points are always collinear.", points);
    }

    Point3D p0 = points[0];
    Vector3D v_ref = vectorFromTwoPoints(p0, points[1]);

    // Handle case where first two points are coincident
    if (v_ref.isZeroVector(EPSILON)) {
        for (size_t i = 2; i < points.size(); ++i) {
            if (!vectorFromTwoPoints(p0, points[i]).isZeroVector(EPSILON)) {
                return CollinearityResult(false, "First two points are coincident, but point " + std::to_string(i) + " is distinct.", points);
            }
        }
        return CollinearityResult(true, "All points are coincident.", points);
    }


    for (size_t i = 2; i < points.size(); ++i) {
        Vector3D v_current = vectorFromTwoPoints(p0, points[i]);
        if (v_current.isZeroVector(EPSILON)) continue; // This point is same as p0, collinear

        // Check if v_current is parallel to v_ref (cross product is zero vector)
        Vector3D crossProd = v_ref.cross(v_current);
        if (crossProd.magnitude() > EPSILON) {
            return CollinearityResult(
                false,
                "Vector from point 0 to point " + std::to_string(i) + " is not parallel to vector from point 0 to point 1.",
                points
            );
        }
    }
    return CollinearityResult(
        true,
        "All vectors formed from the first point to other points are parallel (or points are coincident).",
        points
    );
}

// --- 24. SCALAR OR DOT PRODUCT ---
DotProductResult dotProduct(const Vector3D& v1, const Vector3D& v2) {
    double dp = v1.dot(v2);
    double mag1 = v1.magnitude();
    double mag2 = v2.magnitude();
    std::optional<double> angleRad = std::nullopt;
    std::optional<double> angleDeg = std::nullopt;

    if (std::abs(mag1) > EPSILON && std::abs(mag2) > EPSILON) {
        double cosTheta = dp / (mag1 * mag2);
        // Clamp cosTheta to [-1, 1] to avoid domain errors with acos due to precision
        cosTheta = std::max(-1.0, std::min(1.0, cosTheta));
        double rad = std::acos(cosTheta);
        angleRad = rad;
        angleDeg = toDegrees(rad);
    }
    return DotProductResult(v1, v2, dp, angleRad, angleDeg);
}

ProjectionResult projectionVectorOnVector(const Vector3D& vectorA, const Vector3D& vectorB) {
    double magB = vectorB.magnitude();
    if (std::abs(magB) < EPSILON) {
        throw std::invalid_argument("Cannot project onto a zero vector (vectorB).");
    }
    double scalarProj = vectorA.dot(vectorB) / magB;
    Vector3D unitB = vectorB.normalize(); // Safe due to magB check
    Vector3D vectorProj = unitB.scalarMultiply(scalarProj);
    return ProjectionResult(vectorA, vectorB, scalarProj, vectorProj);
}

// --- 25. VECTOR OR CROSS PRODUCT ---
CrossProductResult crossProduct(const Vector3D& v1, const Vector3D& v2) {
    Vector3D cp_v = v1.cross(v2);
    return CrossProductResult(v1, v2, cp_v, cp_v.magnitude());
}

AreaTriangleResult areaTriangleVectors(const Vector3D& adjacentSide1, const Vector3D& adjacentSide2) {
    CrossProductResult cpRes = crossProduct(adjacentSide1, adjacentSide2);
    double area = 0.5 * cpRes.magnitudeOfCrossProduct.value_or(0.0);
    std::map<std::string, std::string> context;
    context["method"] = "0.5 * |side1 x side2|";
    context["side1"] = adjacentSide1.toString();
    context["side2"] = adjacentSide2.toString();
    return AreaTriangleResult(area, context);
}

AreaTriangleResult areaTrianglePoints(const Point3D& p1, const Point3D& p2, const Point3D& p3) {
    Vector3D v12 = vectorFromTwoPoints(p1, p2);
    Vector3D v13 = vectorFromTwoPoints(p1, p3);
    AreaTriangleResult vecAreaRes = areaTriangleVectors(v12, v13);
    
    std::map<std::string, std::string> context;
    context["method"] = "0.5 * |(P2-P1) x (P3-P1)|";
    context["P1"] = p1.toString();
    context["P2"] = p2.toString();
    context["P3"] = p3.toString();
    return AreaTriangleResult(vecAreaRes.area, context);
}

ScalarTripleProductResult scalarTripleProduct(const Vector3D& a, const Vector3D& b, const Vector3D& c) {
    double stp = a.dot(b.cross(c));
    bool areCoplanar = (std::abs(stp) < EPSILON);
    return ScalarTripleProductResult(a, b, c, stp, areCoplanar);
}

// --- 26. DIRECTION COSINES AND DIRECTION RATIOS ---
DirectionRatios directionRatiosFromVector(const Vector3D& v) {
    return DirectionRatios(v.x, v.y, v.z);
}

DirectionRatios directionRatiosFromPoints(const Point3D& p1, const Point3D& p2) {
    Vector3D v = vectorFromTwoPoints(p1, p2);
    return DirectionRatios(v.x, v.y, v.z);
}

DirectionCosines directionCosinesFromRatios(const DirectionRatios& dr) {
    double magSq = dr.a * dr.a + dr.b * dr.b + dr.c * dr.c;
    if (std::abs(magSq) < EPSILON) { // Zero vector case
        return DirectionCosines(0, 0, 0, false); // l,m,n, isValid
    }
    double mag = std::sqrt(magSq);
    return DirectionCosines(dr.a / mag, dr.b / mag, dr.c / mag, true);
}

DirectionCosines directionCosinesFromVector(const Vector3D& v) {
    if (v.isZeroVector(EPSILON)) {
         return DirectionCosines(0, 0, 0, false);
    }
    try {
        Vector3D unitV = v.normalize();
        return DirectionCosines(unitV.x, unitV.y, unitV.z, true);
    } catch (const std::runtime_error&) { // Should be caught by isZeroVector
        return DirectionCosines(0, 0, 0, false);
    }
}

// --- 27. STRAIGHT LINE IN SPACE ---
LineEquationResult lineEqVectorForm(const Point3D& point, const Vector3D& directionVector) {
    if (directionVector.isZeroVector(EPSILON)) {
        throw std::invalid_argument("Direction vector for a line cannot be a zero vector.");
    }
    std::ostringstream oss;
    oss << "r = " << point.toString() << " + λ" << directionVector.toString();
    return LineEquationResult("vector_form", oss.str(), point, directionVector, directionRatiosFromVector(directionVector));
}

LineEquationResult lineEqCartesianSymmetric(const Point3D& point, const DirectionRatios& dr) {
    if (std::abs(dr.a) < EPSILON && std::abs(dr.b) < EPSILON && std::abs(dr.c) < EPSILON) {
        // All DRs are zero - it's a point, not a line.
        std::string eq_str = "Point: " + point.toString();
        return LineEquationResult("point_form (not a line)", eq_str, point, Vector3D(0,0,0), dr);
    }

    std::vector<std::string> parts;
    if (std::abs(dr.a) > EPSILON) parts.push_back("(x - " + f_eq(point.x) + ")/" + f_eq(dr.a));
    if (std::abs(dr.b) > EPSILON) parts.push_back("(y - " + f_eq(point.y) + ")/" + f_eq(dr.b));
    if (std::abs(dr.c) > EPSILON) parts.push_back("(z - " + f_eq(point.z) + ")/" + f_eq(dr.c));
    
    std::string mainEq;
    for(size_t i=0; i < parts.size(); ++i) {
        mainEq += parts[i];
        if (i < parts.size() - 1) mainEq += " = ";
    }

    std::vector<std::string> fixedCoords;
    if (std::abs(dr.a) < EPSILON) fixedCoords.push_back("x = " + f_eq(point.x));
    if (std::abs(dr.b) < EPSILON) fixedCoords.push_back("y = " + f_eq(point.y));
    if (std::abs(dr.c) < EPSILON) fixedCoords.push_back("z = " + f_eq(point.z));

    std::string fullEqStr = mainEq;
    if (!fixedCoords.empty()) {
        if (!fullEqStr.empty()) fullEqStr += "; ";
        for(size_t i=0; i < fixedCoords.size(); ++i) {
            fullEqStr += fixedCoords[i];
            if (i < fixedCoords.size() - 1) fullEqStr += ", ";
        }
    }
    return LineEquationResult("cartesian_symmetric_form", fullEqStr, point, Vector3D(dr.a, dr.b, dr.c), dr);
}

std::vector<LineEquationResult> lineEqFromTwoPoints(const Point3D& p1, const Point3D& p2) {
    Vector3D dirVec = vectorFromTwoPoints(p1, p2);
    if (dirVec.isZeroVector(EPSILON)) {
        throw std::invalid_argument("The two points are coincident, cannot define a unique line.");
    }
    DirectionRatios dr = directionRatiosFromVector(dirVec);
    std::vector<LineEquationResult> results;
    results.push_back(lineEqVectorForm(p1, dirVec)); // Use p1 as the point
    results.push_back(lineEqCartesianSymmetric(p1, dr));
    return results;
}

AngleBetweenLinesResult angleBetweenLines(const Vector3D& dir1, const Vector3D& dir2) {
    if (dir1.isZeroVector(EPSILON) || dir2.isZeroVector(EPSILON)) {
        throw std::invalid_argument("Direction vectors cannot be zero for angle calculation.");
    }
    DotProductResult dpRes = dotProduct(dir1, dir2);
    if (!dpRes.angleRadians.has_value()) { // Should not happen if vectors are non-zero and dotProduct is correct
         throw std::runtime_error("Could not compute angle from dot product, check vector magnitudes.");
    }
    return AngleBetweenLinesResult(dir1, dir2, dpRes.angleRadians.value(), dpRes.angleDegrees.value());
}

// ... Implementations for linesRelationship, distancePointLine, imageOfPointInLine will follow ...
// ... Implementations for Plane functions will follow ...
// ... (Previous code from three_d_utils.cc Part 1) ...

    // (Continuing from Part 1)
    
    LinesRelationshipResult linesRelationship(const Point3D& p1_pt, const Vector3D& d1_vec, const Point3D& p2_pt, const Vector3D& d2_vec) {
        if (d1_vec.isZeroVector(EPSILON) || d2_vec.isZeroVector(EPSILON)) {
            throw std::invalid_argument("Direction vectors for lines cannot be zero.");
        }
    
        LineEquationResult line1Def = lineEqVectorForm(p1_pt, d1_vec);
        LineEquationResult line2Def = lineEqVectorForm(p2_pt, d2_vec);
    
        Vector3D p1p2 = vectorFromTwoPoints(p1_pt, p2_pt); // Vector from point on line1 to point on line2
        Vector3D d1_cross_d2 = d1_vec.cross(d2_vec);
    
        if (d1_cross_d2.isZeroVector(EPSILON)) { // Lines are parallel
            // Check if collinear: vector P1P2 must be parallel to d1 (or d2)
            // i.e., P1P2 x d1 = 0
            if (p1p2.cross(d1_vec).isZeroVector(EPSILON)) {
                return LinesRelationshipResult("collinear (same line)", line1Def, line2Def, std::nullopt, 0.0);
            } else {
                // Distance between parallel lines = |P1P2 x d1| / |d1|
                double dist = p1p2.cross(d1_vec).magnitude() / d1_vec.magnitude();
                return LinesRelationshipResult("parallel_distinct", line1Def, line2Def, std::nullopt, dist);
            }
        } else { // Lines are skew or intersecting
            // Check for intersection: Scalar Triple Product [P1P2 d1 d2] must be 0
            double stp = p1p2.dot(d1_cross_d2);
            double shortest_dist = std::abs(stp) / d1_cross_d2.magnitude();
    
            if (std::abs(stp) < EPSILON) { // Lines intersect (shortest_dist is effectively 0)
                // Find intersection point: p1 + t*d1 = p2 + s*d2
                // One way to find t for line1: t = ((P2-P1) x d2) . (d1 x d2) / |d1 x d2|^2
                // Note: P2-P1 is p1p2 but from p1's perspective, so (p2_pt - p1_pt)
                Vector3D p2_minus_p1 = vectorFromTwoPoints(p1_pt, p2_pt);
                double t_numerator = (p2_minus_p1.cross(d2_vec)).dot(d1_cross_d2);
                double t_denominator = d1_cross_d2.dot(d1_cross_d2); // |d1 x d2|^2
    
                if (std::abs(t_denominator) < EPSILON) { // Should not happen if d1_cross_d2 is non-zero
                    return LinesRelationshipResult("intersecting (calculation issue)", line1Def, line2Def, std::nullopt, 0.0);
                }
                double t = t_numerator / t_denominator;
                Point3D intersection_pt = p1_pt.toVector3D().add(d1_vec.scalarMultiply(t)).toPoint3D();
                return LinesRelationshipResult("intersecting", line1Def, line2Def, intersection_pt, 0.0);
            } else { // Lines are skew
                return LinesRelationshipResult("skew", line1Def, line2Def, std::nullopt, shortest_dist);
            }
        }
    }
    
    DistancePointLineResult distancePointLine(const Point3D& point, const Point3D& linePoint, const Vector3D& lineDir) {
        if (lineDir.isZeroVector(EPSILON)) {
            throw std::invalid_argument("Line direction vector cannot be zero.");
        }
        Vector3D ap = vectorFromTwoPoints(linePoint, point); // Vector from point on line to the given point
        
        // Distance = |AP x lineDir| / |lineDir|
        Vector3D crossProd_ap_lineDir = ap.cross(lineDir);
        double distance = crossProd_ap_lineDir.magnitude() / lineDir.magnitude();
    
        // Foot of perpendicular (M) on line: M = linePoint + t * lineDir_unit
        // t_param_for_projection = (AP . lineDir) / |lineDir|^2
        // Foot = linePoint + t_param_for_projection * lineDir
        double t_param = ap.dot(lineDir) / lineDir.dot(lineDir); // lineDir.dot(lineDir) is |lineDir|^2
        Point3D foot = linePoint.toVector3D().add(lineDir.scalarMultiply(t_param)).toPoint3D();
        
        LineEquationResult lineDef = lineEqVectorForm(linePoint, lineDir);
        return DistancePointLineResult(point, lineDef, distance, foot);
    }
    
    ImagePointResult imageOfPointInLine(const Point3D& point, const LineEquationResult& line) {
        if (!line.pointOnLine.has_value() || !line.directionVector.has_value()) {
            throw std::invalid_argument("Line definition must include a point and a direction vector.");
        }
        if (line.directionVector.value().isZeroVector(EPSILON)) {
            throw std::invalid_argument("Line direction vector cannot be zero for image calculation.");
        }
    
        Point3D linePt = line.pointOnLine.value();
        Vector3D lineDir = line.directionVector.value();
    
        DistancePointLineResult distRes = distancePointLine(point, linePt, lineDir);
        Point3D foot = distRes.footOfPerpendicular.value(); // footOfPerpendicular should always be calculable
    
        // Image P' = Foot + (Foot - P_original) = 2*Foot - P_original
        Vector3D imageVec = foot.toVector3D().scalarMultiply(2.0).subtract(point.toVector3D());
        Point3D imagePoint = imageVec.toPoint3D();
    
        return ImagePointResult(point, imagePoint, foot, "line", line.equationStr);
    }
    
    
    // --- 28. THE PLANE ---
    PlaneEquationResult planeEqVectorNormalForm(const Vector3D& normalIn, double distanceFromOrigin) {
        if (normalIn.isZeroVector(EPSILON)) {
            throw std::invalid_argument("Normal vector for a plane cannot be zero.");
        }
        Vector3D unitNormal = normalIn.normalize(); // Throws if normalIn is zero
        
        Vector3D nEff = unitNormal;
        double dEff = distanceFromOrigin;
        // Standard form usually has d >= 0. If d < 0, flip normal and d.
        if (dEff < -EPSILON) { // Check against -EPSILON for negative numbers
            dEff = -dEff;
            nEff = unitNormal.scalarMultiply(-1.0);
        }
        std::ostringstream oss;
        oss << "r . " << nEff.toString() << " = " << f_eq(dEff);
        
        // For Ax+By+Cz+D=0 form, if r.n_unit = d, then n_unit_x*x + n_unit_y*y + n_unit_z*z - d = 0
        // So A=nEff.x, B=nEff.y, C=nEff.z, D_lhs = -dEff
        PlaneEquationCoefficients coeffs(nEff.x, nEff.y, nEff.z, -dEff);
    
        return PlaneEquationResult("vector_normal_form", oss.str(), nEff, dEff, coeffs);
    }
    
    PlaneEquationResult planeEqCartesianFromNormalPoint(const Vector3D& normal, const Point3D& pointOnPlane) {
        if (normal.isZeroVector(EPSILON)) {
            throw std::invalid_argument("Normal vector for a plane cannot be zero.");
        }
        // Equation: A(x-x0) + B(y-y0) + C(z-z0) = 0
        //  => Ax + By + Cz - (A*x0 + B*y0 + C*z0) = 0
        // So D_lhs = -(A*x0 + B*y0 + C*z0) = -normal.dot(pointOnPlane.toVector3D())
        double A = normal.x;
        double B = normal.y;
        double C = normal.z;
        double D_lhs = -normal.dot(pointOnPlane.toVector3D());
        
        PlaneEquationCoefficients coeffs(A, B, C, D_lhs);
        
        return PlaneEquationResult("cartesian_form_normal_point", coeffs.toString(), normal, std::nullopt, coeffs);
    }
    
    PlaneEquationResult planeEqFromCoefficients(const PlaneEquationCoefficients& coeffs) {
        Vector3D normal(coeffs.a, coeffs.b, coeffs.c);
        if (normal.isZeroVector(EPSILON)) {
             throw std::invalid_argument("Coefficients A,B,C for normal vector cannot all be zero.");
        }
        
        double mag_normal = normal.magnitude();
        // For normal form r.n_unit = d, where d = -D_lhs / |N| (if D_lhs refers to Ax+By+Cz+D_lhs=0)
        // We want d >= 0.
        double d_candidate = -coeffs.d_lhs / mag_normal;
        Vector3D n_unit_eff = normal.normalize();
        double d_eff = d_candidate;
    
        if (d_eff < -EPSILON) {
            d_eff = -d_eff;
            n_unit_eff = n_unit_eff.scalarMultiply(-1.0);
        }
        
        return PlaneEquationResult("cartesian_form_coeffs", coeffs.toString(), normal, d_eff, coeffs);
    }
    
    
    PlaneEquationResult planeEqFromThreePoints(const Point3D& p1, const Point3D& p2, const Point3D& p3) {
        Vector3D v12 = vectorFromTwoPoints(p1, p2);
        Vector3D v13 = vectorFromTwoPoints(p1, p3);
        Vector3D normal = v12.cross(v13);
    
        if (normal.isZeroVector(EPSILON)) {
            throw std::invalid_argument("The three points are collinear and do not define a unique plane.");
        }
        // Use p1 as a point on the plane
        return planeEqCartesianFromNormalPoint(normal, p1);
    }
    
    AngleBetweenPlanesResult angleBetweenPlanes(const PlaneEquationResult& plane1, const PlaneEquationResult& plane2) {
        if (!plane1.normalVector.has_value() || !plane2.normalVector.has_value()) {
            throw std::invalid_argument("Plane definitions must include normal vectors for angle calculation.");
        }
        Vector3D n1 = plane1.normalVector.value();
        Vector3D n2 = plane2.normalVector.value();
    
        // Angle between planes is the angle between their normals
        AngleBetweenLinesResult angleLinesRes = angleBetweenLines(n1, n2);
        return AngleBetweenPlanesResult(angleLinesRes.angleRadians, angleLinesRes.angleDegrees, plane1, plane2);
    }
    
    AngleLinePlaneResult angleLinePlane(const LineEquationResult& line, const PlaneEquationResult& plane) {
        if (!line.directionVector.has_value() || !plane.normalVector.has_value()) {
            throw std::invalid_argument("Line and Plane definitions must include direction/normal vectors.");
        }
        Vector3D lineDir = line.directionVector.value();
        Vector3D planeNormal = plane.normalVector.value();
    
        if (lineDir.isZeroVector(EPSILON) || planeNormal.isZeroVector(EPSILON)) {
            throw std::invalid_argument("Direction/normal vector(s) cannot be zero for angle calculation.");
        }
    
        // Let θ be the angle between lineDir and planeNormal.
        // sin(α) = |cos(θ)| = |(lineDir . planeNormal) / (|lineDir| * |planeNormal|)|
        // where α is the angle between the line and the plane.
        double dot_prod_abs = std::abs(lineDir.dot(planeNormal));
        double mag_mult = lineDir.magnitude() * planeNormal.magnitude();
    
        if (std::abs(mag_mult) < EPSILON) { // Should be caught by isZeroVector checks
            throw std::runtime_error("Magnitude product is zero, cannot calculate angle for line and plane.");
        }
        
        double sinAlpha = dot_prod_abs / mag_mult;
        sinAlpha = std::max(-1.0, std::min(1.0, sinAlpha)); // Clamp for precision
    
        double alphaRadians = std::asin(sinAlpha);
        double alphaDegrees = toDegrees(alphaRadians);
    
        return AngleLinePlaneResult(alphaRadians, alphaDegrees, line, plane);
    }
    
    // ... Implementations for RelationshipLinePlaneResult, DistancePointPlaneResult, etc. will follow in Part 3 ...
    // ... (Previous code from three_d_utils.cc Part 1 and Part 2) ...


    // (Continuing from Part 2)
    
    RelationshipLinePlaneResult relationshipLinePlane(const LineEquationResult& line, const PlaneEquationCoefficients& planeCoeffs) {
        if (!line.directionVector.has_value() || !line.pointOnLine.has_value()) {
            throw std::invalid_argument("Line definition must include point and direction vector.");
        }
        Vector3D lineDir = line.directionVector.value();
        Point3D linePoint = line.pointOnLine.value();
        Vector3D planeNormal(planeCoeffs.a, planeCoeffs.b, planeCoeffs.c);
        double D_lhs = planeCoeffs.d_lhs;
    
        if (planeNormal.isZeroVector(EPSILON)) {
            throw std::invalid_argument("Plane normal vector derived from coefficients (A,B,C) cannot be zero.");
        }
        PlaneEquationResult planeDef = planeEqFromCoefficients(planeCoeffs); // For returning in result
    
        double N_dot_d = planeNormal.dot(lineDir);
    
        if (std::abs(N_dot_d) < EPSILON) { // Line direction is perpendicular to plane normal => Line is parallel to plane
            // Check if point on line lies on the plane: A*px + B*py + C*pz + D_lhs = 0
            double valAtPoint = planeNormal.dot(linePoint.toVector3D()) + D_lhs;
            if (std::abs(valAtPoint) < EPSILON) { // Point on line is on the plane
                return RelationshipLinePlaneResult("line_lies_in_plane", line, planeDef, std::nullopt, 0.0);
            } else { // Point on line is not on the plane
                // Distance from point on line to plane = |A*px + B*py + C*pz + D_lhs| / |N|
                double dist = std::abs(valAtPoint) / planeNormal.magnitude();
                return RelationshipLinePlaneResult("line_parallel_to_plane_distinct", line, planeDef, std::nullopt, dist);
            }
        } else { // Line intersects the plane
            // Parameter λ for intersection: r = linePoint + λ*lineDir
            // Substitute into plane equation: A(x) + B(y) + C(z) + D_lhs = 0
            // N . (linePoint + λ*lineDir) + D_lhs = 0
            // N . linePoint + λ*(N . lineDir) + D_lhs = 0
            // λ*(N . lineDir) = -(N . linePoint + D_lhs)
            double lambda_numerator = -(planeNormal.dot(linePoint.toVector3D()) + D_lhs);
            double lambda = lambda_numerator / N_dot_d;
            
            Point3D intersectionPoint = linePoint.toVector3D().add(lineDir.scalarMultiply(lambda)).toPoint3D();
            return RelationshipLinePlaneResult("line_intersects_plane", line, planeDef, intersectionPoint, std::nullopt);
        }
    }
    
    DistancePointPlaneResult distancePointPlane(const Point3D& point, const PlaneEquationCoefficients& planeCoeffs) {
        double A = planeCoeffs.a;
        double B = planeCoeffs.b;
        double C = planeCoeffs.c;
        double D_lhs = planeCoeffs.d_lhs; // For Ax+By+Cz+D_lhs = 0
    
        Vector3D normal(A, B, C);
        if (normal.isZeroVector(EPSILON)) {
            throw std::invalid_argument("Plane normal vector (A,B,C) derived from coefficients is zero, plane is ill-defined.");
        }
        PlaneEquationResult planeDef = planeEqFromCoefficients(planeCoeffs);
    
    
        // Distance = |Ax0 + By0 + Cz0 + D_lhs| / sqrt(A^2 + B^2 + C^2)
        double numerator = std::abs(A * point.x + B * point.y + C * point.z + D_lhs);
        double denominator = normal.magnitude();
        
        double dist = (std::abs(denominator) < EPSILON) ? 0.0 : (numerator / denominator); // Avoid div by zero if somehow normal was not zero but mag is.
    
        // Foot of perpendicular: P_foot = Point - t_signed_dist * Normal_unit_vector
        // where signed_distance_t = (A*x0 + B*y0 + C*z0 + D_lhs) / |N|
        double signed_distance_t = (A * point.x + B * point.y + C * point.z + D_lhs) / denominator;
        Vector3D unitNormal = normal.normalize(); // Safe if normal is not zero
        Point3D foot = point.toVector3D().subtract(unitNormal.scalarMultiply(signed_distance_t)).toPoint3D();
        
        return DistancePointPlaneResult(point, planeDef, dist, foot);
    }
    
    IntersectionLinePlaneResult intersectionLinePlane(const LineEquationResult& line, const PlaneEquationCoefficients& planeCoeffs) {
        RelationshipLinePlaneResult rel = relationshipLinePlane(line, planeCoeffs);
        bool intersects_flag = false;
        std::optional<Point3D> intersection_pt_opt = std::nullopt;
        std::string msg = rel.relationship; // Start with the relationship string
    
        if (rel.relationship == "line_intersects_plane") {
            intersects_flag = true;
            intersection_pt_opt = rel.intersectionPoint;
            msg = "Line intersects the plane at a single point.";
        } else if (rel.relationship == "line_lies_in_plane") {
            intersects_flag = true; // Infinitely many intersection points
            msg = "Line lies in the plane (infinite intersection points).";
        } else { // "line_parallel_to_plane_distinct"
            intersects_flag = false;
            msg = "Line is parallel to the plane and does not intersect.";
        }
        
        // The planeDef in rel is already created from planeCoeffs
        return IntersectionLinePlaneResult(intersects_flag, msg, intersection_pt_opt, line, rel.planeDefinition);
    }
    
    IntersectionTwoPlanesResult intersectionTwoPlanes(const PlaneEquationCoefficients& p1Coeffs, const PlaneEquationCoefficients& p2Coeffs) {
        Vector3D n1(p1Coeffs.a, p1Coeffs.b, p1Coeffs.c);
        double d1_lhs = p1Coeffs.d_lhs;
        PlaneEquationResult plane1Def = planeEqFromCoefficients(p1Coeffs);
    
        Vector3D n2(p2Coeffs.a, p2Coeffs.b, p2Coeffs.c);
        double d2_lhs = p2Coeffs.d_lhs;
        PlaneEquationResult plane2Def = planeEqFromCoefficients(p2Coeffs);
    
        if (n1.isZeroVector(EPSILON) || n2.isZeroVector(EPSILON)) {
            throw std::invalid_argument("Normal vector from plane coefficients cannot be zero.");
        }
    
        Vector3D lineDir_vec = n1.cross(n2);
    
        if (lineDir_vec.isZeroVector(EPSILON)) { // Planes are parallel
            // Check if they are the same plane.
            // A robust check: If n1 = k*n2, then planes are parallel. If also d1_lhs = k*d2_lhs, then coincident.
            // Or, pick a point on plane1 and check if it's on plane2.
            // Example point on plane1 (if p1Coeffs.a is not zero): (-d1_lhs/p1Coeffs.a, 0, 0)
            Point3D pointOnPlane1;
            bool p1_is_consistent = true; // Check if 0x+0y+0z+D=0 with D!=0
    
            if (std::abs(p1Coeffs.a) > EPSILON) pointOnPlane1 = Point3D(-d1_lhs / p1Coeffs.a, 0, 0);
            else if (std::abs(p1Coeffs.b) > EPSILON) pointOnPlane1 = Point3D(0, -d1_lhs / p1Coeffs.b, 0);
            else if (std::abs(p1Coeffs.c) > EPSILON) pointOnPlane1 = Point3D(0, 0, -d1_lhs / p1Coeffs.c);
            else { // n1 is zero vector, already checked. This path should not be hit due to initial check.
                // However, if it means 0x+0y+0z+D1=0
                if (std::abs(d1_lhs) > EPSILON) p1_is_consistent = false; // 0x+0y+0z = -D1 (non-zero), impossible
                // If d1_lhs is also zero, 0=0, it's all space.
            }
            
            if (!p1_is_consistent) {
                 return IntersectionTwoPlanesResult(false, "Plane 1 is inconsistent (0x+0y+0z+D=0, D!=0).", std::nullopt, plane1Def, plane2Def);
            }
            // If n1 was (0,0,0) and d1_lhs=0, pointOnPlane1 remains default (0,0,0), which satisfies 0=0.
    
            // Check if this point (or (0,0,0) if plane1 is 0=0) lies on plane2
            if (std::abs(n2.dot(pointOnPlane1.toVector3D()) + d2_lhs) < EPSILON) {
                // Point on plane1 is also on plane2. Since they are parallel, they are coincident.
                return IntersectionTwoPlanesResult(true, "Planes are coincident (same plane).", std::nullopt, plane1Def, plane2Def);
            } else {
                return IntersectionTwoPlanesResult(false, "Planes are parallel and distinct.", std::nullopt, plane1Def, plane2Def);
            }
        }
    
        // Planes intersect in a line. Find a point on this line.
        // Set one coordinate to 0 (e.g., z=0) and solve the 2D system:
        // A1x + B1y = -d1_lhs
        // A2x + B2y = -d2_lhs
        Point3D pointOnLine;
        // Using Cramer's rule or substitution. For Ax = B, x = A_inv * B
        // Matrix for [x,y] (when z=0): [[A1, B1], [A2, B2]] [x,y]^T = [-d1, -d2]^T
        double det_xy = p1Coeffs.a * p2Coeffs.b - p2Coeffs.a * p1Coeffs.b;
        // Matrix for [y,z] (when x=0): [[B1, C1], [B2, C2]] [y,z]^T = [-d1, -d2]^T
        double det_yz = p1Coeffs.b * p2Coeffs.c - p2Coeffs.b * p1Coeffs.c;
        // Matrix for [z,x] (when y=0) (or [x,z]): [[A1,C1],[A2,C2]] [x,z]^T = [-d1,-d2]^T
        double det_xz = p1Coeffs.a * p2Coeffs.c - p2Coeffs.a * p1Coeffs.c; // (x,z) order
    
        bool point_found = false;
        if (std::abs(det_xy) > EPSILON) { // Try setting z=0
            double x = (-d1_lhs * p2Coeffs.b - (-d2_lhs) * p1Coeffs.b) / det_xy;
            double y = (p1Coeffs.a * (-d2_lhs) - p2Coeffs.a * (-d1_lhs)) / det_xy;
            pointOnLine = Point3D(x, y, 0);
            point_found = true;
        } else if (std::abs(det_yz) > EPSILON) { // Try setting x=0
            double y = (-d1_lhs * p2Coeffs.c - (-d2_lhs) * p1Coeffs.c) / det_yz;
            double z = (p1Coeffs.b * (-d2_lhs) - p2Coeffs.b * (-d1_lhs)) / det_yz;
            pointOnLine = Point3D(0, y, z);
            point_found = true;
        } else if (std::abs(det_xz) > EPSILON) { // Try setting y=0
            double x = (-d1_lhs * p2Coeffs.c - (-d2_lhs) * p1Coeffs.c) / det_xz; // careful with order here. For x,z
            double z = (p1Coeffs.a * (-d2_lhs) - p2Coeffs.a * (-d1_lhs)) / det_xz; // if matrix was [[A,C],[A',C']]
            pointOnLine = Point3D(x, 0, z);
            point_found = true;
        }
        
        if (!point_found) {
            // This implies normals n1, n2 are not parallel (lineDir is non-zero),
            // but all 2x2 sub-determinants of the system for finding a point are zero.
            // This can happen if the line of intersection is parallel to one of the axes,
            // and we tried setting that axis's coordinate to zero.
            // E.g. if line is parallel to z-axis, x=x0, y=y0. det_xy would be zero.
            // A more robust general point finding method is needed for all edge cases,
            // or testing multiple combinations (e.g., setting z=1 instead of z=0).
            // For now, indicate a calculation issue if common point is not found this way.
            return IntersectionTwoPlanesResult(true, "Planes intersect, but finding a specific point on the line failed (edge case).",
                                               std::nullopt, plane1Def, plane2Def);
        }
    
        LineEquationResult lineOfIntersection = lineEqVectorForm(pointOnLine, lineDir_vec);
        return IntersectionTwoPlanesResult(true, "Planes intersect in a line.", lineOfIntersection, plane1Def, plane2Def);
    }
    
    CoplanarityLinesResult checkCoplanarityLines(const LineEquationResult& line1, const LineEquationResult& line2) {
        if (!line1.pointOnLine.has_value() || !line1.directionVector.has_value() ||
            !line2.pointOnLine.has_value() || !line2.directionVector.has_value()) {
            throw std::invalid_argument("Both line definitions must include point and direction vector.");
        }
        Point3D p1 = line1.pointOnLine.value(); Vector3D d1 = line1.directionVector.value();
        Point3D p2 = line2.pointOnLine.value(); Vector3D d2 = line2.directionVector.value();
    
        if (d1.isZeroVector(EPSILON) || d2.isZeroVector(EPSILON)) {
            throw std::invalid_argument("Direction vectors for lines cannot be zero.");
        }
    
        Vector3D p1p2 = vectorFromTwoPoints(p1, p2);
        // Lines are coplanar if the scalar triple product [P1P2 d1 d2] = 0
        ScalarTripleProductResult stpRes = scalarTripleProduct(p1p2, d1, d2);
        
        std::optional<PlaneEquationResult> planeContaining = std::nullopt;
        std::string reason;
    
        if (stpRes.areCoplanar) {
            Vector3D d1_cross_d2 = d1.cross(d2);
            if (d1_cross_d2.isZeroVector(EPSILON)) { // Parallel lines
                // Check if P1P2 is also parallel to d1 (collinear)
                if (p1p2.isZeroVector(EPSILON) || p1p2.cross(d1).isZeroVector(EPSILON)) {
                    reason = "Lines are collinear (same line).";
                } else {
                    reason = "Lines are parallel and distinct, thus coplanar.";
                }
                // Plane containing them: normal = (P1P2 x d1), point = p1
                // (Only if P1P2 is not parallel to d1, i.e., not collinear)
                if (reason == "Lines are parallel and distinct, thus coplanar.") {
                    Vector3D planeNormal = p1p2.cross(d1);
                    if (!planeNormal.isZeroVector(EPSILON)) { // Should be non-zero if distinct parallel
                        planeContaining = planeEqCartesianFromNormalPoint(planeNormal, p1);
                    } else { // This implies P1P2 was parallel to d1, so collinear. Already handled.
                        reason += " (Issue defining unique plane if collinear).";
                    }
                } else if (reason == "Lines are collinear (same line).") {
                    // Infinitely many planes. Pick one. e.g. normal perpendicular to d1.
                    // If d1 = (a,b,c), try normal (-b,a,0) or similar to get non-zero.
                    Vector3D arb_n;
                    if (std::abs(d1.x) > EPSILON || std::abs(d1.y) > EPSILON) arb_n = Vector3D(-d1.y, d1.x, 0);
                    else if (std::abs(d1.y) > EPSILON || std::abs(d1.z) > EPSILON) arb_n = Vector3D(0, -d1.z, d1.y);
                    else arb_n = Vector3D(d1.z, 0, -d1.x); // Last resort if d1 is along an axis
    
                    if (!arb_n.isZeroVector(EPSILON)) {
                        planeContaining = planeEqCartesianFromNormalPoint(arb_n.normalize(), p1);
                    } else { // d1 was likely (0,0,0), should be caught earlier.
                         reason += " (Cannot define arbitrary plane for collinear lines if direction is zero).";
                    }
                }
            } else { // Intersecting lines
                reason = "Lines are intersecting and coplanar.";
                // Plane containing them: normal = (d1 x d2), point = p1 (or p2)
                planeContaining = planeEqCartesianFromNormalPoint(d1_cross_d2, p1);
            }
            return CoplanarityLinesResult(true, reason, planeContaining, line1, line2);
        } else {
            reason = "Lines are skew (not coplanar).";
            return CoplanarityLinesResult(false, reason, std::nullopt, line1, line2);
        }
    }
    
    ImagePointResult imageOfPointInPlane(const Point3D& point, const PlaneEquationCoefficients& planeCoeffs) {
        DistancePointPlaneResult distRes = distancePointPlane(point, planeCoeffs);
        // footOfPerpendicular should always be calculated by distancePointPlane
        if (!distRes.footOfPerpendicular.has_value()){
            throw std::runtime_error("Could not determine foot of perpendicular for image calculation.");
        }
        Point3D foot = distRes.footOfPerpendicular.value();
        
        // Image P' = Foot + (Foot - P_original) = 2*Foot - P_original
        Vector3D imageVec = foot.toVector3D().scalarMultiply(2.0).subtract(point.toVector3D());
        Point3D imagePoint = imageVec.toPoint3D();
        
        return ImagePointResult(point, imagePoint, foot, "plane", distRes.planeDefinition.equationStr);
    }
    
    
  
} // namespace three_d_geometry
} // namespace michu_fr