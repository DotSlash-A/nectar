#ifndef THREE_D_TYPES_H
#define THREE_D_TYPES_H

#include <string>
#include <vector>
#include <map>
#include <sstream>    // For std::ostringstream
#include <optional>   // For std::optional (C++17)
#include <iomanip>    // For std::fixed, std::setprecision
#include <cmath>      // For std::abs, std::sqrt, std::pow, M_PI (if available)
#include <stdexcept>  // For exceptions

// Define M_PI if not available (e.g., on MSVC without _USE_MATH_DEFINES)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace michu_fr {
namespace three_d_geometry {

// --- Forward Declarations for inter-dependencies if any (not strictly needed here yet) ---
struct Vector3D;
struct Point3D;
struct LineEquationResult; // For results that contain line equations
struct PlaneEquationResult; // For results that contain plane equations

// --- Basic Geometric Entities ---
struct Point3D {
    double x, y, z;

    Point3D(double x_val = 0.0, double y_val = 0.0, double z_val = 0.0)
        : x(x_val), y(y_val), z(z_val) {}

    Vector3D toVector3D() const; // Implementation after Vector3D

    std::string toString(int precision = 2) const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(precision);
        oss << "(" << x << ", " << y << ", " << z << ")";
        return oss.str();
    }

    bool operator==(const Point3D& other) const {
        double epsilon = 1e-9;
        return std::abs(x - other.x) < epsilon &&
               std::abs(y - other.y) < epsilon &&
               std::abs(z - other.z) < epsilon;
    }
};

struct Vector3D {
    double x, y, z;

    Vector3D(double x_val = 0.0, double y_val = 0.0, double z_val = 0.0)
        : x(x_val), y(y_val), z(z_val) {}

    Point3D toPoint3D() const {
        return Point3D(x, y, z);
    }

    double magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector3D normalize() const {
        double mag = magnitude();
        if (std::abs(mag) < 1e-9) {
            throw std::runtime_error("Cannot normalize a zero vector.");
        }
        return Vector3D(x / mag, y / mag, z / mag);
    }

    Vector3D add(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    Vector3D subtract(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    Vector3D scalarMultiply(double scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    double dot(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3D cross(const Vector3D& other) const {
        return Vector3D(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    bool isZeroVector(double epsilon = 1e-9) const {
        return std::abs(x) < epsilon && std::abs(y) < epsilon && std::abs(z) < epsilon;
    }

    std::string toString(int precision = 2) const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(precision);
        oss << x << "i";
        if (y >= 0) oss << " + " << y << "j"; else oss << " - " << std::abs(y) << "j";
        if (z >= 0) oss << " + " << z << "k"; else oss << " - " << std::abs(z) << "k";
        return oss.str();
    }
     bool operator==(const Vector3D& other) const {
        double epsilon = 1e-9;
        return std::abs(x - other.x) < epsilon &&
               std::abs(y - other.y) < epsilon &&
               std::abs(z - other.z) < epsilon;
    }
};

// Implementation of Point3D::toVector3D (needs Vector3D definition)
inline Vector3D Point3D::toVector3D() const {
    return Vector3D(x, y, z);
}


// --- Vector Algebra Results ---
struct MagnitudeResult {
    Vector3D vector;
    double magnitude;

    MagnitudeResult(Vector3D v, double m) : vector(v), magnitude(m) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << "MagnitudeResult{vector=" << vector.toString()
            << ", magnitude=" << std::fixed << std::setprecision(4) << magnitude << "}";
        return oss.str();
    }
};

struct UnitVectorResult {
    Vector3D originalVector;
    Vector3D unitVector;
    double calculatedMagnitude; // Should be 1.0

    UnitVectorResult(Vector3D ov, Vector3D uv)
        : originalVector(ov), unitVector(uv), calculatedMagnitude(uv.magnitude()) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << "UnitVectorResult{original=" << originalVector.toString()
            << ", unit=" << unitVector.toString()
            << ", mag=" << std::fixed << std::setprecision(4) << calculatedMagnitude << "}";
        return oss.str();
    }
};

struct SectionFormulaResult {
    Point3D resultingPoint;
    Point3D p1;
    Point3D p2;
    double ratioM;
    double ratioN;
    std::string divisionType; // "internal" or "external"

    SectionFormulaResult(Point3D rp, Point3D pt1, Point3D pt2, double m, double n, std::string dt)
        : resultingPoint(rp), p1(pt1), p2(pt2), ratioM(m), ratioN(n), divisionType(std::move(dt)) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << "SectionFormulaResult{point=" << resultingPoint.toString()
            << ", p1=" << p1.toString() << ", p2=" << p2.toString()
            << ", m=" << ratioM << ", n=" << ratioN << ", type='" << divisionType << "'}";
        return oss.str();
    }
};

struct CollinearityResult {
    bool areCollinear;
    std::string reason;
    std::vector<Point3D> points;

    CollinearityResult(bool ac, std::string r, std::vector<Point3D> pts)
        : areCollinear(ac), reason(std::move(r)), points(std::move(pts)) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << "CollinearityResult{areCollinear=" << (areCollinear ? "true" : "false")
            << ", reason='" << reason << "', points=[";
        for (size_t i = 0; i < points.size(); ++i) {
            oss << points[i].toString() << (i == points.size() - 1 ? "" : ", ");
        }
        oss << "]}";
        return oss.str();
    }
};

// --- Scalar and Vector Product Results ---
struct DotProductResult {
    Vector3D vector1;
    Vector3D vector2;
    double dotProduct;
    std::optional<double> angleRadians;
    std::optional<double> angleDegrees;

