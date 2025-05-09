// cpp_code/real_numbers/real_numbers_types.h
#ifndef REAL_NUMBERS_TYPES_H
#define REAL_NUMBERS_TYPES_H

#include <string>
#include <vector>
#include <map>
#include <sstream> // For formatting strings
#include <iomanip> // For std::fixed, std::setprecision

namespace RealNumbers {

struct EuclidLemmaResult {
    int dividend;
    int divisor;
    int quotient;
    int remainder;
    std::string equation;

    std::string toString() const {
        return "EuclidLemmaResult{ equation='" + equation + "' }";
    }
};

struct HCFResult {
    int num1;
    int num2;
    int hcf;

    std::string toString() const {
        std::ostringstream oss;
        oss << "HCFResult{ num1=" << num1 << ", num2=" << num2 << ", hcf=" << hcf << " }";
        return oss.str();
    }
};

struct PrimeFactorizationResult {
    int number;
    std::map<int, int> factors; // prime -> exponent

    std::string toString() const {
        std::ostringstream oss;
        oss << "PrimeFactorizationResult{ number=" << number << ", factors={";
        bool first = true;
        for (const auto& pair : factors) {
            if (!first) oss << ", ";
            oss << pair.first << ":" << pair.second;
            first = false;
        }
        oss << "} }";
        return oss.str();
    }
};

struct HCFAndLCMResult {
    int num1;
    int num2;
    std::map<int, int> primeFactorizationNum1;
    std::map<int, int> primeFactorizationNum2;
    int hcf;
    long long lcm; // LCM can be large

    std::string factorsToString(const std::map<int, int>& factors) const {
        std::ostringstream oss;
        oss << "{";
        bool first = true;
        for (const auto& pair : factors) {
            if (!first) oss << ", ";
            oss << pair.first << ":" << pair.second;
            first = false;
        }
        oss << "}";
        return oss.str();
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << "HCFAndLCMResult{ num1=" << num1 << ", num2=" << num2
            << ", pf1=" << factorsToString(primeFactorizationNum1)
            << ", pf2=" << factorsToString(primeFactorizationNum2)
            << ", hcf=" << hcf << ", lcm=" << lcm << " }";
        return oss.str();
    }
};

struct IrrationalityCheckResult {
    std::string numberForm; // e.g., "sqrt(5)"
    bool isIrrational;
    std::string reason;

    std::string toString() const {
        std::ostringstream oss;
        oss << "IrrationalityCheckResult{ numberForm='" << numberForm << '\''
            << ", isIrrational=" << (isIrrational ? "true" : "false")
            << ", reason='" << reason << "' }";
        return oss.str();
    }
};

struct DecimalExpansionResult {
    int numerator;
    int denominator;
    std::string fraction;
    std::string expansionType; // "terminating", "non-terminating recurring", "undefined"
    std::string reason;

    std::string toString() const {
        std::ostringstream oss;
        oss << "DecimalExpansionResult{ fraction='" << fraction << '\''
            << ", expansionType='" << expansionType << '\''
            << ", reason='" << reason << "' }";
        return oss.str();
    }
};

// For Polynomials, C++ without a symbolic library is limited.
// We might define a simpler struct focusing on Vieta's formulas if coefficients are given,
// or just degree for a general polynomial string (parsing which is non-trivial).
// For now, let's keep it minimal or defer a complex implementation.
struct BasicPolynomialInfo {
    std::string expression; // The input expression
    int degree;
    std::vector<double> coefficients; // If parsed or provided [a_n, a_{n-1}, ..., a_0]
    // Roots are hard to find symbolically without a library.
    // Numerical roots are possible but add complexity (e.g. Durand-Kerner, Jenkins-Traub).
    // std::vector<std::complex<double>> roots;
    std::string sumOfRootsViete;    // Calculated if degree >= 1
    std::string productOfRootsViete; // Calculated if degree >= 1

    std::string coeffsToString() const {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < coefficients.size(); ++i) {
            oss << coefficients[i] << (i == coefficients.size() - 1 ? "" : ", ");
        }
        oss << "]";
        return oss.str();
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << "BasicPolynomialInfo{ expression='" << expression << '\''
            << ", degree=" << degree;
        if (!coefficients.empty()) {
            oss << ", coefficients=" << coeffsToString();
        }
        if (!sumOfRootsViete.empty()) {
             oss << ", sumOfRootsViete='" << sumOfRootsViete << '\'';
        }
        if (!productOfRootsViete.empty()) {
             oss << ", productOfRootsViete='" << productOfRootsViete << '\'';
        }
        oss << " }";
        return oss.str();
    }
};


} // namespace RealNumbers

#endif // REAL_NUMBERS_TYPES_H