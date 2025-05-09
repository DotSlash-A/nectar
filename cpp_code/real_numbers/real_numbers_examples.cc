// cpp_code/real_numbers/real_numbers_examples.cc
#include "real_numbers_utils.h" // Includes real_numbers_types.h as well
#include <iostream>
#include <vector>
#include <stdexcept> // For catching exceptions

int main() {
    std::cout << "--- Real Numbers Examples ---" << std::endl;

    // 1. Euclid's Division Lemma
    std::cout << "\n1. Euclid's Division Lemma:" << std::endl;
    try {
        RealNumbers::EuclidLemmaResult lemma1 = RealNumbers::euclidsDivisionLemma(455, 42);
        std::cout << "   455 / 42: " << lemma1.toString() << std::endl;
        RealNumbers::EuclidLemmaResult lemma2 = RealNumbers::euclidsDivisionLemma(-7, 3);
        std::cout << "   -7 / 3: " << lemma2.toString() << std::endl;
        RealNumbers::EuclidLemmaResult lemma3 = RealNumbers::euclidsDivisionLemma(7, -3);
        std::cout << "   7 / -3: " << lemma3.toString() << std::endl;
        RealNumbers::EuclidLemmaResult lemma4 = RealNumbers::euclidsDivisionLemma(-7, -3);
        std::cout << "   -7 / -3: " << lemma4.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error in Euclid's Lemma: " << e.what() << std::endl;
    }

    // 2. Euclid's Algorithm for HCF
    std::cout << "\n2. Euclid's Algorithm for HCF:" << std::endl;
    try {
        RealNumbers::HCFResult hcf1 = RealNumbers::euclidsAlgorithmHCF(455, 42);
        std::cout << "   HCF(455, 42): " << hcf1.toString() << std::endl;
        RealNumbers::HCFResult hcf2 = RealNumbers::euclidsAlgorithmHCF(96, 404);
        std::cout << "   HCF(96, 404): " << hcf2.toString() << std::endl;
        RealNumbers::HCFResult hcf3 = RealNumbers::euclidsAlgorithmHCF(0, 5);
        std::cout << "   HCF(0, 5): " << hcf3.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error in HCF: " << e.what() << std::endl;
    }

    // 3. Prime Factorization
    std::cout << "\n3. Prime Factorization:" << std::endl;
    try {
        RealNumbers::PrimeFactorizationResult pf1 = RealNumbers::getPrimeFactorization(3825);
        std::cout << "   Prime Factors of 3825: " << pf1.toString() << std::endl;
        RealNumbers::PrimeFactorizationResult pf2 = RealNumbers::getPrimeFactorization(140);
        std::cout << "   Prime Factors of 140: " << pf2.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error in Prime Factorization: " << e.what() << std::endl;
    }

    // 4. HCF and LCM Details
    std::cout << "\n4. HCF and LCM Details (using prime factorization for HCF):" << std::endl;
    try {
        RealNumbers::HCFAndLCMResult details1 = RealNumbers::getHCFAndLCMDetails(96, 404);
        std::cout << "   Details for 96 and 404: " << details1.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error in HCF/LCM Details: " << e.what() << std::endl;
    }
     std::cout << "   LCM(96, 404) using direct formula: " << RealNumbers::calculateLCM(96, 404) << std::endl;


    // 5. Irrationality Check for Sqrt(N)
    std::cout << "\n5. Irrationality Check for Sqrt(N):" << std::endl;
    RealNumbers::IrrationalityCheckResult irr1 = RealNumbers::checkSqrtIrrationality(5);
    std::cout << "   " << irr1.toString() << std::endl;
    RealNumbers::IrrationalityCheckResult irr2 = RealNumbers::checkSqrtIrrationality(9);
    std::cout << "   " << irr2.toString() << std::endl;
    RealNumbers::IrrationalityCheckResult irr3 = RealNumbers::checkSqrtIrrationality(6); // Non-prime, non-perfect square
    std::cout << "   " << irr3.toString() << std::endl;

    // 6. Decimal Expansion Type
    std::cout << "\n6. Decimal Expansion Type:" << std::endl;
    try {
        RealNumbers::DecimalExpansionResult dec1 = RealNumbers::getDecimalExpansionType(13, 3125); // Terminating
        std::cout << "   13/3125: " << dec1.toString() << std::endl;
        RealNumbers::DecimalExpansionResult dec2 = RealNumbers::getDecimalExpansionType(1, 7);    // Non-terminating recurring
        std::cout << "   1/7: " << dec2.toString() << std::endl;
        RealNumbers::DecimalExpansionResult dec3 = RealNumbers::getDecimalExpansionType(17, 8);   // Terminating
        std::cout << "   17/8: " << dec3.toString() << std::endl;
        RealNumbers::DecimalExpansionResult dec4 = RealNumbers::getDecimalExpansionType(77, 210); // Simplify to 11/30 (Non-term recurring)
        std::cout << "   77/210: " << dec4.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error in Decimal Expansion: " << e.what() << std::endl;
    }
    
    // 7. Basic Polynomial Analysis (from coefficients)
    std::cout << "\n7. Basic Polynomial Analysis (from coefficients):" << std::endl;
    // x^2 - 3x + 2 => coeffs: [1, -3, 2]
    std::vector<double> coeffs_poly1 = {1.0, -3.0, 2.0};
    RealNumbers::BasicPolynomialInfo info1 = RealNumbers::analyzePolynomialCoeffs(coeffs_poly1);
    std::cout << "   Poly 1 (x^2 - 3x + 2): " << info1.toString() << std::endl;

    // 2x^3 + 0x^2 - 5x + 1 => coeffs: [2, 0, -5, 1]
    std::vector<double> coeffs_poly2 = {2.0, 0.0, -5.0, 1.0};
    RealNumbers::BasicPolynomialInfo info2 = RealNumbers::analyzePolynomialCoeffs(coeffs_poly2);
    std::cout << "   Poly 2 (2x^3 - 5x + 1): " << info2.toString() << std::endl;
    
    // Constant polynomial: 7 => coeffs: [7]
    std::vector<double> coeffs_poly3 = {7.0};
    RealNumbers::BasicPolynomialInfo info3 = RealNumbers::analyzePolynomialCoeffs(coeffs_poly3);
    std::cout << "   Poly 3 (7): " << info3.toString() << std::endl;

    // Leading zero coefficients: 0x^2 + 2x - 1 => effective coeffs {2, -1} for 2x - 1
    std::vector<double> coeffs_poly4 = {0.0, 0.0, 2.0, -1.0};
    RealNumbers::BasicPolynomialInfo info4 = RealNumbers::analyzePolynomialCoeffs(coeffs_poly4);
    std::cout << "   Poly 4 (0x^3 + 0x^2 + 2x - 1): " << info4.toString() << std::endl;
    
    // Zero polynomial
    std::vector<double> coeffs_poly5 = {0.0, 0.0, 0.0};
    RealNumbers::BasicPolynomialInfo info5 = RealNumbers::analyzePolynomialCoeffs(coeffs_poly5);
    std::cout << "   Poly 5 (Zero polynomial): " << info5.toString() << std::endl;


    std::cout << "\n--- End of Real Numbers Examples ---" << std::endl;
    return 0;
}