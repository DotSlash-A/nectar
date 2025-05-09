#ifndef ARITHMETIC_PROGRESSION_UTILS_H
#define ARITHMETIC_PROGRESSION_UTILS_H

#include "progressions_types.h"

/**
 * @brief Calculates the nth term and sum of an AP.
 * @param a First term.
 * @param d Common difference.
 * @param n Number of terms.
 * @param result Pointer to APResult_C to store the results.
 * @return PROG_SUCCESS or error code.
 */
int ap_calculate_term_and_sum(double a, double d, int n, APResult_C* result);

/**
 * @brief Calculates the nth term from the end of an AP.
 * @param l Last term.
 * @param d Common difference.
 * @param n Which term from the end.
 * @param result_term Pointer to store the calculated term.
 * @return PROG_SUCCESS or error code.
 */
int ap_calculate_nth_term_from_last(double l, double d, int n, double* result_term);

/**
 * @brief Finds the middle term(s) of an AP given a, d, and last_term.
 * @param a First term.
 * @param d Common difference.
 * @param last_term The last term of the progression.
 * @param result Pointer to APMiddleTermResult_C to store the results.
 * @return PROG_SUCCESS or error code.
 */
int ap_find_middle_terms(double a, double d, double last_term, APMiddleTermResult_C* result);

#endif // ARITHMETIC_PROGRESSION_UTILS_H