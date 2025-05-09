#include "linear_equations_utils.h"
#include <math.h>   // For fabs, sqrt, round, copysign, NAN, INFINITY
#include <stdio.h>  // For snprintf, vsnprintf
#include <string.h> // For strcpy, strncpy, memset, strcmp
#include <float.h>  // For DBL_EPSILON
#include <stdarg.h> // For va_list, va_start, va_end (used in add_step)


// Define custom epsilon for floating point comparisons in algorithms
const double LE_EPSILON = 1e-9;

// Define string constants for consistency types
const char* const LE_CONSISTENT_UNIQUE = "CONSISTENT_UNIQUE";
const char* const LE_CONSISTENT_INFINITE = "CONSISTENT_INFINITE";
const char* const LE_INCONSISTENT_PARALLEL = "INCONSISTENT_PARALLEL";
const char* const LE_ERROR_TYPE = "ERROR_STATE";


// Helper to format double to string for output, trying to be neat
static void format_double_str(double val, char* buffer, size_t buffer_len) {
    if (!buffer || buffer_len == 0) return;
    // Heuristic for "close to integer" to avoid unnecessary decimals like "5.00"
    if (fabs(val - round(val)) < LE_EPSILON * 100 * fmax(1.0, fabs(val)) ) {
        snprintf(buffer, buffer_len, "%.0f", round(val)); // Use round to get actual integer
    } else {
        snprintf(buffer, buffer_len, "%.2f", val); // Default to 2 decimal places
    }
    buffer[buffer_len - 1] = '\0'; // Ensure null termination
}

// Helper for more precise formatting, often used in intermediate steps
static void format_double_str_precise(double val, char* buffer, size_t buffer_len) {
    if (!buffer || buffer_len == 0) return;
    // Handle NaN and Inf explicitly as %g might not be ideal for them across all platforms/compilers
    if (isnan(val)) {
        strncpy(buffer, "NaN", buffer_len -1);
    } else if (isinf(val)) {
        if (val > 0) strncpy(buffer, "Inf", buffer_len -1);
        else strncpy(buffer, "-Inf", buffer_len -1);
    } else {
        snprintf(buffer, buffer_len, "%.4g", val); // More precision, general format
    }
    buffer[buffer_len - 1] = '\0'; // Ensure null termination
}


void init_equation_coefficients_c(EquationCoefficients_C* coeffs,
                                  double a1, double b1, double c1,
                                  double a2, double b2, double c2) {
    if (!coeffs) return;
    coeffs->a1 = a1; coeffs->b1 = b1; coeffs->c1 = c1;
    coeffs->a2 = a2; coeffs->b2 = b2; coeffs->c2 = c2;

    char temp_a1[32], temp_b1[32], temp_c1[32]; // Increased buffer size for safety
    char temp_a2[32], temp_b2[32], temp_c2[32];
    format_double_str(a1, temp_a1, sizeof(temp_a1));
    format_double_str(b1, temp_b1, sizeof(temp_b1));
    format_double_str(c1, temp_c1, sizeof(temp_c1));
    format_double_str(a2, temp_a2, sizeof(temp_a2));
    format_double_str(b2, temp_b2, sizeof(temp_b2));
    format_double_str(c2, temp_c2, sizeof(temp_c2));

    snprintf(coeffs->eq1_str, MAX_STRING_LEN, "%sx + %sy = %s", temp_a1, temp_b1, temp_c1);
    coeffs->eq1_str[MAX_STRING_LEN-1] = '\0';
    snprintf(coeffs->eq2_str, MAX_STRING_LEN, "%sx + %sy = %s", temp_a2, temp_b2, temp_c2);
    coeffs->eq2_str[MAX_STRING_LEN-1] = '\0';
}


// ---- Print functions for structs (implementation) ----
void print_equation_coefficients_c(const EquationCoefficients_C* coeffs) {
    if (!coeffs) return;
    printf("Eq1: %s; Eq2: %s\n", coeffs->eq1_str, coeffs->eq2_str);
}

void print_consistency_check_result_c(const ConsistencyCheckResult_C* res) {
    if (!res) return;
    printf("ConsistencyCheckResult_C:\n");
    printf("  Equations: "); print_equation_coefficients_c(&res->equations);
    printf("  Type: %s\n", res->consistency_type);
    printf("  Graphical: %s\n", res->graphical_interpretation);
    printf("  Description: %s\n", res->description);
}

