#ifndef THREE_D_GEOMETRY_TYPES_H
#define THREE_D_GEOMETRY_TYPES_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h> // For strcpy, memset, etc.
#include <math.h>   // For M_PI, sqrt, fabs, etc.

// Define M_PI if not defined (e.g. on older compilers or specific standards)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef MAX_STRING_LEN // If not already defined by real_numbers_types.h
#define MAX_STRING_LEN 256
#endif

// Forward declaration
struct Vector3D_C;
struct LineEquationResult_C;
struct PlaneEquationResult_C;

typedef struct {
    double x, y, z;
} Point3D_C;

typedef struct Vector3D_C {
    double x, y, z;
} Vector3D_C;

// --- Vector Algebra Results ---
typedef struct {
    Vector3D_C vector;
    double magnitude;
    char to_string_buff[MAX_STRING_LEN];
} MagnitudeResult_C;

typedef struct {
    Vector3D_C original_vector;
    Vector3D_C unit_vector;
    double calculated_magnitude;
    char to_string_buff[MAX_STRING_LEN * 2];
} UnitVectorResult_C;

typedef struct {
    Point3D_C resulting_point;
    Point3D_C p1;
    Point3D_C p2;
    double ratio_m;
    double ratio_n;
    char division_type[32]; // "internal" or "external"
    char to_string_buff[MAX_STRING_LEN * 2];
} SectionFormulaResult_C;

#define MAX_COLLINEAR_POINTS 10 // Example limit for simple array
typedef struct {
    bool are_collinear;
    char reason[MAX_STRING_LEN];
    Point3D_C points[MAX_COLLINEAR_POINTS];
    int num_points;
    char to_string_buff[MAX_STRING_LEN * 3];
} CollinearityResult_C;

// --- Scalar and Vector Product Results ---
typedef struct {
    Vector3D_C vector1;
    Vector3D_C vector2;
    double dot_product;
    double angle_radians; // Use NAN if not calculable
    double angle_degrees; // Use NAN if not calculable
    char to_string_buff[MAX_STRING_LEN * 2];
} DotProductResult_C;

typedef struct {
    Vector3D_C vector_a;
    Vector3D_C vector_b;
    double scalar_projection;
    Vector3D_C vector_projection;
    char to_string_buff[MAX_STRING_LEN * 3];
} ProjectionResult_C;

typedef struct {
    Vector3D_C vector1;
    Vector3D_C vector2;
    Vector3D_C cross_product_vector;
    double magnitude_of_cross_product;
    double area_of_parallelogram; // Same as magnitude
    char to_string_buff[MAX_STRING_LEN * 3];
} CrossProductResult_C;

typedef struct {
    double area;
    // Context in C is harder without maps. Maybe a few fixed context strings.
    char context_method[MAX_STRING_LEN];
    char context_item1[MAX_STRING_LEN];
    char context_item2[MAX_STRING_LEN];
    char context_item3[MAX_STRING_LEN]; // For points
    char to_string_buff[MAX_STRING_LEN * 4];
} AreaTriangleResult_C;

typedef struct {
    Vector3D_C vector_a;
    Vector3D_C vector_b;
    Vector3D_C vector_c;
    double scalar_triple_product;
    bool are_coplanar;
    char to_string_buff[MAX_STRING_LEN * 4];
} ScalarTripleProductResult_C;

// --- Direction Cosines and Ratios ---
typedef struct {
    double a, b, c;
    char to_string_buff[MAX_STRING_LEN];
} DirectionRatios_C;

typedef struct {
    double l, m, n;
    bool is_valid_set;
    char to_string_buff[MAX_STRING_LEN];
} DirectionCosines_C;

// --- Straight Line Results ---
typedef struct LineEquationResult_C {
    char type[64]; // "vector_form", "cartesian_symmetric_form"
    char equation_str[MAX_STRING_LEN * 2];
    Point3D_C point_on_line; // Assume always present for a defined line
    Vector3D_C direction_vector; // Assume always present
    DirectionRatios_C direction_ratios; // Derived
    char to_string_buff[MAX_STRING_LEN * 4];
} LineEquationResult_C;

typedef struct {
    LineEquationResult_C line1_def;
    LineEquationResult_C line2_def;
    double angle_radians;
    double angle_degrees;
    char to_string_buff[MAX_STRING_LEN * 2];
} AngleBetweenLinesResult_C;

typedef struct {
    LineEquationResult_C line1_definition;
    LineEquationResult_C line2_definition;
    char relationship[64]; // "parallel_distinct", "collinear", "intersecting", "skew"
    Point3D_C intersection_point; // Valid if intersecting
    bool has_intersection_point;
    double shortest_distance;    // Valid if skew or parallel_distinct
    bool has_shortest_distance;
    char to_string_buff[MAX_STRING_LEN * 3];
} LinesRelationshipResult_C;

typedef struct {
    Point3D_C point;
    LineEquationResult_C line_definition;
    double distance;
    Point3D_C foot_of_perpendicular;
    bool has_foot_of_perpendicular;
    char to_string_buff[MAX_STRING_LEN * 3];
} DistancePointLineResult_C;

