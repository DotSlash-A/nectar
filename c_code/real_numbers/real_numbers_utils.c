#include "real_numbers_utils.h"
#include <string.h> // For strcpy, strcat, memset, snprintf
#include <math.h>   // For abs, sqrt, pow, floor, round
#include <limits.h> // For INT_MAX, LLONG_MAX

// Helper for GCD since C standard library doesn't have one before C17's <numeric>
// We'll implement a simple one.
static int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Implementation for print functions (from types.h)
void print_euclid_lemma_result_c(const EuclidLemmaResult_C* res) {
    if (!res) return;
    printf("EuclidLemmaResult_C{equation='%s'}\n", res->equation);
}

void print_hcf_result_c(const HCFResult_C* res) {
    if (!res) return;
    printf("HCFResult_C{num1=%d, num2=%d, hcf=%d}\n", res->num1, res->num2, res->hcf);
}

void print_prime_factorization_result_c(const PrimeFactorizationResult_C* res) {
    if (!res) return;
    printf("PrimeFactorizationResult_C{number=%d, factors={", res->number);
    for (int i = 0; i < res->factor_count; ++i) {
        printf("%d:%d", res->factors[i].prime, res->factors[i].exponent);
        if (i < res->factor_count - 1) {
            printf(", ");
        }
    }
    printf("}}\n");
}

void print_hcf_and_lcm_result_c(const HCFAndLCMResult_C* res) {
    if (!res) return;
    printf("HCFAndLCMResult_C{num1=%d, num2=%d, hcf=%d, lcm=%lld, pf1='%s', pf2='%s'}\n",
           res->num1, res->num2, res->hcf, res->lcm, res->pf_num1_str, res->pf_num2_str);
}

void print_irrationality_check_result_c(const IrrationalityCheckResult_C* res) {
    if (!res) return;
    printf("IrrationalityCheckResult_C{numberForm='%s', isIrrational=%s, reason='%s'}\n",
           res->number_form, res->is_irrational ? "true" : "false", res->reason);
}

void print_decimal_expansion_result_c(const DecimalExpansionResult_C* res) {
    if (!res) return;
    printf("DecimalExpansionResult_C{fraction='%s', expansionType='%s', reason='%s'}\n",
           res->fraction_str, res->expansion_type, res->reason);
}

void print_polynomial_analysis_result_c(const PolynomialAnalysisResult_C* res) {
    if (!res) return;
    printf("PolynomialAnalysisResult_C{degree=%d, coeffs=[", res->degree);
    for(int i=0; i<res->num_coeffs; ++i) {
        printf("%.2f%s", res->coefficients[i], (i == res->num_coeffs -1) ? "" : ", ");
    }
    printf("], roots=[");
    for (int i = 0; i < res->num_roots_found; ++i) {
        printf("'%s'", res->roots_str[i]);
        if (i < res->num_roots_found - 1) printf(", ");
    }
    printf("], sumRootsViete='%s', prodRootsViete='%s', notes='%s'}\n",
           res->sum_of_roots_vieta_str, res->product_of_roots_vieta_str, res->notes);
}


// Function Implementations
int rn_euclids_division_lemma(int dividend, int divisor, EuclidLemmaResult_C* result) {
    if (!result) return RN_ERROR_INVALID_ARG;
    if (divisor == 0) {
        strncpy(result->equation, "Error: Divisor cannot be zero.", MAX_STRING_LEN -1);
        result->equation[MAX_STRING_LEN-1] = '\0';
        return RN_ERROR_INVALID_ARG;
    }

    result->dividend = dividend;
    result->divisor = divisor;
    result->quotient = dividend / divisor;
    result->remainder = dividend % divisor;

    // C's % operator can give negative remainder if dividend is negative.
    // Standard Euclid lemma: 0 <= r < |b|
    if (result->remainder < 0) {
        if (divisor > 0) {
            result->remainder += divisor;
            result->quotient--;
        } else { // divisor < 0
            result->remainder -= divisor; // equivalent to adding abs(divisor)
            result->quotient++;
        }
    }
    snprintf(result->equation, MAX_STRING_LEN, "%d = %d * %d + %d",
             result->dividend, result->divisor, result->quotient, result->remainder);
    return RN_SUCCESS;
}

