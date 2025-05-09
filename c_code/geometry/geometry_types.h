#ifndef GEOMETRY_TYPES_H
#define GEOMETRY_TYPES_H

#include <stdbool.h>
#include <stdio.h> // For snprintf

#define GEO_MAX_STRING_LEN 128
#define GEO_SUCCESS 0
#define GEO_ERROR_INVALID_ARG -1

// For M_PI, might need #define _USE_MATH_DEFINES before #include <math.h> on Windows
// Or define it manually if not available.
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif


// --- Dimension Structs ---
typedef struct { double length, breadth, height; } CuboidDimensions_C;
typedef struct { double side; } CubeDimensions_C;
typedef struct { double radius, height; } CylinderDimensions_C;
typedef struct { double radius, height; } ConeDimensions_C; // Slant height calculated
typedef struct { double radius; } SphereDimensions_C;
typedef SphereDimensions_C HemisphereDimensions_C; // Same input
typedef struct { double height, radius1_R, radius2_r; } FrustumDimensions_C;


// --- Result Structs ---
typedef struct {
    char shape[GEO_MAX_STRING_LEN];
    char dimensions_str[GEO_MAX_STRING_LEN];
    double lateral_or_curved_surface_area; // Use NaN or a flag if not applicable
    double total_surface_area;             // Use NaN or a flag if not applicable
    double surface_area_sphere;            // Specific for sphere, else NaN/flag
    double calculated_slant_height;        // For cone/frustum, else NaN/flag
    bool lcsa_applicable, tsa_applicable, sa_sphere_applicable, slant_h_applicable;
} SurfaceAreaResult_C;

typedef struct {
    char shape[GEO_MAX_STRING_LEN];
    char dimensions_str[GEO_MAX_STRING_LEN];
    double volume;
} VolumeResult_C;

typedef struct {
    char shape[GEO_MAX_STRING_LEN];
    char dimensions_str[GEO_MAX_STRING_LEN];
    double diagonal;
} DiagonalResult_C;

// --- Print Helper Function Declarations ---
void geo_print_surface_area_result(const SurfaceAreaResult_C* res);
void geo_print_volume_result(const VolumeResult_C* res);
void geo_print_diagonal_result(const DiagonalResult_C* res);

#endif // GEOMETRY_TYPES_H