void print_solution_result_c(const SolutionResult_C* res) {
    if (!res) return;
    printf("SolutionResult_C (Method: %s):\n", res->method_used);
    printf("  Equations: "); print_equation_coefficients_c(&res->equations);
    printf("  Consistency: %s\n", res->consistency_type);
    printf("  Solution: x = %s, y = %s\n", res->solution_x_str, res->solution_y_str);
    // printf("  Description: %s\n", res->description); // Can be verbose
    if (res->num_steps > 0) {
        printf("  Steps (%d):\n", res->num_steps);
        for (int i = 0; i < res->num_steps; ++i) {
            printf("    %d. %s\n", i + 1, res->steps[i]);
        }
    }
}
void print_reducible_solution_result_c(const ReducibleSolutionResult_C* res) {
    if(!res) return;
    printf("ReducibleSolutionResult_C:\n");
    printf("  Substituted System (u=%s, v=%s):\n", res->u_represents_str, res->v_represents_str);
    printf("    Eq1: %s\n", res->substituted_eq1_str);
    printf("    Eq2: %s\n", res->substituted_eq2_str);
    printf("  Solution for u,v: "); print_solution_result_c(&res->substituted_system_solution); // This might be too verbose
    printf("  Original Solution: x = %s, y = %s\n", res->original_solution_x_str, res->original_solution_y_str);
}

// ---- Add step safely ----
static void add_step(SolutionResult_C* result, const char* step_format, ...) {
    if (!result || result->num_steps >= MAX_SOLUTION_STEPS) return;
    
    va_list args;
    va_start(args, step_format);
    vsnprintf(result->steps[result->num_steps], MAX_STEP_STRING_LEN, step_format, args);
    va_end(args);
    result->steps[result->num_steps][MAX_STEP_STRING_LEN - 1] = '\0'; // Ensure null termination
    result->num_steps++;
}


// ---- Function Implementations ----
int le_check_consistency(double a1, double b1, double c1,
                         double a2, double b2, double c2,
                         ConsistencyCheckResult_C* result) {
    if (!result) return LE_ERROR_INVALID_ARG;
    memset(result, 0, sizeof(ConsistencyCheckResult_C));
    init_equation_coefficients_c(&result->equations, a1, b1, c1, a2, b2, c2);

    char r_a1a2_str[32], r_b1b2_str[32], r_c1c2_str[32], det_str[32];

    // Calculate ratios textually for the description
    if (fabs(a2) > LE_EPSILON) format_double_str_precise(a1/a2, r_a1a2_str, sizeof(r_a1a2_str));
    else if (fabs(a1) < LE_EPSILON) strncpy(r_a1a2_str, "0/0", sizeof(r_a1a2_str)-1);
    else {
        char temp_a1[32];
        format_double_str_precise(a1, temp_a1, sizeof(temp_a1));
        snprintf(r_a1a2_str, sizeof(r_a1a2_str), "%s/0", temp_a1); // Temp buffer used here
    }

    if (fabs(b2) > LE_EPSILON) format_double_str_precise(b1/b2, r_b1b2_str, sizeof(r_b1b2_str));
    else if (fabs(b1) < LE_EPSILON) strncpy(r_b1b2_str, "0/0", sizeof(r_b1b2_str)-1);
    else {
        char temp_b1[32];
        format_double_str_precise(b1, temp_b1, sizeof(temp_b1));
        snprintf(r_b1b2_str, sizeof(r_b1b2_str), "%s/0", temp_b1); // Temp buffer used here
    }

    if (fabs(c2) > LE_EPSILON) format_double_str_precise(c1/c2, r_c1c2_str, sizeof(r_c1c2_str));
    else if (fabs(c1) < LE_EPSILON) strncpy(r_c1c2_str, "0/0", sizeof(r_c1c2_str)-1);
    else {
        char temp_c1[32];
        format_double_str_precise(c1, temp_c1, sizeof(temp_c1));
        snprintf(r_c1c2_str, sizeof(r_c1c2_str), "%s/0", temp_c1); // Temp buffer used here
    }


    double determinant = a1 * b2 - a2 * b1;
    format_double_str_precise(determinant, det_str, sizeof(det_str));


    if (fabs(determinant) > LE_EPSILON) {
        strncpy(result->consistency_type, LE_CONSISTENT_UNIQUE, MAX_STRING_LEN-1);
        snprintf(result->graphical_interpretation, MAX_STRING_LEN, "Lines intersect at a single point.");
        snprintf(result->description, sizeof(result->description),
                 "System has a unique solution. Determinant (a1*b2 - a2*b1) = %s != 0. Ratios: a1/a2=%s, b1/b2=%s.",
                 det_str, r_a1a2_str, r_b1b2_str);
    } else {
        double dx_prime = c1 * b2 - c2 * b1;
        double dy_prime = a1 * c2 - a2 * c1;

        if (fabs(dx_prime) > LE_EPSILON || fabs(dy_prime) > LE_EPSILON) {
            strncpy(result->consistency_type, LE_INCONSISTENT_PARALLEL, MAX_STRING_LEN-1);
            snprintf(result->graphical_interpretation, MAX_STRING_LEN, "Lines are parallel and distinct.");
            if ((fabs(a1) < LE_EPSILON && fabs(b1) < LE_EPSILON && fabs(c1) > LE_EPSILON) ||
                (fabs(a2) < LE_EPSILON && fabs(b2) < LE_EPSILON && fabs(c2) > LE_EPSILON)) {
                 snprintf(result->description, sizeof(result->description),
                     "System is inconsistent. One equation is 0x + 0y = C (C!=0). Ratios: a1/a2=%s, b1/b2=%s, c1/c2=%s.",
                     r_a1a2_str, r_b1b2_str, r_c1c2_str);
            } else {
                snprintf(result->description, sizeof(result->description),
                     "System is inconsistent. Determinant is ~0, but lines are not coincident. Ratios: a1/a2=%s, b1/b2=%s, c1/c2=%s.",
                     r_a1a2_str, r_b1b2_str, r_c1c2_str);
            }
        } else {
            strncpy(result->consistency_type, LE_CONSISTENT_INFINITE, MAX_STRING_LEN-1);
            snprintf(result->graphical_interpretation, MAX_STRING_LEN, "Lines are coincident (overlap completely).");
            snprintf(result->description, sizeof(result->description),
                     "System has infinitely many solutions. All determinants (D, Dx', Dy') are ~0. Ratios: a1/a2=%s, b1/b2=%s, c1/c2=%s.",
                     r_a1a2_str, r_b1b2_str, r_c1c2_str);
        }
    }
    result->description[sizeof(result->description)-1] = '\0';
    return LE_SUCCESS;
}


