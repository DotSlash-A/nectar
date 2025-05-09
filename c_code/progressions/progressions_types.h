#ifndef PROGRESSIONS_TYPES_H
#define PROGRESSIONS_TYPES_H

#include <stdbool.h>
#include <stdio.h> // For snprintf

#define PROG_MAX_STRING_LEN 128
#define PROG_MAX_TERMS_IN_LIST 10 // For storing inserted means or middle terms
#define PROG_SUCCESS 0
#define PROG_ERROR_INVALID_ARG -1
#define PROG_ERROR_CALCULATION -2 // e.g., overflow, division by zero, invalid condition
#define PROG_ERROR_BUFFER_TOO_SMALL -3

// For EPSILON comparison with doubles
#define PROG_EPSILON 1e-9

typedef struct {
    double nth_term;
    double sum_n_terms;
} APResult_C;

typedef struct {
    int number_of_terms;
    int middle_indices[2];      // Max 2 middle terms for AP
    double middle_values[2];    // Max 2 middle term values
    int num_middle_terms_found; // 1 or 2
} APMiddleTermResult_C;

typedef struct {
    double nth_term;
    double sum_n_terms;
} GPResult_C;

typedef struct {
    double common_ratio;
    double geometric_means[PROG_MAX_TERMS_IN_LIST];
    int num_means_inserted;
} GPInsertMeansResult_C;

// --- Print Helper Function Declarations ---
void prog_print_ap_result(const APResult_C* res);
void prog_print_ap_middle_term_result(const APMiddleTermResult_C* res);
void prog_print_gp_result(const GPResult_C* res);
void prog_print_gp_insert_means_result(const GPInsertMeansResult_C* res);

#endif // PROGRESSIONS_TYPES_H