    DotProductResult(Vector3D v1, Vector3D v2, double dp, std::optional<double> ar, std::optional<double> ad)
        : vector1(v1), vector2(v2), dotProduct(dp), angleRadians(ar), angleDegrees(ad) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(4);
        oss << "DotProductResult{v1=" << vector1.toString() << ", v2=" << vector2.toString()
            << ", dotProduct=" << dotProduct;
        if (angleDegrees.has_value()) {
            oss << ", angleDegrees=" << std::setprecision(2) << angleDegrees.value();
        }
        oss << "}";
        return oss.str();
    }
};

struct ProjectionResult {
    Vector3D vectorA; // Vector being projected
    Vector3D vectorB; // Vector onto which A is projected
    double scalarProjection;
    Vector3D vectorProjection;

    ProjectionResult(Vector3D va, Vector3D vb, double sp, Vector3D vp)
        : vectorA(va), vectorB(vb), scalarProjection(sp), vectorProjection(vp) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << "ProjectionResult{A=" << vectorA.toString() << ", ontoB=" << vectorB.toString()
            << ", scalarProj=" << std::fixed << std::setprecision(4) << scalarProjection
            << ", vectorProj=" << vectorProjection.toString() << "}";
        return oss.str();
    }
};

struct CrossProductResult {
    Vector3D vector1;
    Vector3D vector2;
    Vector3D crossProductVector;
    std::optional<double> magnitudeOfCrossProduct;
    std::optional<double> areaOfParallelogram; // Same as magnitude

    CrossProductResult(Vector3D v1, Vector3D v2, Vector3D cpv, std::optional<double> mag)
        : vector1(v1), vector2(v2), crossProductVector(cpv), magnitudeOfCrossProduct(mag), areaOfParallelogram(mag) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << "CrossProductResult{v1=" << vector1.toString() << ", v2=" << vector2.toString()
            << ", crossProduct=" << crossProductVector.toString();
        if (areaOfParallelogram.has_value()) {
            oss << ", areaParallelogram=" << std::fixed << std::setprecision(4) << areaOfParallelogram.value();
        }
        oss << "}";
        return oss.str();
    }
};

struct AreaTriangleResult {
    double area;
    std::map<std::string, std::string> context; // e.g., vertices or vectors used

