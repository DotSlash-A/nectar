#include <stdio.h>
#include <math.h>
#include "slope.h"

#define EPSILON 1e-9


double slopecoordinates(SlopeCoordinates coords) {
    double denominator = coords.x2 - coords.x1;
    if (fabs(denominator) < EPSILON) {
        fprintf(stderr, "Error: Division by zero in slope calculation.\n");
        return 0.0; // or handle the error as needed
    }
    return (coords.y2 - coords.y1) / denominator;
}



// 2. Solve for a missing variable in the slope formula
int solve_for_missing_slope_param(SolveSlopeParams *params, int param_to_find) {
    // Reset error state
    params->error = false;
    params->error_message[0] = '\0'; // Clear error message

    // --- Input Validation ---
    // Check if pointers in the struct are valid based on 'param_to_find'
    // This is complex to write generically. We'll check inside each case.

    double x1_val, y1_val, x2_val, y2_val, m_val;

    // Helper macro to safely get value from pointer or set error
    #define GET_VAL(ptr, name, target) \
        if (ptr == NULL) { \
            params->error = true; \
            snprintf(params->error_message, sizeof(params->error_message), "Missing input: %s", name); \
            return -1; \
        } \
        target = *ptr;

    switch (param_to_find) {
        case 1: // Find x1
            GET_VAL(params->y2, "y2", y2_val);
            GET_VAL(params->y1, "y1", y1_val);
            GET_VAL(params->x2, "x2", x2_val);
            GET_VAL(params->m, "m", m_val);
            if (fabs(m_val) < EPSILON) {
                params->error = true;
                snprintf(params->error_message, sizeof(params->error_message), "Cannot solve for x1 with zero slope (horizontal line).");
                return -1;
            }
            params->result = x2_val - (y2_val - y1_val) / m_val;
            break;

        case 2: // Find y1
            GET_VAL(params->y2, "y2", y2_val);
            GET_VAL(params->x2, "x2", x2_val);
            GET_VAL(params->x1, "x1", x1_val);
            GET_VAL(params->m, "m", m_val);
            params->result = y2_val - m_val * (x2_val - x1_val);
            break;

        case 3: // Find x2
            GET_VAL(params->y2, "y2", y2_val);
            GET_VAL(params->y1, "y1", y1_val);
            GET_VAL(params->x1, "x1", x1_val);
            GET_VAL(params->m, "m", m_val);
             if (fabs(m_val) < EPSILON) {
                params->error = true;
                snprintf(params->error_message, sizeof(params->error_message), "Cannot solve for x2 with zero slope (horizontal line).");
                return -1;
            }
            params->result = x1_val + (y2_val - y1_val) / m_val;
            break;

        case 4: // Find y2
            GET_VAL(params->y1, "y1", y1_val);
            GET_VAL(params->x2, "x2", x2_val);
            GET_VAL(params->x1, "x1", x1_val);
            GET_VAL(params->m, "m", m_val);
            params->result = y1_val + m_val * (x2_val - x1_val);
            break;

        case 5: // Find m
            GET_VAL(params->x1, "x1", x1_val);
            GET_VAL(params->y1, "y1", y1_val);
            GET_VAL(params->x2, "x2", x2_val);
            GET_VAL(params->y2, "y2", y2_val);
            double dx = x2_val - x1_val;
            if (fabs(dx) < EPSILON) {
                 params->error = true;
                 snprintf(params->error_message, sizeof(params->error_message), "Cannot calculate slope m for vertical line (x1=x2).");
                 return -1;
            }
            params->result = (y2_val - y1_val) / dx;
            break;

        default:
            params->error = true;
            snprintf(params->error_message, sizeof(params->error_message), "Invalid value for param_to_find: %d", param_to_find);
            return -1;
    }

    // Check for potential calculation errors like NAN/INF result
    if (isnan(params->result) || isinf(params->result)) {
         params->error = true;
         snprintf(params->error_message, sizeof(params->error_message), "Calculation resulted in NAN or Infinity.");
         return -1;
    }

    return 0; // Success
}






int main() {
    SlopeCoordinates coords = {1.0, 2.0, 3.0, 6.0};
    double slope = slopecoordinates(coords);
    printf("Slope: %f\n", slope);
    return 0;
}