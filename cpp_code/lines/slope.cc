#include "slope.h"
#include "geometry_types.h"

#include <cmath>       // For fabs, sqrt, pow, cos, sin, tan, atan, M_PI (maybe)
#include <sstream>     // For string formatting
#include <iomanip>     // For std::fixed, std::setprecision
#include <stdexcept>   // For exceptions
#include <limits>      // For infinity

namespace LineGeometry {

    // Define PI if not available (M_PI is common but not standard C++)
    #ifndef M_PI
    #define M_PI 3.14159265358979323846
    #endif

    constexpr double EPSILON = 1e-9; // Small value for float comparison

    // --- Helper Function ---
    /**
     * @brief Formats a slope-intercept equation string nicely (y = mx + b).
     */
    std::string format_slope_intercept_equation(double m, double b) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2); // Set precision for output

        bool m_is_zero = std::fabs(m) < EPSILON;
        bool b_is_zero = std::fabs(b) < EPSILON;
        bool m_is_one = std::fabs(m - 1.0) < EPSILON;
        bool m_is_neg_one = std::fabs(m + 1.0) < EPSILON;

        oss << "y = ";

        if (m_is_zero) {
            oss << b;
        } else {
            if (m_is_neg_one) {
                oss << "-"; // Sign only
            } else if (!m_is_one) {
                oss << m; // Print slope value if not 1 or -1
            }
            oss << "x"; // Always print x if slope is non-zero

            if (!b_is_zero) {
                oss << (b > 0 ? " + " : " - ") << std::fabs(b);
            }
        }
        return oss.str();
    }
    // --- End Helper ---


    double calculate_slope(const Coordinates& p1, const Coordinates& p2) {
        if (std::fabs(p2.x - p1.x) < EPSILON) {
            throw std::invalid_argument("Cannot calculate slope for a vertical line (x1 == x2).");
        }
        return (p2.y - p1.y) / (p2.x - p1.x);
    }

    double find_missing_slope_variable(const std::string& variable_to_find, const SlopeInput& input) {
        // Check if slope 'm' (tangent value) is required but missing
        if (variable_to_find != "m" && !input.m.has_value()) {
            throw std::invalid_argument("Error: Slope 'm' (tangent) is required unless finding 'm'.");
        }

        // Get values, using .value() which throws if optional is empty
        try {
            if (variable_to_find == "x2") {
                if (!input.y2 || !input.y1 || !input.x1) throw std::invalid_argument("Missing required values (y2, y1, x1) to find 'x2'.");
                double m_val = input.m.value();
                if (std::fabs(m_val) < EPSILON) throw std::runtime_error("Cannot solve for x2 with zero slope (horizontal line).");
                return input.x1.value() + (input.y2.value() - input.y1.value()) / m_val;
            } else if (variable_to_find == "x1") {
                 if (!input.y2 || !input.y1 || !input.x2) throw std::invalid_argument("Missing required values (y2, y1, x2) to find 'x1'.");
                 double m_val = input.m.value();
                if (std::fabs(m_val) < EPSILON) throw std::runtime_error("Cannot solve for x1 with zero slope (horizontal line).");
                 return input.x2.value() - (input.y2.value() - input.y1.value()) / m_val;
            } else if (variable_to_find == "y2") {
                if (!input.x2 || !input.y1 || !input.x1) throw std::invalid_argument("Missing required values (x2, y1, x1) to find 'y2'.");
                return input.y1.value() + input.m.value() * (input.x2.value() - input.x1.value());
            } else if (variable_to_find == "y1") {
                 if (!input.x2 || !input.y2 || !input.x1) throw std::invalid_argument("Missing required values (x2, y2, x1) to find 'y1'.");
                 return input.y2.value() - input.m.value() * (input.x2.value() - input.x1.value());
            } else if (variable_to_find == "m") {
                if (!input.x1 || !input.y1 || !input.x2 || !input.y2) throw std::invalid_argument("Missing required values (x1, y1, x2, y2) to find 'm'.");
                double dx = input.x2.value() - input.x1.value();
                if (std::fabs(dx) < EPSILON) throw std::runtime_error("Cannot calculate slope 'm' when x1 and x2 are equal (vertical line).");
                return (input.y2.value() - input.y1.value()) / dx;
            } else {
                 throw std::invalid_argument("Invalid value for 'variable_to_find'. Must be one of 'x1', 'y1', 'x2', 'y2', 'm'.");
            }
        } catch (const std::bad_optional_access& e) {
            // This catches cases where .value() was called on an empty optional,
            // though the initial checks should prevent this.
            throw std::invalid_argument("Missing required input value for calculation.");
        } catch (const std::runtime_error&) {
            // Re-throw runtime errors (like division by zero)
            throw;
        }
    }

     double find_missing_slope_variable_angle(const std::string& variable_to_find, const SlopeInput& input) {
         // Check if slope angle 'm' is required but missing
         if (variable_to_find != "m" && !input.m.has_value()) {
             throw std::invalid_argument("Error: Slope angle 'm' (degrees) is required unless finding 'm'.");
         }

         std::optional<double> tangent_m = std::nullopt;
         bool is_vertical = false;

         if (input.m.has_value()) {
             double angle_deg = input.m.value();
             double angle_rad = angle_deg * M_PI / 180.0;
             if (std::fabs(std::cos(angle_rad)) < EPSILON) { // Check for vertical (90, -90, 270...)
                 is_vertical = true;
                 tangent_m = std::numeric_limits<double>::infinity(); // Represent vertical slope tangent
             } else {
                 tangent_m = std::tan(angle_rad);
             }
         }

         // Handle finding 'm' (angle) separately
         if (variable_to_find == "m") {
             if (!input.x1 || !input.y1 || !input.x2 || !input.y2) {
                 throw std::invalid_argument("Missing required values (x1, y1, x2, y2) to find 'm'.");
             }
             double dx = input.x2.value() - input.x1.value();
             double dy = input.y2.value() - input.y1.value();
             if (std::fabs(dx) < EPSILON) {
                 // Vertical line, return 90 degrees (or handle based on dy sign if needed)
                 return (dy > 0) ? 90.0 : (dy < 0 ? -90.0 : 0.0); // Or just 90.0
             } else {
                 double slope_tan = dy / dx;
                 return std::atan(slope_tan) * 180.0 / M_PI; // Convert radians back to degrees
             }
         }

         // Handle vertical line cases for other variables
         if (is_vertical) {
             if (variable_to_find == "x1") {
                 if (!input.x2) throw std::invalid_argument("Missing x2 for vertical line case to find x1.");
                 return input.x2.value(); // x1 must equal x2
             } else if (variable_to_find == "x2") {
                 if (!input.x1) throw std::invalid_argument("Missing x1 for vertical line case to find x2.");
                 return input.x1.value(); // x2 must equal x1
             } else if (variable_to_find == "y1" || variable_to_find == "y2") {
                 throw std::invalid_argument("Cannot solve for y1 or y2 for a vertical line using this slope method.");
             }
         }

         // If not vertical or finding angle, delegate to the tangent-based function
         SlopeInput tangent_input = input; // Copy input
         tangent_input.m = tangent_m;     // Set the calculated tangent
         return find_missing_slope_variable(variable_to_find, tangent_input);
     }


    LineEquationResult calculate_slope_intercept_form(
        const std::optional<Coordinates>& p1_opt,
        const std::optional<Coordinates>& p2_opt,
        const std::optional<double>& slope_opt)
    {
        double m, b;
        Coordinates p1_val; // Need a point to calculate intercept

        if (slope_opt.has_value()) {
            // Slope is given, need at least one point
            if (!p1_opt.has_value()) {
                throw std::invalid_argument("At least one point (p1) is required when slope is provided.");
            }
            m = slope_opt.value();
            p1_val = p1_opt.value();
        } else {
            // Slope needs calculation from two points
            if (!p1_opt.has_value() || !p2_opt.has_value()) {
                throw std::invalid_argument("Both point1 and point2 are required when slope is not provided.");
            }
            p1_val = p1_opt.value(); // Use p1 for intercept calc
            const Coordinates& p2_val = p2_opt.value();
            // calculate_slope throws if vertical
            m = calculate_slope(p1_val, p2_val);
        }

        // Calculate y-intercept: b = y1 - m*x1
        b = p1_val.y - m * p1_val.x;

        std::string equation = format_slope_intercept_equation(m, b);
        return LineEquationResult(m, b, equation);
    }

     LineEquationResult calculate_perpendicular_line(
         double new_y_intercept,
         const std::optional<Coordinates>& p1_opt,
         const std::optional<Coordinates>& p2_opt,
         const std::optional<double>& original_slope_opt)
     {
         double m_orig;

         // 1. Find original slope
         if (original_slope_opt.has_value()) {
             m_orig = original_slope_opt.value();
         } else {
             if (!p1_opt.has_value() || !p2_opt.has_value()) {
                 throw std::invalid_argument("Both p1 and p2 required if original_slope is not provided.");
             }
             const auto& p1 = p1_opt.value();
             const auto& p2 = p2_opt.value();
             if (std::fabs(p2.x - p1.x) < EPSILON) {
                  // Original line is vertical. Perpendicular is horizontal.
                  double perp_slope = 0.0;
                  std::string equation = format_slope_intercept_equation(perp_slope, new_y_intercept);
                  return LineEquationResult(perp_slope, new_y_intercept, equation);
             }
              m_orig = calculate_slope(p1, p2);
         }

         // 2. Check if original line is horizontal
          if (std::fabs(m_orig) < EPSILON) {
              throw std::invalid_argument("Original line is horizontal (slope=0), perpendicular line is vertical (undefined slope-intercept).");
          }

         // 3. Calculate perpendicular slope
         double perp_slope = -1.0 / m_orig;

         // 4. Format the equation
         std::string equation = format_slope_intercept_equation(perp_slope, new_y_intercept);
         return LineEquationResult(perp_slope, new_y_intercept, equation);
     }

    std::string get_point_slope_form(const Coordinates& point, double slope) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);
        oss << "y - " << point.y << " = " << slope << "(x - " << point.x << ")";
        return oss.str();
    }

    std::string get_two_point_form(const Coordinates& p1, const Coordinates& p2) {
        // calculate_slope throws if vertical
        double slope = calculate_slope(p1, p2);
        return get_point_slope_form(p1, slope); // Use p1 for the form
    }

    std::string get_intercept_form(double x_intercept, double y_intercept) {
         if (std::fabs(x_intercept) < EPSILON || std::fabs(y_intercept) < EPSILON) {
            throw std::invalid_argument("Intercepts cannot be zero for the standard intercept form x/a + y/b = 1.");
        }
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);
        oss << "x / " << x_intercept << " + y / " << y_intercept << " = 1";
        return oss.str();
    }

     std::string get_symmetric_form(double theta_degrees, const Coordinates& p1, const std::optional<Coordinates>& p2) {
         double theta_rad = theta_degrees * M_PI / 180.0;
         double cos_theta = std::cos(theta_rad);
         double sin_theta = std::sin(theta_rad);

         if (std::fabs(cos_theta) < EPSILON || std::fabs(sin_theta) < EPSILON) {
              throw std::invalid_argument("Symmetric form is ill-defined for horizontal or vertical lines.");
         }

         std::ostringstream oss;
         oss << std::fixed << std::setprecision(3); // Use more precision for trig results
         oss << "(x - " << std::fixed << std::setprecision(2) << p1.x << ") / "
             << std::fixed << std::setprecision(3) << cos_theta
             << " = (y - " << std::fixed << std::setprecision(2) << p1.y << ") / "
             << std::fixed << std::setprecision(3) << sin_theta;

          // Optionally calculate and add the distance 'r' if p2 is provided
         if (p2.has_value()) {
              const auto& p2_val = p2.value();
              double dist = std::sqrt(std::pow(p2_val.x - p1.x, 2) + std::pow(p2_val.y - p1.y, 2));
              // Note: Sign of 'r' depends on direction, simple distance shown here
              oss << " (= +/-" << std::fixed << std::setprecision(2) << dist << ")";
         }

         return oss.str();
     }

    std::string get_normal_form(double alpha_degrees, const std::optional<double>& p_opt, const std::optional<Coordinates>& point_on_line) {
        double p_value;
        double alpha_rad = alpha_degrees * M_PI / 180.0;
        double cos_alpha = std::cos(alpha_rad);
        double sin_alpha = std::sin(alpha_rad);

        if (p_opt.has_value()) {
            p_value = p_opt.value();
            if (p_value < -EPSILON) { // Allow for small floating point inaccuracies near zero
                 throw std::invalid_argument("Distance 'p' in normal form must be non-negative.");
            }
             if (p_value < 0) p_value = 0; // Clamp small negative values to 0
        } else {
            if (!point_on_line.has_value()) {
                 throw std::invalid_argument("point_on_line is required if p is nullopt.");
            }
            const auto& pt = point_on_line.value();
            p_value = pt.x * cos_alpha + pt.y * sin_alpha;
            // Warning: This p_value might be negative. Standard normal form requires p >= 0.
            // A proper conversion would adjust alpha and p if p_value is negative.
            if (p_value < -EPSILON) {
                 // For simplicity here, we allow it but a robust implementation should fix it.
                 // std::cerr << "Warning: Calculated 'p' is negative. Standard normal form requires p >= 0." << std::endl;
            }
             if (std::fabs(p_value) < EPSILON) p_value = 0.0;
        }

         std::ostringstream oss;
         // Option 1: Show explicit cos/sin
         // oss << std::fixed << std::setprecision(3);
         // oss << "x * (" << cos_alpha << ") + y * (" << sin_alpha << ") = " << p_value;

         // Option 2: Show angles
         oss << std::fixed << std::setprecision(1); // Precision for angle display
         oss << "x * cos(" << alpha_degrees << "°) + y * sin(" << alpha_degrees << "°) = "
             << std::fixed << std::setprecision(3) << p_value; // Precision for p

         return oss.str();
    }


    std::string transform_general_to_slope_intercept(const GeneralLineInput& input) {
        double a = input.a;
        double b = input.b;
        double c = input.c;

        if (std::fabs(b) < EPSILON) {
            // Vertical line: Ax + C = 0 => x = -C/A
            if (std::fabs(a) < EPSILON) {
                return (std::fabs(c) < EPSILON) ? "Degenerate line (0 = 0)" : "Invalid line (non-zero constant = 0)";
            }
             std::ostringstream oss;
             oss << std::fixed << std::setprecision(2);
             oss << "Vertical line: x = " << (-c / a);
             return oss.str();
        }

        // y = (-A/B)x + (-C/B)
        double m = -a / b;
        double y_intercept = -c / b;
        return format_slope_intercept_equation(m, y_intercept);
    }

     std::string transform_general_to_intercept_form(const GeneralLineInput& input) {
        double a = input.a;
        double b = input.b;
        double c = input.c;

        if (std::fabs(c) < EPSILON) {
            throw std::invalid_argument("Line passes through the origin (C=0), intercept form x/a + y/b = 1 is undefined.");
        }
        if (std::fabs(a) < EPSILON || std::fabs(b) < EPSILON) {
            throw std::invalid_argument("Line is parallel to an axis (A=0 or B=0), intercept form x/a + y/b = 1 is undefined.");
        }

        // Ax + By = -C
        // x / (-C/A) + y / (-C/B) = 1
        double x_intercept = -c / a;
        double y_intercept = -c / b;

        return get_intercept_form(x_intercept, y_intercept);
     }


} // namespace LineGeometry

// int main() {
//     SlopeCoordinates coords = {1.0, 2.0, 3.0, 6.0};
//     double slope = slopecoordinates(coords);
//     printf("Slope: %f\n", slope);
//     return 0;
// }