#ifndef QUADRATIC_UTILS_H
#define QUADRATIC_UTILS_H

#include "poly_quad_types.h"

/**
 * @brief Solves ax^2 + bx + c = 0.
 * @param a Coefficient of x^2.
 * @param b Coefficient of x.
 * @param c Constant term.
 * @param result Pointer to QuadraticSolution_C to store results.
 * @return PQ_SUCCESS or error code.
 */
int quad_solve_equation(double a, double b, double c, QuadraticSolution_C* result);

#endif // QUADRATIC_UTILS_H