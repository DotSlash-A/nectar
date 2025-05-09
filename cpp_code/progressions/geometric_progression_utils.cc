#include "geometric_progression_utils.h"
#include <stdexcept>   // For std::invalid_argument, std::runtime_error
#include <algorithm>   // For std::vector operations if needed
#include <vector>

namespace michu_fr {
namespace progressions {

GPResult calculateGPTermAndSum(double a, double r, int n) {
    if (n <= 0) {
        throw std::invalid_argument("Number of terms (n) must be a positive integer.");
    }
    if (std::abs(a) < EPSILON && std::abs(r) < EPSILON && n > 1) {
        throw std::invalid_argument("Ambiguous case: a=0, r=0, n>1. Sequence is 0, 0,... but formulas can lead to 0^0.");
    }
    if (std::abs(a) < EPSILON) {
        return GPResult(0.0, 0.0);
    }

    double nth_term = a * std::pow(r, n - 1);
    if (std::isinf(nth_term) || std::isnan(nth_term)) {
        throw std::runtime_error("Calculation of GP nth term resulted in overflow or undefined value.");
    }

    double sum_n_terms;
    if (std::abs(r - 1.0) < EPSILON) {
        sum_n_terms = static_cast<double>(n) * a;
    } else {
        double r_pow_n = std::pow(r, n);
        if (std::isinf(r_pow_n) || std::isnan(r_pow_n)) {
             throw std::runtime_error("Calculation of r^n in GP sum resulted in overflow or undefined value.");
        }
        double numerator = a * (r_pow_n - 1.0);
        double denominator = r - 1.0;
        if (std::abs(denominator) < EPSILON * EPSILON) { // Should be caught by |r-1| check
             sum_n_terms = static_cast<double>(n) * a; // Treat as r=1
        } else {
            sum_n_terms = numerator / denominator;
        }
    }
    if (std::isinf(sum_n_terms) || std::isnan(sum_n_terms)) {
        throw std::runtime_error("Calculation of GP sum resulted in overflow or undefined value.");
    }
    return GPResult(nth_term, sum_n_terms);
}

double calculateGPSumToInfinity(double a, double r) {
    if (std::abs(r) >= 1.0 - EPSILON) { // Check |r| >= 1
        throw std::invalid_argument("Sum to infinity exists only if the absolute value of the common ratio |r| is less than 1.");
    }
    double denominator = 1.0 - r;
    if (std::abs(denominator) < EPSILON * EPSILON) {
        throw std::runtime_error("Denominator (1-r) for sum to infinity is too close to zero.");
    }
    double sum_inf = a / denominator;
    if (std::isinf(sum_inf) || std::isnan(sum_inf)) {
        throw std::runtime_error("Calculation of sum to infinity resulted in overflow or undefined value.");
    }
    return sum_inf;
}

double calculateGeometricMean(double num1, double num2) {
    if (num1 < -EPSILON || num2 < -EPSILON) {
        throw std::invalid_argument("Geometric Mean is typically defined for non-negative numbers.");
    }
    if (std::abs(num1) < EPSILON || std::abs(num2) < EPSILON) {
        return 0.0;
    }
    return std::sqrt(num1 * num2);
}

GPInsertMeansResult insertGeometricMeans(double a, double b, int k) {
    if (k <= 0) {
        throw std::invalid_argument("Number of means to insert (k) must be a positive integer.");
    }

    if (std::abs(a) < EPSILON) {
        if (std::abs(b) < EPSILON) {
            std::vector<double> means(k, 0.0);
            return GPInsertMeansResult(0.0, means);
        } else {
            throw std::invalid_argument("Cannot insert geometric means starting from 0 to a non-zero number.");
        }
    }

    double ratio_power_k_plus_1 = b / a;
    int root_index = k + 1;

    if (ratio_power_k_plus_1 < -EPSILON && root_index % 2 == 0) {
        std::ostringstream err_msg;
        err_msg << "Cannot compute real geometric means: requires taking an even root (" << root_index
                << ") of a negative number (" << ratio_power_k_plus_1 << ").";
        throw std::invalid_argument(err_msg.str());
    }

    double r_val;
    if (std::abs(ratio_power_k_plus_1) < EPSILON) { // b is zero, a is non-zero
        r_val = 0.0;
    } else if (ratio_power_k_plus_1 < 0) { // Negative base, root_index must be odd
        r_val = -std::pow(std::abs(ratio_power_k_plus_1), 1.0 / static_cast<double>(root_index));
    } else { // Positive base
        r_val = std::pow(ratio_power_k_plus_1, 1.0 / static_cast<double>(root_index));
    }

    if (std::isinf(r_val) || std::isnan(r_val)) {
        throw std::runtime_error("Calculated common ratio is invalid (Infinite or NaN). Check input values.");
    }

    std::vector<double> means;
    means.reserve(k);
    double current_term = a;
    for (int i = 0; i < k; ++i) {
        current_term *= r_val;
        if (std::isinf(current_term) || std::isnan(current_term)) {
            std::ostringstream err_msg;
            err_msg << "Calculation of mean " << (i + 1) << " resulted in overflow or undefined value.";
            throw std::runtime_error(err_msg.str());
        }
        means.push_back(current_term);
    }
    return GPInsertMeansResult(r_val, means);
}

} // namespace progressions
} // namespace michu_fr