// cpp_code/circles/circles_types.h
#ifndef CIRCLES_TYPES_H
#define CIRCLES_TYPES_H

#include "../lines/geometry_types.h" // Include Coordinates from lines dir
#include <string>
#include <optional> // Requires C++17
#include <vector>   // Include vector for PointPositionResponse if needed

namespace geometry {
namespace circles {

// Input for creating circle from center/radius (matches python circleGenral)
struct CircleGeneralInput {
    double h = 0.0; // Center x
    double k = 0.0; // Center y
    double r = 0.0; // Radius
};

struct Coordinates {
    double x;
    double y;

    // Overload << for easy printing (optional but helpful)
    friend std::ostream& operator<<(std::ostream& os, const Coordinates& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};
struct GeneralLineInput {
    double a;
    double b;
    double c;

     // Overload << for easy printing (optional but helpful)
    friend std::ostream& operator<<(std::ostream& os, const GeneralLineInput& line) {
        os << line.a << "x + " << line.b << "y + " << line.c << " = 0";
        return os;
    }
};

// Response containing circle equations and details
struct CircleEqnResponse {
    std::string standardForm;
    std::string generalForm;
    double centerH = 0.0;
    double centerK = 0.0;
    double radius = 0.0;
    double coeffA = 0.0; // General form coeffs (A=1 assumed often)
    double coeffB = 0.0; // General form coeffs (B=1 assumed often)
    double coeffC = 0.0;
    double coeffD = 0.0;
    double coeffE = 0.0;
};

// Input for getting details from general form string (use with caution)
// Better alternative: struct CircleCoeffsInput { double a, b, c, d, e; };
struct CircleGeneralFormInput {
    std::string equation;
};

// Response containing calculated center/radius from general form
struct CircleDetailsResponse {
    double centerH = 0.0;
    double centerK = 0.0;
    double radius = 0.0;
    std::string inputEquation;
    std::optional<std::string> normalizedEquation; // Optional field
};

// Input for creating circle from three points
struct CircleWThreePointsInput {
    Coordinates p;
    Coordinates q;
    Coordinates r;
};

// Input for parametric/position functions (if taking equation string)
struct EquationInput {
    std::string equation;
};

// Response for parametric equations
struct ParametricCircleResponse {
    std::string parametricX; // e.g., "h + r*cos(t)"
    std::string parametricY; // e.g., "k + r*sin(t)"
    double centerH = 0.0;
    double centerK = 0.0;
    double radius = 0.0;
};

// Response for functions returning only the equation string
struct CircleEquationOnlyResponse {
    std::string circleEquation;
};

// Response for point position relative to circle
struct PointPositionResponse {
    std::string position; // "inside", "on", "outside"
};

// Coefficients from a general circle equation (useful internal representation)
// Ax^2 + By^2 + Cx + Dy + E = 0
struct CircleCoeffs {
     double a = 0.0;
     double b = 0.0;
     double c = 0.0;
     double d = 0.0;
     double e = 0.0;
};


} // namespace circles
} // namespace geometry

#endif // CIRCLES_TYPES_H