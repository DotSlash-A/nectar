#include "real_numbers_utils.h"
#include <stdexcept> // For std::invalid_argument, std::runtime_error, std::overflow_error
#include <numeric>   // For std::gcd (C++17 and later)
#include <cmath>     // For std::abs, std::sqrt, std::pow, NAN
#include <algorithm> // For std::max, std::min
#include <sstream>   // For std::ostringstream
#include <iomanip>   // For std::fixed, std::setprecision

namespace michu_fr {
namespace real_numbers {

EuclidLemmaResult euclidsDivisionLemma(int dividend, int divisor) {
    if (divisor == 0) {
        throw std::invalid_argument("Divisor cannot be zero.");
    }
    int quotient = dividend / divisor;
    int remainder = dividend % divisor;
    
    // Ensure remainder is non-negative and less than |divisor|
    // C++ % operator can yield negative remainder if dividend is negative
    if (remainder < 0) {
        if (divisor > 0) {
            remainder += divisor;
            quotient--;
        } else { // divisor < 0
            remainder -= divisor; // Add abs(divisor)
            quotient++;
        }
    }
    
    std::ostringstream oss;
    oss << dividend << " = " << divisor << " * " << quotient << " + " << remainder;
    return EuclidLemmaResult(dividend, divisor, quotient, remainder, oss.str());
}

HCFResult euclidsAlgorithmHCF(int n1, int n2) {
    if (n1 == 0 && n2 == 0) {
        // std::gcd(0,0) is 0 by standard, but problem context might prefer undefined
        throw std::invalid_argument("HCF(0, 0) is typically undefined or 0. For this context, provide at least one non-zero number.");
    }
    return HCFResult(n1, n2, std::gcd(n1, n2));
}

PrimeFactorizationResult getPrimeFactorization(int n) {
    if (n <= 1) {
        throw std::invalid_argument("Number must be greater than 1 for prime factorization.");
    }

    std::map<int, int> factors_map;
    int num = n;

    while (num % 2 == 0) {
        factors_map[2]++;
        num /= 2;
    }

    for (int i = 3; i * i <= num; i += 2) {
        while (num % i == 0) {
            factors_map[i]++;
            num /= i;
        }
    }

    if (num > 1) {
        factors_map[num]++;
    }
    return PrimeFactorizationResult(n, factors_map);
}

int hcfFromPrimeFactorization(const std::map<int, int>& factors1, const std::map<int, int>& factors2) {
    int hcf_val = 1;
    for (const auto& pair1 : factors1) {
        int prime = pair1.first;
        int power1 = pair1.second;
        auto it2 = factors2.find(prime);
        if (it2 != factors2.end()) {
            int power2 = it2->second;
            int common_power = std::min(power1, power2);
            for (int i = 0; i < common_power; ++i) {
                // Check for overflow before multiplication, though hcf is usually small
                if (prime > 0 && hcf_val > std::numeric_limits<int>::max() / prime) {
                    throw std::overflow_error("HCF calculation resulted in overflow.");
                }
                hcf_val *= prime;
            }
        }
    }
    return hcf_val;
}

long long lcmFromPrimeFactorization(const std::map<int, int>& factors1, const std::map<int, int>& factors2) {
    long long lcm_val = 1LL;
    std::map<int, int> max_powers = factors1;

    for (const auto& pair2 : factors2) {
        int prime = pair2.first;
        int power2 = pair2.second;
        max_powers[prime] = std::max(max_powers.count(prime) ? max_powers[prime] : 0, power2);
    }

    for (const auto& pair_max : max_powers) {
        int prime = pair_max.first;
        int max_power = pair_max.second;
        for (int i = 0; i < max_power; ++i) {
            if (prime > 0 && lcm_val > std::numeric_limits<long long>::max() / prime) {
                 throw std::overflow_error("LCM calculation resulted in overflow during prime power multiplication.");
            }
            lcm_val *= prime;
        }
    }
    return lcm_val;
}


long long calculateLCM(int n1, int n2) {
    if (n1 == 0 && n2 == 0) {
         throw std::invalid_argument("LCM(0,0) is undefined. At least one number must be non-zero.");
    }
    if (n1 == 0 || n2 == 0) {
        return 0LL; 
    }
    int hcf_val = std::gcd(n1, n2); // std::gcd handles 0 correctly.
    if (hcf_val == 0) { // Should only happen if n1=0 and n2=0, caught above.
        return 0LL; // Or throw error, but gcd(0,0)=0, so this means n1 and n2 were 0.
    }
    
    long long num1_ll = n1;
    long long num2_ll = n2;

    // (a / gcd) * b to prevent intermediate overflow of a*b
    long long term1 = num1_ll / hcf_val; 
    if (num2_ll != 0 && std::abs(term1) > std::numeric_limits<long long>::max() / std::abs(num2_ll) ) {
        throw std::overflow_error("LCM calculation: (num1/hcf) * num2 would overflow.");
    }
    return std::abs(term1 * num2_ll);
}

HCFAndLCMResult getHCFAndLCMDetails(int num1, int num2) {
    if (num1 <= 0 || num2 <= 0) { // Adjusted to allow 1, but typically for >1
        throw std::invalid_argument("Numbers must be positive for this detailed HCF/LCM via prime factorization.");
    }
    
    PrimeFactorizationResult pf1_res = (num1 > 1) ? getPrimeFactorization(num1) : PrimeFactorizationResult(num1, {});
    PrimeFactorizationResult pf2_res = (num2 > 1) ? getPrimeFactorization(num2) : PrimeFactorizationResult(num2, {});
    
    int hcf_val = std::gcd(num1, num2);
    long long lcm_val = calculateLCM(num1, num2);
    
    return HCFAndLCMResult(num1, num2, pf1_res.factors, pf2_res.factors, hcf_val, lcm_val);
}

bool isPrimeBasic(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i = i + 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

bool isNumberPerfectSquare(int n) {
    if (n < 0) throw std::invalid_argument("Input number cannot be negative for perfect square check.");
    if (n == 0) return true;
    int sqrt_n_int = static_cast<int>(std::sqrt(static_cast<double>(n))); // Cast n to double for sqrt
    return sqrt_n_int * sqrt_n_int == n;
}

IrrationalityCheckResult checkSqrtIrrationality(int number) {
    std::string form = "sqrt(" + std::to_string(number) + ")";
    std::string reason_str;
    bool is_irrational_flag;

    if (number < 0) {
        is_irrational_flag = false; 
        reason_str = "sqrt(" + std::to_string(number) + ") is a complex number, not a real irrational number.";
    } else if (isNumberPerfectSquare(number)) {
        is_irrational_flag = false;
        reason_str = "sqrt(" + std::to_string(number) + ") = " + std::to_string(static_cast<int>(std::sqrt(static_cast<double>(number)))) +
                        ", which is rational (an integer).";
    } else {
        is_irrational_flag = true;
        if (isPrimeBasic(number)) {
            reason_str = std::to_string(number) + " is a prime number. The square root of a prime number is irrational.";
        } else {
            reason_str = std::to_string(number) + " is not a perfect square. The square root of a non-perfect square integer is irrational.";
        }
    }
    return IrrationalityCheckResult(form, is_irrational_flag, reason_str);
}

DecimalExpansionResult getDecimalExpansionType(int numerator, int denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("Denominator cannot be zero.");
    }

    std::string fraction_str_val = std::to_string(numerator) + "/" + std::to_string(denominator);
    std::string expansion_type_val;
    std::string reason_val;

    int common = std::gcd(std::abs(numerator), std::abs(denominator));
    int simplified_den = std::abs(denominator) / common;

    if (simplified_den == 0) { // Should not happen if HCF is correct & original den != 0
        expansion_type_val = "undefined";
        reason_val = "Denominator became zero after simplification.";
    } else if (simplified_den == 1) {
        expansion_type_val = "terminating";
        reason_val = "The fraction simplifies to an integer (" + std::to_string(numerator / common) + "). Denominator is 1.";
    } else {
        int temp_den = simplified_den;
        std::ostringstream factors_oss;
        bool first_factor_written = false;

        auto append_factor = [&](int prime, int count) {
            if (count > 0) {
                if (first_factor_written) factors_oss << " * ";
                factors_oss << prime;
                if (count > 1) factors_oss << "^" << count;
                first_factor_written = true;
            }
        };
        
        int count2 = 0;
        while (temp_den > 0 && temp_den % 2 == 0) { temp_den /= 2; count2++; }
        append_factor(2, count2);

        int count5 = 0;
        while (temp_den > 0 && temp_den % 5 == 0) { temp_den /= 5; count5++; }
        append_factor(5, count5);
        
        bool only_2_and_5 = true;
        int original_temp_den_for_loop = temp_den; // Store before modification by loop
        for (int i = 3; i * i <= original_temp_den_for_loop; i += 2) {
            if (temp_den % i == 0) {
                int count_other = 0;
                while (temp_den % i == 0) {
                    temp_den /= i;
                    count_other++;
                }
                only_2_and_5 = false;
                append_factor(i, count_other);
            }
        }
        if (temp_den > 1) { // Remaining temp_den is a prime factor
            if (temp_den != 2 && temp_den != 5) { only_2_and_5 = false; } // Already factored out
            append_factor(temp_den, 1);
        }
        
        std::string den_factors_str = factors_oss.str();
        if (den_factors_str.empty() && simplified_den == 1) den_factors_str = "1";
        else if (den_factors_str.empty()) den_factors_str = std::to_string(simplified_den);

        if (only_2_and_5) {
            expansion_type_val = "terminating";
            reason_val = "Simplified denominator (" + std::to_string(simplified_den) + ") has prime factors: " +
                            den_factors_str + " (only 2s and/or 5s).";
        } else {
            expansion_type_val = "non-terminating recurring";
            reason_val = "Simplified denominator (" + std::to_string(simplified_den) + ") has prime factors: " +
                            den_factors_str + " (includes primes other than 2 and 5).";
        }
    }
    return DecimalExpansionResult(numerator, denominator, fraction_str_val, expansion_type_val, reason_val);
}


PolynomialAnalysisResult analyzePolynomial(const std::vector<double>& coeffs_in) {
    std::vector<std::string> roots_s;
    std::string sum_v_s = "N/A", prod_v_s = "N/A", notes_s;
    int degree_val = -1;

    if (coeffs_in.empty()) {
        notes_s = "No coefficients provided.";
        return PolynomialAnalysisResult(coeffs_in, degree_val, roots_s, sum_v_s, prod_v_s, notes_s);
    }

    // Find the actual first non-zero coefficient to determine true degree
    size_t first_non_zero_idx = 0;
    while (first_non_zero_idx < coeffs_in.size() && std::abs(coeffs_in[first_non_zero_idx]) < 1e-9) {
        first_non_zero_idx++;
    }

    if (first_non_zero_idx == coeffs_in.size()) { // All coefficients are effectively zero
        degree_val = 0; 
        notes_s = "All coefficients are zero (0 = 0 polynomial).";
        sum_v_s = "N/A (0=0)"; prod_v_s = "N/A (0=0)";
        return PolynomialAnalysisResult(coeffs_in, degree_val, roots_s, sum_v_s, prod_v_s, notes_s);
    }
    
    // Effective coefficients (highest power first)
    std::vector<double> effective_coeffs;
    for(size_t i = first_non_zero_idx; i < coeffs_in.size(); ++i) {
        effective_coeffs.push_back(coeffs_in[i]);
    }

    degree_val = static_cast<int>(effective_coeffs.size()) - 1;
    double leading_coeff = effective_coeffs[0];

    if (degree_val == 0) {
        notes_s = "Constant non-zero polynomial.";
    } else { // degree_val >= 1
        // Vieta's formulas
        if (effective_coeffs.size() > 1) { // has at least ax+b form
            sum_v_s = std::to_string(-effective_coeffs[1] / leading_coeff);
        } else { // Monomial ax^n, n>=1
            sum_v_s = "0"; // All roots are 0
        }
        prod_v_s = std::to_string(std::pow(-1.0, degree_val) * effective_coeffs.back() / leading_coeff);

        // Roots
        if (degree_val == 1) { // ax + b = 0 => x = -b/a
            notes_s = "Root for linear polynomial.";
            roots_s.push_back(std::to_string(-effective_coeffs[1] / leading_coeff));
        } else if (degree_val == 2) { // ax^2 + bx + c = 0
            notes_s = "Roots for quadratic polynomial.";
            double a = effective_coeffs[0];
            double b = effective_coeffs[1];
            double c = effective_coeffs[2];
            double discriminant = b * b - 4 * a * c;

            if (discriminant > 1e-9) {
                roots_s.push_back(std::to_string((-b + std::sqrt(discriminant)) / (2 * a)));
                roots_s.push_back(std::to_string((-b - std::sqrt(discriminant)) / (2 * a)));
            } else if (std::abs(discriminant) < 1e-9) {
                roots_s.push_back(std::to_string(-b / (2 * a)));
            } else { // Complex roots
                std::ostringstream r1, r2;
                r1 << std::fixed << std::setprecision(4) << (-b / (2 * a)) << " + " << (std::sqrt(-discriminant) / (2 * a)) << "i";
                r2 << std::fixed << std::setprecision(4) << (-b / (2 * a)) << " - " << (std::sqrt(-discriminant) / (2 * a)) << "i";
                roots_s.push_back(r1.str());
                roots_s.push_back(r2.str());
            }
        } else {
            notes_s = "Root finding for degree > 2 not implemented here.";
            if (std::abs(effective_coeffs.back()) < 1e-9) { // If constant term is zero
                 roots_s.push_back("0 (at least one root, others not found)");
            }
        }
    }
    return PolynomialAnalysisResult(coeffs_in, degree_val, roots_s, sum_v_s, prod_v_s, notes_s);
}

} // namespace real_numbers
} // namespace michu_fr