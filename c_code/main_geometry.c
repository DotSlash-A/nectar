#include <stdio.h>
#include "geometry/solid_geometry_utils.h"

int main() {
    printf("--- C Solid Geometry Examples ---\n");
    int ret;

    // Cuboid
    printf("\n-- Cuboid --\n");
    CuboidDimensions_C cuboid_dims = {5, 4, 3};
    SurfaceAreaResult_C sa_res;
    VolumeResult_C vol_res;
    DiagonalResult_C diag_res;

    ret = geo_cuboid_surface_areas(&cuboid_dims, &sa_res);
    if(ret == GEO_SUCCESS) geo_print_surface_area_result(&sa_res);
    ret = geo_cuboid_volume(&cuboid_dims, &vol_res);
    if(ret == GEO_SUCCESS) geo_print_volume_result(&vol_res);
    ret = geo_cuboid_diagonal(&cuboid_dims, &diag_res);
    if(ret == GEO_SUCCESS) geo_print_diagonal_result(&diag_res);

    // Cube
    printf("\n-- Cube --\n");
    CubeDimensions_C cube_dims = {4};
    ret = geo_cube_surface_areas(&cube_dims, &sa_res);
    if(ret == GEO_SUCCESS) geo_print_surface_area_result(&sa_res);
    ret = geo_cube_volume(&cube_dims, &vol_res);
    if(ret == GEO_SUCCESS) geo_print_volume_result(&vol_res);
    ret = geo_cube_diagonal(&cube_dims, &diag_res);
    if(ret == GEO_SUCCESS) geo_print_diagonal_result(&diag_res);

    // Cylinder
    printf("\n-- Cylinder --\n");
    CylinderDimensions_C cyl_dims = {3, 7};
    ret = geo_cylinder_surface_areas(&cyl_dims, &sa_res);
    if(ret == GEO_SUCCESS) geo_print_surface_area_result(&sa_res);
    ret = geo_cylinder_volume(&cyl_dims, &vol_res);
    if(ret == GEO_SUCCESS) geo_print_volume_result(&vol_res);

    // Cone
    printf("\n-- Cone --\n");
    ConeDimensions_C cone_dims = {3,4}; // r=3, h=4 => slant=5
    ret = geo_cone_surface_areas(&cone_dims, &sa_res);
    if(ret == GEO_SUCCESS) geo_print_surface_area_result(&sa_res);
    ret = geo_cone_volume(&cone_dims, &vol_res);
    if(ret == GEO_SUCCESS) geo_print_volume_result(&vol_res);

    // Sphere
    printf("\n-- Sphere --\n");
    SphereDimensions_C sphere_dims = {5};
    ret = geo_sphere_surface_area(&sphere_dims, &sa_res);
    if(ret == GEO_SUCCESS) geo_print_surface_area_result(&sa_res);
    ret = geo_sphere_volume(&sphere_dims, &vol_res);
    if(ret == GEO_SUCCESS) geo_print_volume_result(&vol_res);

    // Hemisphere
    printf("\n-- Hemisphere --\n");
    HemisphereDimensions_C hemi_dims = {5};
    ret = geo_hemisphere_surface_areas(&hemi_dims, &sa_res);
    if(ret == GEO_SUCCESS) geo_print_surface_area_result(&sa_res);
    ret = geo_hemisphere_volume(&hemi_dims, &vol_res);
    if(ret == GEO_SUCCESS) geo_print_volume_result(&vol_res);

    // Frustum
    printf("\n-- Frustum --\n");
    FrustumDimensions_C frustum_dims = {6, 5, 2}; // h=6, R=5, r=2
    ret = geo_frustum_surface_areas(&frustum_dims, &sa_res);
    if(ret == GEO_SUCCESS) geo_print_surface_area_result(&sa_res);
    ret = geo_frustum_volume(&frustum_dims, &vol_res);
    if(ret == GEO_SUCCESS) geo_print_volume_result(&vol_res);

    return 0;
}