int le_solve_general_cramer(double a1, double b1, double c1,
                            double a2, double b2, double c2,
                            SolutionResult_C* result) {
    if (!result) return LE_ERROR_INVALID_ARG;
    memset(result, 0, sizeof(SolutionResult_C));
    init_equation_coefficients_c(&result->equations, a1, b1, c1, a2, b2, c2);
    strncpy(result->method_used, "General (Cramer's Rule)", MAX_STRING_LEN-1);
    result->method_used[MAX_STRING_LEN-1]='\0';
    result->num_steps = 0;

    ConsistencyCheckResult_C consistency_res;
    le_check_consistency(a1, b1, c1, a2, b2, c2, &consistency_res);
    strncpy(result->consistency_type, consistency_res.consistency_type, MAX_STRING_LEN-1);
    result->consistency_type[MAX_STRING_LEN-1]='\0';
    strncpy(result->description, consistency_res.description, sizeof(result->description)-1);
    result->description[sizeof(result->description)-1]='\0';

    char det_D_str[32], det_Dx_str[32], det_Dy_str[32];

    if (strcmp(result->consistency_type, LE_CONSISTENT_UNIQUE) == 0) {
        double det_D = a1 * b2 - a2 * b1;
        double det_Dx = c1 * b2 - c2 * b1;
        double det_Dy = a1 * c2 - a2 * c1;
        
        format_double_str_precise(det_D, det_D_str, sizeof(det_D_str));
        format_double_str_precise(det_Dx, det_Dx_str, sizeof(det_Dx_str));
        format_double_str_precise(det_Dy, det_Dy_str, sizeof(det_Dy_str));

        add_step(result, "D = a1*b2 - a2*b1 = %s", det_D_str);
        add_step(result, "Dx = c1*b2 - c2*b1 = %s", det_Dx_str);
        add_step(result, "Dy = a1*c2 - a2*c1 = %s", det_Dy_str);

        result->solution_x = det_Dx / det_D;
        result->solution_y = det_Dy / det_D;
        format_double_str_precise(result->solution_x, result->solution_x_str, MAX_STRING_LEN);
        format_double_str_precise(result->solution_y, result->solution_y_str, MAX_STRING_LEN);
        add_step(result, "x = Dx / D = %s", result->solution_x_str);
        add_step(result, "y = Dy / D = %s", result->solution_y_str);
    } else if (strcmp(result->consistency_type, LE_CONSISTENT_INFINITE) == 0) {
        strncpy(result->solution_x_str, "Infinite", MAX_STRING_LEN-1);
        result->solution_x_str[MAX_STRING_LEN-1]='\0';
        strncpy(result->solution_y_str, "Infinite", MAX_STRING_LEN-1);
        result->solution_y_str[MAX_STRING_LEN-1]='\0';
        add_step(result, "System has infinitely many solutions.");
    } else { // INCONSISTENT_PARALLEL or ERROR
        strncpy(result->solution_x_str, "None", MAX_STRING_LEN-1);
        result->solution_x_str[MAX_STRING_LEN-1]='\0';
        strncpy(result->solution_y_str, "None", MAX_STRING_LEN-1);
        result->solution_y_str[MAX_STRING_LEN-1]='\0';
        add_step(result, "System has no solution.");
    }
    return LE_SUCCESS;
}

