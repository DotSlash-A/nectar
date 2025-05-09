#ifndef LINEAR_EQUATIONS_TYPES_H
#define LINEAR_EQUATIONS_TYPES_H

#include <stdbool.h> // For bool
#include <stdio.h>   // For snprintf
#include <string.h>  // For strncpy

#ifndef MAX_STRING_LEN // Define if not already defined (e.g., by real_numbers_types.h if included first)
#define MAX_STRING_LEN 256
#endif

// Error codes specific to linear equations module (can be combined with Real Numbers ones)
#define LE_SUCCESS 0
#define LE_ERROR_INVALID_ARG -101
#define LE_ERROR_NO_UNIQUE_SOLUTION -102 // For methods that expect unique solution
#define LE_ERROR_INTERNAL -103 // General internal error

// Represents a pair of equations: a1x + b1y = c1 and a2x + b2y = c2
typedef struct {
    double a1, b1, c1;
    double a2, b2, c2;
    char eq1_str[MAX_STRING_LEN];
    char eq2_str[MAX_STRING_LEN];
} EquationCoefficients_C;

typedef struct {
    EquationCoefficients_C equations;
    char consistency_type[MAX_STRING_LEN]; // "CONSISTENT_UNIQUE", etc.
    char description[MAX_STRING_LEN * 2];
    // Ratios can be complex to store in a fixed C struct; we'll put them in description.
    char graphical_interpretation[MAX_STRING_LEN];
} ConsistencyCheckResult_C;

#define MAX_SOLUTION_STEPS 20
#define MAX_STEP_STRING_LEN 128

typedef struct {
    EquationCoefficients_C equations;
    char consistency_type[MAX_STRING_LEN];
    char description[MAX_STRING_LEN * 2]; // Description of overall solution/consistency
    double solution_x; // Valid if unique solution
    double solution_y; // Valid if unique solution
    char solution_x_str[MAX_STRING_LEN]; // For "Infinite", "None", or numerical value
    char solution_y_str[MAX_STRING_LEN]; // For "Infinite", "None", or numerical value
    char method_used[MAX_STRING_LEN];
    char steps[MAX_SOLUTION_STEPS][MAX_STEP_STRING_LEN];
    int num_steps;
} SolutionResult_C;

typedef struct {
    SolutionResult_C substituted_system_solution; // Solution for u and v
    double original_solution_x;
    double original_solution_y;
    char original_solution_x_str[MAX_STRING_LEN];
    char original_solution_y_str[MAX_STRING_LEN];
    char u_represents_str[MAX_STRING_LEN];
    char v_represents_str[MAX_STRING_LEN];
    char substituted_eq1_str[MAX_STRING_LEN];
    char substituted_eq2_str[MAX_STRING_LEN];
} ReducibleSolutionResult_C;

// Helper to initialize EquationCoefficients_C and format its strings
void init_equation_coefficients_c(EquationCoefficients_C* coeffs,
                                  double a1, double b1, double c1,
                                  double a2, double b2, double c2);

// Helper printing functions (declarations)
void print_equation_coefficients_c(const EquationCoefficients_C* coeffs);
void print_consistency_check_result_c(const ConsistencyCheckResult_C* res);
void print_solution_result_c(const SolutionResult_C* res);
void print_reducible_solution_result_c(const ReducibleSolutionResult_C* res);


#endif // LINEAR_EQUATIONS_TYPES_H