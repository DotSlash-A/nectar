
#include "slope.h"
#include "geometry_types.h"

#include <stdio.h>  // For snprintf
#include <math.h>   // For fabs, sqrt, pow, cos, sin, tan, atan, M_PI, NAN, isinf
#include <string.h> // For strcmp
#include <stdbool.h>// For bool

// Define PI if not available from math.h (less common in C99+)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// --- Helper Function Example ---
/**
 * @brief Safely formats a slope-intercept equation string (y = mx + b).
 * Internal helper, not exposed in slope.h
 */
static int format_slope_intercept_string(double m, double b, char *buffer, size_t buffer_size) {
    int chars_written;
    bool m_is_zero = fabs(m) < LINE_EPSILON;
    bool b_is_zero = fabs(b) < LINE_EPSILON;
    bool m_is_one = fabs(m - 1.0) < LINE_EPSILON;
    bool m_is_neg_one = fabs(m + 1.0) < LINE_EPSILON;

    if (m_is_zero) {
        chars_written = snprintf(buffer, buffer_size, "y = %.2f", b);
    } else {
        if (b_is_zero) {
             if (m_is_one) chars_written = snprintf(buffer, buffer_size, "y = x");
             else if (m_is_neg_one) chars_written = snprintf(buffer, buffer_size, "y = -x");
             else chars_written = snprintf(buffer, buffer_size, "y = %.2fx", m);
        } else {
             // Non-zero m and non-zero b
             const char *op = (b > 0) ? "+" : "-";
             double abs_b = fabs(b);
             if (m_is_one) chars_written = snprintf(buffer, buffer_size, "y = x %s %.2f", op, abs_b);
             else if (m_is_neg_one) chars_written = snprintf(buffer, buffer_size, "y = -x %s %.2f", op, abs_b);
             else chars_written = snprintf(buffer, buffer_size, "y = %.2fx %s %.2f", m, op, abs_b);
        }
    }

    // Check for errors / buffer truncation
    if (chars_written < 0) {
        return LINE_ERR_INVALID_ARG; // Some snprintf error
    }
    if ((size_t)chars_written >= buffer_size) {
        return LINE_ERR_BUFFER_TOO_SMALL;
    }
    return LINE_SUCCESS;
}
// --- End Helper ---


int Line_calculate_slope(const Line_Coordinates *p1, const Line_Coordinates *p2, double *out_slope) {
    if (!p1 || !p2 || !out_slope) {
        return LINE_ERR_INVALID_ARG; // Null pointer check
    }

    double dx = p2->x - p1->x;
    if (fabs(dx) < LINE_EPSILON) {
        return LINE_ERR_MATH; // Vertical line
    }

    *out_slope = (p2->y - p1->y) / dx;
    return LINE_SUCCESS;
}

int Line_calculate_slope_intercept_form(
    const Line_Coordinates *p1,
    const Line_Coordinates *p2,
    const double *slope,
    Line_EquationResult *out_result)
{
    if (!out_result) return LINE_ERR_INVALID_ARG;

    // Initialize result struct
    out_result->has_slope = false;
    out_result->has_y_intercept = false;
    out_result->has_x_intercept = false; // Assuming not calculated here
    out_result->equation[0] = '\0'; // Empty string

    double m, b;
    const Line_Coordinates *point_for_intercept = NULL; // Need one point

    if (slope != NULL) {
        // Slope is given, need at least one point
        if (!p1 && !p2) return LINE_ERR_INVALID_ARG; // Need a point
        m = *slope;
        point_for_intercept = (p1 != NULL) ? p1 : p2; // Use whichever point is available
    } else {
        // Calculate slope from two points
        if (!p1 || !p2) return LINE_ERR_INVALID_ARG; // Need both points
        int slope_status = Line_calculate_slope(p1, p2, &m);
        if (slope_status != LINE_SUCCESS) {
            // Handle vertical line case (maybe set a specific error or flag in result?)
            snprintf(out_result->equation, LINE_EQUATION_MAX_LEN, "Vertical line: x = %.2f", p1->x);
            return LINE_ERR_MATH; // Or a specific code for vertical
        }
        point_for_intercept = p1; // Use p1 for intercept calc
    }

    // Calculate y-intercept: b = y1 - m*x1
    b = point_for_intercept->y - m * point_for_intercept->x;

    // Store results
    out_result->slope = m;
    out_result->has_slope = true;
    out_result->y_intercept = b;
    out_result->has_y_intercept = true;

    // Format equation string
    int format_status = format_slope_intercept_string(m, b, out_result->equation, LINE_EQUATION_MAX_LEN);
    if (format_status != LINE_SUCCESS) {
        // Optionally clear results if formatting fails? Or return formatting error code?
        out_result->equation[0] = '\0'; // Clear equation on format error
        return format_status; // Propagate format error
    }

    return LINE_SUCCESS;
}