// Placeholder for Substitution - complex to generate human-readable steps for all cases
int le_solve_by_substitution(double a1, double b1, double c1,
                             double a2, double b2, double c2,
                             SolutionResult_C* result) {
    if (!result) return LE_ERROR_INVALID_ARG;
    int ret = le_solve_general_cramer(a1, b1, c1, a2, b2, c2, result);
    if (ret == LE_SUCCESS) {
        strncpy(result->method_used, "Substitution (via Cramer)", MAX_STRING_LEN-1);
        result->method_used[MAX_STRING_LEN-1]='\0';
        // Add a placeholder step, or clear existing steps from Cramer and add new ones if implementing fully
        if(result->num_steps < MAX_SOLUTION_STEPS) { // Check if there's space for one more step
            add_step(result, "Substitution steps complex; showing general solution.");
        }
    }
    return ret;
}

// Placeholder for Elimination
int le_solve_by_elimination(double a1, double b1, double c1,
                            double a2, double b2, double c2,
                            SolutionResult_C* result) {
    if (!result) return LE_ERROR_INVALID_ARG;
    int ret = le_solve_general_cramer(a1, b1, c1, a2, b2, c2, result);
     if (ret == LE_SUCCESS) {
        strncpy(result->method_used, "Elimination (via Cramer)", MAX_STRING_LEN-1);
        result->method_used[MAX_STRING_LEN-1]='\0';
        if(result->num_steps < MAX_SOLUTION_STEPS) {
            add_step(result, "Elimination steps complex; showing general solution.");
        }
    }
    return ret;
}