typedef struct {
    Point3D_C original_point;
    Point3D_C image_point;
    Point3D_C foot_of_perpendicular;
    char in_object_type[32]; // "line" or "plane"
    char object_definition_str[MAX_STRING_LEN * 2];
    char to_string_buff[MAX_STRING_LEN * 4];
} ImagePointResult_C;

// --- Plane Results ---
typedef struct { // Input type
    double a, b, c, d_lhs; // For Ax + By + Cz + D_lhs = 0
    char to_string_buff[MAX_STRING_LEN];
} PlaneEquationCoefficients_C;

typedef struct PlaneEquationResult_C {
    char type[64];
    char equation_str[MAX_STRING_LEN * 2];
    Vector3D_C normal_vector;
    bool has_normal_vector;
    double distance_from_origin; // For r.n_unit = d
    bool has_distance_from_origin;
    PlaneEquationCoefficients_C coeffs_cartesian;
    bool has_coeffs_cartesian;
    char to_string_buff[MAX_STRING_LEN * 4];
} PlaneEquationResult_C;

typedef struct {
    PlaneEquationResult_C plane1_def;
    PlaneEquationResult_C plane2_def;
    double angle_radians;
    double angle_degrees;
    char to_string_buff[MAX_STRING_LEN * 2];
} AngleBetweenPlanesResult_C;

typedef struct {
    LineEquationResult_C line_def;
    PlaneEquationResult_C plane_def;
    double angle_radians;
    double angle_degrees;
    char to_string_buff[MAX_STRING_LEN * 2];
} AngleLinePlaneResult_C;

typedef struct {
    LineEquationResult_C line_definition;
    PlaneEquationResult_C plane_definition;
    char relationship[64]; // "line_parallel_to_plane_distinct", etc.
    Point3D_C intersection_point;
    bool has_intersection_point;
    double distance_if_parallel;
    bool has_distance_if_parallel;
    char to_string_buff[MAX_STRING_LEN * 3];
} RelationshipLinePlaneResult_C;

typedef struct {
    Point3D_C point;
    PlaneEquationResult_C plane_definition;
    double distance;
    Point3D_C foot_of_perpendicular;
    bool has_foot_of_perpendicular;
    char to_string_buff[MAX_STRING_LEN * 3];
} DistancePointPlaneResult_C;

typedef struct {
    bool intersects;
    Point3D_C intersection_point; // Valid if intersects is true and not line_in_plane
    bool has_intersection_point;
    char message[MAX_STRING_LEN];
    LineEquationResult_C line_def;
    PlaneEquationResult_C plane_def;
    char to_string_buff[MAX_STRING_LEN * 3];
} IntersectionLinePlaneResult_C;

typedef struct {
    bool intersects_in_line;
    LineEquationResult_C line_of_intersection; // Valid if intersects_in_line
    bool has_line_of_intersection;
    char message[MAX_STRING_LEN];
    PlaneEquationResult_C plane1_def;
    PlaneEquationResult_C plane2_def;
    char to_string_buff[MAX_STRING_LEN * 3];
} IntersectionTwoPlanesResult_C;

typedef struct {
    bool are_coplanar;
    char reason[MAX_STRING_LEN];
    PlaneEquationResult_C plane_containing_lines;
    bool has_plane_containing_lines;
    LineEquationResult_C line1_def;
    LineEquationResult_C line2_def;
    char to_string_buff[MAX_STRING_LEN * 3];
} CoplanarityLinesResult_C;


// Helper functions for initializing and printing structs (declarations)
// Point3D_C
void point3d_c_init(Point3D_C* p, double x, double y, double z);
const char* point3d_c_to_string(const Point3D_C* p, char* buffer, size_t buffer_len);

// Vector3D_C
void vector3d_c_init(Vector3D_C* v, double x, double y, double z);
const char* vector3d_c_to_string(const Vector3D_C* v, char* buffer, size_t buffer_len);
double vector3d_c_magnitude(const Vector3D_C* v);
int vector3d_c_normalize(const Vector3D_C* v_in, Vector3D_C* v_out); // returns error code
Vector3D_C vector3d_c_add(const Vector3D_C* v1, const Vector3D_C* v2);
Vector3D_C vector3d_c_subtract(const Vector3D_C* v1, const Vector3D_C* v2);
Vector3D_C vector3d_c_scalar_multiply(const Vector3D_C* v, double scalar);
double vector3d_c_dot(const Vector3D_C* v1, const Vector3D_C* v2);
Vector3D_C vector3d_c_cross(const Vector3D_C* v1, const Vector3D_C* v2);
bool vector3d_c_is_zero(const Vector3D_C* v, double epsilon);

// ... Declarations for toString functions for all result structs ...
// (These will mostly call snprintf into their internal to_string_buff)
// e.g.
const char* magnitude_result_c_to_string(MagnitudeResult_C* res);
const char* unit_vector_result_c_to_string(UnitVectorResult_C* res);
const char* section_formula_result_c_to_string(SectionFormulaResult_C* res);
// ... and so on for all other _C result structs

#endif // THREE_D_GEOMETRY_TYPES_H