#ifndef GEOMETRIC_PROGRESSION_UTILS_H
#define GEOMETRIC_PROGRESSION_UTILS_H

#include "progressions_types.h"

/**
 * @brief Calculates the nth term and sum of a GP.
 * @param a First term.
 * @param r Common ratio.
 * @param n Number of terms.
 * @param result Pointer to GPResult_C to store the results.
 * @return PROG_SUCCESS or error code.
 */
int gp_calculate_term_and_sum(double a, double r, int n, GPResult_C* result);

/**
 * @brief Calculates the sum to infinity of a GP.
 * @param a First term.
 * @param r Common ratio.
 * @param result_sum Pointer to store the calculated sum.
 * @return PROG_SUCCESS or error code.
 */
int gp_calculate_sum_to_infinity(double a, double r, double* result_sum);

/**
 * @brief Calculates the geometric mean of two non-negative numbers.
 * @param num1 First number.
 * @param num2 Second number.
 * @param result_gm Pointer to store the geometric mean.
 * @return PROG_SUCCESS or error code.
 */
int gp_calculate_geometric_mean(double num1, double num2, double* result_gm);

/**
 * @brief Inserts 'k' geometric means between 'a' and 'b'.
 * @param a First number of the sequence.
 * @param b Last number of the sequence.
 * @param k Number of geometric means to insert.
 * @param result Pointer to GPInsertMeansResult_C to store results. Max PROG_MAX_TERMS_IN_LIST means.
 * @return PROG_SUCCESS or error code.
 */
int gp_insert_geometric_means(double a, double b, int k, GPInsertMeansResult_C* result);

#endif // GEOMETRIC_PROGRESSION_UTILS_H