int le_solve_by_cross_multiplication(double a1, double b1, double c1_form_axbyc0,
                                     double a2, double b2, double c2_form_axbyc0,
                                     SolutionResult_C* result) {
    if (!result) return LE_ERROR_INVALID_ARG;
    memset(result, 0, sizeof(SolutionResult_C));
    init_equation_coefficients_c(&result->equations, a1, b1, -c1_form_axbyc0, a2, b2, -c2_form_axbyc0);
    strncpy(result->method_used, "Cross-Multiplication", MAX_STRING_LEN-1);
    result->method_used[MAX_STRING_LEN-1]='\0';
    result->num_steps = 0;
    
    char eq1_axbyc0_str[MAX_STRING_LEN], eq2_axbyc0_str[MAX_STRING_LEN];
    char a1_s[32], b1_s[32], c1_s[32], a2_s[32], b2_s[32], c2_s[32]; // Buffers for formatted numbers

    format_double_str_precise(a1, a1_s, sizeof(a1_s));
    format_double_str_precise(b1, b1_s, sizeof(b1_s));
    format_double_str_precise(c1_form_axbyc0, c1_s, sizeof(c1_s));
    format_double_str_precise(a2, a2_s, sizeof(a2_s));
    format_double_str_precise(b2, b2_s, sizeof(b2_s));
    format_double_str_precise(c2_form_axbyc0, c2_s, sizeof(c2_s));

    snprintf(eq1_axbyc0_str, MAX_STRING_LEN, "%sx + %sy + %s = 0", a1_s, b1_s, c1_s);
    snprintf(eq2_axbyc0_str, MAX_STRING_LEN, "%sx + %sy + %s = 0", a2_s, b2_s, c2_s);
    add_step(result, "Equations (form ax+by+c=0): %s; %s", eq1_axbyc0_str, eq2_axbyc0_str);


    ConsistencyCheckResult_C consistency_res;
    le_check_consistency(a1, b1, -c1_form_axbyc0, a2, b2, -c2_form_axbyc0, &consistency_res);
    strncpy(result->consistency_type, consistency_res.consistency_type, MAX_STRING_LEN-1);
    result->consistency_type[MAX_STRING_LEN-1]='\0';
    strncpy(result->description, consistency_res.description, sizeof(result->description)-1);
    result->description[sizeof(result->description)-1]='\0';

    if (strcmp(result->consistency_type, LE_CONSISTENT_UNIQUE) == 0) {
        double den_x_num = b1 * c2_form_axbyc0 - b2 * c1_form_axbyc0;
        double den_y_num = c1_form_axbyc0 * a2 - c2_form_axbyc0 * a1;
        double den_1_val = a1 * b2 - a2 * b1; 

        char den_x_s[32], den_y_s[32], den_1_s[32];
        format_double_str_precise(den_x_num, den_x_s, sizeof(den_x_s));
        format_double_str_precise(den_y_num, den_y_s, sizeof(den_y_s));
        format_double_str_precise(den_1_val, den_1_s, sizeof(den_1_s));

        add_step(result, "x / (b1*C2 - b2*C1) = x / (%s*%s - %s*%s) = x / %s", b1_s, c2_s, b2_s, c1_s, den_x_s);
        add_step(result, "y / (C1*a2 - C2*a1) = y / (%s*%s - %s*%s) = y / %s", c1_s, a2_s, c2_s, a1_s, den_y_s);
        add_step(result, "1 / (a1*b2 - a2*b1) = 1 / (%s*%s - %s*%s) = 1 / %s", a1_s, b2_s, a2_s, b1_s, den_1_s);
        
        if (fabs(den_1_val) > LE_EPSILON) {
            result->solution_x = den_x_num / den_1_val;
            result->solution_y = den_y_num / den_1_val;
            format_double_str_precise(result->solution_x, result->solution_x_str, MAX_STRING_LEN);
            format_double_str_precise(result->solution_y, result->solution_y_str, MAX_STRING_LEN);
            add_step(result, "x = (%s) / (%s) = %s", den_x_s, den_1_s, result->solution_x_str);
            add_step(result, "y = (%s) / (%s) = %s", den_y_s, den_1_s, result->solution_y_str);
        } else { 
            strncpy(result->consistency_type, LE_ERROR_TYPE, MAX_STRING_LEN-1);
            result->consistency_type[MAX_STRING_LEN-1]='\0';
            strncpy(result->solution_x_str, "Error", MAX_STRING_LEN-1);
            result->solution_x_str[MAX_STRING_LEN-1]='\0';
            strncpy(result->solution_y_str, "Error", MAX_STRING_LEN-1);
            result->solution_y_str[MAX_STRING_LEN-1]='\0';
            add_step(result, "Error: Denom for 1 is zero, contradicts unique analysis.");
            return LE_ERROR_INTERNAL;
        }
    } else if (strcmp(result->consistency_type, LE_CONSISTENT_INFINITE) == 0) {
        strncpy(result->solution_x_str, "Infinite", MAX_STRING_LEN-1);
        result->solution_x_str[MAX_STRING_LEN-1]='\0';
        strncpy(result->solution_y_str, "Infinite", MAX_STRING_LEN-1);
        result->solution_y_str[MAX_STRING_LEN-1]='\0';
        add_step(result, "System has infinitely many solutions.");
    } else { 
        strncpy(result->solution_x_str, "None", MAX_STRING_LEN-1);
        result->solution_x_str[MAX_STRING_LEN-1]='\0';
        strncpy(result->solution_y_str, "None", MAX_STRING_LEN-1);
        result->solution_y_str[MAX_STRING_LEN-1]='\0';
        add_step(result, "System has no solution.");
    }
    return LE_SUCCESS;
}