    AreaTriangleResult(double a, std::map<std::string, std::string> ctx)
        : area(a), context(std::move(ctx)) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << "AreaTriangleResult{area=" << std::fixed << std::setprecision(4) << area << ", context={";
        bool first = true;
        for(const auto& pair : context) {
            if (!first) oss << ", ";
            oss << pair.first << ":" << pair.second;
            first = false;
        }
        oss << "}}";
        return oss.str();
    }
};

struct ScalarTripleProductResult {
    Vector3D vectorA;
    Vector3D vectorB;
    Vector3D vectorC;
    double scalarTripleProduct; // Volume of parallelepiped
    bool areCoplanar;

    ScalarTripleProductResult(Vector3D va, Vector3D vb, Vector3D vc, double stp, bool ac)
        : vectorA(va), vectorB(vb), vectorC(vc), scalarTripleProduct(stp), areCoplanar(ac) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << "ScalarTripleProductResult{stp(volume)=" << std::fixed << std::setprecision(4) << scalarTripleProduct
            << ", areCoplanar=" << (areCoplanar ? "true" : "false")
            << ", a=" << vectorA.toString() << ", b=" << vectorB.toString() << ", c=" << vectorC.toString() << "}";
        return oss.str();
    }
};

// --- Direction Cosines and Ratios ---
struct DirectionRatios {
    double a, b, c;
    DirectionRatios(double aval=0, double bval=0, double cval=0) : a(aval), b(bval), c(cval) {}
    std::string toString(int precision = 2) const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(precision);
        oss << "<" << a << ", " << b << ", " << c << ">";
        return oss.str();
    }
};

struct DirectionCosines {
    double l, m, n;
    bool isValidSet;

    DirectionCosines(double lval=0, double mval=0, double nval=0, bool valid = false)
        : l(lval), m(mval), n(nval), isValidSet(valid) {}

    std::string toString(int precision = 4) const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(precision);
        oss << "l=" << l << ", m=" << m << ", n=" << n
            << " (Valid: " << (isValidSet ? "true" : "false") << ")";
        return oss.str();
    }
};

// --- Straight Line Results ---
struct LineEquationResult {
    std::string type; // e.g., "vector_form", "cartesian_symmetric_form"
    std::string equationStr;
    std::optional<Point3D> pointOnLine;
    std::optional<Vector3D> directionVector;
    std::optional<DirectionRatios> directionRatios; // Can be derived from vector

    LineEquationResult(std::string t, std::string eq,
                       std::optional<Point3D> p = std::nullopt,
                       std::optional<Vector3D> dv = std::nullopt,
                       std::optional<DirectionRatios> dr = std::nullopt)
        : type(std::move(t)), equationStr(std::move(eq)), pointOnLine(p), directionVector(dv), directionRatios(dr) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << "LineEquationResult{type='" << type << "', eq='" << equationStr << "'";
        if (pointOnLine.has_value()) oss << ", point=" << pointOnLine.value().toString();
        if (directionVector.has_value()) oss << ", dirVec=" << directionVector.value().toString();
        if (directionRatios.has_value()) oss << ", dirRat=" << directionRatios.value().toString();
        oss << "}";
        return oss.str();
    }
};

struct AngleBetweenLinesResult {
    std::optional<LineEquationResult> line1Def; // Could be just vectors
    std::optional<LineEquationResult> line2Def;
    std::optional<Vector3D> dir1; // More direct
    std::optional<Vector3D> dir2;
    double angleRadians;
    double angleDegrees;

    AngleBetweenLinesResult(std::optional<Vector3D> d1, std::optional<Vector3D> d2, double ar, double ad)
        : dir1(d1), dir2(d2), angleRadians(ar), angleDegrees(ad) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << std::fixed;
        oss << "AngleBetweenLinesResult{angleDegrees=" << std::setprecision(2) << angleDegrees;
        if(dir1.has_value()) oss << ", dir1=" << dir1.value().toString();
        if(dir2.has_value()) oss << ", dir2=" << dir2.value().toString();
        oss << "}";
        return oss.str();
    }
};

