#include "geometric_progression_utils.h"
#include <string.h> // For memset
#include <math.h>   // For fabs, pow, sqrt, isinf, isnan
#include <float.h>  // For DBL_MAX for overflow check (approximate)

// --- GP Utility Function Implementations ---

int gp_calculate_term_and_sum(double a, double r, int n, GPResult_C* result) {
    if (!result) return PROG_ERROR_INVALID_ARG;
    if (n <= 0) return PROG_ERROR_INVALID_ARG;

    if (fabs(a) < PROG_EPSILON && fabs(r) < PROG_EPSILON && n > 1) {
        return PROG_ERROR_CALCULATION; // Ambiguous 0^0 case
    }
    if (fabs(a) < PROG_EPSILON) {
        result->nth_term = 0.0;
        result->sum_n_terms = 0.0;
        return PROG_SUCCESS;
    }

    result->nth_term = a * pow(r, (double)n - 1.0);
    if (isinf(result->nth_term) || isnan(result->nth_term)) {
        return PROG_ERROR_CALCULATION; // Overflow or NaN
    }

    if (fabs(r - 1.0) < PROG_EPSILON) {
        result->sum_n_terms = (double)n * a;
    } else {
        double r_pow_n = pow(r, (double)n);
        if (isinf(r_pow_n) || isnan(r_pow_n)) {
            return PROG_ERROR_CALCULATION;
        }
        double numerator = a * (r_pow_n - 1.0);
        double denominator = r - 1.0;
        if (fabs(denominator) < PROG_EPSILON * PROG_EPSILON) { // Should be caught by |r-1| check
            return PROG_ERROR_CALCULATION; // Division by (near) zero
        }
        result->sum_n_terms = numerator / denominator;
    }
    if (isinf(result->sum_n_terms) || isnan(result->sum_n_terms)) {
        return PROG_ERROR_CALCULATION;
    }
    return PROG_SUCCESS;
}

int gp_calculate_sum_to_infinity(double a, double r, double* result_sum) {
    if (!result_sum) return PROG_ERROR_INVALID_ARG;
    if (fabs(r) >= 1.0 - PROG_EPSILON) { // |r| >= 1
        return PROG_ERROR_CALCULATION; // Sum to infinity does not converge
    }
    double denominator = 1.0 - r;
    if (fabs(denominator) < PROG_EPSILON * PROG_EPSILON) {
        return PROG_ERROR_CALCULATION; // Division by (near) zero
    }
    *result_sum = a / denominator;
    if (isinf(*result_sum) || isnan(*result_sum)) {
        return PROG_ERROR_CALCULATION;
    }
    return PROG_SUCCESS;
}

int gp_calculate_geometric_mean(double num1, double num2, double* result_gm) {
    if (!result_gm) return PROG_ERROR_INVALID_ARG;
    if (num1 < -PROG_EPSILON || num2 < -PROG_EPSILON) {
        return PROG_ERROR_INVALID_ARG; // GM for non-negative numbers
    }
    if (fabs(num1) < PROG_EPSILON || fabs(num2) < PROG_EPSILON) {
        *result_gm = 0.0;
        return PROG_SUCCESS;
    }
    *result_gm = sqrt(num1 * num2);
    return PROG_SUCCESS;
}

int gp_insert_geometric_means(double a, double b, int k, GPInsertMeansResult_C* result) {
    if (!result) return PROG_ERROR_INVALID_ARG;
    if (k <= 0) return PROG_ERROR_INVALID_ARG;
    if (k > PROG_MAX_TERMS_IN_LIST) return PROG_ERROR_BUFFER_TOO_SMALL;

    memset(result, 0, sizeof(GPInsertMeansResult_C));

    if (fabs(a) < PROG_EPSILON) {
        if (fabs(b) < PROG_EPSILON) { // Means between 0 and 0 are 0
            result->common_ratio = 0.0; // Or undefined, 0 is practical
            result->num_means_inserted = k;
            for (int i = 0; i < k; ++i) result->geometric_means[i] = 0.0;
            return PROG_SUCCESS;
        } else { // a=0, b!=0
            return PROG_ERROR_CALCULATION;
        }
    }

    double ratio_power_k_plus_1 = b / a;
    int root_index = k + 1;

    if (ratio_power_k_plus_1 < -PROG_EPSILON && root_index % 2 == 0) {
        return PROG_ERROR_CALCULATION; // Even root of negative number for real means
    }

    double r_val;
    if (fabs(ratio_power_k_plus_1) < PROG_EPSILON) { // b is zero, a is non-zero
        r_val = 0.0;
    } else if (ratio_power_k_plus_1 < 0) { // Negative base, root_index must be odd
        r_val = -pow(fabs(ratio_power_k_plus_1), 1.0 / (double)root_index);
    } else { // Positive base
        r_val = pow(ratio_power_k_plus_1, 1.0 / (double)root_index);
    }

    if (isinf(r_val) || isnan(r_val)) {
        return PROG_ERROR_CALCULATION;
    }
    result->common_ratio = r_val;
    result->num_means_inserted = k;

    double current_term = a;
    for (int i = 0; i < k; ++i) {
        current_term *= r_val;
        if (isinf(current_term) || isnan(current_term)) {
            // If one mean overflows, mark remaining and error out
            result->num_means_inserted = i; // Only 'i' means were successfully calculated
            return PROG_ERROR_CALCULATION;
        }
        result->geometric_means[i] = current_term;
    }
    return PROG_SUCCESS;
}