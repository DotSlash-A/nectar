#ifndef LINES_SLOPE_H
#define LINES_SLOPE_H

#include "geometry_types.h" // Include our type definitions
#include <string>
#include <vector>
#include <stdexcept> // For throwing exceptions
#include <optional>

namespace LineGeometry {

    /**
     * @brief Calculates the slope between two points.
     * @param p1 The first point.
     * @param p2 The second point.
     * @return The slope.
     * @throws std::invalid_argument if the points form a vertical line (x1 == x2).
     */
    double calculate_slope(const Coordinates& p1, const Coordinates& p2);

    /**
     * @brief Solves for a missing variable in the slope formula m = (y2 - y1) / (x2 - x1).
     * @details Assumes 'm' in input represents the *tangent* of the slope angle.
     * @param variable_to_find The name ("x1", "y1", "x2", "y2", "m").
     * @param input A SlopeInput struct containing known values.
     * @return The calculated value of the missing variable.
     * @throws std::invalid_argument if input is invalid, required values missing, or calc impossible.
     * @throws std::runtime_error for calculation errors like division by zero.
     */
    double find_missing_slope_variable(const std::string& variable_to_find, const SlopeInput& input);

     /**
      * @brief Solves for a missing variable in the slope formula using slope angle in degrees.
      * @details Handles angle-to-tangent conversion and vertical line cases.
      * @param variable_to_find The name ("x1", "y1", "x2", "y2", "m").
      * @param input A SlopeInput struct containing known values (m is angle in degrees).
      * @return The calculated value (or angle in degrees if finding 'm'). Returns infinity for vertical slope 'm'.
      * @throws std::invalid_argument if input invalid/missing, or calculation impossible.
      * @throws std::runtime_error for calculation errors.
      */
     double find_missing_slope_variable_angle(const std::string& variable_to_find, const SlopeInput& input);


    /**
     * @brief Calculates the slope-intercept form (y = mx + b) of a line.
     * @param p1 Optional first point. Required if p2 is provided and slope is nullopt. Required if slope is provided.
     * @param p2 Optional second point. Required if p1 is provided and slope is nullopt.
     * @param slope Optional slope. If nullopt, calculated from p1 and p2.
     * @return A LineEquationResult containing slope, y-intercept, and equation string.
     * @throws std::invalid_argument if insufficient info or vertical line.
     */
    LineEquationResult calculate_slope_intercept_form(
        const std::optional<Coordinates>& p1,
        const std::optional<Coordinates>& p2,
        const std::optional<double>& slope);

     /**
      * @brief Calculates the equation of a line perpendicular to a given line/points, passing through a specified y-intercept.
      * @param new_y_intercept The desired y-intercept for the perpendicular line.
      * @param p1 Optional first point defining the original line.
      * @param p2 Optional second point defining the original line.
      * @param original_slope Optional slope of the original line.
      * @return LineEquationResult for the perpendicular line.
      * @throws std::invalid_argument if original line is horizontal (perp is vertical) or insufficient info.
      */
     LineEquationResult calculate_perpendicular_line(
         double new_y_intercept,
         const std::optional<Coordinates>& p1,
         const std::optional<Coordinates>& p2,
         const std::optional<double>& original_slope);

    /**
     * @brief Generates the point-slope form string: y - y1 = m(x - x1).
     * @param point The point (x1, y1).
     * @param slope The slope (m).
     * @return The equation string in point-slope form.
     */
    std::string get_point_slope_form(const Coordinates& point, double slope);

    /**
     * @brief Generates the two-point form string: y - y1 = m(x - x1), where m is calculated.
     * @param p1 The first point.
     * @param p2 The second point.
     * @return The equation string in two-point form.
     * @throws std::invalid_argument if the points form a vertical line.
     */
    std::string get_two_point_form(const Coordinates& p1, const Coordinates& p2);

    /**
     * @brief Generates the intercept form string: x/a + y/b = 1.
     * @param x_intercept The x-intercept (a).
     * @param y_intercept The y-intercept (b).
     * @return The equation string in intercept form.
     * @throws std::invalid_argument if either intercept is zero.
     */
    std::string get_intercept_form(double x_intercept, double y_intercept);

     /**
      * @brief Generates the symmetric form string: (x - x1)/cos(theta) = (y - y1)/sin(theta) [= r].
      * @param theta_degrees Angle in degrees with positive x-axis.
      * @param p1 A point on the line (x1, y1).
      * @param p2 Another point (optional, used to calculate distance 'r' if desired, simple version omits '= r').
      * @return The equation string in symmetric form.
      * @throws std::invalid_argument for horizontal/vertical lines where form is ill-defined.
      */
     std::string get_symmetric_form(double theta_degrees, const Coordinates& p1, const std::optional<Coordinates>& p2 = std::nullopt);


    /**
     * @brief Generates the normal form string: x*cos(alpha) + y*sin(alpha) = p.
     * @param alpha_degrees The angle (alpha) the normal from origin makes with positive x-axis (degrees).
     * @param p Optional length of the normal (non-negative). If nullopt, calculated from point_on_line.
     * @param point_on_line Optional point on the line. Required if p is nullopt.
     * @return The equation string in normal form.
     * @throws std::invalid_argument if p is negative, or required info missing.
     */
    std::string get_normal_form(double alpha_degrees, const std::optional<double>& p, const std::optional<Coordinates>& point_on_line);

    /**
     * @brief Transforms general form (Ax + By + C = 0) to slope-intercept form (y = mx + b).
     * @param input GeneralLineInput containing A, B, C.
     * @return Equation string in slope-intercept form, or description if vertical/degenerate.
     */
    std::string transform_general_to_slope_intercept(const GeneralLineInput& input);

    /**
     * @brief Transforms general form (Ax + By + C = 0) to intercept form (x/a + y/b = 1).
     * @param input GeneralLineInput containing A, B, C.
     * @return Equation string in intercept form.
     * @throws std::invalid_argument if transformation is not possible (e.g., passes through origin, parallel to axis).
     */
    std::string transform_general_to_intercept_form(const GeneralLineInput& input);

} // namespace LineGeometry

#endif // LINES_SLOPE_H