struct LinesRelationshipResult {
    std::optional<LineEquationResult> line1Definition;
    std::optional<LineEquationResult> line2Definition;
    std::string relationship; // "parallel_distinct", "collinear", "intersecting", "skew"
    std::optional<Point3D> intersectionPoint;
    std::optional<double> shortestDistance;

    LinesRelationshipResult(std::string rel,
                            std::optional<LineEquationResult> l1d = std::nullopt,
                            std::optional<LineEquationResult> l2d = std::nullopt,
                            std::optional<Point3D> ip = std::nullopt,
                            std::optional<double> sd = std::nullopt)
        : line1Definition(l1d), line2Definition(l2d), relationship(std::move(rel)),
          intersectionPoint(ip), shortestDistance(sd) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << "LinesRelationshipResult{relationship='" << relationship << "'";
        if (intersectionPoint.has_value()) oss << ", intersection=" << intersectionPoint.value().toString();
        if (shortestDistance.has_value()) oss << ", shortestDist=" << std::fixed << std::setprecision(4) << shortestDistance.value();
        // Optionally print line definitions if needed
        oss << "}";
        return oss.str();
    }
};

struct DistancePointLineResult {
    Point3D point;
    LineEquationResult lineDefinition;
    double distance;
    std::optional<Point3D> footOfPerpendicular;

    DistancePointLineResult(Point3D p, LineEquationResult ld, double d, std::optional<Point3D> fop)
        : point(p), lineDefinition(ld), distance(d), footOfPerpendicular(fop) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << "DistancePointLineResult{point=" << point.toString()
            << ", lineEq='" << lineDefinition.equationStr << "'"
            << ", distance=" << std::fixed << std::setprecision(4) << distance;
        if (footOfPerpendicular.has_value()) oss << ", foot=" << footOfPerpendicular.value().toString();
        oss << "}";
        return oss.str();
    }
};

struct ImagePointResult { // Generic for line or plane
    Point3D originalPoint;
    Point3D imagePoint;
    Point3D footOfPerpendicular;
    std::string inObjectType; // "line" or "plane"
    std::string objectDefinitionStr;

    ImagePointResult(Point3D op, Point3D ip, Point3D fop, std::string objType, std::string objDef)
        : originalPoint(op), imagePoint(ip), footOfPerpendicular(fop),
          inObjectType(std::move(objType)), objectDefinitionStr(std::move(objDef)) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << "ImagePointResult{original=" << originalPoint.toString()
            << ", image=" << imagePoint.toString()
            << ", foot=" << footOfPerpendicular.toString()
            << ", in " << inObjectType << "='" << objectDefinitionStr << "'}";
        return oss.str();
    }
};


// --- Plane Results ---
struct PlaneEquationCoefficients { // Input type
    double a, b, c, d_lhs; // For Ax + By + Cz + D_lhs = 0
    // D_rhs would be -d_lhs if Ax + By + Cz = D_rhs

    PlaneEquationCoefficients(double aval, double bval, double cval, double dlhs_val)
        : a(aval), b(bval), c(cval), d_lhs(dlhs_val) {}
    std::string toString(int precision = 2) const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(precision);
        oss << a << "x";
        if (b >= 0) oss << " + " << b << "y"; else oss << " - " << std::abs(b) << "y";
        if (c >= 0) oss << " + " << c << "z"; else oss << " - " << std::abs(c) << "z";
        if (d_lhs >= 0) oss << " + " << d_lhs; else oss << " - " << std::abs(d_lhs);
        oss << " = 0";
        return oss.str();
    }
};

struct PlaneEquationResult {
    std::string type; // "vector_normal_form", "cartesian_form", etc.
    std::string equationStr;
    std::optional<Vector3D> normalVector;
    std::optional<double> distanceFromOrigin; // For normal form r.n_unit = d
    std::optional<PlaneEquationCoefficients> coeffsCartesian; // For Ax+By+Cz+D=0

