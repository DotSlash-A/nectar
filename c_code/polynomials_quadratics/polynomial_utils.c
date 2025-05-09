#include "polynomial_utils.h"
#include <string.h>
#include <math.h> // For fabs, pow, round
#include <limits.h> // For INT_MAX

// --- Print Helper Function Implementations (from poly_quad_types.h) ---
void pq_print_complex_number(const ComplexNumber_C* cn) {
    if (!cn) return;
    printf("%s", cn->str_representation);
}

void pq_print_polynomial_division_result(const PolynomialDivisionResult_C* res) {
    if (!res) return;
    printf("PolynomialDivisionResult_C{quotient='%s', remainder='%s', equation='%s'}\n",
           res->quotient_string, res->remainder_string, res->equation_string);
}

void pq_print_quadratic_solution(const QuadraticSolution_C* sol) {
    if (!sol) return;
    printf("QuadraticSolution_C{equation='%s', discriminant_applicable=%s, discriminant=%.4f, nature='%s', roots=[",
           sol->equation_string, sol->discriminant_applicable ? "true" : "false", sol->discriminant, sol->nature_of_roots);
    if (sol->num_roots_found > 0) {
        for (int i = 0; i < sol->num_roots_found; ++i) {
            pq_print_complex_number(&sol->roots[i]);
            if (i < sol->num_roots_found - 1) printf(", ");
        }
    } else if (strlen(sol->special_solution_note) > 0) {
        printf("%s", sol->special_solution_note);
    }
    printf("]}\n");
}

void pq_print_roots_coefficients_relation(const RootsCoefficientsRelation_C* rel) {
    if (!rel) return;
    printf("RootsCoefficientsRelation_C{polynomial='%s', degree=%d, relations_applicable=%s, ",
           rel->polynomial_string, rel->degree, rel->relations_applicable ? "true" : "false");
    if (rel->relations_applicable) {
        printf("sum=%.4f, product=%.4f", rel->sum_roots_val, rel->product_roots_val);
        if (rel->degree == 3) printf(", sum_prod_pairwise=%.4f", rel->sum_prod_pairwise_val);
    }
    printf(", note='%s'}\n", rel->verification_note);
}

void pq_print_formed_polynomial(const FormedPolynomial_C* poly) {
    if (!poly) return;
    printf("FormedPolynomial_C{polynomialString='%s', leadingCoeff=%.4f, rootsProvided=[",
           poly->polynomial_string, poly->leading_coefficient_used);
    for (int i = 0; i < poly->num_roots_provided; ++i) {
        printf("%.4f%s", poly->roots_provided[i], (i == poly->num_roots_provided - 1) ? "" : ", ");
    }
    printf("], coeffs=[");
     for (int i = 0; i < poly->num_coeffs; ++i) {
        printf("%.4f%s", poly->polynomial_coeffs[i], (i == poly->num_coeffs - 1) ? "" : ", ");
    }
    printf("]}\n");
}


// --- Polynomial Utility Function Implementations ---

// Helper to remove leading zero coefficients and return the new count
static int poly_normalize_coeffs(const double in_coeffs[], int num_in_coeffs,
                                 double out_coeffs[], int max_out_coeffs) {
    if (num_in_coeffs == 0) return 0;
    int first_nz_idx = 0;
    while (first_nz_idx < num_in_coeffs -1 && fabs(in_coeffs[first_nz_idx]) < PQ_EPSILON) {
        first_nz_idx++;
    }

    int new_num_coeffs = num_in_coeffs - first_nz_idx;
    if (new_num_coeffs > max_out_coeffs) return -1; // Buffer too small

    for (int i = 0; i < new_num_coeffs; ++i) {
        out_coeffs[i] = in_coeffs[first_nz_idx + i];
    }
    // If all were zero, out_coeffs[0] will be the last zero, new_num_coeffs = 1
    if (new_num_coeffs == 1 && fabs(out_coeffs[0]) < PQ_EPSILON) {
         // It's just "0"
    }
    return new_num_coeffs;
}