int rn_euclids_algorithm_hcf(int n1, int n2, HCFResult_C* result) {
    if (!result) return RN_ERROR_INVALID_ARG;
    if (n1 == 0 && n2 == 0) {
        result->hcf = 0; // Or handle as error depending on convention
        return RN_ERROR_INVALID_ARG; // Let's treat as an error for this API
    }
    result->num1 = n1;
    result->num2 = n2;
    result->hcf = gcd(n1, n2);
    return RN_SUCCESS;
}

int rn_get_prime_factorization(int n, PrimeFactorizationResult_C* result) {
    if (!result) return RN_ERROR_INVALID_ARG;
    if (n <= 1) return RN_ERROR_INVALID_ARG;

    memset(result, 0, sizeof(PrimeFactorizationResult_C)); // Clear struct
    result->number = n;
    result->factor_count = 0;
    int num = n;

    // Factor out 2s
    if (num % 2 == 0) {
        if (result->factor_count >= MAX_PRIME_FACTORS) return RN_ERROR_BUFFER_TOO_SMALL;
        result->factors[result->factor_count].prime = 2;
        result->factors[result->factor_count].exponent = 0;
        while (num % 2 == 0) {
            result->factors[result->factor_count].exponent++;
            num /= 2;
        }
        result->factor_count++;
    }

    // Factor out odd primes
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) {
            if (result->factor_count >= MAX_PRIME_FACTORS) return RN_ERROR_BUFFER_TOO_SMALL;
            result->factors[result->factor_count].prime = i;
            result->factors[result->factor_count].exponent = 0;
            while (num % i == 0) {
                result->factors[result->factor_count].exponent++;
                num /= i;
            }
            result->factor_count++;
        }
    }

    // If num is still greater than 1, it's a prime factor itself
    if (num > 1) {
        if (result->factor_count >= MAX_PRIME_FACTORS) return RN_ERROR_BUFFER_TOO_SMALL;
        result->factors[result->factor_count].prime = num;
        result->factors[result->factor_count].exponent = 1;
        result->factor_count++;
    }
    return RN_SUCCESS;
}

// Helper to find exponent of a prime in factorization result
static int get_exponent(const PrimeFactorizationResult_C* pf, int prime) {
    for (int i = 0; i < pf->factor_count; ++i) {
        if (pf->factors[i].prime == prime) {
            return pf->factors[i].exponent;
        }
    }
    return 0;
}

int rn_hcf_from_prime_factorization(const PrimeFactorizationResult_C* pf1,
                                    const PrimeFactorizationResult_C* pf2,
                                    int* hcf_val) {
    if (!pf1 || !pf2 || !hcf_val) return RN_ERROR_INVALID_ARG;
    *hcf_val = 1;
    for (int i = 0; i < pf1->factor_count; ++i) {
        int prime = pf1->factors[i].prime;
        int power1 = pf1->factors[i].exponent;
        int power2 = get_exponent(pf2, prime);
        if (power2 > 0) {
            int common_power = (power1 < power2) ? power1 : power2;
            for (int k = 0; k < common_power; ++k) {
                if (prime > 0 && *hcf_val > INT_MAX / prime) return RN_ERROR_OVERFLOW;
                *hcf_val *= prime;
            }
        }
    }
    return RN_SUCCESS;
}

