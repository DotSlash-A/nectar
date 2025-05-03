#ifndef LINES_SLOPE_H
#define LINES_SLOPE_H

#include "geometry_types.h" // Include our type definitions
#include <stddef.h>         // For size_t

// --- Function Declarations ---
// Functions generally return an integer status code (0 for success).
// Results are returned via output parameters (pointers).

/**
 * @brief Calculates the slope between two points.
 * @param p1 Pointer to the first point.
 * @param p2 Pointer to the second point.
 * @param out_slope Pointer to a double where the calculated slope will be stored.
 * @return LINE_SUCCESS on success, LINE_ERR_MATH if vertical, LINE_ERR_INVALID_ARG if p1/p2/out_slope is NULL.
 */
int Line_calculate_slope(const Line_Coordinates *p1, const Line_Coordinates *p2, double *out_slope);

/**
 * @brief Solves for a missing variable in the slope formula m = (y2 - y1) / (x2 - x1).
 * @details Assumes 'm' in input represents the *tangent* of the slope angle.
 * @param variable_to_find String naming the variable ("x1", "y1", "x2", "y2", "m").
 * @param input Pointer to a Line_SlopeInput struct containing known values (use NULL pointers for unknowns).
 * @param out_result Pointer to a double where the calculated value will be stored.
 * @return LINE_SUCCESS on success, LINE_ERR_INVALID_ARG for bad input/missing values, LINE_ERR_MATH for calculation errors.
 */
int Line_find_missing_slope_variable(const char *variable_to_find, const Line_SlopeInput *input, double *out_result);

/**
 * @brief Solves for a missing variable in the slope formula using slope angle in degrees.
 * @details Handles angle-to-tangent conversion and vertical line cases.
 * @param variable_to_find String naming the variable ("x1", "y1", "x2", "y2", "m").
 * @param input Pointer to a Line_SlopeInput struct (input->m points to angle in degrees).
 * @param out_result Pointer to a double where the calculated value (or angle in degrees if finding 'm') will be stored.
 * @return LINE_SUCCESS on success, LINE_ERR_INVALID_ARG for bad input/missing values, LINE_ERR_MATH for calculation errors.
 */
int Line_find_missing_slope_variable_angle(const char *variable_to_find, const Line_SlopeInput *input, double *out_result);


/**
 * @brief Calculates the slope-intercept form (y = mx + b) of a line.
 * @param p1 Pointer to the first point (can be NULL if slope is provided).
 * @param p2 Pointer to the second point (can be NULL if slope is provided).
 * @param slope Pointer to the slope (can be NULL if p1 and p2 are provided).
 * @param out_result Pointer to a Line_EquationResult struct to store the results (slope, intercept, equation string).
 * @return LINE_SUCCESS on success, LINE_ERR_INVALID_ARG if insufficient info or output ptr NULL, LINE_ERR_MATH if vertical.
 */
int Line_calculate_slope_intercept_form(
    const Line_Coordinates *p1,
    const Line_Coordinates *p2,
    const double *slope,
    Line_EquationResult *out_result);

/**
 * @brief Calculates the equation of a line perpendicular to a given line/points, passing through a specified y-intercept.
 * @param new_y_intercept The desired y-intercept for the perpendicular line.
 * @param p1 Pointer to the first point defining the original line (can be NULL if original_slope is provided).
 * @param p2 Pointer to the second point defining the original line (can be NULL if original_slope is provided).
 * @param original_slope Pointer to the slope of the original line (can be NULL if p1 and p2 provided).
 * @param out_result Pointer to a Line_EquationResult struct for the perpendicular line.
 * @return LINE_SUCCESS on success, LINE_ERR_INVALID_ARG if insufficient info or output ptr NULL, LINE_ERR_MATH if original line horizontal/vertical issues.
 */
int Line_calculate_perpendicular_line(
    double new_y_intercept,
    const Line_Coordinates *p1,
    const Line_Coordinates *p2,
    const double *original_slope,
    Line_EquationResult *out_result);


/**
 * @brief Generates the point-slope form string: y - y1 = m(x - x1).
 * @param point Pointer to the point (x1, y1).
 * @param slope The slope (m).
 * @param buffer Char buffer to store the resulting equation string.
 * @param buffer_size The size of the provided buffer.
 * @return LINE_SUCCESS on success, LINE_ERR_INVALID_ARG if point/buffer NULL, LINE_ERR_BUFFER_TOO_SMALL if buffer insufficient.
 */
