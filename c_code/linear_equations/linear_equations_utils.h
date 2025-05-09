#ifndef LINEAR_EQUATIONS_UTILS_H
#define LINEAR_EQUATIONS_UTILS_H

#include "linear_equations_types.h" // Our types

// Constants for consistency types (can be defined here or used as strings directly)
extern const char* const LE_CONSISTENT_UNIQUE;
extern const char* const LE_CONSISTENT_INFINITE;
extern const char* const LE_INCONSISTENT_PARALLEL;

// Function declarations

/**
 * @brief Checks the consistency of a pair of linear equations.
 * @param a1, b1, c1 Coefficients for eq1: a1x + b1y = c1
 * @param a2, b2, c2 Coefficients for eq2: a2x + b2y = c2
 * @param result Pointer to ConsistencyCheckResult_C to store the result.
 * @return LE_SUCCESS on success, error code otherwise.
 */
int le_check_consistency(double a1, double b1, double c1,
                         double a2, double b2, double c2,
                         ConsistencyCheckResult_C* result);

/**
 * @brief Solves a pair of linear equations using Cramer's rule.
 * @param a1, b1, c1 Coefficients for eq1.
 * @param a2, b2, c2 Coefficients for eq2.
 * @param result Pointer to SolutionResult_C to store the result and steps.
 * @return LE_SUCCESS on success, error code otherwise.
 */
int le_solve_general_cramer(double a1, double b1, double c1,
                            double a2, double b2, double c2,
                            SolutionResult_C* result);

/**
 * @brief Solves a pair of linear equations using the substitution method.
 * @param result Pointer to SolutionResult_C.
 * @return LE_SUCCESS on success or if non-unique, error code on failure.
 */
int le_solve_by_substitution(double a1, double b1, double c1,
                             double a2, double b2, double c2,
                             SolutionResult_C* result);

/**
 * @brief Solves a pair of linear equations using the elimination method.
 * @param result Pointer to SolutionResult_C.
 * @return LE_SUCCESS on success or if non-unique, error code on failure.
 */
int le_solve_by_elimination(double a1, double b1, double c1,
                            double a2, double b2, double c2,
                            SolutionResult_C* result);

/**
 * @brief Solves by cross-multiplication. Expects c1_form, c2_form from ax+by+C=0.
 * @param c1_form_axbyc0 Constant from eq1 in ax+by+C1=0 form.
 * @param c2_form_axbyc0 Constant from eq2 in ax+by+C2=0 form.
 * @param result Pointer to SolutionResult_C.
 * @return LE_SUCCESS on success or if non-unique, error code on failure.
 */
int le_solve_by_cross_multiplication(double a1, double b1, double c1_form_axbyc0,
                                     double a2, double b2, double c2_form_axbyc0,
                                     SolutionResult_C* result);

/**
 * @brief Solves equations reducible to linear form.
 * @param u_coeff1, v_coeff1, const1 For substituted equation 1 (in u, v).
 * @param u_coeff2, v_coeff2, const2 For substituted equation 2 (in u, v).
 * @param u_represents String like "1/x".
 * @param v_represents String like "1/y".
 * @param result Pointer to ReducibleSolutionResult_C.
 * @return LE_SUCCESS on success, error code otherwise.
 */
int le_solve_reducible(double u_coeff1, double v_coeff1, double const1,
                       double u_coeff2, double v_coeff2, double const2,
                       const char* u_represents, const char* v_represents,
                       ReducibleSolutionResult_C* result);

#endif // LINEAR_EQUATIONS_UTILS_H