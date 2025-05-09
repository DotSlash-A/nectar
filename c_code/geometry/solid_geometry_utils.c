#include "solid_geometry_utils.h"
#include <string.h> // For strcpy, snprintf, memset
#include <math.h>   // For M_PI, sqrt, pow

// --- Print Helper Function Implementations (from geometry_types.h) ---
void geo_print_surface_area_result(const SurfaceAreaResult_C* res) {
    if (!res) return;
    printf("SurfaceAreaResult_C{shape='%s', dimensions={%s}", res->shape, res->dimensions_str);
    if (res->lcsa_applicable) printf(", LSA/CSA=%.4f", res->lateral_or_curved_surface_area);
    if (res->tsa_applicable) printf(", TSA=%.4f", res->total_surface_area);
    if (res->sa_sphere_applicable) printf(", SA(Sphere)=%.4f", res->surface_area_sphere);
    if (res->slant_h_applicable) printf(", SlantHeight(calc)=%.4f", res->calculated_slant_height);
    printf("}\n");
}
void geo_print_volume_result(const VolumeResult_C* res) {
    if (!res) return;
    printf("VolumeResult_C{shape='%s', dimensions={%s}, volume=%.4f}\n",
           res->shape, res->dimensions_str, res->volume);
}
void geo_print_diagonal_result(const DiagonalResult_C* res) {
    if (!res) return;
    printf("DiagonalResult_C{shape='%s', dimensions={%s}, diagonal=%.4f}\n",
           res->shape, res->dimensions_str, res->diagonal);
}

// Helper to set common fields in SurfaceAreaResult_C and initialize flags
static void init_sa_result(SurfaceAreaResult_C* res, const char* shape_name) {
    memset(res, 0, sizeof(SurfaceAreaResult_C)); // Clear all fields, flags to false
    strncpy(res->shape, shape_name, GEO_MAX_STRING_LEN -1);
    res->shape[GEO_MAX_STRING_LEN-1] = '\0';
    // Initialize numeric fields that might not be set to a known "not applicable" value if needed,
    // e.g., NAN from math.h, but flags are clearer.
}


// --- Cuboid ---
int geo_cuboid_surface_areas(const CuboidDimensions_C* dims, SurfaceAreaResult_C* result) {
    if (!dims || !result) return GEO_ERROR_INVALID_ARG;
    if (dims->length <= 0 || dims->breadth <= 0 || dims->height <= 0) return GEO_ERROR_INVALID_ARG;
    init_sa_result(result, "Cuboid");
    snprintf(result->dimensions_str, GEO_MAX_STRING_LEN, "l=%.2f, b=%.2f, h=%.2f",
             dims->length, dims->breadth, dims->height);
    result->dimensions_str[GEO_MAX_STRING_LEN-1] = '\0';

    result->lateral_or_curved_surface_area = 2 * (dims->length + dims->breadth) * dims->height;
    result->total_surface_area = 2 * ((dims->length * dims->breadth) +
                                     (dims->breadth * dims->height) +
                                     (dims->height * dims->length));
    result->lcsa_applicable = true;
    result->tsa_applicable = true;
    return GEO_SUCCESS;
}

int geo_cuboid_volume(const CuboidDimensions_C* dims, VolumeResult_C* result) {
    if (!dims || !result) return GEO_ERROR_INVALID_ARG;
    if (dims->length <= 0 || dims->breadth <= 0 || dims->height <= 0) return GEO_ERROR_INVALID_ARG;
    memset(result, 0, sizeof(VolumeResult_C));
    strncpy(result->shape, "Cuboid", GEO_MAX_STRING_LEN-1);
    result->shape[GEO_MAX_STRING_LEN-1] = '\0';
    snprintf(result->dimensions_str, GEO_MAX_STRING_LEN, "l=%.2f, b=%.2f, h=%.2f",
             dims->length, dims->breadth, dims->height);
    result->dimensions_str[GEO_MAX_STRING_LEN-1] = '\0';
    result->volume = dims->length * dims->breadth * dims->height;
    return GEO_SUCCESS;
}

