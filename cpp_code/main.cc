#include <iostream>
#include <vector>
#include <stdexcept> // For std::exception
#include "three_d_geometry/three_d_utils.h" // Correct path

// Using namespace for convenience in main
using namespace michu_fr::three_d_geometry;

void printSection(const std::string& title) {
    std::cout << "\n--- " << title << " ---" << std::endl;
}

int main() {
    std::cout << "--- 3D Geometry C++ Examples (C++17) ---" << std::endl;

    try {
        printSection("Vector Algebra");
        Vector3D v1(1, 2, 3), v2(4, -1, 2);
        std::cout << "v1 = " << v1.toString() << std::endl;
        std::cout << "v2 = " << v2.toString() << std::endl;
        std::cout << "v1 + v2 = " << addVectors(v1, v2).toString() << std::endl;
        std::cout << "Magnitude of v1: " << vectorMagnitude(v1).toString() << std::endl;
        std::cout << "Unit vector of v1: " << unitVector(v1).toString() << std::endl;
        Point3D pA(1,0,1), pB(3,2,-1);
        std::cout << "Vector P_A P_B: " << vectorFromTwoPoints(pA, pB).toString() << std::endl;
        std::cout << "Section formula (internal 1:2 for pA,pB): " << sectionFormula(pA, pB, 1, 2, true).toString() << std::endl;
        std::vector<Point3D> points_col = {Point3D(1,1,1), Point3D(2,2,2), Point3D(3,3,3)};
        std::cout << "Collinearity check (collinear): " << checkCollinearityPoints(points_col).toString() << std::endl;


        printSection("Dot and Cross Products");
        Vector3D dp_v1(1,-1,2), dp_v2(2,3,-1);
        std::cout << "Dot Product (v1.v2): " << dotProduct(dp_v1, dp_v2).toString() << std::endl;
        std::cout << "Projection of v1 on v2: " << projectionVectorOnVector(dp_v1, dp_v2).toString() << std::endl;
        Vector3D cp_v1(2,1,-1), cp_v2(1,-1,2);
        std::cout << "Cross Product (v1 x v2): " << crossProduct(cp_v1, cp_v2).toString() << std::endl;
        Point3D t_p1(1,1,0), t_p2(3,1,0), t_p3(1,3,0); // Triangle in xy-plane, base 2, height 2, area 2
        std::cout << "Area of Triangle (points): " << areaTrianglePoints(t_p1, t_p2, t_p3).toString() << std::endl;
        std::cout << "Scalar Triple Product [i j k]: " << scalarTripleProduct(Vector3D(1,0,0), Vector3D(0,1,0), Vector3D(0,0,1)).toString() << std::endl;

        printSection("Direction Cosines and Ratios");
        Vector3D dir_vec(3,4,0); // mag 5
        DirectionRatios dr_ex = directionRatiosFromVector(dir_vec);
        std::cout << "DR for " << dir_vec.toString() << ": " << dr_ex.toString() << std::endl;
        std::cout << "DC from DR " << dr_ex.toString() << ": " << directionCosinesFromRatios(dr_ex).toString() << std::endl;

        printSection("Straight Line in Space");
        Point3D line_p0(1,2,3); Vector3D line_dir_v(2,-1,2);
        LineEquationResult line_eq_vec = lineEqVectorForm(line_p0, line_dir_v);
        std::cout << "Line (Vector Form): " << line_eq_vec.toString() << std::endl;
        DirectionRatios line_dr_cart(2,0,-3);
        std::cout << "Line (Cartesian Symm): " << lineEqCartesianSymmetric(line_p0, line_dr_cart).toString() << std::endl;
        std::cout << "Angle between (1,1,0) and (1,-1,1): " << angleBetweenLines(Vector3D(1,1,0), Vector3D(1,-1,1)).toString() << std::endl;

        Point3D l1p(1,0,1), l2p(0,1,0); Vector3D l1d(1,1,1), l2d(1,-1,0); // Skew lines
        std::cout << "Lines Relationship (skew): " << linesRelationship(l1p, l1d, l2p, l2d).toString() << std::endl;
        Point3D dist_pt(1,1,5);
        std::cout << "Distance Point to Line: " << distancePointLine(dist_pt, line_p0, line_dir_v).toString() << std::endl;
        std::cout << "Image of Point in Line: " << imageOfPointInLine(dist_pt, line_eq_vec).toString() << std::endl;


        printSection("The Plane");
        Vector3D plane_norm_unit(0,0,1);
        PlaneEquationResult plane_eq_norm = planeEqVectorNormalForm(plane_norm_unit, 5);
        std::cout << "Plane (Vector Normal Form z=5): " << plane_eq_norm.toString() << std::endl;
        PlaneEquationCoefficients plane_coeffs(1,1,1,-3); // x+y+z-3=0
        PlaneEquationResult plane_eq_coeff = planeEqFromCoefficients(plane_coeffs);
        std::cout << "Plane (from coeffs x+y+z-3=0): " << plane_eq_coeff.toString() << std::endl;
        Point3D pl_p1(1,0,0), pl_p2(0,1,0), pl_p3(0,0,1); // x+y+z-1=0
        PlaneEquationResult plane_eq_3pts = planeEqFromThreePoints(pl_p1, pl_p2, pl_p3);
        std::cout << "Plane (from 3 points for x+y+z-1=0): " << plane_eq_3pts.toString() << std::endl;

        std::cout << "Angle between x+y+z-3=0 and x+y+z-1=0 (parallel): " << angleBetweenPlanes(plane_eq_coeff, plane_eq_3pts).toString() << std::endl;
        LineEquationResult line_for_plane_ops = lineEqVectorForm(Point3D(0,0,0), Vector3D(1,1,-2)); // Line passes through x+y+z-3=0 if point (1,1,1) used
        std::cout << "Angle Line and Plane (x+y+z-3=0): " << angleLinePlane(line_for_plane_ops, plane_eq_coeff).toString() << std::endl;
        std::cout << "Relationship Line and Plane: " << relationshipLinePlane(line_for_plane_ops, plane_coeffs).toString() << std::endl;
        Point3D pt_dist_plane(4,4,4);
        std::cout << "Distance Point to Plane (x+y+z-3=0): " << distancePointPlane(pt_dist_plane, plane_coeffs).toString() << std::endl;
        std::cout << "Intersection Line and Plane: " << intersectionLinePlane(line_for_plane_ops, plane_coeffs).toString() << std::endl;
        
        PlaneEquationCoefficients pcoeffs1(1,1,1,-6); // x+y+z-6=0
        PlaneEquationCoefficients pcoeffs2(1,-1,1,-2); // x-y+z-2=0
        std::cout << "Intersection of Two Planes: " << intersectionTwoPlanes(pcoeffs1, pcoeffs2).toString() << std::endl;
        
        LineEquationResult lineC1 = lineEqVectorForm(Point3D(1,1,0), Vector3D(1,-1,2));
        LineEquationResult lineC2 = lineEqVectorForm(Point3D(2,0,2), Vector3D(-1,1,0)); // Intersecting
        std::cout << "Coplanarity of Lines (Intersecting): " << checkCoplanarityLines(lineC1, lineC2).toString() << std::endl;
        
        std::cout << "Image of Point in Plane (x+y+z-3=0): " << imageOfPointInPlane(pt_dist_plane, plane_coeffs).toString() << std::endl;


    } catch (const std::exception& e) {
        std::cerr << "\n*** An error occurred: " << e.what() << " ***" << std::endl;
        return 1;
    }

    std::cout << "\n--- End of 3D Geometry Examples ---" << std::endl;
    return 0;
}