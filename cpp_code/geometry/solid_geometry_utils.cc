#include "solid_geometry_utils.h"
#include <stdexcept> // For std::invalid_argument

namespace michu_fr {
namespace geometry {

// --- Cuboid ---
SurfaceAreaResult cuboidSurfaceAreas(const CuboidDimensions& dims) {
    double lsa = 2 * (dims.length + dims.breadth) * dims.height;
    double tsa = 2 * ((dims.length * dims.breadth) + (dims.breadth * dims.height) + (dims.height * dims.length));
    return SurfaceAreaResult("Cuboid", dims.toString(), lsa, tsa, std::nullopt, std::nullopt);
}
VolumeResult cuboidVolume(const CuboidDimensions& dims) {
    return VolumeResult("Cuboid", dims.toString(), dims.length * dims.breadth * dims.height);
}
DiagonalResult cuboidDiagonal(const CuboidDimensions& dims) {
    double d_sq = dims.length * dims.length + dims.breadth * dims.breadth + dims.height * dims.height;
    return DiagonalResult("Cuboid", dims.toString(), std::sqrt(d_sq));
}

// --- Cube ---
SurfaceAreaResult cubeSurfaceAreas(const CubeDimensions& dims) {
    double lsa = 4 * dims.side * dims.side;
    double tsa = 6 * dims.side * dims.side;
    return SurfaceAreaResult("Cube", dims.toString(), lsa, tsa, std::nullopt, std::nullopt);
}
VolumeResult cubeVolume(const CubeDimensions& dims) {
    return VolumeResult("Cube", dims.toString(), std::pow(dims.side, 3));
}
DiagonalResult cubeDiagonal(const CubeDimensions& dims) {
    return DiagonalResult("Cube", dims.toString(), dims.side * std::sqrt(3.0));
}

// --- Cylinder ---
SurfaceAreaResult cylinderSurfaceAreas(const CylinderDimensions& dims) {
    double csa = 2 * M_PI * dims.radius * dims.height;
    double tsa = 2 * M_PI * dims.radius * (dims.height + dims.radius);
    return SurfaceAreaResult("Cylinder", dims.toString(), csa, tsa, std::nullopt, std::nullopt);
}
VolumeResult cylinderVolume(const CylinderDimensions& dims) {
    return VolumeResult("Cylinder", dims.toString(), M_PI * dims.radius * dims.radius * dims.height);
}

// --- Cone ---
double calculateConeSlantHeight(double radius, double height) {
    return std::sqrt(radius * radius + height * height);
}
SurfaceAreaResult coneSurfaceAreas(const ConeDimensions& dims) {
    double slant_height = calculateConeSlantHeight(dims.radius, dims.height);
    double csa = M_PI * dims.radius * slant_height;
    double tsa = M_PI * dims.radius * (slant_height + dims.radius);
    return SurfaceAreaResult("Cone", dims.toString(), csa, tsa, std::nullopt, slant_height);
}
VolumeResult coneVolume(const ConeDimensions& dims) {
    return VolumeResult("Cone", dims.toString(), (1.0/3.0) * M_PI * dims.radius * dims.radius * dims.height);
}

// --- Sphere ---
SurfaceAreaResult sphereSurfaceArea(const SphereDimensions& dims) {
    double sa = 4 * M_PI * dims.radius * dims.radius;
    return SurfaceAreaResult("Sphere", dims.toString(), std::nullopt, std::nullopt, sa, std::nullopt);
}
VolumeResult sphereVolume(const SphereDimensions& dims) {
    return VolumeResult("Sphere", dims.toString(), (4.0/3.0) * M_PI * std::pow(dims.radius, 3));
}

// --- Hemisphere ---
SurfaceAreaResult hemisphereSurfaceAreas(const HemisphereDimensions& dims) {
    double csa = 2 * M_PI * dims.radius * dims.radius;
    double tsa = 3 * M_PI * dims.radius * dims.radius;
    return SurfaceAreaResult("Hemisphere", dims.toString(), csa, tsa, std::nullopt, std::nullopt);
}
VolumeResult hemisphereVolume(const HemisphereDimensions& dims) {
    return VolumeResult("Hemisphere", dims.toString(), (2.0/3.0) * M_PI * std::pow(dims.radius, 3));
}

// --- Frustum ---
double calculateFrustumSlantHeight(double height, double R, double r) {
    return std::sqrt(height * height + std::pow(R - r, 2));
}
SurfaceAreaResult frustumSurfaceAreas(const FrustumDimensions& dims) {
    double R = dims.radius1;
    double r = dims.radius2;
    double h = dims.height;
    double slant_height = calculateFrustumSlantHeight(h, R, r);

    double csa = M_PI * slant_height * (R + r);
    double tsa = csa + (M_PI * R * R) + (M_PI * r * r);
    return SurfaceAreaResult("Frustum", dims.toString(), csa, tsa, std::nullopt, slant_height);
}
VolumeResult frustumVolume(const FrustumDimensions& dims) {
    double R = dims.radius1;
    double r = dims.radius2;
    double h = dims.height;
    double vol = (1.0/3.0) * M_PI * h * (R*R + r*r + R*r);
    return VolumeResult("Frustum", dims.toString(), vol);
}

} // namespace geometry
} // namespace michu_fr