int geo_cuboid_diagonal(const CuboidDimensions_C* dims, DiagonalResult_C* result) {
    if (!dims || !result) return GEO_ERROR_INVALID_ARG;
    if (dims->length <= 0 || dims->breadth <= 0 || dims->height <= 0) return GEO_ERROR_INVALID_ARG;
    memset(result, 0, sizeof(DiagonalResult_C));
    strncpy(result->shape, "Cuboid", GEO_MAX_STRING_LEN-1);
    result->shape[GEO_MAX_STRING_LEN-1] = '\0';
    snprintf(result->dimensions_str, GEO_MAX_STRING_LEN, "l=%.2f, b=%.2f, h=%.2f",
             dims->length, dims->breadth, dims->height);
    result->dimensions_str[GEO_MAX_STRING_LEN-1] = '\0';
    result->diagonal = sqrt(pow(dims->length, 2) + pow(dims->breadth, 2) + pow(dims->height, 2));
    return GEO_SUCCESS;
}


// --- Cube ---
int geo_cube_surface_areas(const CubeDimensions_C* dims, SurfaceAreaResult_C* result){
    if (!dims || !result) return GEO_ERROR_INVALID_ARG;
    if (dims->side <= 0) return GEO_ERROR_INVALID_ARG;
    init_sa_result(result, "Cube");
    snprintf(result->dimensions_str, GEO_MAX_STRING_LEN, "side=%.2f", dims->side);
    result->dimensions_str[GEO_MAX_STRING_LEN-1] = '\0';
    result->lateral_or_curved_surface_area = 4 * dims->side * dims->side;
    result->total_surface_area = 6 * dims->side * dims->side;
    result->lcsa_applicable = true; result->tsa_applicable = true;
    return GEO_SUCCESS;
}

int geo_cube_volume(const CubeDimensions_C* dims, VolumeResult_C* result) {
    if (!dims || !result) return GEO_ERROR_INVALID_ARG;
    if (dims->side <= 0) return GEO_ERROR_INVALID_ARG;
    memset(result, 0, sizeof(VolumeResult_C));
    strncpy(result->shape, "Cube", GEO_MAX_STRING_LEN-1);
    result->shape[GEO_MAX_STRING_LEN-1] = '\0';
    snprintf(result->dimensions_str, GEO_MAX_STRING_LEN, "side=%.2f", dims->side);
    result->dimensions_str[GEO_MAX_STRING_LEN-1] = '\0';
    result->volume = pow(dims->side, 3);
    return GEO_SUCCESS;
}

int geo_cube_diagonal(const CubeDimensions_C* dims, DiagonalResult_C* result){
    if (!dims || !result) return GEO_ERROR_INVALID_ARG;
    if (dims->side <= 0) return GEO_ERROR_INVALID_ARG;
    memset(result, 0, sizeof(DiagonalResult_C));
    strncpy(result->shape, "Cube", GEO_MAX_STRING_LEN-1);
    result->shape[GEO_MAX_STRING_LEN-1] = '\0';
    snprintf(result->dimensions_str, GEO_MAX_STRING_LEN, "side=%.2f", dims->side);
    result->dimensions_str[GEO_MAX_STRING_LEN-1] = '\0';
    result->diagonal = dims->side * sqrt(3.0);
    return GEO_SUCCESS;
}

// --- Cylinder ---
int geo_cylinder_surface_areas(const CylinderDimensions_C* dims, SurfaceAreaResult_C* result){
    if (!dims || !result) return GEO_ERROR_INVALID_ARG;
    if (dims->radius <= 0 || dims->height <=0) return GEO_ERROR_INVALID_ARG;
    init_sa_result(result, "Cylinder");
    snprintf(result->dimensions_str, GEO_MAX_STRING_LEN, "r=%.2f, h=%.2f", dims->radius, dims->height);
    result->dimensions_str[GEO_MAX_STRING_LEN-1] = '\0';
    result->lateral_or_curved_surface_area = 2 * M_PI * dims->radius * dims->height; // CSA
    result->total_surface_area = 2 * M_PI * dims->radius * (dims->height + dims->radius);
    result->lcsa_applicable = true; result->tsa_applicable = true;
    return GEO_SUCCESS;
}
int geo_cylinder_volume(const CylinderDimensions_C* dims, VolumeResult_C* result){
    if (!dims || !result) return GEO_ERROR_INVALID_ARG;
    if (dims->radius <= 0 || dims->height <=0) return GEO_ERROR_INVALID_ARG;
    memset(result, 0, sizeof(VolumeResult_C));
    strncpy(result->shape, "Cylinder", GEO_MAX_STRING_LEN-1);
    result->shape[GEO_MAX_STRING_LEN-1] = '\0';
    snprintf(result->dimensions_str, GEO_MAX_STRING_LEN, "r=%.2f, h=%.2f", dims->radius, dims->height);
    result->dimensions_str[GEO_MAX_STRING_LEN-1] = '\0';
    result->volume = M_PI * dims->radius * dims->radius * dims->height;
    return GEO_SUCCESS;
}

