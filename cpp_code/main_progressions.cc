#include <iostream>
#include <vector>
#include <stdexcept>
#include "progressions/arithmetic_progression_utils.h"
#include "progressions/geometric_progression_utils.h"

void print_line_separator() {
    std::cout << "----------------------------------------" << std::endl;
}

int main() {
    std::cout << "--- Progressions C++ Examples & Tests ---" << std::endl;
    print_line_separator();

    using namespace michu_fr::progressions;

    // --- Arithmetic Progression ---
    std::cout << "--- Arithmetic Progression (AP) ---" << std::endl;
    try {
        std::cout << "AP Basic (a=2, d=3, n=10): "
                  << calculateAPTermAndSum(2.0, 3.0, 10).toString() << std::endl;
        std::cout << "AP Nth from Last (l=29, d=3, n=3): "
                  << calculateNthTermFromLastAP(29.0, 3.0, 3) << std::endl;
        std::cout << "AP Middle Terms (a=2, d=3, last=29): "
                  << findMiddleTermsAP(2.0, 3.0, 29.0).toString() << std::endl;
        std::cout << "AP Middle Terms (a=1, d=2, last=9): "
                  << findMiddleTermsAP(1.0, 2.0, 9.0).toString() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "AP Error: " << e.what() << std::endl;
    }
    print_line_separator();

    // --- Geometric Progression ---
    std::cout << "--- Geometric Progression (GP) ---" << std::endl;
    try {
        std::cout << "GP Basic (a=3, r=2, n=5): "
                  << calculateGPTermAndSum(3.0, 2.0, 5).toString() << std::endl;
        std::cout << "GP Sum to Infinity (a=10, r=0.5): "
                  << calculateGPSumToInfinity(10.0, 0.5) << std::endl;
        std::cout << "GP Geometric Mean (num1=4, num2=9): "
                  << calculateGeometricMean(4.0, 9.0) << std::endl;
        std::cout << "GP Insert Means (a=2, b=162, k=3): "
                  << insertGeometricMeans(2.0, 162.0, 3).toString() << std::endl;
        std::cout << "GP Insert Means (a=1, b=-8, k=2): " // r=-2
                  << insertGeometricMeans(1.0, -8.0, 2).toString() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "GP Error: " << e.what() << std::endl;
    }
    print_line_separator();

    // --- Testing Error Cases (like ProgressionTester.java) ---
    std::cout << "--- Testing Expected Errors ---" << std::endl;

    // AP errors
    try { calculateAPTermAndSum(1, 1, 0); }
    catch(const std::exception& e) { std::cerr << "Caught AP Error (n=0): " << e.what() << std::endl;}
    try { findMiddleTermsAP(1, 0, 5); }
    catch(const std::exception& e) { std::cerr << "Caught AP Error (d=0, a!=l): " << e.what() << std::endl;}

    // GP errors
    try { calculateGPTermAndSum(1, 2, 0); }
    catch(const std::exception& e) { std::cerr << "Caught GP Error (n=0): " << e.what() << std::endl;}
    try { calculateGPSumToInfinity(10, 1.5); }
    catch(const std::exception& e) { std::cerr << "Caught GP Error (sum_inf |r|>=1): " << e.what() << std::endl;}
    try { insertGeometricMeans(1, -16, 3); } // r^4 = -16
    catch(const std::exception& e) { std::cerr << "Caught GP Error (insert means, even root of neg): " << e.what() << std::endl;}

    print_line_separator();
    std::cout << "--- End of Examples & Tests ---" << std::endl;

    return 0;
}