int rn_lcm_from_prime_factorization(const PrimeFactorizationResult_C* pf1,
                                     const PrimeFactorizationResult_C* pf2,
                                     long long* lcm_val) {
    if (!pf1 || !pf2 || !lcm_val) return RN_ERROR_INVALID_ARG;
    *lcm_val = 1LL;

    // Collect all unique primes and their max powers
    // This is much simpler with a map, more verbose with arrays in C
    // For simplicity, iterate through pf1, then add/update from pf2
    for (int i = 0; i < pf1->factor_count; ++i) {
        int prime = pf1->factors[i].prime;
        int power1 = pf1->factors[i].exponent;
        int power2 = get_exponent(pf2, prime);
        int max_power = (power1 > power2) ? power1 : power2;
        for (int k = 0; k < max_power; ++k) {
            if (prime > 0 && *lcm_val > LLONG_MAX / prime) return RN_ERROR_OVERFLOW;
            *lcm_val *= prime;
        }
    }
    // Add primes from pf2 not in pf1
    for (int i = 0; i < pf2->factor_count; ++i) {
        int prime = pf2->factors[i].prime;
        if (get_exponent(pf1, prime) == 0) { // Prime only in pf2
            int power2 = pf2->factors[i].exponent;
            for (int k = 0; k < power2; ++k) {
                 if (prime > 0 && *lcm_val > LLONG_MAX / prime) return RN_ERROR_OVERFLOW;
                *lcm_val *= prime;
            }
        }
    }
    return RN_SUCCESS;
}


int rn_calculate_lcm(int n1, int n2, long long* lcm_val) {
    if (!lcm_val) return RN_ERROR_INVALID_ARG;
    if (n1 == 0 && n2 == 0) return RN_ERROR_INVALID_ARG;
    if (n1 == 0 || n2 == 0) {
        *lcm_val = 0LL;
        return RN_SUCCESS;
    }
    int hcf = gcd(n1, n2);
    if (hcf == 0) return RN_ERROR_INVALID_ARG; // Should not happen if n1,n2 not both 0

    long long num1_ll = n1;
    long long num2_ll = n2;

    // (a / gcd) * b to prevent intermediate overflow
    long long term1 = num1_ll / hcf;
    if (num2_ll != 0 && ( (term1 > 0 && num2_ll > 0 && term1 > LLONG_MAX / num2_ll) ||
                          (term1 < 0 && num2_ll < 0 && term1 < LLONG_MAX / num2_ll) ||
                          (term1 > 0 && num2_ll < 0 && num2_ll < LLONG_MIN / term1) ||
                          (term1 < 0 && num2_ll > 0 && term1 < LLONG_MIN / num2_ll) ) ) {
        return RN_ERROR_OVERFLOW;
    }
    *lcm_val = term1 * num2_ll;
    *lcm_val = (*lcm_val < 0) ? -(*lcm_val) : *lcm_val; // abs for long long
    return RN_SUCCESS;
}


static void format_pf_string(const PrimeFactorizationResult_C* pf, char* buffer, size_t buffer_size) {
    if (!pf || !buffer || buffer_size == 0) {
        if (buffer && buffer_size > 0) buffer[0] = '\0';
        return;
    }
    buffer[0] = '\0';
    if (pf->factor_count == 0 && pf->number == 1) { // Special case for 1
        strncpy(buffer, "1 (no prime factors)", buffer_size - 1);
        buffer[buffer_size - 1] = '\0';
        return;
    }
    for (int i = 0; i < pf->factor_count; ++i) {
        char term[64];
        snprintf(term, sizeof(term), "%d^%d", pf->factors[i].prime, pf->factors[i].exponent);
        if (strlen(buffer) + strlen(term) + (i > 0 ? 3 : 0) < buffer_size) {
            if (i > 0) strcat(buffer, " * ");
            strcat(buffer, term);
        } else {
            // Buffer too small, append "..." and stop
            if (strlen(buffer) + 3 < buffer_size) strcat(buffer, "...");
            break;
        }
    }
}