int Line_get_point_slope_form(const Line_Coordinates *point, double slope, char *buffer, size_t buffer_size) {
     if (!point || !buffer || buffer_size == 0) {
        return LINE_ERR_INVALID_ARG;
     }

    int chars_written = snprintf(buffer, buffer_size, "y - %.2f = %.2f(x - %.2f)",
                                point->y, slope, point->x);

    if (chars_written < 0) return LINE_ERR_INVALID_ARG; // snprintf error
    if ((size_t)chars_written >= buffer_size) return LINE_ERR_BUFFER_TOO_SMALL;

    return LINE_SUCCESS;
}

int Line_get_two_point_form(const Line_Coordinates *p1, const Line_Coordinates *p2, char *buffer, size_t buffer_size) {
    if (!p1 || !p2 || !buffer || buffer_size == 0) {
        return LINE_ERR_INVALID_ARG;
    }
    double slope;
    int slope_status = Line_calculate_slope(p1, p2, &slope);
    if (slope_status != LINE_SUCCESS) {
        return slope_status; // Propagate vertical line error
    }
    return Line_get_point_slope_form(p1, slope, buffer, buffer_size); // Use p1 for the form
}


// --- Implement other functions following similar patterns ---
// - Check input pointers for NULL.
// - Check optional inputs (pointers) for NULL before dereferencing.
// - Perform calculations using fabs() for comparisons.
// - Return error codes on failure.
// - Use snprintf for string formatting, checking return value and buffer size.
// - Set output parameters (*out_result = value) on success.
// - Set boolean flags in result structs for optional outputs.
// -------------------------------------------------------------

int Line_find_missing_slope_variable(const char *variable_to_find, const Line_SlopeInput *input, double *out_result) {
    if (!variable_to_find || !input || !out_result) return LINE_ERR_INVALID_ARG;

    // Check if slope 'm' (tangent value) is required but missing
    if (strcmp(variable_to_find, "m") != 0 && input->m == NULL) {
        // fprintf(stderr, "Error: Slope 'm' (tangent) is required unless finding 'm'.\n");
        return LINE_ERR_INVALID_ARG;
    }

    // Local copies for easier access (handle potential NULLs)
    double x1_val, y1_val, x2_val, y2_val, m_val;

    // Assign values, checking for NULLs as needed by the specific case
    // This part needs careful handling based on 'variable_to_find'

    if (strcmp(variable_to_find, "x2") == 0) {
        if (!input->y2 || !input->y1 || !input->x1 || !input->m) return LINE_ERR_INVALID_ARG;
        y2_val = *(input->y2); y1_val = *(input->y1); x1_val = *(input->x1); m_val = *(input->m);
        if (fabs(m_val) < LINE_EPSILON) return LINE_ERR_MATH; // Horizontal line
        *out_result = x1_val + (y2_val - y1_val) / m_val;
    } else if (strcmp(variable_to_find, "x1") == 0) {
        if (!input->y2 || !input->y1 || !input->x2 || !input->m) return LINE_ERR_INVALID_ARG;
        y2_val = *(input->y2); y1_val = *(input->y1); x2_val = *(input->x2); m_val = *(input->m);
        if (fabs(m_val) < LINE_EPSILON) return LINE_ERR_MATH; // Horizontal line
        *out_result = x2_val - (y2_val - y1_val) / m_val;
    } else if (strcmp(variable_to_find, "y2") == 0) {
        if (!input->x2 || !input->y1 || !input->x1 || !input->m) return LINE_ERR_INVALID_ARG;
        x2_val = *(input->x2); y1_val = *(input->y1); x1_val = *(input->x1); m_val = *(input->m);
        *out_result = y1_val + m_val * (x2_val - x1_val);
    } else if (strcmp(variable_to_find, "y1") == 0) {
        if (!input->x2 || !input->y2 || !input->x1 || !input->m) return LINE_ERR_INVALID_ARG;
        x2_val = *(input->x2); y2_val = *(input->y2); x1_val = *(input->x1); m_val = *(input->m);
        *out_result = y2_val - m_val * (x2_val - x1_val);
     } else if (strcmp(variable_to_find, "m") == 0) {
        if (!input->x1 || !input->y1 || !input->x2 || !input->y2) return LINE_ERR_INVALID_ARG;
        x1_val = *(input->x1); y1_val = *(input->y1); x2_val = *(input->x2); y2_val = *(input->y2);
        double dx = x2_val - x1_val;
        if (fabs(dx) < LINE_EPSILON) return LINE_ERR_MATH; // Vertical line
        *out_result = (y2_val - y1_val) / dx;
    } else {
        return LINE_ERR_INVALID_ARG; // Unknown variable name
    }

    return LINE_SUCCESS;
}


