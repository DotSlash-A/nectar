#ifndef THREE_D_GEOMETRY_UTILS_H
#define THREE_D_GEOMETRY_UTILS_H

#include "three_d_geometry_types.h"

// Error Codes
#define TDG_SUCCESS 0
#define TDG_ERROR_INVALID_ARG -1
#define TDG_ERROR_CALCULATION -2 // General calculation error (e.g. division by zero)
#define TDG_ERROR_BUFFER_TOO_SMALL -3
#define TDG_ERROR_NOT_IMPLEMENTED -4

// --- Helper for degrees/radians ---
double tdg_to_radians(double degrees);
double tdg_to_degrees(double radians);

// --- 23. ALGEBRA OF VECTORS ---
// Basic vector ops are part of three_d_geometry_types.h / .c now

int tdg_vector_magnitude(const Vector3D_C* v, MagnitudeResult_C* result);
int tdg_unit_vector(const Vector3D_C* v, UnitVectorResult_C* result);
int tdg_vector_from_two_points(const Point3D_C* p1, const Point3D_C* p2, Vector3D_C* result_vec);
int tdg_section_formula(const Point3D_C* p1, const Point3D_C* p2, double m, double n, bool internal, SectionFormulaResult_C* result);
int tdg_check_collinearity_points(const Point3D_C points[], int num_points, CollinearityResult_C* result);

// --- 24. SCALAR OR DOT PRODUCT ---
int tdg_dot_product(const Vector3D_C* v1, const Vector3D_C* v2, DotProductResult_C* result);
int tdg_projection_vector_on_vector(const Vector3D_C* vector_a, const Vector3D_C* vector_b, ProjectionResult_C* result);

// --- 25. VECTOR OR CROSS PRODUCT ---
int tdg_cross_product(const Vector3D_C* v1, const Vector3D_C* v2, CrossProductResult_C* result);
int tdg_area_triangle_vectors(const Vector3D_C* side1, const Vector3D_C* side2, AreaTriangleResult_C* result);
int tdg_area_triangle_points(const Point3D_C* p1, const Point3D_C* p2, const Point3D_C* p3, AreaTriangleResult_C* result);
int tdg_scalar_triple_product(const Vector3D_C* a, const Vector3D_C* b, const Vector3D_C* c, ScalarTripleProductResult_C* result);

// --- 26. DIRECTION COSINES AND DIRECTION RATIOS ---
int tdg_direction_ratios_from_vector(const Vector3D_C* v, DirectionRatios_C* result);
int tdg_direction_ratios_from_points(const Point3D_C* p1, const Point3D_C* p2, DirectionRatios_C* result);
int tdg_direction_cosines_from_ratios(const DirectionRatios_C* dr, DirectionCosines_C* result);
int tdg_direction_cosines_from_vector(const Vector3D_C* v, DirectionCosines_C* result);

// --- 27. STRAIGHT LINE IN SPACE ---
int tdg_line_eq_vector_form(const Point3D_C* point, const Vector3D_C* direction_vector, LineEquationResult_C* result);
int tdg_line_eq_cartesian_symmetric(const Point3D_C* point, const DirectionRatios_C* dr, LineEquationResult_C* result);
// For line from two points, we might return a single primary form or fill multiple result structs if needed.
// Let's simplify to return one (vector form) and the caller can derive others.
int tdg_line_eq_from_two_points(const Point3D_C* p1, const Point3D_C* p2, LineEquationResult_C* result_vec_form);
int tdg_angle_between_lines(const Vector3D_C* dir1, const Vector3D_C* dir2, AngleBetweenLinesResult_C* result);
int tdg_lines_relationship(const Point3D_C* p1, const Vector3D_C* d1, const Point3D_C* p2, const Vector3D_C* d2, LinesRelationshipResult_C* result);
int tdg_distance_point_line(const Point3D_C* point, const Point3D_C* line_point, const Vector3D_C* line_dir, DistancePointLineResult_C* result);
int tdg_image_of_point_in_line(const Point3D_C* point, const LineEquationResult_C* line, ImagePointResult_C* result);

// --- 28. THE PLANE ---
int tdg_plane_eq_vector_normal_form(const Vector3D_C* unit_normal, double distance_from_origin, PlaneEquationResult_C* result);
int tdg_plane_eq_cartesian_from_normal_point(const Vector3D_C* normal, const Point3D_C* point_on_plane, PlaneEquationResult_C* result);
int tdg_plane_eq_from_coeffs(const PlaneEquationCoefficients_C* coeffs, PlaneEquationResult_C* result);
int tdg_plane_eq_from_three_points(const Point3D_C* p1, const Point3D_C* p2, const Point3D_C* p3, PlaneEquationResult_C* result);
int tdg_angle_between_planes(const PlaneEquationResult_C* plane1, const PlaneEquationResult_C* plane2, AngleBetweenPlanesResult_C* result);
int tdg_angle_line_plane(const LineEquationResult_C* line, const PlaneEquationResult_C* plane, AngleLinePlaneResult_C* result);
int tdg_relationship_line_plane(const LineEquationResult_C* line, const PlaneEquationCoefficients_C* plane_coeffs, RelationshipLinePlaneResult_C* result);
int tdg_distance_point_plane(const Point3D_C* point, const PlaneEquationCoefficients_C* plane_coeffs, DistancePointPlaneResult_C* result);
int tdg_intersection_line_plane(const LineEquationResult_C* line, const PlaneEquationCoefficients_C* plane_coeffs, IntersectionLinePlaneResult_C* result);
int tdg_intersection_two_planes(const PlaneEquationCoefficients_C* p1_coeffs, const PlaneEquationCoefficients_C* p2_coeffs, IntersectionTwoPlanesResult_C* result);
int tdg_check_coplanarity_lines(const LineEquationResult_C* line1, const LineEquationResult_C* line2, CoplanarityLinesResult_C* result);
int tdg_image_of_point_in_plane(const Point3D_C* point, const PlaneEquationCoefficients_C* plane_coeffs, ImagePointResult_C* result);


#endif // THREE_D_GEOMETRY_UTILS_H