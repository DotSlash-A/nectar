#ifndef LINES_GEOMETRY_TYPES_H
#define LINES_GEOMETRY_TYPES_H

#include <string>
#include <optional> // For representing optional values (like Python's Optional)
#include <vector>   // Might be useful for other geometry later
#include <ostream> // <--- ADD THIS LINE

namespace LineGeometry {

    // Represents a point with X and Y coordinates.
    struct Coordinates {
        double x;
        double y;

        // Overload << for easy printing (optional but helpful)
        friend std::ostream& operator<<(std::ostream& os, const Coordinates& p) {
            os << "(" << p.x << ", " << p.y << ")";
            return os;
        }
    };

    // Represents the result of calculating line properties.
    struct LineEquationResult {
        std::optional<double> slope;
        std::optional<double> yIntercept;
        std::optional<double> xIntercept; // Added for completeness
        std::string equation;

        // Default constructor
        LineEquationResult() = default;

        // Constructor for common case
        LineEquationResult(std::optional<double> m, std::optional<double> b, std::string eq)
            : slope(m), yIntercept(b), xIntercept(std::nullopt), equation(std::move(eq)) {}
    };

    // Input for finding a missing variable in the slope formula.
    // Uses std::optional<double> to represent values that might not be provided.
    struct SlopeInput {
        std::optional<double> x1;
        std::optional<double> y1;
        std::optional<double> x2;
        std::optional<double> y2;
        std::optional<double> m; // Slope (can be angle or tangent depending on context)
    };

    // Input for a line in general form: Ax + By + C = 0.
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

    // Add other necessary structs corresponding to your Python models
    // e.g., Circle related structs would go here too.

} // namespace LineGeometry

#endif // LINES_GEOMETRY_TYPES_H