int le_solve_reducible(double u_coeff1, double v_coeff1, double const1,
                       double u_coeff2, double v_coeff2, double const2,
                       const char* u_represents, const char* v_represents,
                       ReducibleSolutionResult_C* result) {
    if (!result || !u_represents || !v_represents) return LE_ERROR_INVALID_ARG;
    memset(result, 0, sizeof(ReducibleSolutionResult_C));

    strncpy(result->u_represents_str, u_represents, MAX_STRING_LEN-1);
    result->u_represents_str[MAX_STRING_LEN-1]='\0';
    strncpy(result->v_represents_str, v_represents, MAX_STRING_LEN-1);
    result->v_represents_str[MAX_STRING_LEN-1]='\0';
    
    char temp_u1[32], temp_v1[32], temp_c1[32], temp_u2[32], temp_v2[32], temp_c2[32];
    format_double_str(u_coeff1, temp_u1, sizeof(temp_u1)); 
    format_double_str(v_coeff1, temp_v1, sizeof(temp_v1)); 
    format_double_str(const1, temp_c1, sizeof(temp_c1));
    format_double_str(u_coeff2, temp_u2, sizeof(temp_u2)); 
    format_double_str(v_coeff2, temp_v2, sizeof(temp_v2)); 
    format_double_str(const2, temp_c2, sizeof(temp_c2));

    snprintf(result->substituted_eq1_str, MAX_STRING_LEN, "%su + %sv = %s", temp_u1, temp_v1, temp_c1);
    result->substituted_eq1_str[MAX_STRING_LEN-1]='\0';
    snprintf(result->substituted_eq2_str, MAX_STRING_LEN, "%su + %sv = %s", temp_u2, temp_v2, temp_c2);
    result->substituted_eq2_str[MAX_STRING_LEN-1]='\0';

    int ret = le_solve_general_cramer(u_coeff1, v_coeff1, const1, u_coeff2, v_coeff2, const2, &result->substituted_system_solution);
    if (ret != LE_SUCCESS) {
        strncpy(result->original_solution_x_str, "Err in sub-solve", MAX_STRING_LEN-1);
        result->original_solution_x_str[MAX_STRING_LEN-1]='\0';
        strncpy(result->original_solution_y_str, "Err in sub-solve", MAX_STRING_LEN-1);
        result->original_solution_y_str[MAX_STRING_LEN-1]='\0';
        return ret; 
    }
    
    if (strcmp(result->substituted_system_solution.consistency_type, LE_CONSISTENT_UNIQUE) == 0) {
        double u_val = result->substituted_system_solution.solution_x;
        double v_val = result->substituted_system_solution.solution_y;

        if (strcmp(u_represents, "1/x") == 0) {
            if (fabs(u_val) > LE_EPSILON) {
                result->original_solution_x = 1.0 / u_val;
                format_double_str_precise(result->original_solution_x, result->original_solution_x_str, MAX_STRING_LEN);
            } else { strncpy(result->original_solution_x_str, "Error (u=0 for 1/x)", MAX_STRING_LEN-1); result->original_solution_x_str[MAX_STRING_LEN-1]='\0'; }
        } else if (strcmp(u_represents, "x") == 0) {
            result->original_solution_x = u_val;
            format_double_str_precise(result->original_solution_x, result->original_solution_x_str, MAX_STRING_LEN);
        } else { snprintf(result->original_solution_x_str, MAX_STRING_LEN, "Unknown u=%s form", u_represents); result->original_solution_x_str[MAX_STRING_LEN-1]='\0'; }

        if (strcmp(v_represents, "1/y") == 0) {
            if (fabs(v_val) > LE_EPSILON) {
                result->original_solution_y = 1.0 / v_val;
                format_double_str_precise(result->original_solution_y, result->original_solution_y_str, MAX_STRING_LEN);
            } else { strncpy(result->original_solution_y_str, "Error (v=0 for 1/y)", MAX_STRING_LEN-1); result->original_solution_y_str[MAX_STRING_LEN-1]='\0';}
        } else if (strcmp(v_represents, "y") == 0) {
            result->original_solution_y = v_val;
            format_double_str_precise(result->original_solution_y, result->original_solution_y_str, MAX_STRING_LEN);
        } else { snprintf(result->original_solution_y_str, MAX_STRING_LEN, "Unknown v=%s form", v_represents); result->original_solution_y_str[MAX_STRING_LEN-1]='\0';}
    } else {
        snprintf(result->original_solution_x_str, MAX_STRING_LEN, "From u: %s", result->substituted_system_solution.solution_x_str);
        result->original_solution_x_str[MAX_STRING_LEN-1]='\0';
        snprintf(result->original_solution_y_str, MAX_STRING_LEN, "From v: %s", result->substituted_system_solution.solution_y_str);
        result->original_solution_y_str[MAX_STRING_LEN-1]='\0';
    }
    return LE_SUCCESS;
}