#ifndef POLY_QUAD_TYPES_H
#define POLY_QUAD_TYPES_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> // For abs with doubles (fabs)

#define PQ_MAX_STRING_LEN 256
#define PQ_MAX_POLY_TERMS 20 // Max terms (degree + 1) for a polynomial representation
#define PQ_MAX_ROOTS 10      // Max roots to store (e.g. for higher degree placeholders)
#define PQ_SUCCESS 0
#define PQ_ERROR_INVALID_ARG -1
#define PQ_ERROR_BUFFER_TOO_SMALL -2
#define PQ_ERROR_CALCULATION -3 // General calculation error (e.g. division by zero)

// For EPSILON comparison with doubles
#define PQ_EPSILON 1e-9

typedef struct {
    double real;
    double imaginary;
    char str_representation[PQ_MAX_STRING_LEN];
} ComplexNumber_C;

typedef struct {
    double quotient_coeffs[PQ_MAX_POLY_TERMS];
    int num_quotient_coeffs;
    double remainder_coeffs[PQ_MAX_POLY_TERMS];
    int num_remainder_coeffs;
    char quotient_string[PQ_MAX_STRING_LEN];
    char remainder_string[PQ_MAX_STRING_LEN];
    char equation_string[PQ_MAX_STRING_LEN * 3]; // For P(x) = D(x)Q(x) + R(x)
} PolynomialDivisionResult_C;

typedef struct {
    char equation_string[PQ_MAX_STRING_LEN];
    double a, b, c;
    double discriminant; // No optional in C, use a flag or specific value if not applicable
    bool discriminant_applicable;
    char nature_of_roots[PQ_MAX_STRING_LEN];
    ComplexNumber_C roots[2]; // Max 2 roots for quadratic
    int num_roots_found;      // 0, 1, or 2 (or special string for identity)
    char special_solution_note[PQ_MAX_STRING_LEN]; // For "All real numbers" or "No solution"
} QuadraticSolution_C;

typedef struct {
    char polynomial_string[PQ_MAX_STRING_LEN];
    int degree;
    // For simplicity in C, Vieta's relations stored as strings or direct values
    double sum_roots_val;          // For quadratic/cubic
    double product_roots_val;      // For quadratic/cubic
    double sum_prod_pairwise_val; // For cubic
    bool relations_applicable;
    char verification_note[PQ_MAX_STRING_LEN];
} RootsCoefficientsRelation_C;

typedef struct {
    double polynomial_coeffs[PQ_MAX_POLY_TERMS];
    int num_coeffs;
    char polynomial_string[PQ_MAX_STRING_LEN];
    // Roots provided are assumed double for simplicity
    double roots_provided[PQ_MAX_ROOTS];
    int num_roots_provided;
    double leading_coefficient_used;
} FormedPolynomial_C;

// --- Print Helper Function Declarations ---
void pq_print_complex_number(const ComplexNumber_C* cn);
void pq_print_polynomial_division_result(const PolynomialDivisionResult_C* res);
void pq_print_quadratic_solution(const QuadraticSolution_C* sol);
void pq_print_roots_coefficients_relation(const RootsCoefficientsRelation_C* rel);
void pq_print_formed_polynomial(const FormedPolynomial_C* poly);

#endif // POLY_QUAD_TYPES_H