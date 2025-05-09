#ifndef SOLID_GEOMETRY_UTILS_H
#define SOLID_GEOMETRY_UTILS_H

#include "geometry_types.h"

namespace michu_fr {
namespace geometry {

// Cuboid
SurfaceAreaResult cuboidSurfaceAreas(const CuboidDimensions& dims);
VolumeResult cuboidVolume(const CuboidDimensions& dims);
DiagonalResult cuboidDiagonal(const CuboidDimensions& dims);

// Cube
SurfaceAreaResult cubeSurfaceAreas(const CubeDimensions& dims);
VolumeResult cubeVolume(const CubeDimensions& dims);
DiagonalResult cubeDiagonal(const CubeDimensions& dims);

// Cylinder
SurfaceAreaResult cylinderSurfaceAreas(const CylinderDimensions& dims);
VolumeResult cylinderVolume(const CylinderDimensions& dims);

// Cone
SurfaceAreaResult coneSurfaceAreas(const ConeDimensions& dims);
VolumeResult coneVolume(const ConeDimensions& dims);

// Sphere
SurfaceAreaResult sphereSurfaceArea(const SphereDimensions& dims);
VolumeResult sphereVolume(const SphereDimensions& dims);

// Hemisphere
SurfaceAreaResult hemisphereSurfaceAreas(const HemisphereDimensions& dims);
VolumeResult hemisphereVolume(const HemisphereDimensions& dims);

// Frustum
SurfaceAreaResult frustumSurfaceAreas(const FrustumDimensions& dims);
VolumeResult frustumVolume(const FrustumDimensions& dims);

} // namespace geometry
} // namespace michu_fr

#endif // SOLID_GEOMETRY_UTILS_H