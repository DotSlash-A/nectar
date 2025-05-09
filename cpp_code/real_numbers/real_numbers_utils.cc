// cpp_code/real_numbers/real_numbers_utils.cc
#include "real_numbers_utils.h"
#include <stdexcept> // For std::invalid_argument, std::overflow_error
#include <numeric>   // For std::gcd in C++17 and later
#include <cmath>     // For std::sqrt, std::abs, std::pow
#include <algorithm> // For std::max, std::min
#include <sstream>   // For string formatting in results
#include <iomanip>   // For std::fixed, std::setprecision

// Helper for older C++ versions if std::gcd is not available (C++17+)
// Or ensure your compiler is set to C++17 or newer.
// For simplicity, I'll assume C++17 std::gcd. If not, you'd implement it:
/*
int custom_gcd(int a, int b) {
    return b == 0 ? a : custom_gcd(b, a % b);
}
*/

namespace RealNumbers {

EuclidLemmaResult euclidsDivisionLemma(int dividend, int divisor) {
    if (divisor == 0) {
        throw std::invalid_argument("Divisor cannot be zero.");
    }
    EuclidLemmaResult result;
    result.dividend = dividend;
    result.divisor = divisor;
    result.quotient = dividend / divisor;
    result.remainder = dividend % divisor;

    // Ensure remainder is non-negative if divisor is negative (C++ standard behavior might vary for %)
    // For a = bq + r, 0 <= r < |b|
    if (result.remainder < 0) {
        if (divisor > 0) { // Should not happen if dividend is positive
            // This case is tricky with integer division and % with negative numbers.
            // Standard C++: a/b rounds towards zero. a % b has same sign as a.
            // We want: dividend = divisor * quotient + remainder, with 0 <= remainder < abs(divisor)
            // If remainder is negative, adjust:
            // Example: -7 / 3 = -2, rem = -1. Want: -7 = 3*(-3) + 2
            // Example: -7 / -3 = 2, rem = -1. Want: -7 = (-3)*3 + 2
        } else { // divisor < 0
             result.remainder -= divisor; // Add |divisor|
             result.quotient++;
        }
    }
     // A more robust way to ensure 0 <= r < |b| for a = bq+r
    int r = dividend % divisor;
    int q = dividend / divisor;
    if (r < 0) {
        if (divisor > 0) { // e.g. -5 % 3 = -2. We want -5 = 3*(-2) + 1
            r += divisor;
            q--;
        } else { // e.g. -5 % -3 = -2. We want -5 = (-3)*2 + 1
            r -= divisor; // r = r + abs(divisor)
            q++; // q must be adjusted to compensate.
                 // -5 = (-3)*q + r => -5 - r = -3q => q = (5+r)/3
                 // This part is tricky. Let's assume positive divisors for simplicity of lemma presentation or rely on std::div.
        }
    }
    // For positive divisors, standard C++ % is fine for 0 <= r < divisor
    // For general case, it's often easier to work with absolute values for Euclidean algorithm.
    // The lemma itself a = bq+r with 0 <= r < |b| can be constructed.
    // Using std::div for clarity with negative numbers:
    std::ldiv_t div_result = std::ldiv(dividend, divisor);
    result.quotient = div_result.quot;
    result.remainder = div_result.rem;
    if (result.remainder < 0) { // Ensure 0 <= remainder < |divisor|
        result.remainder += std::abs(divisor);
        result.quotient = (dividend - result.remainder) / divisor; // Recalculate quotient
    }


    std::ostringstream oss;
    oss << result.dividend << " = " << result.divisor << " * " << result.quotient << " + " << result.remainder;
    result.equation = oss.str();
    return result;
}

HCFResult euclidsAlgorithmHCF(int n1, int n2) {
    if (n1 == 0 && n2 == 0) {
        throw std::invalid_argument("HCF(0, 0) is undefined. At least one number must be non-zero.");
    }
    // std::gcd handles signs and zero inputs correctly (gcd(a,0)=|a|)
    HCFResult result;
    result.num1 = n1;
    result.num2 = n2;
    result.hcf = std::gcd(n1, n2); // Requires <numeric> and C++17
    // If not C++17, implement Euclidean algorithm manually:
    /*
    int a = std::abs(n1);
    int b = std::abs(n2);
    if (a == 0) result.hcf = b;
    else if (b == 0) result.hcf = a;
    else {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        result.hcf = a;
    }
    */
    return result;
}

PrimeFactorizationResult getPrimeFactorization(int n) {
    if (n <= 1) {
        throw std::invalid_argument("Number must be greater than 1 for prime factorization.");
    }
    PrimeFactorizationResult result;
    result.number = n;
    int num = n;

    while (num % 2 == 0) {
        result.factors[2]++;
        num /= 2;
    }
    for (int i = 3; i * i <= num; i += 2) {
        while (num % i == 0) {
            result.factors[i]++;
            num /= i;
        }
    }
    if (num > 1) {
        result.factors[num]++;
    }
    return result;
}

int hcfFromPrimeFactorization(const std::map<int, int>& factors1, const std::map<int, int>& factors2) {
    int hcf = 1;
    for (const auto& pair1 : factors1) {
        int prime = pair1.first;
        int power1 = pair1.second;
        auto it = factors2.find(prime);
        if (it != factors2.end()) {
            int power2 = it->second;
            int commonPower = std::min(power1, power2);
            for (int i = 0; i < commonPower; ++i) {
                hcf *= prime;
            }
        }
    }
    return hcf;
}

long long lcmFromPrimeFactorization(const std::map<int, int>& factors1, const std::map<int, int>& factors2) {
    long long lcm = 1LL;
    std::map<int, int> allPrimesMaxPower = factors1;

    for (const auto& pair2 : factors2) {
        int prime = pair2.first;
        int power2 = pair2.second;
        allPrimesMaxPower[prime] = std::max(allPrimesMaxPower[prime], power2); // operator[] creates if not exists (with 0)
    }

    for (const auto& pair : allPrimesMaxPower) {
        for (int i = 0; i < pair.second; ++i) {
            if (__builtin_mul_overflow(lcm, pair.first, &lcm)) { // GCC/Clang intrinsic
                 throw std::overflow_error("LCM calculation resulted in overflow.");
            }
            // Without intrinsic:
            // if (pair.first == 0) { /* handle error or special case */ }
            // if (lcm > LLONG_MAX / pair.first) { throw std::overflow_error("LCM overflow"); }
            // lcm *= pair.first;
        }
    }
    return lcm;
}

long long calculateLCM(int n1, int n2) {
    if (n1 == 0 || n2 == 0) {
        return 0; // Conventionally LCM(a,0) = 0
    }
    int hcf = euclidsAlgorithmHCF(n1, n2).hcf;
    if (hcf == 0) { // Should only happen if n1=0, n2=0, caught by above
        throw std::logic_error("HCF is zero, implies both inputs were zero, but LCM(0,0) is undefined.");
    }
    // LCM(a,b) = (|a*b|) / HCF(a,b)
    // Use long long for product to prevent overflow
    long long prod = static_cast<long long>(std::abs(n1)) * std::abs(n2);
    return prod / hcf;
}

HCFAndLCMResult getHCFAndLCMDetails(int num1, int num2) {
    if (num1 <= 1 || num2 <= 1) { // Factorization typically for > 1
        throw std::invalid_argument("Numbers must be greater than 1 for detailed HCF/LCM via prime factorization.");
    }
    HCFAndLCMResult result;
    result.num1 = num1;
    result.num2 = num2;
    result.primeFactorizationNum1 = getPrimeFactorization(num1).factors;
    result.primeFactorizationNum2 = getPrimeFactorization(num2).factors;
    result.hcf = hcfFromPrimeFactorization(result.primeFactorizationNum1, result.primeFactorizationNum2);
    // Or use result.hcf = euclidsAlgorithmHCF(num1, num2).hcf;
    result.lcm = calculateLCM(num1, num2);
    return result;
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
    if (n < 0) return false;
    if (n == 0) return true;
    int sqrt_n = static_cast<int>(std::sqrt(n));
    return sqrt_n * sqrt_n == n;
}

IrrationalityCheckResult checkSqrtIrrationality(int number) {
    IrrationalityCheckResult result;
    result.numberForm = "sqrt(" + std::to_string(number) + ")";
    if (number < 0) {
        result.isIrrational = false; // Or true, as it's complex
        result.reason = "sqrt(" + std::to_string(number) + ") is a complex number, not a real irrational number.";
        return result;
    }
    if (isNumberPerfectSquare(number)) {
        result.isIrrational = false;
        result.reason = "sqrt(" + std::to_string(number) + ") = " + std::to_string(static_cast<int>(std::sqrt(number))) +
                        ", which is rational (an integer).";
    } else {
        result.isIrrational = true;
        if (isPrimeBasic(number)) {
            result.reason = std::to_string(number) + " is a prime number. The square root of a prime number is irrational.";
        } else {
            result.reason = std::to_string(number) + " is not a perfect square. The square root of a non-perfect square integer is irrational.";
        }
    }
    return result;
}

DecimalExpansionResult getDecimalExpansionType(int numerator, int denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("Denominator cannot be zero.");
    }
    DecimalExpansionResult result;
    result.numerator = numerator;
    result.denominator = denominator;
    result.fraction = std::to_string(numerator) + "/" + std::to_string(denominator);

