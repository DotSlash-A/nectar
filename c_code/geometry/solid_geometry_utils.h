#ifndef SOLID_GEOMETRY_UTILS_H
#define SOLID_GEOMETRY_UTILS_H

#include "geometry_types.h"

// Cuboid
int geo_cuboid_surface_areas(const CuboidDimensions_C* dims, SurfaceAreaResult_C* result);
int geo_cuboid_volume(const CuboidDimensions_C* dims, VolumeResult_C* result);
int geo_cuboid_diagonal(const CuboidDimensions_C* dims, DiagonalResult_C* result);

// Cube
int geo_cube_surface_areas(const CubeDimensions_C* dims, SurfaceAreaResult_C* result);
int geo_cube_volume(const CubeDimensions_C* dims, VolumeResult_C* result);
int geo_cube_diagonal(const CubeDimensions_C* dims, DiagonalResult_C* result);

// Cylinder
int geo_cylinder_surface_areas(const CylinderDimensions_C* dims, SurfaceAreaResult_C* result);
int geo_cylinder_volume(const CylinderDimensions_C* dims, VolumeResult_C* result);

// Cone
int geo_cone_surface_areas(const ConeDimensions_C* dims, SurfaceAreaResult_C* result);
int geo_cone_volume(const ConeDimensions_C* dims, VolumeResult_C* result);

// Sphere
int geo_sphere_surface_area(const SphereDimensions_C* dims, SurfaceAreaResult_C* result);
int geo_sphere_volume(const SphereDimensions_C* dims, VolumeResult_C* result);

// Hemisphere
int geo_hemisphere_surface_areas(const HemisphereDimensions_C* dims, SurfaceAreaResult_C* result);
int geo_hemisphere_volume(const HemisphereDimensions_C* dims, VolumeResult_C* result);

// Frustum
int geo_frustum_surface_areas(const FrustumDimensions_C* dims, SurfaceAreaResult_C* result);
int geo_frustum_volume(const FrustumDimensions_C* dims, VolumeResult_C* result);

#endif // SOLID_GEOMETRY_UTILS_H