int poly_format_to_string(const double coeffs_in[], int num_coeffs_in, char var_symbol,
                          char* output_buffer, size_t buffer_size) {
    if (!output_buffer || buffer_size == 0) return PQ_ERROR_BUFFER_TOO_SMALL;
    output_buffer[0] = '\0';
    if (!coeffs_in || num_coeffs_in <= 0) {
        if (buffer_size > 1) strncpy(output_buffer, "0", buffer_size -1);
        else return PQ_ERROR_BUFFER_TOO_SMALL;
        return PQ_SUCCESS;
    }

    double current_coeffs[PQ_MAX_POLY_TERMS];
    int num_current_coeffs = poly_normalize_coeffs(coeffs_in, num_coeffs_in, current_coeffs, PQ_MAX_POLY_TERMS);
    if (num_current_coeffs < 0) return PQ_ERROR_BUFFER_TOO_SMALL; // Should not happen if input num_coeffs_in is sane


    if (num_current_coeffs == 0 || (num_current_coeffs == 1 && fabs(current_coeffs[0]) < PQ_EPSILON)) {
         if (buffer_size > 1) strncpy(output_buffer, "0", buffer_size -1);
         else return PQ_ERROR_BUFFER_TOO_SMALL;
         output_buffer[buffer_size-1] = '\0';
         return PQ_SUCCESS;
    }


    int degree = num_current_coeffs - 1;
    size_t current_len = 0;
    bool first_term = true;

    for (int i = 0; i <= degree; ++i) {
        double coeff = current_coeffs[i];
        int power = degree - i;

        if (fabs(coeff) < PQ_EPSILON) continue;

        // Sign
        char sign_str[4] = "";
        if (!first_term) {
            if (coeff > 0) strcpy(sign_str, " + ");
            else strcpy(sign_str, " - ");
        } else if (coeff < 0) {
            strcpy(sign_str, "-");
        }
        if (current_len + strlen(sign_str) >= buffer_size) return PQ_ERROR_BUFFER_TOO_SMALL;
        strcat(output_buffer, sign_str); current_len += strlen(sign_str);

        double abs_coeff = fabs(coeff);
        bool coeff_is_one = fabs(abs_coeff - 1.0) < PQ_EPSILON;

        // Coefficient value
        char coeff_str[32] = "";
        if (!coeff_is_one || power == 0) {
            if (fabs(abs_coeff - round(abs_coeff)) < PQ_EPSILON) { // Integer
                snprintf(coeff_str, sizeof(coeff_str), "%lld", (long long)round(abs_coeff));
            } else { // Double
                snprintf(coeff_str, sizeof(coeff_str), "%.4g", abs_coeff); // %.4g is nice
            }
            if (current_len + strlen(coeff_str) >= buffer_size) return PQ_ERROR_BUFFER_TOO_SMALL;
            strcat(output_buffer, coeff_str); current_len += strlen(coeff_str);
        }
        // else if coeff_is_one and power > 0, don't print "1"

        // Variable and power
        if (power > 0) {
            char var_part[16]; // For "x" or "x^N"
            if (power == 1) snprintf(var_part, sizeof(var_part), "%c", var_symbol);
            else snprintf(var_part, sizeof(var_part), "%c^%d", var_symbol, power);

            // Add space if coefficient was printed and it wasn't just a sign
            if (strlen(coeff_str) > 0 && !coeff_is_one && current_len + 1 < buffer_size && power > 0) {
                // strcat(output_buffer, " "); current_len++; // Optional space e.g "2 x" vs "2x"
            }

            if (current_len + strlen(var_part) >= buffer_size) return PQ_ERROR_BUFFER_TOO_SMALL;
            strcat(output_buffer, var_part); current_len += strlen(var_part);
        }
        first_term = false;
    }
    if (first_term) { // All coeffs were zero
         if (buffer_size > 1) strncpy(output_buffer, "0", buffer_size -1); else return PQ_ERROR_BUFFER_TOO_SMALL;
    }
    output_buffer[buffer_size-1] = '\0'; // Ensure null termination
    return PQ_SUCCESS;
}

int poly_evaluate(const double coeffs[], int num_coeffs, double x_val, double* result) {
    if (!result || !coeffs || num_coeffs < 0) return PQ_ERROR_INVALID_ARG;
    if (num_coeffs == 0) {
        *result = 0.0;
        return PQ_SUCCESS;
    }
    *result = 0.0;
    for (int i = 0; i < num_coeffs; ++i) {
        *result = (*result) * x_val + coeffs[i];
    }
    return PQ_SUCCESS;
}