int Line_get_point_slope_form(const Line_Coordinates *point, double slope, char *buffer, size_t buffer_size);

/**
 * @brief Generates the two-point form string: y - y1 = m(x - x1), where m is calculated.
 * @param p1 Pointer to the first point.
 * @param p2 Pointer to the second point.
 * @param buffer Char buffer to store the resulting equation string.
 * @param buffer_size The size of the provided buffer.
 * @return LINE_SUCCESS on success, LINE_ERR_INVALID_ARG if points/buffer NULL, LINE_ERR_MATH if vertical, LINE_ERR_BUFFER_TOO_SMALL.
 */
int Line_get_two_point_form(const Line_Coordinates *p1, const Line_Coordinates *p2, char *buffer, size_t buffer_size);

/**
 * @brief Generates the intercept form string: x/a + y/b = 1.
 * @param x_intercept The x-intercept (a).
 * @param y_intercept The y-intercept (b).
 * @param buffer Char buffer to store the resulting equation string.
 * @param buffer_size The size of the provided buffer.
 * @return LINE_SUCCESS on success, LINE_ERR_INVALID_ARG if intercepts zero or buffer NULL, LINE_ERR_BUFFER_TOO_SMALL.
 */
int Line_get_intercept_form(double x_intercept, double y_intercept, char *buffer, size_t buffer_size);

/**
 * @brief Generates the symmetric form string: (x - x1)/cos(theta) = (y - y1)/sin(theta).
 * @param theta_degrees Angle in degrees with positive x-axis.
 * @param p1 Pointer to a point on the line (x1, y1).
 * @param buffer Char buffer to store the resulting equation string.
 * @param buffer_size The size of the provided buffer.
 * @return LINE_SUCCESS on success, LINE_ERR_INVALID_ARG if p1/buffer NULL or horizontal/vertical line, LINE_ERR_BUFFER_TOO_SMALL.
 */
int Line_get_symmetric_form(double theta_degrees, const Line_Coordinates *p1, char *buffer, size_t buffer_size);


/**
 * @brief Generates the normal form string: x*cos(alpha) + y*sin(alpha) = p.
 * @param alpha_degrees The angle (alpha) the normal from origin makes with positive x-axis (degrees).
 * @param p Pointer to the length of the normal (non-negative). If NULL, calculated from point_on_line.
 * @param point_on_line Pointer to a point on the line. Required if p is NULL.
 * @param buffer Char buffer to store the resulting equation string.
 * @param buffer_size The size of the provided buffer.
 * @return LINE_SUCCESS on success, LINE_ERR_INVALID_ARG if required info missing, p negative, or buffer NULL, LINE_ERR_BUFFER_TOO_SMALL.
 */
int Line_get_normal_form(double alpha_degrees, const double *p, const Line_Coordinates *point_on_line, char *buffer, size_t buffer_size);

/**
 * @brief Transforms general form (Ax + By + C = 0) to slope-intercept form (y = mx + b).
 * @param input Pointer to GeneralLineInput containing A, B, C.
 * @param out_result Pointer to a Line_EquationResult struct to store results.
 *                   The equation field will contain "Vertical line: x = ..." if applicable.
 * @return LINE_SUCCESS on success, LINE_ERR_INVALID_ARG if input/output NULL, LINE_ERR_MATH if degenerate (A=B=0, C!=0).
 */
int Line_transform_general_to_slope_intercept(const Line_GeneralLineInput *input, Line_EquationResult *out_result);

/**
 * @brief Transforms general form (Ax + By + C = 0) to intercept form (x/a + y/b = 1).
 * @param input Pointer to GeneralLineInput containing A, B, C.
 * @param buffer Char buffer to store the resulting equation string.
 * @param buffer_size The size of the provided buffer.
 * @return LINE_SUCCESS on success, LINE_ERR_INVALID_ARG if input/buffer NULL or transformation impossible (passes through origin, parallel to axis), LINE_ERR_BUFFER_TOO_SMALL.
 */
int Line_transform_general_to_intercept_form(const Line_GeneralLineInput *input, char *buffer, size_t buffer_size);


#endif // LINES_SLOPE_H