    PlaneEquationResult(std::string t, std::string eq,
                        std::optional<Vector3D> nv = std::nullopt,
                        std::optional<double> dfo = std::nullopt,
                        std::optional<PlaneEquationCoefficients> cc = std::nullopt)
        : type(std::move(t)), equationStr(std::move(eq)), normalVector(nv),
          distanceFromOrigin(dfo), coeffsCartesian(cc) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << "PlaneEquationResult{type='" << type << "', eq='" << equationStr << "'";
        if (normalVector.has_value()) oss << ", normal=" << normalVector.value().toString();
        if (distanceFromOrigin.has_value()) oss << ", distOrigin=" << std::fixed << std::setprecision(4) << distanceFromOrigin.value();
        if (coeffsCartesian.has_value()) oss << ", coeffs(Ax+By+Cz+D=0)=" << coeffsCartesian.value().toString();
        oss << "}";
        return oss.str();
    }
};

struct AngleBetweenPlanesResult {
    std::optional<PlaneEquationResult> plane1Def; // Could be just normals
    std::optional<PlaneEquationResult> plane2Def;
    double angleRadians;
    double angleDegrees;

    AngleBetweenPlanesResult(double ar, double ad,
                             std::optional<PlaneEquationResult> p1 = std::nullopt,
                             std::optional<PlaneEquationResult> p2 = std::nullopt)
        : plane1Def(p1), plane2Def(p2), angleRadians(ar), angleDegrees(ad) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << std::fixed;
        oss << "AngleBetweenPlanesResult{angleDegrees=" << std::setprecision(2) << angleDegrees;
        // Optionally print plane definitions if needed
        oss << "}";
        return oss.str();
    }
};

struct AngleLinePlaneResult {
    std::optional<LineEquationResult> lineDef;
    std::optional<PlaneEquationResult> planeDef;
    double angleRadians;
    double angleDegrees;

     AngleLinePlaneResult(double ar, double ad,
                         std::optional<LineEquationResult> ld = std::nullopt,
                         std::optional<PlaneEquationResult> pd = std::nullopt)
        : lineDef(ld), planeDef(pd), angleRadians(ar), angleDegrees(ad) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << std::fixed;
        oss << "AngleLinePlaneResult{angleDegrees=" << std::setprecision(2) << angleDegrees;
        // Optionally print definitions if needed
        oss << "}";
        return oss.str();
    }
};

struct RelationshipLinePlaneResult {
    std::optional<LineEquationResult> lineDefinition;
    std::optional<PlaneEquationResult> planeDefinition;
    std::string relationship; // "line_parallel_to_plane_distinct", "line_lies_in_plane", "line_intersects_plane"
    std::optional<Point3D> intersectionPoint;
    std::optional<double> distanceIfParallel;

    RelationshipLinePlaneResult(std::string rel,
                                std::optional<LineEquationResult> ld = std::nullopt,
                                std::optional<PlaneEquationResult> pd = std::nullopt,
                                std::optional<Point3D> ip = std::nullopt,
                                std::optional<double> dip = std::nullopt)
        : lineDefinition(ld), planeDefinition(pd), relationship(std::move(rel)),
          intersectionPoint(ip), distanceIfParallel(dip) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << "RelationshipLinePlaneResult{relationship='" << relationship << "'";
        if (intersectionPoint.has_value()) oss << ", intersection=" << intersectionPoint.value().toString();
        if (distanceIfParallel.has_value()) oss << ", distIfParallel=" << std::fixed << std::setprecision(4) << distanceIfParallel.value();
        oss << "}";
        return oss.str();
    }
};


struct DistancePointPlaneResult {
    Point3D point;
    PlaneEquationResult planeDefinition;
    double distance;
    std::optional<Point3D> footOfPerpendicular;

