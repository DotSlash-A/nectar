#include "arithmetic_progression_utils.h"
#include <string.h> // For memset
#include <math.h>   // For fabs, round

// --- Print Helper Function Implementations (from progressions_types.h) ---
void prog_print_ap_result(const APResult_C* res) {
    if (!res) return;
    printf("APResult_C{nthTerm=%.4f, sumNTerms=%.4f}\n", res->nth_term, res->sum_n_terms);
}

void prog_print_ap_middle_term_result(const APMiddleTermResult_C* res) {
    if (!res) return;
    printf("APMiddleTermResult_C{numberOfTerms=%d, numMiddleTermsFound=%d, middleIndices=[",
           res->number_of_terms, res->num_middle_terms_found);
    for (int i = 0; i < res->num_middle_terms_found; ++i) {
        printf("%d%s", res->middle_indices[i], (i == res->num_middle_terms_found - 1) ? "" : ", ");
    }
    printf("], middleValues=[");
    for (int i = 0; i < res->num_middle_terms_found; ++i) {
        printf("%.4f%s", res->middle_values[i], (i == res->num_middle_terms_found - 1) ? "" : ", ");
    }
    printf("]}\n");
}

void prog_print_gp_result(const GPResult_C* res) {
    if (!res) return;
    printf("GPResult_C{nthTerm=%.4f, sumNTerms=%.4f}\n", res->nth_term, res->sum_n_terms);
}

void prog_print_gp_insert_means_result(const GPInsertMeansResult_C* res) {
    if (!res) return;
    printf("GPInsertMeansResult_C{commonRatio=%.4f, numMeansInserted=%d, geometricMeans=[",
           res->common_ratio, res->num_means_inserted);
    for (int i = 0; i < res->num_means_inserted; ++i) {
        printf("%.4f%s", res->geometric_means[i], (i == res->num_means_inserted - 1) ? "" : ", ");
    }
    printf("]}\n");
}


// --- AP Utility Function Implementations ---

int ap_calculate_term_and_sum(double a, double d, int n, APResult_C* result) {
    if (!result) return PROG_ERROR_INVALID_ARG;
    if (n <= 0) return PROG_ERROR_INVALID_ARG;

    result->nth_term = a + (double)(n - 1) * d;
    result->sum_n_terms = ((double)n / 2.0) * (2.0 * a + (double)(n - 1) * d);
    return PROG_SUCCESS;
}

int ap_calculate_nth_term_from_last(double l, double d, int n, double* result_term) {
    if (!result_term) return PROG_ERROR_INVALID_ARG;
    if (n <= 0) return PROG_ERROR_INVALID_ARG;

    *result_term = l - (double)(n - 1) * d;
    return PROG_SUCCESS;
}

int ap_find_middle_terms(double a, double d, double last_term, APMiddleTermResult_C* result) {
    if (!result) return PROG_ERROR_INVALID_ARG;
    memset(result, 0, sizeof(APMiddleTermResult_C));

    int num_of_terms_val;

    if (fabs(d) < PROG_EPSILON) { // Common difference is zero
        if (fabs(a - last_term) < PROG_EPSILON) {
            num_of_terms_val = 1;
        } else {
            return PROG_ERROR_INVALID_ARG; // d is 0 but first and last terms differ
        }
    } else { // Common difference is non-zero
        if ((last_term - a) / d < -PROG_EPSILON && fabs(last_term - a) > PROG_EPSILON) {
            return PROG_ERROR_CALCULATION; // Last term not reachable in specified direction
        }
        double n_float = (last_term - a) / d + 1.0;

        if (n_float < (1.0 - PROG_EPSILON)) {
            return PROG_ERROR_CALCULATION; // Non-positive number of terms
        }
        if (fabs(n_float - round(n_float)) > PROG_EPSILON) {
            return PROG_ERROR_CALCULATION; // Non-integer number of terms
        }
        num_of_terms_val = (int)round(n_float);
        if (num_of_terms_val <= 0) {
            return PROG_ERROR_CALCULATION; // Should be caught above
        }
    }
    result->number_of_terms = num_of_terms_val;

    if (num_of_terms_val % 2 == 1) { // Odd number of terms
        result->num_middle_terms_found = 1;
        result->middle_indices[0] = (num_of_terms_val + 1) / 2;
        result->middle_values[0] = a + (double)(result->middle_indices[0] - 1) * d;
    } else { // Even number of terms
        result->num_middle_terms_found = 2;
        result->middle_indices[0] = num_of_terms_val / 2;
        result->middle_values[0] = a + (double)(result->middle_indices[0] - 1) * d;

        result->middle_indices[1] = num_of_terms_val / 2 + 1;
        result->middle_values[1] = a + (double)(result->middle_indices[1] - 1) * d;
    }
    return PROG_SUCCESS;
}