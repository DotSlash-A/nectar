#ifndef POLYNOMIAL_QUADRATIC_TYPES_H
#define POLYNOMIAL_QUADRATIC_TYPES_H

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <optional>
#include <iomanip> // For std::fixed, std::setprecision
#include <cmath>   // For std::abs, std::sqrt, std::pow
#include <numeric> // For std::gcd

namespace michu_fr {
namespace polynomials_quadratics {

const double EPSILON = 1e-9;

// Forward declaration for ComplexNumber if it's used by other structs before its definition
struct ComplexNumber;

struct PolynomialDivisionResult {
    std::vector<double> quotient_coefficients;
    std::vector<double> remainder_coefficients;
    std::string quotient_string;
    std::string remainder_string;
    std::string equation_string; // p(x) = d(x)q(x) + r(x)

    PolynomialDivisionResult(std::vector<double> qc, std::vector<double> rc,
                             std::string qs, std::string rs, std::string eq_s)
        : quotient_coefficients(std::move(qc)), remainder_coefficients(std::move(rc)),
          quotient_string(std::move(qs)), remainder_string(std::move(rs)),
          equation_string(std::move(eq_s)) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << "PolynomialDivisionResult{quotient=" << quotient_string
            << ", remainder=" << remainder_string
            << ", equation='" << equation_string << "'}";
        return oss.str();
    }
};

struct ComplexNumber {
    double real;
    double imaginary;

    ComplexNumber(double r = 0.0, double i = 0.0) : real(r), imaginary(i) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(4); // Adjust precision as needed

        bool real_is_zero = std::abs(real) < EPSILON;
        bool imag_is_zero = std::abs(imaginary) < EPSILON;

        if (real_is_zero && imag_is_zero) {
            oss << "0";
        } else if (imag_is_zero) {
            oss << real;
        } else if (real_is_zero) {
            oss << imaginary << "i";
        } else {
            oss << real;
            if (imaginary > 0) {
                oss << " + " << imaginary << "i";
            } else {
                oss << " - " << std::abs(imaginary) << "i";
            }
        }
        return oss.str();
    }
};


struct QuadraticSolution {
    std::string equation_string;
    double a, b, c;
    std::optional<double> discriminant; // Optional because it's not relevant for linear/trivial cases
    std::string nature_of_roots;
    std::vector<ComplexNumber> roots_complex; // Store all roots as complex for uniformity
    std::vector<double> roots_real;           // Store real roots separately if preferred for output

    QuadraticSolution(std::string eq_s, double ca, double cb, double cc,
                      std::optional<double> disc, std::string nature,
                      std::vector<ComplexNumber> r_c, std::vector<double> r_r)
        : equation_string(std::move(eq_s)), a(ca), b(cb), c(cc),
          discriminant(disc), nature_of_roots(std::move(nature)),
          roots_complex(std::move(r_c)), roots_real(std::move(r_r)) {}

    // Default constructor if needed
    QuadraticSolution() : a(0), b(0), c(0) {}


    std::string toString() const {
        std::ostringstream oss;
        oss << "QuadraticSolution{equation='" << equation_string << "'";
        if (discriminant.has_value()) {
            oss << ", discriminant=" << discriminant.value();
        }
        oss << ", natureOfRoots='" << nature_of_roots << "', roots=";
        if (!roots_complex.empty()) {
            oss << "[";
            for (size_t i = 0; i < roots_complex.size(); ++i) {
                oss << roots_complex[i].toString() << (i == roots_complex.size() - 1 ? "" : ", ");
            }
            oss << "]";
        } else if (!roots_real.empty()) {
             oss << "[";
            for (size_t i = 0; i < roots_real.size(); ++i) {
                oss << roots_real[i] << (i == roots_real.size() - 1 ? "" : ", ");
            }
            oss << "]";
        } else if (nature_of_roots.find("All real numbers") != std::string::npos || nature_of_roots.find("identity") != std::string::npos) {
            oss << "[All real numbers]";
        }
         else {
            oss << "[]";
        }
        oss << "}";
        return oss.str();
    }
};


struct RootsCoefficientsRelation {
    std::string polynomial_string;
    int degree;
    std::map<std::string, double> relations; // Using double for relation values
    std::string verification_note;

    RootsCoefficientsRelation(std::string ps, int deg, std::map<std::string, double> rel, std::string note)
        : polynomial_string(std::move(ps)), degree(deg), relations(std::move(rel)),
          verification_note(std::move(note)) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << "RootsCoefficientsRelation{polynomial='" << polynomial_string << "'"
            << ", degree=" << degree << ", relations={";
        bool first = true;
        for (const auto& pair : relations) {
            if (!first) oss << ", ";
            oss << pair.first << ":" << pair.second;
            first = false;
        }
        oss << "}";
        if (!verification_note.empty()) {
            oss << ", note='" << verification_note << "'";
        }
        oss << "}";
        return oss.str();
    }
};

struct FormedPolynomial {
    std::vector<double> polynomial_coefficients;
    std::string polynomial_string;
    std::vector<double> roots_provided; // Assuming real roots for simplicity
    double leading_coefficient_used;

    FormedPolynomial(std::vector<double> coeffs, std::string poly_str,
                     std::vector<double> roots, double lc_used)
        : polynomial_coefficients(std::move(coeffs)), polynomial_string(std::move(poly_str)),
          roots_provided(std::move(roots)), leading_coefficient_used(lc_used) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << "FormedPolynomial{polynomialString='" << polynomial_string << "'"
            << ", coefficients=[";
        for(size_t i = 0; i < polynomial_coefficients.size(); ++i) {
            oss << polynomial_coefficients[i] << (i == polynomial_coefficients.size() - 1 ? "" : ", ");
        }
        oss << "], rootsProvided=[";
        for(size_t i = 0; i < roots_provided.size(); ++i) {
            oss << roots_provided[i] << (i == roots_provided.size() - 1 ? "" : ", ");
        }
        oss << "], leadingCoefficientUsed=" << leading_coefficient_used << "}";
        return oss.str();
    }
};


} // namespace polynomials_quadratics
} // namespace michu_fr

#endif // POLYNOMIAL_QUADRATIC_TYPES_H