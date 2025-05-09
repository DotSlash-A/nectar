#ifndef REAL_NUMBERS_UTILS_H
#define REAL_NUMBERS_UTILS_H

#include "real_numbers_types.h" // Our type definitions

// Function return codes for error handling (example)
#define RN_SUCCESS 0
#define RN_ERROR_INVALID_ARG -1
#define RN_ERROR_OVERFLOW -2
#define RN_ERROR_BUFFER_TOO_SMALL -3
// ... other error codes

// Function Declarations

/**
 * @brief Applies Euclid's Division Lemma.
 * @param dividend The number to be divided.
 * @param divisor The number by which to divide (must be non-zero).
 * @param result Pointer to a EuclidLemmaResult_C struct to store the result.
 * @return RN_SUCCESS on success, error code otherwise.
 */
int rn_euclids_division_lemma(int dividend, int divisor, EuclidLemmaResult_C* result);

/**
 * @brief Calculates HCF using Euclid's Algorithm.
 * @param n1 First integer.
 * @param n2 Second integer.
 * @param result Pointer to an HCFResult_C struct to store the result.
 * @return RN_SUCCESS on success, RN_ERROR_INVALID_ARG if both n1 and n2 are 0.
 */
int rn_euclids_algorithm_hcf(int n1, int n2, HCFResult_C* result);

/**
 * @brief Computes prime factorization.
 * @param n Integer to factorize (must be > 1).
 * @param result Pointer to a PrimeFactorizationResult_C struct.
 *              The factors array inside must be able to hold MAX_PRIME_FACTORS.
 * @return RN_SUCCESS on success, RN_ERROR_INVALID_ARG if n <= 1,
 *         RN_ERROR_BUFFER_TOO_SMALL if more than MAX_PRIME_FACTORS distinct primes.
 */
int rn_get_prime_factorization(int n, PrimeFactorizationResult_C* result);

/**
 * @brief Calculates HCF from two prime factorization results.
 * @param pf1 Prime factorization of the first number.
 * @param pf2 Prime factorization of the second number.
 * @param hcf_val Pointer to an int to store the calculated HCF.
 * @return RN_SUCCESS on success, error code on overflow.
 */
int rn_hcf_from_prime_factorization(const PrimeFactorizationResult_C* pf1,
                                    const PrimeFactorizationResult_C* pf2,
                                    int* hcf_val);
/**
 * @brief Calculates LCM from two prime factorization results.
 * @param pf1 Prime factorization of the first number.
 * @param pf2 Prime factorization of the second number.
 * @param lcm_val Pointer to a long long to store the calculated LCM.
 * @return RN_SUCCESS on success, error code on overflow.
 */
int rn_lcm_from_prime_factorization(const PrimeFactorizationResult_C* pf1,
                                     const PrimeFactorizationResult_C* pf2,
                                     long long* lcm_val);
/**
 * @brief Calculates LCM using the formula LCM(a,b) = |a*b| / HCF(a,b).
 * @param n1 First integer.
 * @param n2 Second integer.
 * @param lcm_val Pointer to a long long to store the LCM.
 * @return RN_SUCCESS on success, RN_ERROR_INVALID_ARG if n1 and n2 are 0,
 *         RN_ERROR_OVERFLOW if calculation overflows.
 */
int rn_calculate_lcm(int n1, int n2, long long* lcm_val);

/**
 * @brief Gets HCF, LCM, and prime factorizations.
 * @param num1 First integer (>0).
 * @param num2 Second integer (>0).
 * @param result Pointer to HCFAndLCMResult_C struct.
 * @return RN_SUCCESS on success, error code otherwise.
 */
int rn_get_hcf_and_lcm_details(int num1, int num2, HCFAndLCMResult_C* result);

/**
 * @brief Basic primality test.
 * @param n Integer to test.
 * @return true if n is prime, false otherwise.
 */
bool rn_is_prime_basic(int n);

/**
 * @brief Checks if a non-negative integer is a perfect square.
 * @param n Integer to check.
 * @param is_square Pointer to bool to store result.
 * @return RN_SUCCESS on success, RN_ERROR_INVALID_ARG if n is negative.
 */
int rn_is_number_perfect_square(int n, bool* is_square);

/**
 * @brief Checks if sqrt(N) is irrational.
 * @param number Non-negative integer N.
 * @param result Pointer to IrrationalityCheckResult_C struct.
 * @return RN_SUCCESS on success.
 */
int rn_check_sqrt_irrationality(int number, IrrationalityCheckResult_C* result);

/**
 * @brief Determines decimal expansion type of num/den.
 * @param numerator Numerator.
 * @param denominator Denominator (must be non-zero).
 * @param result Pointer to DecimalExpansionResult_C struct.
 * @return RN_SUCCESS on success, RN_ERROR_INVALID_ARG if denominator is zero.
 */
int rn_get_decimal_expansion_type(int numerator, int denominator, DecimalExpansionResult_C* result);

/**
 * @brief Analyzes a polynomial given its coefficients (highest power first).
 * @param coeffs Array of double coefficients.
 * @param num_coeffs Number of coefficients in the array.
 * @param result Pointer to PolynomialAnalysisResult_C struct.
 * @return RN_SUCCESS on success, RN_ERROR_INVALID_ARG if num_coeffs is invalid.
 */
int rn_analyze_polynomial(const double coeffs[], int num_coeffs, PolynomialAnalysisResult_C* result);

#endif // REAL_NUMBERS_UTILS_H