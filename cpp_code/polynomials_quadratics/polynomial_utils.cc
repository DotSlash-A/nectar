#include "polynomial_utils.h"
#include <stdexcept>
#include <algorithm> // For std::sort, std::remove_if
#include <set>       // For unique rational roots

namespace michu_fr {
namespace polynomials_quadratics {

// Helper to get divisors, used in findRationalRoots
std::vector<long long> getDivisorsInternal(long long n_abs) {
    std::set<long long> divisors_set;
    if (n_abs == 0) return {0LL}; // Should be handled before calling
    for (long long i = 1; i * i <= n_abs; ++i) {
        if (n_abs % i == 0) {
            divisors_set.insert(i);
            divisors_set.insert(n_abs / i);
        }
    }
    return std::vector<long long>(divisors_set.begin(), divisors_set.end());
}


std::string formatPolynomialToString(const std::vector<double>& coeffs_in, const std::string& varSymbol) {
    if (coeffs_in.empty()) {
        return "0";
    }

    std::vector<double> coeffs = coeffs_in; // Make a mutable copy

    // Remove leading zeros for correct degree, unless it's just [0.0]
    auto first_non_zero_it = std::find_if(coeffs.begin(), coeffs.end(),
                                          [](double c){ return std::abs(c) > EPSILON; });
    if (first_non_zero_it == coeffs.end()) { // All zeros
        return "0";
    }
    // If there are leading zeros but not all are zero
    if (first_non_zero_it != coeffs.begin() && coeffs.size() > 1) {
        coeffs.erase(coeffs.begin(), first_non_zero_it);
    }
    // if coeffs was like [0,0,0] and became empty, or [0,5] became [5] this is fine.
    // if coeffs was [0] it remains [0] and will be handled below.


    std::ostringstream oss;
    int degree = static_cast<int>(coeffs.size()) - 1;

    for (int i = 0; i <= degree; ++i) {
        double coeff_val = coeffs[i];
        int power = degree - i;

        if (std::abs(coeff_val) < EPSILON) { // Skip zero terms
            if (degree == 0 && i == 0) { // Special case: polynomial is just "0"
                 oss << "0";
                 break;
            }
            continue;
        }

        // Sign
        if (oss.tellp() > 0) { // Not the first term written
            if (coeff_val > 0) {
                oss << " + ";
            } else {
                oss << " - ";
            }
        } else { // First term written
            if (coeff_val < 0) {
                oss << "-";
            }
        }

        double abs_coeff = std::abs(coeff_val);

        // Coefficient value
        bool coeff_is_one = std::abs(abs_coeff - 1.0) < EPSILON;
        if (!coeff_is_one || power == 0) { // Print 1 only if it's the constant term
            // Check if it's an integer
            if (std::abs(abs_coeff - static_cast<long long>(abs_coeff)) < EPSILON) {
                oss << static_cast<long long>(abs_coeff);
            } else {
                oss << std::fixed << std::setprecision(4) << abs_coeff; // Adjust precision
            }
        }
        // else: if coeff is 1 and power > 0, don't print "1" (e.g., x^2 instead of 1x^2)

        // Variable and power
        if (power > 0) {
            if (!coeff_is_one && power == 0 && oss.tellp() > 0 && oss.str().back() != ' ') {
                 // Space between coeff and var, e.g. "2 x" vs "2x" - usually no space
            }
            oss << varSymbol;
            if (power > 1) {
                oss << "^" << power;
            }
        }
    }

    std::string result = oss.str();
    return result.empty() ? "0" : result; // Handle case where all coeffs were zero after processing
}


double evaluatePolynomial(const std::vector<double>& coeffs, double xVal) {
    if (coeffs.empty()) return 0.0;
    double result = 0.0;
    for (double coeff : coeffs) {
        result = result * xVal + coeff;
    }
    return result;
}

PolynomialDivisionResult polynomialDivision(const std::vector<double>& dividend_coeffs_in, const std::vector<double>& divisor_coeffs_in) {
    if (divisor_coeffs_in.empty() || std::abs(divisor_coeffs_in[0]) < EPSILON) {
        throw std::invalid_argument("Divisor cannot be zero or have a zero leading coefficient.");
    }
    if (dividend_coeffs_in.empty()) {
        std::vector<double> zero_poly = {0.0};
        std::string zero_str = formatPolynomialToString(zero_poly);
        return PolynomialDivisionResult(zero_poly, zero_poly, zero_str, zero_str, "0 = (...) * 0 + 0");
    }

    std::vector<double> dividend_coeffs = dividend_coeffs_in;
    std::vector<double> divisor_coeffs = divisor_coeffs_in;

    // Normalize by removing leading zeros
    auto remove_leading_zeros = [](std::vector<double>& p_coeffs) {
        size_t first_nz = 0;
        while(first_nz < p_coeffs.size() -1 && std::abs(p_coeffs[first_nz]) < EPSILON) {
            first_nz++;
        }
        if (first_nz > 0) {
            p_coeffs.erase(p_coeffs.begin(), p_coeffs.begin() + first_nz);
        }
        if (p_coeffs.empty()) p_coeffs.push_back(0.0); // Ensure not empty if all were zero
    };
    remove_leading_zeros(dividend_coeffs);
    remove_leading_zeros(divisor_coeffs);
    if (std::abs(divisor_coeffs[0]) < EPSILON) { // check again after normalization
         throw std::invalid_argument("Divisor became zero after normalization.");
    }


    int dividend_degree = static_cast<int>(dividend_coeffs.size()) - 1;
    int divisor_degree = static_cast<int>(divisor_coeffs.size()) - 1;

    std::string dividend_str_orig = formatPolynomialToString(dividend_coeffs_in);
    std::string divisor_str_orig = formatPolynomialToString(divisor_coeffs_in);


    if (dividend_degree < divisor_degree) {
        std::string eq_s = "(" + dividend_str_orig + ") = (" + divisor_str_orig + ") * (0) + (" + dividend_str_orig + ")";
        return PolynomialDivisionResult({0.0}, dividend_coeffs, "0", dividend_str_orig, eq_s);
    }

    std::vector<double> quotient(dividend_degree - divisor_degree + 1, 0.0);
    std::vector<double> remainder = dividend_coeffs; // Work on a copy

    double lead_divisor_coeff = divisor_coeffs[0];

    for (int i = 0; i <= (dividend_degree - divisor_degree); ++i) {
        double current_lead_remainder_coeff = remainder[i];
        double current_quotient_coeff = current_lead_remainder_coeff / lead_divisor_coeff;
        quotient[i] = current_quotient_coeff;

        for (size_t j = 0; j < divisor_coeffs.size(); ++j) {
            if ((i + j) < remainder.size()) {
                 remainder[i + j] -= current_quotient_coeff * divisor_coeffs[j];
            }
        }
    }

    // Extract the actual remainder part
    std::vector<double> final_remainder_coeffs;
    // The remainder starts after the part that was "consumed" by the quotient terms
    // Its degree should be less than divisor_degree.
    // The 'remainder' vector after loop has leading parts zeroed out.
    // Remainder terms start from index (dividend_degree - divisor_degree + 1)
    // or simply, the last 'divisor_degree' terms (or fewer if degree reduced).
    
    int remainder_start_index = dividend_coeffs.size() - divisor_degree; // Theoretical start if full degree
    if (remainder_start_index < 0) remainder_start_index = 0;

    for(size_t k = static_cast<size_t>(quotient.size()); k < remainder.size(); ++k) {
        final_remainder_coeffs.push_back(remainder[k]);
    }
    remove_leading_zeros(final_remainder_coeffs); // Clean up again
    if (final_remainder_coeffs.empty() || (final_remainder_coeffs.size()==1 && std::abs(final_remainder_coeffs[0]) < EPSILON)) {
        final_remainder_coeffs = {0.0};
    }
    
    std::string quotient_str = formatPolynomialToString(quotient);
    std::string remainder_str = formatPolynomialToString(final_remainder_coeffs);
    std::string equation_str = "(" + dividend_str_orig + ") = (" + divisor_str_orig + ") * (" + quotient_str + ") + (" + remainder_str + ")";

    return PolynomialDivisionResult(quotient, final_remainder_coeffs, quotient_str, remainder_str, equation_str);
}


std::vector<double> findRationalRoots(const std::vector<double>& coeffs_in) {
    if (coeffs_in.empty()) return {};
    
    std::vector<double> coeffs = coeffs_in;
    // Remove leading zeros
    size_t first_nz = 0;
    while(first_nz < coeffs.size() && std::abs(coeffs[first_nz]) < EPSILON) first_nz++;
    if (first_nz == coeffs.size()) return {}; // All zeros
    if (first_nz > 0) coeffs.erase(coeffs.begin(), coeffs.begin() + first_nz);

    if (coeffs.size() == 1) return {}; // Constant non-zero polynomial has no roots

    // RRT works with integer coefficients. Assume input doubles are close to integers.
    std::vector<long long> int_coeffs(coeffs.size());
    for (size_t i = 0; i < coeffs.size(); ++i) {
        int_coeffs[i] = static_cast<long long>(std::round(coeffs[i]));
        if (std::abs(coeffs[i] - int_coeffs[i]) > EPSILON) {
            // Could throw error or issue warning if coefficients are not very close to integers
             // For simplicity here, we proceed with rounded values.
        }
    }

    long long a0 = int_coeffs.back(); // Constant term
    long long an = int_coeffs.front(); // Leading coefficient

    if (an == 0) { // Should have been caught by leading zero removal
        throw std::runtime_error("Leading coefficient became zero after rounding in findRationalRoots.");
    }

    std::set<double> rational_roots_set;

    if (a0 == 0) { // x=0 is a root
        rational_roots_set.insert(0.0);
        if (coeffs.size() > 1) {
            std::vector<double> reduced_coeffs(coeffs.begin(), coeffs.end() - 1);
            if (!reduced_coeffs.empty()){
                 auto sub_roots = findRationalRoots(reduced_coeffs);
                 rational_roots_set.insert(sub_roots.begin(), sub_roots.end());
            }
        }
        std::vector<double> result(rational_roots_set.begin(), rational_roots_set.end());
        std::sort(result.begin(), result.end());
        return result;
    }

    std::vector<long long> p_divs = getDivisorsInternal(std::abs(a0));
    std::vector<long long> q_divs = getDivisorsInternal(std::abs(an));

    for (long long p : p_divs) {
        for (long long q : q_divs) {
            if (q == 0) continue;
            double root1 = static_cast<double>(p) / q;
            double root2 = -static_cast<double>(p) / q;

            if (std::abs(evaluatePolynomial(coeffs, root1)) < EPSILON) {
                rational_roots_set.insert(root1);
            }
            if (std::abs(evaluatePolynomial(coeffs, root2)) < EPSILON) {
                rational_roots_set.insert(root2);
            }
        }
    }
    std::vector<double> result(rational_roots_set.begin(), rational_roots_set.end());
    std::sort(result.begin(), result.end());
    return result;
}

RootsCoefficientsRelation relationRootsCoefficientsQuadratic(const std::vector<double>& coeffs) {
    if (coeffs.size() != 3) {
        throw std::invalid_argument("Quadratic polynomial must have 3 coefficients.");
    }
    double a = coeffs[0], b = coeffs[1], c = coeffs[2];
    if (std::abs(a) < EPSILON) {
        throw std::invalid_argument("Leading coefficient 'a' cannot be zero for quadratic.");
    }
    std::map<std::string, double> relations;
    relations["sum_of_roots"] = -b / a;
    relations["product_of_roots"] = c / a;
    return RootsCoefficientsRelation(formatPolynomialToString(coeffs), 2, relations,
                                     "For ax^2+bx+c=0: Sum = -b/a, Product = c/a");
}

RootsCoefficientsRelation relationRootsCoefficientsCubic(const std::vector<double>& coeffs) {
    if (coeffs.size() != 4) {
        throw std::invalid_argument("Cubic polynomial must have 4 coefficients.");
    }
    double a = coeffs[0], b = coeffs[1], c = coeffs[2], d_coeff = coeffs[3];
    if (std::abs(a) < EPSILON) {
        throw std::invalid_argument("Leading coefficient 'a' cannot be zero for cubic.");
    }
    std::map<std::string, double> relations;
    relations["sum_of_roots"] = -b / a;
    relations["sum_prod_pairwise"] = c / a;
    relations["product_of_roots"] = -d_coeff / a;
    return RootsCoefficientsRelation(formatPolynomialToString(coeffs), 3, relations,
                                     "For ax^3+bx^2+cx+d=0: Sum = -b/a, Sum_pair = c/a, Product = -d/a");
}

std::vector<double> multiplyPolynomials(const std::vector<double>& poly1_coeffs, const std::vector<double>& poly2_coeffs) {
    if (poly1_coeffs.empty() || poly2_coeffs.empty()) return {0.0};

    int deg1 = static_cast<int>(poly1_coeffs.size()) - 1;
    int deg2 = static_cast<int>(poly2_coeffs.size()) - 1;
    std::vector<double> result_coeffs(deg1 + deg2 + 1, 0.0);

    for (int i = 0; i <= deg1; ++i) {
        for (int j = 0; j <= deg2; ++j) {
            result_coeffs[i + j] += poly1_coeffs[i] * poly2_coeffs[j];
        }
    }
    return result_coeffs;
}

FormedPolynomial formPolynomialFromRoots(const std::vector<double>& roots, double leading_coefficient, const std::string& var_symbol) {
    if (roots.empty()) {
        std::vector<double> c = {leading_coefficient};
        return FormedPolynomial(c, formatPolynomialToString(c, var_symbol), roots, leading_coefficient);
    }

    std::vector<double> current_coeffs = {leading_coefficient};
    for (double root : roots) {
        // Factor (x - root) -> {1.0, -root}
        std::vector<double> factor_coeffs = {1.0, -root};
        current_coeffs = multiplyPolynomials(current_coeffs, factor_coeffs);
    }
    return FormedPolynomial(current_coeffs, formatPolynomialToString(current_coeffs, var_symbol),
                            roots, leading_coefficient);
}


} // namespace polynomials_quadratics
} // namespace michu_fr