// --- Cone ---
static double cone_slant_height_c(double radius, double height) {
    return sqrt(radius*radius + height*height);
}
int geo_cone_surface_areas(const ConeDimensions_C* dims, SurfaceAreaResult_C* result){
    if (!dims || !result) return GEO_ERROR_INVALID_ARG;
    if (dims->radius <= 0 || dims->height <=0) return GEO_ERROR_INVALID_ARG;
    init_sa_result(result, "Cone");
    snprintf(result->dimensions_str, GEO_MAX_STRING_LEN, "r=%.2f, h=%.2f", dims->radius, dims->height);
    result->dimensions_str[GEO_MAX_STRING_LEN-1] = '\0';
    result->calculated_slant_height = cone_slant_height_c(dims->radius, dims->height);
    result->slant_h_applicable = true;
    result->lateral_or_curved_surface_area = M_PI * dims->radius * result->calculated_slant_height; // CSA
    result->total_surface_area = M_PI * dims->radius * (result->calculated_slant_height + dims->radius);
    result->lcsa_applicable = true; result->tsa_applicable = true;
    return GEO_SUCCESS;
}
int geo_cone_volume(const ConeDimensions_C* dims, VolumeResult_C* result){
    if (!dims || !result) return GEO_ERROR_INVALID_ARG;
     if (dims->radius <= 0 || dims->height <=0) return GEO_ERROR_INVALID_ARG;
    memset(result, 0, sizeof(VolumeResult_C));
    strncpy(result->shape, "Cone", GEO_MAX_STRING_LEN-1);
    result->shape[GEO_MAX_STRING_LEN-1] = '\0';
    snprintf(result->dimensions_str, GEO_MAX_STRING_LEN, "r=%.2f, h=%.2f", dims->radius, dims->height);
    result->dimensions_str[GEO_MAX_STRING_LEN-1] = '\0';
    result->volume = (1.0/3.0) * M_PI * dims->radius * dims->radius * dims->height;
    return GEO_SUCCESS;
}

// --- Sphere ---
int geo_sphere_surface_area(const SphereDimensions_C* dims, SurfaceAreaResult_C* result){
    if (!dims || !result) return GEO_ERROR_INVALID_ARG;
    if (dims->radius <= 0) return GEO_ERROR_INVALID_ARG;
    init_sa_result(result, "Sphere");
    snprintf(result->dimensions_str, GEO_MAX_STRING_LEN, "r=%.2f", dims->radius);
    result->dimensions_str[GEO_MAX_STRING_LEN-1] = '\0';
    result->surface_area_sphere = 4 * M_PI * dims->radius * dims->radius;
    result->sa_sphere_applicable = true;
    return GEO_SUCCESS;
}
int geo_sphere_volume(const SphereDimensions_C* dims, VolumeResult_C* result){
    if (!dims || !result) return GEO_ERROR_INVALID_ARG;
    if (dims->radius <= 0) return GEO_ERROR_INVALID_ARG;
    memset(result, 0, sizeof(VolumeResult_C));
    strncpy(result->shape, "Sphere", GEO_MAX_STRING_LEN-1);
    result->shape[GEO_MAX_STRING_LEN-1] = '\0';
    snprintf(result->dimensions_str, GEO_MAX_STRING_LEN, "r=%.2f", dims->radius);
    result->dimensions_str[GEO_MAX_STRING_LEN-1] = '\0';
    result->volume = (4.0/3.0) * M_PI * pow(dims->radius, 3);
    return GEO_SUCCESS;
}