    DistancePointPlaneResult(Point3D p, PlaneEquationResult pd, double d, std::optional<Point3D> fop)
        : point(p), planeDefinition(pd), distance(d), footOfPerpendicular(fop) {}
     std::string toString() const {
        std::ostringstream oss;
        oss << "DistancePointPlaneResult{point=" << point.toString()
            << ", planeEq='" << planeDefinition.equationStr << "'"
            << ", distance=" << std::fixed << std::setprecision(4) << distance;
        if (footOfPerpendicular.has_value()) oss << ", foot=" << footOfPerpendicular.value().toString();
        oss << "}";
        return oss.str();
    }
};

struct IntersectionLinePlaneResult { // Can reuse RelationshipLinePlaneResult or be specific
    bool intersects;
    std::optional<Point3D> intersectionPoint;
    std::string message; // "intersects_at_point", "line_lies_in_plane", "line_parallel_distinct"
    std::optional<LineEquationResult> lineDef;
    std::optional<PlaneEquationResult> planeDef;


    IntersectionLinePlaneResult(bool i, std::string msg,
                                std::optional<Point3D> ip = std::nullopt,
                                std::optional<LineEquationResult> ld = std::nullopt,
                                std::optional<PlaneEquationResult> pd = std::nullopt)
        : intersects(i), intersectionPoint(ip), message(std::move(msg)), lineDef(ld), planeDef(pd) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << "IntersectionLinePlaneResult{intersects=" << (intersects ? "true" : "false")
            << ", message='" << message << "'";
        if (intersectionPoint.has_value()) oss << ", point=" << intersectionPoint.value().toString();
        oss << "}";
        return oss.str();
    }
};

struct IntersectionTwoPlanesResult {
    bool intersectsInLine; // True if not parallel, or if coincident
    std::optional<LineEquationResult> lineOfIntersection; // Nullable if parallel & distinct
    std::string message; // "parallel_distinct", "coincident", "intersects_in_line"
    std::optional<PlaneEquationResult> plane1Def;
    std::optional<PlaneEquationResult> plane2Def;

    IntersectionTwoPlanesResult(bool iil, std::string msg,
                                std::optional<LineEquationResult> loi = std::nullopt,
                                std::optional<PlaneEquationResult> p1d = std::nullopt,
                                std::optional<PlaneEquationResult> p2d = std::nullopt)
        : intersectsInLine(iil), lineOfIntersection(loi), message(std::move(msg)),
          plane1Def(p1d), plane2Def(p2d) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << "IntersectionTwoPlanesResult{intersectsInLine=" << (intersectsInLine ? "true" : "false")
            << ", message='" << message << "'";
        if (lineOfIntersection.has_value()) oss << ", lineEq='" << lineOfIntersection.value().equationStr << "'";
        oss << "}";
        return oss.str();
    }
};

struct CoplanarityLinesResult {
    bool areCoplanar;
    std::string reason; // e.g. "Lines are skew", "Lines are parallel and coplanar", "Lines intersect and are coplanar"
    std::optional<PlaneEquationResult> planeContainingLines; // Nullable
    std::optional<LineEquationResult> line1Def;
    std::optional<LineEquationResult> line2Def;

    CoplanarityLinesResult(bool ac, std::string r,
                           std::optional<PlaneEquationResult> pcl = std::nullopt,
                           std::optional<LineEquationResult> l1d = std::nullopt,
                           std::optional<LineEquationResult> l2d = std::nullopt)
        : areCoplanar(ac), reason(std::move(r)), planeContainingLines(pcl),
          line1Def(l1d), line2Def(l2d) {}
    std::string toString() const {
        std::ostringstream oss;
        oss << "CoplanarityLinesResult{areCoplanar=" << (areCoplanar ? "true" : "false")
            << ", reason='" << reason << "'";
        if (planeContainingLines.has_value()) oss << ", planeEq='" << planeContainingLines.value().equationStr << "'";
        oss << "}";
        return oss.str();
    }
};


} // namespace three_d_geometry
} // namespace michu_fr

#endif // THREE_D_TYPES_H