#ifndef REAL_NUMBERS_UTILS_H
#define REAL_NUMBERS_UTILS_H

#include "real_numbers_types.h" // Include our type definitions

namespace michu_fr {
namespace real_numbers {

EuclidLemmaResult euclidsDivisionLemma(int dividend, int divisor);
HCFResult euclidsAlgorithmHCF(int n1, int n2);
PrimeFactorizationResult getPrimeFactorization(int n);
int hcfFromPrimeFactorization(const std::map<int, int>& factors1, const std::map<int, int>& factors2);
long long lcmFromPrimeFactorization(const std::map<int, int>& factors1, const std::map<int, int>& factors2);
long long calculateLCM(int n1, int n2);
HCFAndLCMResult getHCFAndLCMDetails(int num1, int num2);
bool isPrimeBasic(int n);
bool isNumberPerfectSquare(int n);
IrrationalityCheckResult checkSqrtIrrationality(int number);
DecimalExpansionResult getDecimalExpansionType(int numerator, int denominator);
PolynomialAnalysisResult analyzePolynomial(const std::vector<double>& coeffs);

} // namespace real_numbers
} // namespace michu_fr

#endif // REAL_NUMBERS_UTILS_H