int poly_division(const double dividend_coeffs_in[], int num_dividend_coeffs_in,
                  const double divisor_coeffs_in[], int num_divisor_coeffs_in,
                  PolynomialDivisionResult_C* result) {
    if (!result || !dividend_coeffs_in || !divisor_coeffs_in ||
        num_dividend_coeffs_in < 0 || num_divisor_coeffs_in <= 0) return PQ_ERROR_INVALID_ARG;

    memset(result, 0, sizeof(PolynomialDivisionResult_C));

    double norm_dividend[PQ_MAX_POLY_TERMS], norm_divisor[PQ_MAX_POLY_TERMS];
    int num_norm_dividend = poly_normalize_coeffs(dividend_coeffs_in, num_dividend_coeffs_in, norm_dividend, PQ_MAX_POLY_TERMS);
    int num_norm_divisor = poly_normalize_coeffs(divisor_coeffs_in, num_divisor_coeffs_in, norm_divisor, PQ_MAX_POLY_TERMS);

    if (num_norm_dividend < 0 || num_norm_divisor < 0) return PQ_ERROR_BUFFER_TOO_SMALL;
    if (num_norm_divisor == 0 || (num_norm_divisor == 1 && fabs(norm_divisor[0]) < PQ_EPSILON)) {
        return PQ_ERROR_INVALID_ARG; // Divisor is zero
    }

    // Store original strings for the equation
    char dividend_str_orig[PQ_MAX_STRING_LEN], divisor_str_orig[PQ_MAX_STRING_LEN];
    poly_format_to_string(dividend_coeffs_in, num_dividend_coeffs_in, 'x', dividend_str_orig, sizeof(dividend_str_orig));
    poly_format_to_string(divisor_coeffs_in, num_divisor_coeffs_in, 'x', divisor_str_orig, sizeof(divisor_str_orig));


    int dividend_degree = num_norm_dividend - 1;
    int divisor_degree = num_norm_divisor - 1;

    if (dividend_degree < divisor_degree) {
        result->num_quotient_coeffs = 1; result->quotient_coeffs[0] = 0.0;
        poly_format_to_string(result->quotient_coeffs, 1, 'x', result->quotient_string, sizeof(result->quotient_string));
        
        memcpy(result->remainder_coeffs, norm_dividend, num_norm_dividend * sizeof(double));
        result->num_remainder_coeffs = num_norm_dividend;
        poly_format_to_string(result->remainder_coeffs, result->num_remainder_coeffs, 'x', result->remainder_string, sizeof(result->remainder_string));
        
        snprintf(result->equation_string, sizeof(result->equation_string), "(%s) = (%s) * (%s) + (%s)",
                 dividend_str_orig, divisor_str_orig, result->quotient_string, result->remainder_string);
        return PQ_SUCCESS;
    }

    double remainder_temp[PQ_MAX_POLY_TERMS];
    memcpy(remainder_temp, norm_dividend, num_norm_dividend * sizeof(double));
    
    int quotient_degree = dividend_degree - divisor_degree;
    result->num_quotient_coeffs = quotient_degree + 1;
    if (result->num_quotient_coeffs > PQ_MAX_POLY_TERMS) return PQ_ERROR_BUFFER_TOO_SMALL;

    double lead_divisor_coeff = norm_divisor[0];

    for (int i = 0; i <= quotient_degree; ++i) {
        double current_lead_remainder = remainder_temp[i];
        double current_quotient_term = current_lead_remainder / lead_divisor_coeff;
        result->quotient_coeffs[i] = current_quotient_term;

        for (int j = 0; j < num_norm_divisor; ++j) {
            if (i + j < num_norm_dividend) { // Check bounds for remainder_temp
                 remainder_temp[i + j] -= current_quotient_term * norm_divisor[j];
            }
        }
    }

    // Remainder starts after the part "consumed" by quotient
    // Remainder degree = divisor_degree - 1 or less.
    // Number of remainder terms = divisor_degree.
    result->num_remainder_coeffs = 0;
    int remainder_start_idx_in_temp = num_norm_dividend - divisor_degree; 
    if (num_norm_dividend < num_norm_divisor) remainder_start_idx_in_temp = 0; // This case handled above (deg_div < deg_div)

    int k = 0; // Index for result->remainder_coeffs
    bool non_zero_found_in_rem = false;
    for(int i = quotient_degree + 1; i < num_norm_dividend; ++i) {
        if (k < PQ_MAX_POLY_TERMS) {
            if (fabs(remainder_temp[i]) > PQ_EPSILON || !non_zero_found_in_rem ) { // keep leading zeros if part of remainder
                 // This logic needs care: effective remainder coeffs
            }
             // Simplification: just copy the tail based on expected degree
        } else {
            return PQ_ERROR_BUFFER_TOO_SMALL; // Remainder too long
        }
    }
    // A simpler way for remainder:
    // The remainder terms are the last 'divisor_degree' terms of 'remainder_temp' after calculations,
    // possibly with leading zeros within this segment.
    // The actual degree of remainder should be < divisor_degree.
    int effective_rem_start_idx = num_norm_dividend - divisor_degree;
    if (num_norm_dividend < num_norm_divisor) effective_rem_start_idx = 0; // Should be covered by deg_div < deg_div case

    if (divisor_degree > 0) { // if divisor is not constant
         result->num_remainder_coeffs = poly_normalize_coeffs(
             &remainder_temp[quotient_degree + 1], 
             num_norm_dividend - (quotient_degree + 1), // Number of remaining terms in temp
             result->remainder_coeffs, 
             PQ_MAX_POLY_TERMS
         );
         if(result->num_remainder_coeffs < 0) return PQ_ERROR_BUFFER_TOO_SMALL;
    } else { // Divisor is constant, remainder should be 0
        result->num_remainder_coeffs = 1;
        result->remainder_coeffs[0] = 0.0;
    }


    if (result->num_remainder_coeffs == 0 || (result->num_remainder_coeffs == 1 && fabs(result->remainder_coeffs[0]) < PQ_EPSILON) ) {
        result->num_remainder_coeffs = 1;
        result->remainder_coeffs[0] = 0.0; // Ensure it's explicitly "0"
    }
    
    poly_format_to_string(result->quotient_coeffs, result->num_quotient_coeffs, 'x', result->quotient_string, sizeof(result->quotient_string));
    poly_format_to_string(result->remainder_coeffs, result->num_remainder_coeffs, 'x', result->remainder_string, sizeof(result->remainder_string));
    snprintf(result->equation_string, sizeof(result->equation_string), "(%s) = (%s) * (%s) + (%s)",
             dividend_str_orig, divisor_str_orig, result->quotient_string, result->remainder_string);

    return PQ_SUCCESS;
}

