#ifndef REAL_NUMBERS_TYPES_H
#define REAL_NUMBERS_TYPES_H

#include <stdbool.h> // For bool type (C99 and later)
#include <stdio.h>   // For snprintf, FILE
#include <stdlib.h>  // For malloc, free

// Define a maximum string length for simplicity in some structs
#define MAX_STRING_LEN 256
#define MAX_PRIME_FACTORS 32 // Max distinct prime factors for simple array storage

typedef struct {
    int dividend;
    int divisor;
    int quotient;
    int remainder;
    char equation[MAX_STRING_LEN];
} EuclidLemmaResult_C;

typedef struct {
    int num1;
    int num2;
    int hcf;
} HCFResult_C;

// For prime factorization, using a simple array of structs
typedef struct {
    int prime;
    int exponent;
} PrimeFactorEntry_C;

typedef struct {
    int number;
    PrimeFactorEntry_C factors[MAX_PRIME_FACTORS];
    int factor_count; // Number of distinct prime factors found
} PrimeFactorizationResult_C;

typedef struct {
    int num1;
    int num2;
    // For simplicity, we might not store full factorization maps here in C version directly
    // or pass them separately if needed by a function.
    // We'll focus on HCF and LCM values.
    PrimeFactorizationResult_C pf_num1; // Store the results
    PrimeFactorizationResult_C pf_num2;
    int hcf;
    long long lcm;
    char pf_num1_str[MAX_STRING_LEN * 2]; // String representation of pf1
    char pf_num2_str[MAX_STRING_LEN * 2]; // String representation of pf2
} HCFAndLCMResult_C;

typedef struct {
    char number_form[MAX_STRING_LEN];
    bool is_irrational;
    char reason[MAX_STRING_LEN * 2]; // Reason can be longer
} IrrationalityCheckResult_C;

typedef struct {
    int numerator;
    int denominator;
    char fraction_str[MAX_STRING_LEN];
    char expansion_type[MAX_STRING_LEN]; // "terminating", "non-terminating recurring", etc.
    char reason[MAX_STRING_LEN * 2];
} DecimalExpansionResult_C;

// For polynomial analysis in C, we'll simplify.
// Input: array of coefficients. Output: degree, and Vieta's if simple.
// Root finding is very complex in C without libraries.
#define MAX_POLY_DEGREE 10 // Max degree for which we might store coefficients
#define MAX_ROOT_STRINGS 5 // Max roots to store as strings (e.g. for quadratic)

typedef struct {
    double coefficients[MAX_POLY_DEGREE + 1]; // Store up to degree MAX_POLY_DEGREE
    int num_coeffs; // Actual number of coefficients provided
    int degree;
    char roots_str[MAX_ROOT_STRINGS][MAX_STRING_LEN]; // Store string representation of roots
    int num_roots_found;
    char sum_of_roots_vieta_str[MAX_STRING_LEN];
    char product_of_roots_vieta_str[MAX_STRING_LEN];
    char notes[MAX_STRING_LEN];
} PolynomialAnalysisResult_C;


// Helper functions for printing structs (declarations)
void print_euclid_lemma_result_c(const EuclidLemmaResult_C* res);
void print_hcf_result_c(const HCFResult_C* res);
void print_prime_factorization_result_c(const PrimeFactorizationResult_C* res);
void print_hcf_and_lcm_result_c(const HCFAndLCMResult_C* res);
void print_irrationality_check_result_c(const IrrationalityCheckResult_C* res);
void print_decimal_expansion_result_c(const DecimalExpansionResult_C* res);
void print_polynomial_analysis_result_c(const PolynomialAnalysisResult_C* res);

#endif // REAL_NUMBERS_TYPES_H