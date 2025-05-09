#include "arithmetic_progression_utils.h"
#include <stdexcept> // For std::invalid_argument
#include <algorithm> // For std::vector operations if needed
#include <vector>

namespace michu_fr {
namespace progressions {

APResult calculateAPTermAndSum(double a, double d, int n) {
    if (n <= 0) {
        throw std::invalid_argument("Number of terms (n) must be a positive integer.");
    }
    double nth_term = a + (n - 1) * d;
    double sum_n_terms = (static_cast<double>(n) / 2.0) * (2 * a + (n - 1) * d);
    return APResult(nth_term, sum_n_terms);
}

double calculateNthTermFromLastAP(double l, double d, int n) {
    if (n <= 0) {
        throw std::invalid_argument("Term number from end (n) must be a positive integer.");
    }
    return l - (n - 1) * d;
}

APMiddleTermResult findMiddleTermsAP(double a, double d, double last_term) {
    int num_of_terms;

    if (std::abs(d) < EPSILON) { // Common difference is zero
        if (std::abs(a - last_term) < EPSILON) {
            num_of_terms = 1; // Constant sequence, defined by a and last_term being equal
        } else {
            throw std::invalid_argument("Invalid progression: d is 0 but first and last terms differ.");
        }
    } else { // Common difference is non-zero
        if ((last_term - a) / d < -EPSILON && std::abs(last_term - a) > EPSILON) { // last_term < a with d>0 or last_term > a with d<0
             throw std::invalid_argument("Last term is not reachable from the first term with the given common difference direction.");
        }
        double n_float = (last_term - a) / d + 1.0;

        if (n_float < (1.0 - EPSILON)) {
            throw std::invalid_argument("Invalid progression parameters leading to non-positive or non-integer number of terms.");
        }
        if (std::abs(n_float - std::round(n_float)) > EPSILON) {
            throw std::invalid_argument("The provided last term is not part of the arithmetic progression defined by 'a' and 'd' (non-integer number of terms).");
        }
        num_of_terms = static_cast<int>(std::round(n_float));
        if (num_of_terms <= 0) { // Should be caught above, but as a safeguard
             throw std::invalid_argument("Invalid progression parameters leading to non-positive number of terms after rounding.");
        }
    }

    std::vector<int> middle_indices;
    std::vector<double> middle_values;

    if (num_of_terms % 2 == 1) { // Odd number of terms
        int middle_index = (num_of_terms + 1) / 2;
        double middle_term_value = a + (middle_index - 1) * d;
        middle_indices.push_back(middle_index);
        middle_values.push_back(middle_term_value);
    } else { // Even number of terms
        int middle_index1 = num_of_terms / 2;
        int middle_index2 = num_of_terms / 2 + 1;
        double middle_term1_value = a + (middle_index1 - 1) * d;
        double middle_term2_value = a + (middle_index2 - 1) * d;
        middle_indices.push_back(middle_index1);
        middle_indices.push_back(middle_index2);
        middle_values.push_back(middle_term1_value);
        middle_values.push_back(middle_term2_value);
    }
    return APMiddleTermResult(num_of_terms, middle_indices, middle_values);
}

} // namespace progressions
} // namespace michu_fr