// ... Implementations for poly_find_rational_roots,
// poly_relation_roots_coeffs_quadratic, poly_relation_roots_coeffs_cubic,
// poly_multiply, poly_form_from_roots ...
// These will be non-trivial to implement robustly in C with fixed buffers.
// For rational roots, you'd implement getDivisors, then test.
// For multiply, nested loops. For form from roots, repeated multiplication.

// --- Placeholder for complex functions to keep it runnable ---
int poly_find_rational_roots(const double coeffs[], int num_coeffs,
                             double rational_roots_found[], int max_roots,
                             int* num_rational_roots_found) {
    if (!num_rational_roots_found || !coeffs || num_coeffs <=0 || !rational_roots_found || max_roots <=0) return PQ_ERROR_INVALID_ARG;
    *num_rational_roots_found = 0;
    // Basic: if constant term is 0, then 0 is a root
    if (num_coeffs > 0 && fabs(coeffs[num_coeffs - 1]) < PQ_EPSILON) {
        if (*num_rational_roots_found < max_roots) {
            rational_roots_found[(*num_rational_roots_found)++] = 0.0;
        } else return PQ_ERROR_BUFFER_TOO_SMALL;
    }
    // Actual RRT is more involved: get divisors of constant and leading, test ratios.
    // This is a highly simplified stub.
    return PQ_SUCCESS;
}

