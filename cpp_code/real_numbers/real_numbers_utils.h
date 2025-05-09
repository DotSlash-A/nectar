// cpp_code/real_numbers/real_numbers_utils.h
#ifndef REAL_NUMBERS_UTILS_H
#define REAL_NUMBERS_UTILS_H

#include "real_numbers_types.h" // Include the types we just defined
#include <string>
#include <vector>
#include <map>

namespace RealNumbers {

// Euclid's Division Lemma: dividend = divisor * quotient + remainder
EuclidLemmaResult euclidsDivisionLemma(int dividend, int divisor);

// Euclid's Algorithm for HCF (GCD)
HCFResult euclidsAlgorithmHCF(int n1, int n2);

// Prime Factorization
PrimeFactorizationResult getPrimeFactorization(int n);

// HCF from prime factorizations
int hcfFromPrimeFactorization(const std::map<int, int>& factors1, const std::map<int, int>& factors2);

// LCM from prime factorizations
long long lcmFromPrimeFactorization(const std::map<int, int>& factors1, const std::map<int, int>& factors2);

// LCM using the formula: LCM(a,b) = |a*b| / HCF(a,b)
long long calculateLCM(int n1, int n2);

// Combined HCF and LCM details, including prime factorizations
HCFAndLCMResult getHCFAndLCMDetails(int num1, int num2);

// Basic primality test
bool isPrimeBasic(int n);

// Check if a number is a perfect square
bool isNumberPerfectSquare(int n);

// Check irrationality of sqrt(N)
IrrationalityCheckResult checkSqrtIrrationality(int number);

// Determine decimal expansion type of a rational number
DecimalExpansionResult getDecimalExpansionType(int numerator, int denominator);

// Analyze a polynomial given its coefficients (for Vieta's formulas, degree)
// Parsing a string expression into coefficients is a much larger task.
// This version assumes coefficients are given in order [a_n, a_{n-1}, ..., a_1, a_0]
BasicPolynomialInfo analyzePolynomialCoeffs(const std::vector<double>& coeffs);

// If you want to attempt basic parsing for simple polynomial strings:
// BasicPolynomialInfo analyzePolynomialExpression(const std::string& polyExprStr); // This would be more complex

} // namespace RealNumbers

#endif // REAL_NUMBERS_UTILS_H