    int common = std::gcd(std::abs(numerator), std::abs(denominator));
    int simplifiedDen = std::abs(denominator) / common;

    if (simplifiedDen == 0) { // Should not happen
        result.expansionType = "undefined";
        result.reason = "Denominator became zero after simplification.";
        return result;
    }
    if (simplifiedDen == 1) {
        result.expansionType = "terminating";
        result.reason = "The fraction simplifies to an integer (" + std::to_string(numerator / common) + "). Denominator is 1.";
        return result;
    }

    int tempDen = simplifiedDen;
    std::ostringstream factorsOss;
    bool firstFactor = true;

    auto appendFactor = [&](int prime, int count) {
        if (!firstFactor) factorsOss << " * ";
        factorsOss << prime;
        if (count > 1) factorsOss << "^" << count;
        firstFactor = false;
    };
    
    int count2 = 0;
    while (tempDen % 2 == 0) { tempDen /= 2; count2++; }
    if (count2 > 0) appendFactor(2, count2);

    int count5 = 0;
    while (tempDen % 5 == 0) { tempDen /= 5; count5++; }
    if (count5 > 0) appendFactor(5, count5);
    
    bool only2And5 = true;
    // Check for other prime factors
    for (int i = 3; i * i <= tempDen; i += 2) {
        if (tempDen % i == 0) {
            int countOther = 0;
            while (tempDen % i == 0) {
                tempDen /= i;
                countOther++;
            }
            only2And5 = false;
            appendFactor(i, countOther);
        }
    }
    if (tempDen > 1) { // Remaining tempDen is a prime factor
        if (tempDen != 2 && tempDen != 5) { // Should be caught by loop unless tempDen itself is prime > last i
            only2And5 = false;
        }
        appendFactor(tempDen, 1);
    }
    
