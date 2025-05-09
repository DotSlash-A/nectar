#ifndef GEOMETRY_TYPES_H
#define GEOMETRY_TYPES_H

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <optional>
#include <iomanip> // For std::fixed, std::setprecision
#include <cmath>   // For M_PI (might need _USE_MATH_DEFINES on Windows), std::sqrt, std::pow

// Ensure M_PI is defined
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

namespace michu_fr {
namespace geometry {

// --- Dimension Structs ---
struct CuboidDimensions {
    double length;
    double breadth;
    double height;
    CuboidDimensions(double l, double b, double h) : length(l), breadth(b), height(h) {
        if (l <= 0 || b <= 0 || h <= 0) throw std::invalid_argument("Cuboid dimensions must be positive.");
    }
    std::string toString() const {
        std::ostringstream oss;
        oss << "length=" << length << ", breadth=" << breadth << ", height=" << height;
        return oss.str();
    }
};

struct CubeDimensions {
    double side;
    CubeDimensions(double s) : side(s) {
        if (s <= 0) throw std::invalid_argument("Cube side must be positive.");
    }
    std::string toString() const { return "side=" + std::to_string(side); }
};

struct CylinderDimensions {
    double radius;
    double height;
    CylinderDimensions(double r, double h) : radius(r), height(h) {
        if (r <= 0 || h <= 0) throw std::invalid_argument("Cylinder radius and height must be positive.");
    }
    std::string toString() const {
        return "radius=" + std::to_string(radius) + ", height=" + std::to_string(height);
    }
};

struct ConeDimensions {
    double radius;
    double height;
    ConeDimensions(double r, double h) : radius(r), height(h) {
        if (r <= 0 || h <= 0) throw std::invalid_argument("Cone radius and height must be positive.");
    }
    std::string toString() const {
        return "radius=" + std::to_string(radius) + ", height=" + std::to_string(height);
    }
};

struct SphereDimensions {
    double radius;
    SphereDimensions(double r) : radius(r) {
        if (r <= 0) throw std::invalid_argument("Sphere radius must be positive.");
    }
    std::string toString() const { return "radius=" + std::to_string(radius); }
};

// HemisphereDimensions is same as SphereDimensions for input
using HemisphereDimensions = SphereDimensions;

struct FrustumDimensions {
    double height;
    double radius1; // Larger radius R
    double radius2; // Smaller radius r
    FrustumDimensions(double h, double r1, double r2) : height(h), radius1(r1), radius2(r2) {
        if (h <= 0 || r1 < 0 || r2 < 0)
            throw std::invalid_argument("Frustum height positive, radii non-negative.");
        if (r1 < r2) // Ensure radius1 is R (larger or equal)
            throw std::invalid_argument("For FrustumDimensions, radius1 (R) must be >= radius2 (r).");
    }
    std::string toString() const {
        return "height=" + std::to_string(height) + ", R=" + std::to_string(radius1) + ", r=" + std::to_string(radius2);
    }
};

// --- Result Structs ---
struct SurfaceAreaResult {
    std::string shape;
    std::string dimensions_string;
    std::optional<double> lateral_or_curved_surface_area;
    std::optional<double> total_surface_area;
    std::optional<double> surface_area_sphere; // Specific for sphere
    std::optional<double> calculated_slant_height;

    // General constructor
    SurfaceAreaResult(std::string s, std::string ds,
                      std::optional<double> lcsa, std::optional<double> tsa,
                      std::optional<double> sa_sph, std::optional<double> csh)
        : shape(std::move(s)), dimensions_string(std::move(ds)),
          lateral_or_curved_surface_area(lcsa), total_surface_area(tsa),
          surface_area_sphere(sa_sph), calculated_slant_height(csh) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << "SurfaceAreaResult{shape='" << shape << "', dimensions={" << dimensions_string << "}";
        if (lateral_or_curved_surface_area) oss << ", LSA/CSA=" << *lateral_or_curved_surface_area;
        if (total_surface_area) oss << ", TSA=" << *total_surface_area;
        if (surface_area_sphere) oss << ", SA(Sphere)=" << *surface_area_sphere;
        if (calculated_slant_height) oss << ", SlantHeight(calc)=" << *calculated_slant_height;
        oss << "}";
        return oss.str();
    }
};

struct VolumeResult {
    std::string shape;
    std::string dimensions_string;
    double volume;

    VolumeResult(std::string s, std::string ds, double v)
        : shape(std::move(s)), dimensions_string(std::move(ds)), volume(v) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << "VolumeResult{shape='" << shape << "', dimensions={" << dimensions_string << "}"
            << ", volume=" << volume << "}";
        return oss.str();
    }
};

struct DiagonalResult {
    std::string shape;
    std::string dimensions_string;
    double diagonal;

    DiagonalResult(std::string s, std::string ds, double d)
        : shape(std::move(s)), dimensions_string(std::move(ds)), diagonal(d) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << "DiagonalResult{shape='" << shape << "', dimensions={" << dimensions_string << "}"
            << ", diagonal=" << diagonal << "}";
        return oss.str();
    }
};

} // namespace geometry
} // namespace michu_fr

#endif // GEOMETRY_TYPES_H