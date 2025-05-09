#ifndef THREE_D_UTILS_H
#define THREE_D_UTILS_H

#include "three_d_types.h" // Include our type definitions
#include <vector>          // For functions taking lists of points/vectors
#include <string>

namespace michu_fr {
namespace three_d_geometry {

// --- Helper for converting degrees to radians and vice-versa ---
double toRadians(double degrees);
double toDegrees(double radians);

// --- 23. ALGEBRA OF VECTORS ---
Vector3D addVectors(const Vector3D& v1, const Vector3D& v2);
Vector3D subtractVectors(const Vector3D& v1, const Vector3D& v2);
Vector3D scalarMultiplyVector(double scalar, const Vector3D& v);
MagnitudeResult vectorMagnitude(const Vector3D& v);
UnitVectorResult unitVector(const Vector3D& v);
Vector3D vectorFromTwoPoints(const Point3D& p1, const Point3D& p2);
SectionFormulaResult sectionFormula(const Point3D& p1, const Point3D& p2, double m, double n, bool internal);
CollinearityResult checkCollinearityPoints(const std::vector<Point3D>& points);

// --- 24. SCALAR OR DOT PRODUCT ---
DotProductResult dotProduct(const Vector3D& v1, const Vector3D& v2);
ProjectionResult projectionVectorOnVector(const Vector3D& vectorA, const Vector3D& vectorB);

// --- 25. VECTOR OR CROSS PRODUCT ---
CrossProductResult crossProduct(const Vector3D& v1, const Vector3D& v2);
AreaTriangleResult areaTriangleVectors(const Vector3D& adjacentSide1, const Vector3D& adjacentSide2);
AreaTriangleResult areaTrianglePoints(const Point3D& p1, const Point3D& p2, const Point3D& p3);
ScalarTripleProductResult scalarTripleProduct(const Vector3D& a, const Vector3D& b, const Vector3D& c);

// --- 26. DIRECTION COSINES AND DIRECTION RATIOS ---
DirectionRatios directionRatiosFromVector(const Vector3D& v);
DirectionRatios directionRatiosFromPoints(const Point3D& p1, const Point3D& p2);
DirectionCosines directionCosinesFromRatios(const DirectionRatios& dr);
DirectionCosines directionCosinesFromVector(const Vector3D& v);

// --- 27. STRAIGHT LINE IN SPACE ---
LineEquationResult lineEqVectorForm(const Point3D& point, const Vector3D& directionVector);
LineEquationResult lineEqCartesianSymmetric(const Point3D& point, const DirectionRatios& dr);
std::vector<LineEquationResult> lineEqFromTwoPoints(const Point3D& p1, const Point3D& p2);
AngleBetweenLinesResult angleBetweenLines(const Vector3D& dir1, const Vector3D& dir2); // Input can be DRs or actual vectors
LinesRelationshipResult linesRelationship(const Point3D& p1, const Vector3D& d1, const Point3D& p2, const Vector3D& d2);
DistancePointLineResult distancePointLine(const Point3D& point, const Point3D& linePoint, const Vector3D& lineDir); // Using point-vector form of line
ImagePointResult imageOfPointInLine(const Point3D& point, const LineEquationResult& line); // Takes a line definition


// --- 28. THE PLANE ---
PlaneEquationResult planeEqVectorNormalForm(const Vector3D& unitNormal, double distanceFromOrigin);
PlaneEquationResult planeEqCartesianFromNormalPoint(const Vector3D& normal, const Point3D& pointOnPlane);
PlaneEquationResult planeEqFromCoefficients(const PlaneEquationCoefficients& coeffs);
PlaneEquationResult planeEqFromThreePoints(const Point3D& p1, const Point3D& p2, const Point3D& p3);
AngleBetweenPlanesResult angleBetweenPlanes(const PlaneEquationResult& plane1, const PlaneEquationResult& plane2); // Takes plane definitions
AngleLinePlaneResult angleLinePlane(const LineEquationResult& line, const PlaneEquationResult& plane); // Takes definitions
RelationshipLinePlaneResult relationshipLinePlane(const LineEquationResult& line, const PlaneEquationCoefficients& planeCoeffs);
DistancePointPlaneResult distancePointPlane(const Point3D& point, const PlaneEquationCoefficients& planeCoeffs);
IntersectionLinePlaneResult intersectionLinePlane(const LineEquationResult& line, const PlaneEquationCoefficients& planeCoeffs);
IntersectionTwoPlanesResult intersectionTwoPlanes(const PlaneEquationCoefficients& p1Coeffs, const PlaneEquationCoefficients& p2Coeffs);
CoplanarityLinesResult checkCoplanarityLines(const LineEquationResult& line1, const LineEquationResult& line2);
ImagePointResult imageOfPointInPlane(const Point3D& point, const PlaneEquationCoefficients& planeCoeffs);

} // namespace three_d_geometry
} // namespace michu_fr

#endif // THREE_D_UTILS_H