int rn_get_hcf_and_lcm_details(int num1, int num2, HCFAndLCMResult_C* result) {
    if (!result) return RN_ERROR_INVALID_ARG;
    if (num1 <= 0 || num2 <= 0) return RN_ERROR_INVALID_ARG; // NCERT context often implies positive

    memset(result, 0, sizeof(HCFAndLCMResult_C));
    result->num1 = num1;
    result->num2 = num2;

    int ret;
    if (num1 > 1) {
        ret = rn_get_prime_factorization(num1, &result->pf_num1);
        if (ret != RN_SUCCESS) return ret;
    } else {
        result->pf_num1.number = num1;
        result->pf_num1.factor_count = 0;
    }
    format_pf_string(&result->pf_num1, result->pf_num1_str, sizeof(result->pf_num1_str));


    if (num2 > 1) {
        ret = rn_get_prime_factorization(num2, &result->pf_num2);
        if (ret != RN_SUCCESS) return ret;
    } else {
        result->pf_num2.number = num2;
        result->pf_num2.factor_count = 0;
    }
    format_pf_string(&result->pf_num2, result->pf_num2_str, sizeof(result->pf_num2_str));


    result->hcf = gcd(num1, num2);
    ret = rn_calculate_lcm(num1, num2, &result->lcm);
    if (ret != RN_SUCCESS) return ret;

    return RN_SUCCESS;
}