// --- Hemisphere ---
int geo_hemisphere_surface_areas(const HemisphereDimensions_C* dims, SurfaceAreaResult_C* result){
    if (!dims || !result) return GEO_ERROR_INVALID_ARG;
    if (dims->radius <= 0) return GEO_ERROR_INVALID_ARG;
    init_sa_result(result, "Hemisphere");
    snprintf(result->dimensions_str, GEO_MAX_STRING_LEN, "r=%.2f", dims->radius);
    result->dimensions_str[GEO_MAX_STRING_LEN-1] = '\0';
    result->lateral_or_curved_surface_area = 2 * M_PI * dims->radius * dims->radius; // CSA
    result->total_surface_area = 3 * M_PI * dims->radius * dims->radius;
    result->lcsa_applicable = true; result->tsa_applicable = true;
    return GEO_SUCCESS;
}
int geo_hemisphere_volume(const HemisphereDimensions_C* dims, VolumeResult_C* result){
    if (!dims || !result) return GEO_ERROR_INVALID_ARG;
    if (dims->radius <= 0) return GEO_ERROR_INVALID_ARG;
    memset(result, 0, sizeof(VolumeResult_C));
    strncpy(result->shape, "Hemisphere", GEO_MAX_STRING_LEN-1);
    result->shape[GEO_MAX_STRING_LEN-1] = '\0';
    snprintf(result->dimensions_str, GEO_MAX_STRING_LEN, "r=%.2f", dims->radius);
    result->dimensions_str[GEO_MAX_STRING_LEN-1] = '\0';
    result->volume = (2.0/3.0) * M_PI * pow(dims->radius, 3);
    return GEO_SUCCESS;
}

// --- Frustum ---
static double frustum_slant_height_c(double height, double R, double r) {
    return sqrt(height*height + pow(R - r, 2));
}
int geo_frustum_surface_areas(const FrustumDimensions_C* dims, SurfaceAreaResult_C* result){
    if (!dims || !result) return GEO_ERROR_INVALID_ARG;
    if (dims->height <= 0 || dims->radius1_R < 0 || dims->radius2_r < 0 || dims->radius1_R < dims->radius2_r) return GEO_ERROR_INVALID_ARG;
    init_sa_result(result, "Frustum");
    snprintf(result->dimensions_str, GEO_MAX_STRING_LEN, "h=%.2f, R=%.2f, r=%.2f", dims->height, dims->radius1_R, dims->radius2_r);
    result->dimensions_str[GEO_MAX_STRING_LEN-1] = '\0';
    result->calculated_slant_height = frustum_slant_height_c(dims->height, dims->radius1_R, dims->radius2_r);
    result->slant_h_applicable = true;
    result->lateral_or_curved_surface_area = M_PI * result->calculated_slant_height * (dims->radius1_R + dims->radius2_r);
    result->total_surface_area = result->lateral_or_curved_surface_area +
                                (M_PI * dims->radius1_R * dims->radius1_R) +
                                (M_PI * dims->radius2_r * dims->radius2_r);
    result->lcsa_applicable = true; result->tsa_applicable = true;
    return GEO_SUCCESS;
}
int geo_frustum_volume(const FrustumDimensions_C* dims, VolumeResult_C* result){
    if (!dims || !result) return GEO_ERROR_INVALID_ARG;
    if (dims->height <= 0 || dims->radius1_R < 0 || dims->radius2_r < 0 || dims->radius1_R < dims->radius2_r) return GEO_ERROR_INVALID_ARG;
    memset(result, 0, sizeof(VolumeResult_C));
    strncpy(result->shape, "Frustum", GEO_MAX_STRING_LEN-1);
    result->shape[GEO_MAX_STRING_LEN-1] = '\0';
    snprintf(result->dimensions_str, GEO_MAX_STRING_LEN, "h=%.2f, R=%.2f, r=%.2f", dims->height, dims->radius1_R, dims->radius2_r);
    result->dimensions_str[GEO_MAX_STRING_LEN-1] = '\0';
    result->volume = (1.0/3.0) * M_PI * dims->height *
                     (dims->radius1_R * dims->radius1_R +
                      dims->radius2_r * dims->radius2_r +
                      dims->radius1_R * dims->radius2_r);
    return GEO_SUCCESS;
}