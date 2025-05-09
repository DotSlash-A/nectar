#ifndef POLYNOMIAL_UTILS_H
#define POLYNOMIAL_UTILS_H

#include "polynomial_quadratic_types.h"
#include <vector>
#include <string>
#include <list> // For polynomial division intermediate steps

namespace michu_fr {
namespace polynomials_quadratics {

std::string formatPolynomialToString(const std::vector<double>& coeffs, const std::string& varSymbol = "x");
double evaluatePolynomial(const std::vector<double>& coeffs, double xVal);
PolynomialDivisionResult polynomialDivision(const std::vector<double>& dividend_coeffs, const std::vector<double>& divisor_coeffs);
std::vector<double> findRationalRoots(const std::vector<double>& coeffs);
RootsCoefficientsRelation relationRootsCoefficientsQuadratic(const std::vector<double>& coeffs);
RootsCoefficientsRelation relationRootsCoefficientsCubic(const std::vector<double>& coeffs);
std::vector<double> multiplyPolynomials(const std::vector<double>& poly1_coeffs, const std::vector<double>& poly2_coeffs);
FormedPolynomial formPolynomialFromRoots(const std::vector<double>& roots, double leading_coefficient, const std::string& var_symbol = "x");

} // namespace polynomials_quadratics
} // namespace michu_fr

#endif // POLYNOMIAL_UTILS_H