bool rn_is_prime_basic(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i = i + 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int rn_is_number_perfect_square(int n, bool* is_square) {
    if (!is_square) return RN_ERROR_INVALID_ARG;
    if (n < 0) return RN_ERROR_INVALID_ARG;
    if (n == 0) {
        *is_square = true;
        return RN_SUCCESS;
    }
    // Use double for sqrt then cast, check.
    double sqrt_n_double = sqrt((double)n);
    int sqrt_n_int = (int)sqrt_n_double;
    *is_square = (sqrt_n_int * sqrt_n_int == n);
    return RN_SUCCESS;
}

int rn_check_sqrt_irrationality(int number, IrrationalityCheckResult_C* result) {
    if (!result) return RN_ERROR_INVALID_ARG;
    memset(result, 0, sizeof(IrrationalityCheckResult_C));
    snprintf(result->number_form, MAX_STRING_LEN, "sqrt(%d)", number);

    if (number < 0) {
        result->is_irrational = false; // Or true if complex counts as "not real rational"
        strncpy(result->reason, "sqrt() of a negative number is complex, not real irrational.", sizeof(result->reason) -1);
    } else {
        bool is_sq_val;
        if (rn_is_number_perfect_square(number, &is_sq_val) != RN_SUCCESS) {
             strncpy(result->reason, "Error checking perfect square.", sizeof(result->reason) -1);
             return RN_ERROR_INVALID_ARG; // Propagate error
        }
        if (is_sq_val) {
            result->is_irrational = false;
            snprintf(result->reason, sizeof(result->reason), "sqrt(%d) = %d, which is rational (an integer).",
                     number, (int)sqrt((double)number));
        } else {
            result->is_irrational = true;
            if (rn_is_prime_basic(number)) {
                snprintf(result->reason, sizeof(result->reason), "%d is prime. Sqrt of a prime is irrational.", number);
            } else {
                snprintf(result->reason, sizeof(result->reason), "%d is not a perfect square. Sqrt of a non-perfect square integer is irrational.", number);
            }
        }
    }
    result->reason[sizeof(result->reason)-1] = '\0';
    return RN_SUCCESS;
}

int rn_get_decimal_expansion_type(int numerator, int denominator, DecimalExpansionResult_C* result) {
    if (!result) return RN_ERROR_INVALID_ARG;
    if (denominator == 0) return RN_ERROR_INVALID_ARG;

    memset(result, 0, sizeof(DecimalExpansionResult_C));
    result->numerator = numerator;
    result->denominator = denominator;
    snprintf(result->fraction_str, MAX_STRING_LEN, "%d/%d", numerator, denominator);

    int common = gcd(abs(numerator), abs(denominator));
    int simplified_den = abs(denominator) / common;

    if (simplified_den == 0) { // Should only happen if num also 0 and original den was 0 (caught)
        strncpy(result->expansion_type, "undefined", sizeof(result->expansion_type)-1);
        strncpy(result->reason, "Denominator became zero after simplification (implies numerator also zero).", sizeof(result->reason)-1);
    } else if (simplified_den == 1) {
        strncpy(result->expansion_type, "terminating", sizeof(result->expansion_type)-1);
        snprintf(result->reason, sizeof(result->reason), "Fraction simplifies to an integer (%d). Denominator is 1.", numerator / common);
    } else {
        int temp_den = simplified_den;
        bool only_2_and_5 = true;
        char factors_desc[MAX_STRING_LEN] = "";
        int offset = 0;

        int count2 = 0; while (temp_den % 2 == 0) { temp_den /= 2; count2++; }
        if (count2 > 0) offset += snprintf(factors_desc + offset, sizeof(factors_desc)-offset, "2^%d ", count2);
        
        int count5 = 0; while (temp_den % 5 == 0) { temp_den /= 5; count5++; }
        if (count5 > 0) offset += snprintf(factors_desc + offset, sizeof(factors_desc)-offset, "%s5^%d ", (offset>0?"* ":""), count5);

        // Check other prime factors
        for (int i = 3; i * i <= temp_den; i += 2) {
            if (temp_den % i == 0) {
                only_2_and_5 = false;
                int count_other = 0;
                while (temp_den % i == 0) { temp_den /= i; count_other++; }
                offset += snprintf(factors_desc + offset, sizeof(factors_desc)-offset, "%s%d^%d ", (offset>0?"* ":""), i, count_other);
            }
        }
        if (temp_den > 1) { // Remaining temp_den is a prime
            if (temp_den != 2 && temp_den != 5) only_2_and_5 = false; // Should already be false if it's other prime
            offset += snprintf(factors_desc + offset, sizeof(factors_desc)-offset, "%s%d^1 ", (offset>0?"* ":""), temp_den);
        }
        if (offset == 0 && simplified_den == 1) { // Should be caught by earlier simplified_den == 1
             strncpy(factors_desc, "1", sizeof(factors_desc)-1);
        } else if (offset == 0) { // Should not happen if simplified_den > 1
             snprintf(factors_desc, sizeof(factors_desc), "%d (is prime or no 2/5 factors)", simplified_den);
        }


        if (only_2_and_5) {
            strncpy(result->expansion_type, "terminating", sizeof(result->expansion_type)-1);
            snprintf(result->reason, sizeof(result->reason), "Simplified denominator (%d) has prime factors: %s(only 2s and/or 5s).", simplified_den, factors_desc);
        } else {
            strncpy(result->expansion_type, "non-terminating recurring", sizeof(result->expansion_type)-1);
            snprintf(result->reason, sizeof(result->reason), "Simplified denominator (%d) has prime factors: %s(includes primes other than 2 and 5).", simplified_den, factors_desc);
        }
    }
    // Ensure null termination for all strings
    result->expansion_type[sizeof(result->expansion_type)-1] = '\0';
    result->reason[sizeof(result->reason)-1] = '\0';
    return RN_SUCCESS;
}

int rn_analyze_polynomial(const double coeffs[], int num_coeffs_in, PolynomialAnalysisResult_C* result) {
    if (!result || !coeffs || num_coeffs_in <= 0 || num_coeffs_in > MAX_POLY_DEGREE + 1) {
        if (result) snprintf(result->notes, MAX_STRING_LEN, "Invalid arguments or too many coeffs.");
        return RN_ERROR_INVALID_ARG;
    }
    memset(result, 0, sizeof(PolynomialAnalysisResult_C));

    int first_non_zero_idx = 0;
    while(first_non_zero_idx < num_coeffs_in && fabs(coeffs[first_non_zero_idx]) < 1e-9) {
        first_non_zero_idx++;
    }

    if (first_non_zero_idx == num_coeffs_in) { // All coeffs are zero
        result->degree = 0; // Or undefined, conventionally 0 or -1
        snprintf(result->sum_of_roots_vieta_str, MAX_STRING_LEN, "N/A (0=0 poly)");
        snprintf(result->product_of_roots_vieta_str, MAX_STRING_LEN, "N/A (0=0 poly)");
        snprintf(result->notes, MAX_STRING_LEN, "All coefficients are zero (0=0 polynomial).");
        return RN_SUCCESS;
    }
    
    result->num_coeffs = num_coeffs_in - first_non_zero_idx;
    for(int i = 0; i < result->num_coeffs; ++i) {
        result->coefficients[i] = coeffs[first_non_zero_idx + i];
    }

    result->degree = result->num_coeffs - 1;
    double leading_coeff = result->coefficients[0];

    if (result->degree == 0) {
        snprintf(result->sum_of_roots_vieta_str, MAX_STRING_LEN, "N/A (constant)");
        snprintf(result->product_of_roots_vieta_str, MAX_STRING_LEN, "N/A (constant)");
        snprintf(result->notes, MAX_STRING_LEN, "Constant non-zero polynomial.");
    } else { // Degree >= 1
        if (result->num_coeffs > 1) { // e.g. ax+b
            snprintf(result->sum_of_roots_vieta_str, MAX_STRING_LEN, "%.4f", -result->coefficients[1] / leading_coeff);
        } else { // Monomial like ax^n (n>=1)
             snprintf(result->sum_of_roots_vieta_str, MAX_STRING_LEN, "0");
        }
        snprintf(result->product_of_roots_vieta_str, MAX_STRING_LEN, "%.4f",
                 pow(-1.0, result->degree) * result->coefficients[result->num_coeffs - 1] / leading_coeff);

        if (result->degree == 1) { // ax + b = 0 => x = -b/a
            if (result->num_coeffs > 1) {
                snprintf(result->roots_str[0], MAX_STRING_LEN, "%.4f", -result->coefficients[1] / leading_coeff);
                result->num_roots_found = 1;
            }
            snprintf(result->notes, MAX_STRING_LEN, "Linear polynomial.");
        } else if (result->degree == 2) { // ax^2 + bx + c = 0
            double a = result->coefficients[0];
            double b = result->coefficients[1];
            double c_poly = result->coefficients[2]; // c is a keyword
            double discriminant = b * b - 4 * a * c_poly;

            if (discriminant >= -1e-9) { // Allow for small floating point errors, treat near-zero as zero
                if (discriminant < 0) discriminant = 0; // Correct if it was slightly negative due to precision
                snprintf(result->roots_str[0], MAX_STRING_LEN, "%.4f", (-b + sqrt(discriminant)) / (2 * a));
                snprintf(result->roots_str[1], MAX_STRING_LEN, "%.4f", (-b - sqrt(discriminant)) / (2 * a));
                result->num_roots_found = (fabs(discriminant) < 1e-9) ? 1 : 2; // One root if discriminant is zero
                 if(result->num_roots_found == 1) strcpy(result->roots_str[1], "(repeated)");
            } else { // Complex roots
                snprintf(result->roots_str[0], MAX_STRING_LEN, "%.4f + %.4fi", -b / (2 * a), sqrt(-discriminant) / (2 * a));
                snprintf(result->roots_str[1], MAX_STRING_LEN, "%.4f - %.4fi", -b / (2 * a), sqrt(-discriminant) / (2 * a));
                result->num_roots_found = 2;
            }
            snprintf(result->notes, MAX_STRING_LEN, "Quadratic polynomial.");
        } else {
            snprintf(result->notes, MAX_STRING_LEN, "Root finding for degree > 2 not implemented.");
            if (fabs(result->coefficients[result->num_coeffs-1]) < 1e-9) { // Constant term is zero
                 snprintf(result->roots_str[0], MAX_STRING_LEN, "0 (at least one root)");
                 result->num_roots_found = 1;
            }
        }
    }
    return RN_SUCCESS;
}