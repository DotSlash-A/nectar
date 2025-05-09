#include "quadratic_utils.h"
#include "polynomial_utils.h" // For poly_format_to_string
#include <string.h>
#include <math.h>   // For fabs, sqrt
#include <stdio.h>  // For snprintf

// Helper to format ComplexNumber_C to its str_representation
static void format_complex_number_str(ComplexNumber_C* cn) {
    if (!cn) return;
    if (fabs(cn->imaginary) < PQ_EPSILON) { // Real number
        snprintf(cn->str_representation, PQ_MAX_STRING_LEN, "%.4g", cn->real);
    } else if (fabs(cn->real) < PQ_EPSILON) { // Purely imaginary
        snprintf(cn->str_representation, PQ_MAX_STRING_LEN, "%.4gi", cn->imaginary);
    } else { // Complex
        snprintf(cn->str_representation, PQ_MAX_STRING_LEN, "%.4g %c %.4gi",
                 cn->real, (cn->imaginary < 0 ? '-' : '+'), fabs(cn->imaginary));
    }
}


int quad_solve_equation(double a, double b, double c, QuadraticSolution_C* result) {
    if (!result) return PQ_ERROR_INVALID_ARG;
    memset(result, 0, sizeof(QuadraticSolution_C));

    result->a = a; result->b = b; result->c = c;
    double coeffs[] = {a,b,c};
    poly_format_to_string(coeffs, 3, 'x', result->equation_string, sizeof(result->equation_string));
    strcat(result->equation_string, " = 0"); // Append " = 0"

    result->discriminant_applicable = false; // Default for non-quadratic

    if (fabs(a) < PQ_EPSILON) { // Linear or trivial
        if (fabs(b) < PQ_EPSILON) { // c = 0
            if (fabs(c) < PQ_EPSILON) {
                strncpy(result->nature_of_roots, "Identity (0x + 0 = 0)", sizeof(result->nature_of_roots)-1);
                strncpy(result->special_solution_note, "All real numbers", sizeof(result->special_solution_note)-1);
            } else {
                strncpy(result->nature_of_roots, "Contradiction (0 = non-zero)", sizeof(result->nature_of_roots)-1);
                strncpy(result->special_solution_note, "No solution", sizeof(result->special_solution_note)-1);
            }
        } else { // bx + c = 0
            strncpy(result->nature_of_roots, "Linear equation", sizeof(result->nature_of_roots)-1);
            result->roots[0].real = -c / b;
            result->roots[0].imaginary = 0.0;
            format_complex_number_str(&result->roots[0]);
            result->num_roots_found = 1;
        }
    } else { // Quadratic
        result->discriminant_applicable = true;
        result->discriminant = b * b - 4 * a * c;

        if (result->discriminant > PQ_EPSILON) {
            strncpy(result->nature_of_roots, "Two distinct real roots", sizeof(result->nature_of_roots)-1);
            double sqrt_D = sqrt(result->discriminant);
            result->roots[0].real = (-b + sqrt_D) / (2 * a);
            result->roots[0].imaginary = 0.0;
            format_complex_number_str(&result->roots[0]);

            result->roots[1].real = (-b - sqrt_D) / (2 * a);
            result->roots[1].imaginary = 0.0;
            format_complex_number_str(&result->roots[1]);
            result->num_roots_found = 2;
        } else if (fabs(result->discriminant) < PQ_EPSILON) {
            strncpy(result->nature_of_roots, "Two equal real roots (repeated)", sizeof(result->nature_of_roots)-1);
            result->roots[0].real = -b / (2 * a);
            result->roots[0].imaginary = 0.0;
            format_complex_number_str(&result->roots[0]);
            // Optionally add the second root as same for clarity, or just use num_roots_found=1
            // result->roots[1] = result->roots[0];
            result->num_roots_found = 1; // Or 2, with roots[1] being a copy
        } else { // D < 0
            strncpy(result->nature_of_roots, "Two complex conjugate roots", sizeof(result->nature_of_roots)-1);
            double sqrt_neg_D = sqrt(-result->discriminant);
            result->roots[0].real = -b / (2 * a);
            result->roots[0].imaginary = sqrt_neg_D / (2 * a);
            format_complex_number_str(&result->roots[0]);

            result->roots[1].real = -b / (2 * a);
            result->roots[1].imaginary = -sqrt_neg_D / (2 * a);
            format_complex_number_str(&result->roots[1]);
            result->num_roots_found = 2;
        }
    }
    // Ensure null termination for strings in result
    result->nature_of_roots[sizeof(result->nature_of_roots)-1] = '\0';
    result->special_solution_note[sizeof(result->special_solution_note)-1] = '\0';
    return PQ_SUCCESS;
}