    std::string denominatorFactorsStr = factorsOss.str();
    if (denominatorFactorsStr.empty() && simplifiedDen == 1) denominatorFactorsStr = "1";
    else if (denominatorFactorsStr.empty()) denominatorFactorsStr = std::to_string(simplifiedDen);


    if (only2And5) {
        result.expansionType = "terminating";
        result.reason = "Simplified denominator (" + std::to_string(simplifiedDen) + ") has prime factors: " + denominatorFactorsStr + " (only 2s and/or 5s).";
    } else {
        result.expansionType = "non-terminating recurring";
        result.reason = "Simplified denominator (" + std::to_string(simplifiedDen) + ") has prime factors: " + denominatorFactorsStr + " (includes primes other than 2 and 5).";
    }
    return result;
}


BasicPolynomialInfo analyzePolynomialCoeffs(const std::vector<double>& coeffs) {
    BasicPolynomialInfo info;
    if (coeffs.empty()) {
        info.degree = -1; // Or undefined
        info.expression = "Empty coefficients";
        return info;
    }

    // Find first non-zero coefficient to determine actual degree
    size_t firstNonZeroIdx = 0;
    while (firstNonZeroIdx < coeffs.size() && std::abs(coeffs[firstNonZeroIdx]) < 1e-9) {
        firstNonZeroIdx++;
    }

    if (firstNonZeroIdx == coeffs.size()) { // All coefficients are zero
        info.degree = -1; // Or 0 if you consider 0 a degree 0 polynomial
        info.expression = "Zero polynomial";
        info.coefficients = {0.0};
        return info;
    }
    
    // Actual coefficients start from the first non-zero one
    // Degree is (total_coeffs - 1 - index_of_leading_coeff)
    info.degree = static_cast<int>(coeffs.size() - 1 - firstNonZeroIdx);
    info.coefficients.assign(coeffs.begin() + firstNonZeroIdx, coeffs.end());

    std::ostringstream exprOss;
    for (size_t i = 0; i < info.coefficients.size(); ++i) {
        double coeff = info.coefficients[i];
        int power = info.degree - static_cast<int>(i);

        if (std::abs(coeff) < 1e-9 && info.coefficients.size() > 1) continue; // Skip zero terms unless it's the only term (constant 0)

        if (i > 0 && coeff > 0) exprOss << " + ";
        else if (coeff < 0) exprOss << " - ";
        
        double absCoeff = std::abs(coeff);
        if (std::abs(absCoeff - 1.0) > 1e-9 || power == 0 || info.coefficients.size() == 1) {
             exprOss << std::fixed << std::setprecision(2) << absCoeff;
        } else if (absCoeff == 1.0 && power == 0) { // if it's just '1' or '-1' as constant
             exprOss << std::fixed << std::setprecision(2) << absCoeff;
        }


        if (power > 0) {
            exprOss << "x";
            if (power > 1) {
                exprOss << "^" << power;
            }
        }
        if (i < info.coefficients.size() -1) exprOss << " ";
    }
    info.expression = exprOss.str();
    if (info.expression.empty() && info.degree == -1) info.expression = "0"; // Handle zero poly case

    // Vieta's formulas
    // Sum of roots = - (a_{n-1}) / a_n
    // Product of roots = (-1)^n * (a_0) / a_n
    // Here, info.coefficients are [a_n, a_{n-1}, ..., a_0]
    if (info.degree >= 1 && !info.coefficients.empty() && std::abs(info.coefficients[0]) > 1e-9) {
        double leadingCoeff = info.coefficients[0];
        
        if (info.degree == 1) { // ax + b
             if (info.coefficients.size() >= 2) {
                info.sumOfRootsViete = std::to_string(-info.coefficients[1] / leadingCoeff);
             } else { // ax (root is 0)
                 info.sumOfRootsViete = "0";
             }
             info.productOfRootsViete = info.sumOfRootsViete; // For degree 1, root is sum and product
        } else if (info.coefficients.size() > 1) { // Degree >= 2
            info.sumOfRootsViete = std::to_string(-info.coefficients[1] / leadingCoeff);
        } else { // Monomial like ax^n, n >= 2. Roots are all 0.
            info.sumOfRootsViete = "0";
        }


        if (info.coefficients.size() >= 1) {
            double constantTerm = info.coefficients.back();
            info.productOfRootsViete = std::to_string(std::pow(-1, info.degree) * constantTerm / leadingCoeff);
        } else { // Should not happen if degree >=1
             info.productOfRootsViete = "N/A";
        }

    } else if (info.degree == 0) { // Constant polynomial
        info.sumOfRootsViete = "0 (no roots)";
        info.productOfRootsViete = "N/A (no roots)";
    }

    return info;
}


} // namespace RealNumbers