int poly_relation_roots_coeffs_quadratic(const double coeffs[], int num_coeffs, RootsCoefficientsRelation_C* result) {
    if (!result || !coeffs || num_coeffs != 3) return PQ_ERROR_INVALID_ARG;
    memset(result, 0, sizeof(RootsCoefficientsRelation_C));
    result->degree = 2;
    poly_format_to_string(coeffs, num_coeffs, 'x', result->polynomial_string, sizeof(result->polynomial_string));

    if (fabs(coeffs[0]) < PQ_EPSILON) return PQ_ERROR_INVALID_ARG; // a cannot be 0
    result->sum_roots_val = -coeffs[1] / coeffs[0];
    result->product_roots_val = coeffs[2] / coeffs[0];
    result->relations_applicable = true;
    snprintf(result->verification_note, sizeof(result->verification_note), "Sum = -b/a, Product = c/a");
    return PQ_SUCCESS;
}
int poly_relation_roots_coeffs_cubic(const double coeffs[], int num_coeffs, RootsCoefficientsRelation_C* result) {
     if (!result || !coeffs || num_coeffs != 4) return PQ_ERROR_INVALID_ARG;
    memset(result, 0, sizeof(RootsCoefficientsRelation_C));
    result->degree = 3;
    poly_format_to_string(coeffs, num_coeffs, 'x', result->polynomial_string, sizeof(result->polynomial_string));

    if (fabs(coeffs[0]) < PQ_EPSILON) return PQ_ERROR_INVALID_ARG; // a cannot be 0
    result->sum_roots_val = -coeffs[1] / coeffs[0];
    result->sum_prod_pairwise_val = coeffs[2] / coeffs[0];
    result->product_roots_val = -coeffs[3] / coeffs[0];
    result->relations_applicable = true;
    snprintf(result->verification_note, sizeof(result->verification_note), "Sum = -b/a, SumPair = c/a, Prod = -d/a");
    return PQ_SUCCESS;
}

int poly_multiply(const double p1c[], int n_p1c, const double p2c[], int n_p2c,
                  double res_c[], int* n_res_c) {
    if (!res_c || !n_res_c || !p1c || n_p1c <=0 || !p2c || n_p2c <=0) return PQ_ERROR_INVALID_ARG;
    
    int deg1 = n_p1c - 1;
    int deg2 = n_p2c - 1;
    *n_res_c = deg1 + deg2 + 1;
    if (*n_res_c > PQ_MAX_POLY_TERMS) return PQ_ERROR_BUFFER_TOO_SMALL;

    for (int i = 0; i < *n_res_c; ++i) res_c[i] = 0.0; // Initialize result

    for (int i = 0; i < n_p1c; ++i) {
        for (int j = 0; j < n_p2c; ++j) {
            res_c[i + j] += p1c[i] * p2c[j];
        }
    }
    return PQ_SUCCESS;
}

int poly_form_from_roots(const double roots[], int num_roots, double lead_coeff, char var_sym,
                         FormedPolynomial_C* res) {
    if (!res || !roots && num_roots > 0) return PQ_ERROR_INVALID_ARG;
    memset(res, 0, sizeof(FormedPolynomial_C));
    res->leading_coefficient_used = lead_coeff;
    res->num_roots_provided = num_roots;
    for(int i=0; i<num_roots; ++i) {
        if (i < PQ_MAX_ROOTS) res->roots_provided[i] = roots[i];
        else return PQ_ERROR_BUFFER_TOO_SMALL; // Too many roots for storage
    }

    res->polynomial_coeffs[0] = lead_coeff;
    res->num_coeffs = 1;

    for (int i = 0; i < num_roots; ++i) {
        double factor_coeffs[] = {1.0, -roots[i]}; // (x - root_i)
        double temp_product[PQ_MAX_POLY_TERMS];
        int num_temp_product_coeffs;
        
        int ret = poly_multiply(res->polynomial_coeffs, res->num_coeffs,
                                factor_coeffs, 2,
                                temp_product, &num_temp_product_coeffs);
        if (ret != PQ_SUCCESS) return ret;
        
        if (num_temp_product_coeffs > PQ_MAX_POLY_TERMS) return PQ_ERROR_BUFFER_TOO_SMALL;
        memcpy(res->polynomial_coeffs, temp_product, num_temp_product_coeffs * sizeof(double));
        res->num_coeffs = num_temp_product_coeffs;
    }
    poly_format_to_string(res->polynomial_coeffs, res->num_coeffs, var_sym, res->polynomial_string, sizeof(res->polynomial_string));
    return PQ_SUCCESS;
}