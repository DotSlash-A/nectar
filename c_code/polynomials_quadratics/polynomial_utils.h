#ifndef POLYNOMIAL_UTILS_H
#define POLYNOMIAL_UTILS_H

#include "poly_quad_types.h"

/**
 * @brief Formats polynomial coefficients to a string.
 * @param coeffs Array of coefficients (highest power first).
 * @param num_coeffs Number of coefficients.
 * @param var_symbol Character for the variable (e.g., 'x').
 * @param output_buffer Buffer to store the formatted string.
 * @param buffer_size Size of the output_buffer.
 * @return PQ_SUCCESS or error code.
 */
int poly_format_to_string(const double coeffs[], int num_coeffs, char var_symbol,
                          char* output_buffer, size_t buffer_size);

/**
 * @brief Evaluates P(x_val) using Horner's method.
 * @param coeffs Array of coefficients.
 * @param num_coeffs Number of coefficients.
 * @param x_val Value at which to evaluate.
 * @param result Pointer to store the evaluation result.
 * @return PQ_SUCCESS or error code.
 */
int poly_evaluate(const double coeffs[], int num_coeffs, double x_val, double* result);

/**
 * @brief Performs polynomial long division: dividend / divisor.
 * @param dividend_coeffs Coefficients of the dividend.
 * @param num_dividend_coeffs Number of dividend coefficients.
 * @param divisor_coeffs Coefficients of the divisor.
 * @param num_divisor_coeffs Number of divisor coefficients.
 * @param result Pointer to PolynomialDivisionResult_C to store results.
 * @return PQ_SUCCESS or error code.
 */
int poly_division(const double dividend_coeffs[], int num_dividend_coeffs,
                  const double divisor_coeffs[], int num_divisor_coeffs,
                  PolynomialDivisionResult_C* result);
/**
 * @brief Finds rational roots of a polynomial (assumes integer-like coefficients).
 * @param coeffs Array of coefficients.
 * @param num_coeffs Number of coefficients.
 * @param rational_roots_found Array to store found rational roots.
 * @param max_roots Max capacity of rational_roots_found array.
 * @param num_rational_roots_found Pointer to store the count of roots found.
 * @return PQ_SUCCESS or error code.
 */
int poly_find_rational_roots(const double coeffs[], int num_coeffs,
                             double rational_roots_found[], int max_roots,
                             int* num_rational_roots_found);

/**
 * @brief Calculates Vieta's formulas for quadratic polynomials.
 * @param coeffs Array of 3 coefficients (a, b, c).
 * @param num_coeffs Must be 3.
 * @param result Pointer to RootsCoefficientsRelation_C.
 * @return PQ_SUCCESS or error code.
 */
int poly_relation_roots_coeffs_quadratic(const double coeffs[], int num_coeffs,
                                         RootsCoefficientsRelation_C* result);
/**
 * @brief Calculates Vieta's formulas for cubic polynomials.
 * @param coeffs Array of 4 coefficients (a, b, c, d).
 * @param num_coeffs Must be 4.
 * @param result Pointer to RootsCoefficientsRelation_C.
 * @return PQ_SUCCESS or error code.
 */
int poly_relation_roots_coeffs_cubic(const double coeffs[], int num_coeffs,
                                     RootsCoefficientsRelation_C* result);

/**
 * @brief Multiplies two polynomials.
 * @param poly1_coeffs Coefficients of the first polynomial.
 * @param num_poly1_coeffs Number of coefficients for poly1.
 * @param poly2_coeffs Coefficients of the second polynomial.
 * @param num_poly2_coeffs Number of coefficients for poly2.
 * @param result_coeffs Buffer to store coefficients of the product. Max size PQ_MAX_POLY_TERMS.
 * @param num_result_coeffs Pointer to store the number of coeffs in the product.
 * @return PQ_SUCCESS or error code.
 */
int poly_multiply(const double poly1_coeffs[], int num_poly1_coeffs,
                  const double poly2_coeffs[], int num_poly2_coeffs,
                  double result_coeffs[], int* num_result_coeffs);

/**
 * @brief Forms a polynomial from its roots and a leading coefficient.
 * @param roots Array of (real) roots.
 * @param num_roots Number of roots.
 * @param leading_coefficient The leading coefficient k.
 * @param var_symbol Character for the variable.
 * @param result Pointer to FormedPolynomial_C.
 * @return PQ_SUCCESS or error code.
 */
int poly_form_from_roots(const double roots[], int num_roots,
                         double leading_coefficient, char var_symbol,
                         FormedPolynomial_C* result);

#endif // POLYNOMIAL_UTILS_H