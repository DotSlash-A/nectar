#ifndef LINES_GEOMETRY_TYPES_H
#define LINES_GEOMETRY_TYPES_H

#include <stdbool.h> // For bool type (C99 standard onwards)
#include <stddef.h>  // For size_t

// --- Constants ---

// Define a max length for equation strings
#define LINE_EQUATION_MAX_LEN 256
// Define a small value for floating-point comparisons
#define LINE_EPSILON 1e-9

// --- Error Codes ---
#define LINE_SUCCESS 0
#define LINE_ERR_INVALID_ARG 1 // Bad input pointer, out-of-range value etc.
#define LINE_ERR_MATH 2        // Division by zero, impossible calculation
#define LINE_ERR_BUFFER_TOO_SMALL 3 // Output string buffer insufficient

// --- Structures ---

// Represents a point with X and Y coordinates.
typedef struct {
    double x;
    double y;
} Line_Coordinates;

// Represents the result of calculating line properties.
// Uses boolean flags to indicate if a value is valid/present.
typedef struct {
    double slope;
    bool has_slope;

    double y_intercept;
    bool has_y_intercept;

    double x_intercept; // Added for completeness
    bool has_x_intercept;

    // Fixed-size buffer for the equation string
    char equation[LINE_EQUATION_MAX_LEN];
} Line_EquationResult;

// Input for finding a missing variable in the slope formula.
// Uses pointers; NULL indicates a value is not provided (optional).
// Note: The meaning of 'm' (angle vs tangent) depends on the function called.
typedef struct {
    const double *x1; // Pointer to allow NULL
    const double *y1;
    const double *x2;
    const double *y2;
    const double *m; // Slope (can be angle or tangent)
} Line_SlopeInput;

// Input for a line in general form: Ax + By + C = 0.
typedef struct {
    double a;
    double b;
    double c;
} Line_GeneralLineInput;

// Add other necessary structs here following the same pattern

#endif // LINES_GEOMETRY_TYPES_H