#ifndef REAL_NUMBERS_TYPES_H
#define REAL_NUMBERS_TYPES_H

#include <string>
#include <vector>
#include <map>
#include <sstream>    // For std::ostringstream
#include <optional>   // For std::optional (C++17)
#include <iomanip>    // For std::fixed, std::setprecision
#include <numeric>    // For std::gcd (C++17)
#include <algorithm>  // For std::min, std::max
#include <cmath>      // For std::abs, std::sqrt, std::pow

namespace michu_fr {
namespace real_numbers {

struct EuclidLemmaResult {
    int dividend;
    int divisor;
    int quotient;
    int remainder;
    std::string equation;

    // Constructor for easy initialization
    EuclidLemmaResult(int d, int dv, int q, int r, std::string eq)
        : dividend(d), divisor(dv), quotient(q), remainder(r), equation(std::move(eq)) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << "EuclidLemmaResult{equation='" << equation << "'}";
        return oss.str();
    }
};

struct HCFResult {
    int num1;
    int num2;
    int hcf;

    HCFResult(int n1, int n2_val, int hcf_val)
        : num1(n1), num2(n2_val), hcf(hcf_val) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << "HCFResult{num1=" << num1 << ", num2=" << num2 << ", hcf=" << hcf << "}";
        return oss.str();
    }
};

struct PrimeFactorizationResult {
    int number;
    std::map<int, int> factors; // prime -> exponent

    PrimeFactorizationResult(int n, std::map<int, int> f)
        : number(n), factors(std::move(f)) {}
    PrimeFactorizationResult() : number(0) {} // Default constructor if needed

    std::string toString() const {
        std::ostringstream oss;
        oss << "PrimeFactorizationResult{number=" << number << ", factors={";
        bool first = true;
        for (const auto& pair : factors) {
            if (!first) {
                oss << ", ";
            }
            oss << pair.first << ":" << pair.second;
            first = false;
        }
        oss << "}}";
        return oss.str();
    }
};

struct HCFAndLCMResult {
    int num1;
    int num2;
    std::map<int, int> prime_factorization_num1;
    std::map<int, int> prime_factorization_num2;
    int hcf;
    long long lcm;

    HCFAndLCMResult(int n1, int n2_val, std::map<int, int> pf1, std::map<int, int> pf2, int hcf_val, long long lcm_val)
        : num1(n1), num2(n2_val), prime_factorization_num1(std::move(pf1)),
          prime_factorization_num2(std::move(pf2)), hcf(hcf_val), lcm(lcm_val) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << "HCFAndLCMResult{num1=" << num1 << ", num2=" << num2;
        oss << ", pf1={";
        bool first1 = true;
        for (const auto& pair : prime_factorization_num1) {
            if (!first1) {
                 oss << ", ";
            }
            oss << pair.first << ":" << pair.second;
            first1 = false;
        }
        oss << "}, pf2={";
        bool first2 = true;
        for (const auto& pair : prime_factorization_num2) {
            if (!first2) {
                oss << ", ";
            }
            oss << pair.first << ":" << pair.second;
            first2 = false;
        }
        oss << "}, hcf=" << hcf << ", lcm=" << lcm << "}";
        return oss.str();
    }
};

struct IrrationalityCheckResult {
    std::string number_form;
    bool is_irrational;
    std::string reason;

    IrrationalityCheckResult(std::string nf, bool irr, std::string r)
        : number_form(std::move(nf)), is_irrational(irr), reason(std::move(r)) {}
    IrrationalityCheckResult() : is_irrational(false) {}


    std::string toString() const {
        std::ostringstream oss;
        oss << "IrrationalityCheckResult{numberForm='" << number_form << "'"
            << ", isIrrational=" << (is_irrational ? "true" : "false")
            << ", reason='" << reason << "'}";
        return oss.str();
    }
};

struct DecimalExpansionResult {
    int numerator;
    int denominator;
    std::string fraction_str;
    std::string expansion_type;
    std::string reason;

    DecimalExpansionResult(int num, int den, std::string f_str, std::string et, std::string r)
        : numerator(num), denominator(den), fraction_str(std::move(f_str)),
          expansion_type(std::move(et)), reason(std::move(r)) {}
    DecimalExpansionResult() : numerator(0), denominator(0) {}


    std::string toString() const {
        std::ostringstream oss;
        oss << "DecimalExpansionResult{fraction='" << fraction_str << "'"
            << ", expansionType='" << expansion_type << "'"
            << ", reason='" << reason << "'}";
        return oss.str();
    }
};

struct PolynomialAnalysisResult {
    std::vector<double> input_coefficients;
    int degree;
    std::vector<std::string> roots_str;
    std::string sum_of_roots_vieta_str;
    std::string product_of_roots_vieta_str;
    std::string notes;

    // Default constructor
    PolynomialAnalysisResult() : degree(-1) {}

    // Parameterized constructor
    PolynomialAnalysisResult(std::vector<double> coeffs, int deg, std::vector<std::string> roots,
                             std::string sum_v, std::string prod_v, std::string nts)
        : input_coefficients(std::move(coeffs)), degree(deg), roots_str(std::move(roots)),
          sum_of_roots_vieta_str(std::move(sum_v)), product_of_roots_vieta_str(std::move(prod_v)),
          notes(std::move(nts)) {}


     std::string toString() const {
        std::ostringstream oss;
        oss << "PolynomialAnalysisResult{degree=" << degree;
        oss << ", roots=[";
        for(size_t i = 0; i < roots_str.size(); ++i) {
            oss << roots_str[i] << (i == roots_str.size() - 1 ? "" : ", ");
        }
        oss << "]";
        oss << ", sumRootsViete='" << sum_of_roots_vieta_str << "'";
        oss << ", prodRootsViete='" << product_of_roots_vieta_str << "'";
        if (!notes.empty()) {
            oss << ", notes='" << notes << "'";
        }
        oss << "}";
        return oss.str();
    }
};


} // namespace real_numbers
} // namespace michu_fr

#endif // REAL_NUMBERS_TYPES_H