// ...(Implement the rest of the functions defined in slope.h)...

// main
// #include "lines/slope.h" // Use relative path
// #include "lines/geometry_types.h"
// #include <stdio.h> // For printf, fprintf

// int main() {
//     printf("--- C Line Calculations ---\n");

//     Line_Coordinates p1 = {1.0, 2.0};
//     Line_Coordinates p2 = {4.0, 8.0};
//     Line_Coordinates p_vert1 = {1.0, 5.0};

//     // Buffer for equation strings
//     char eq_buffer[LINE_EQUATION_MAX_LEN];
//     int status; // To store return codes

//     // Example 1: Calculate Slope
//     double slope_result;
//     status = Line_calculate_slope(&p1, &p2, &slope_result);
//     if (status == LINE_SUCCESS) {
//         printf("Slope between (%.1f, %.1f) and (%.1f, %.1f): %.2f\n",
//                p1.x, p1.y, p2.x, p2.y, slope_result);
//     } else {
//         fprintf(stderr, "Error calculating slope (code %d)\n", status);
//     }

//     status = Line_calculate_slope(&p1, &p_vert1, &slope_result);
//     if (status != LINE_SUCCESS) {
//          fprintf(stderr, "Error calculating slope for vertical line (expected, code %d)\n", status);
//     }


//     // Example 2: Slope-Intercept Form from 2 points
//     Line_EquationResult eq_res;
//     status = Line_calculate_slope_intercept_form(&p1, &p2, NULL, &eq_res); // Pass NULL for slope
//     if (status == LINE_SUCCESS) {
//          printf("Slope-Intercept from (%.1f, %.1f) and (%.1f, %.1f):\n", p1.x, p1.y, p2.x, p2.y);
//          printf("  Slope: ");
//          if(eq_res.has_slope) printf("%.2f\n", eq_res.slope); else printf("N/A\n");
//          printf("  Y-Int: ");
//          if(eq_res.has_y_intercept) printf("%.2f\n", eq_res.y_intercept); else printf("N/A\n");
//          printf("  Equation: %s\n", eq_res.equation);
//     } else {
//          fprintf(stderr, "Error getting slope-intercept (code %d)\n", status);
//          if (status == LINE_ERR_MATH && eq_res.equation[0] != '\0') {
//              // Check if the function populated the equation for special cases like vertical
//              fprintf(stderr, "  Equation (special case): %s\n", eq_res.equation);
//          }
//     }

//     // Example 3: Two-Point Form
//     status = Line_get_two_point_form(&p1, &p2, eq_buffer, sizeof(eq_buffer));
//     if (status == LINE_SUCCESS) {
//          printf("Two-Point form for (%.1f, %.1f) and (%.1f, %.1f): %s\n",
//                 p1.x, p1.y, p2.x, p2.y, eq_buffer);
//     } else {
//          fprintf(stderr, "Error getting two-point form (code %d)\n", status);
//     }

//     // Example 4: Find missing variable
//     double x1_find = 1.0, y1_find = 2.0, x2_find = 4.0, m_find = 2.0; // Knowns
//     double found_y2;
//     Line_SlopeInput find_input;
//     find_input.x1 = &x1_find; // Pass addresses of knowns
//     find_input.y1 = &y1_find;
//     find_input.x2 = &x2_find;
//     find_input.y2 = NULL;     // Unknown
//     find_input.m = &m_find;

//     status = Line_find_missing_slope_variable("y2", &find_input, &found_y2);
//      if (status == LINE_SUCCESS) {
//          printf("Find y2: Given x1=%.1f, y1=%.1f, x2=%.1f, m=%.1f -> y2 = %.2f\n",
//                 x1_find, y1_find, x2_find, m_find, found_y2);
//     } else {
//         fprintf(stderr, "Error finding variable 'y2' (code %d)\n", status);
//     }


//     // ... Add more examples calling other functions ...

//     return 0; // Return 0 from main on successful execution
// }