#include <iostream>
#include <vector>
#include <stdexcept>
#include "polynomials_quadratics/polynomial_utils.h"
#include "polynomials_quadratics/quadratic_utils.h"

int main() {
    std::cout << "--- Polynomials & Quadratics C++ Examples ---" << std::endl;

    using namespace michu_fr::polynomials_quadratics;

    // 1. Polynomial Formatting and Evaluation
    std::cout << "\n1. Formatting and Evaluation:" << std::endl;
    std::vector<double> p1_coeffs = {2.0, -3.0, 0.0, 5.0}; // 2x^3 - 3x^2 + 5
    std::cout << "   P1(x) = " << formatPolynomialToString(p1_coeffs) << std::endl;
    std::cout << "   P1(2) = " << evaluatePolynomial(p1_coeffs, 2.0) << std::endl; // Expected: 9

    std::vector<double> p_zero_coeffs = {0.0, 0.0, 0.0};
    std::cout << "   P_zero(x) = " << formatPolynomialToString(p_zero_coeffs) << std::endl;

    // 2. Polynomial Division
    std::cout << "\n2. Polynomial Division:" << std::endl;
    try {
        std::vector<double> dividend = {1.0, -5.0, 6.0};    // x^2 - 5x + 6
        std::vector<double> divisor  = {1.0, -2.0};       // x - 2
        PolynomialDivisionResult div_res1 = polynomialDivision(dividend, divisor);
        std::cout << "   (x^2-5x+6)/(x-2): " << div_res1.toString() << std::endl; // Q=x-3, R=0

        std::vector<double> dividend2 = {1.0, 0.0, 0.0, -1.0}; // x^3 - 1
        std::vector<double> divisor2  = {1.0, -1.0};      // x - 1
        PolynomialDivisionResult div_res2 = polynomialDivision(dividend2, divisor2);
        std::cout << "   (x^3-1)/(x-1): " << div_res2.toString() << std::endl; // Q=x^2+x+1, R=0
    } catch (const std::exception& e) {
        std::cerr << "   Division Error: " << e.what() << std::endl;
    }

    // 3. Quadratic Equation Solving
    std::cout << "\n3. Quadratic Equation Solving:" << std::endl;
    QuadraticSolution sol1 = solveQuadraticEquation(1, -5, 6);
    std::cout << "   x^2-5x+6=0: " << sol1.toString() << std::endl;
    QuadraticSolution sol2 = solveQuadraticEquation(1, -4, 4);
    std::cout << "   x^2-4x+4=0: " << sol2.toString() << std::endl;
    QuadraticSolution sol3 = solveQuadraticEquation(1, 2, 5);
    std::cout << "   x^2+2x+5=0: " << sol3.toString() << std::endl;
    QuadraticSolution sol_linear = solveQuadraticEquation(0, 2, -4); // 2x-4=0
    std::cout << "   2x-4=0: " << sol_linear.toString() << std::endl;


    // 4. Rational Roots
    std::cout << "\n4. Rational Roots:" << std::endl;
    try {
        std::vector<double> poly_rr1 = {1.0, -6.0, 11.0, -6.0}; // (x-1)(x-2)(x-3)
        std::vector<double> roots1 = findRationalRoots(poly_rr1);
        std::cout << "   Roots of " << formatPolynomialToString(poly_rr1) << ": [";
        for(size_t i=0; i<roots1.size(); ++i) std::cout << roots1[i] << (i==roots1.size()-1 ? "" : ", ");
        std::cout << "]" << std::endl;

        std::vector<double> poly_rr2 = {2.0, -1.0, -2.0, 1.0}; // (2x-1)(x-1)(x+1)
        std::vector<double> roots2 = findRationalRoots(poly_rr2);
        std::cout << "   Roots of " << formatPolynomialToString(poly_rr2) << ": [";
        for(size_t i=0; i<roots2.size(); ++i) std::cout << roots2[i] << (i==roots2.size()-1 ? "" : ", ");
        std::cout << "]" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "   Rational Root Error: " << e.what() << std::endl;
    }


    // 5. Roots-Coefficients Relations
    std::cout << "\n5. Roots-Coefficients Relations:" << std::endl;
    try {
        std::vector<double> qc_coeffs = {1.0, -7.0, 10.0}; // x^2 - 7x + 10
        RootsCoefficientsRelation qc_rel = relationRootsCoefficientsQuadratic(qc_coeffs);
        std::cout << "   Quadratic " << formatPolynomialToString(qc_coeffs) << ": " << qc_rel.toString() << std::endl;

        std::vector<double> cubic_coeffs = {1.0, -6.0, 11.0, -6.0}; // x^3 - 6x^2 + 11x - 6
        RootsCoefficientsRelation cubic_rel = relationRootsCoefficientsCubic(cubic_coeffs);
        std::cout << "   Cubic " << formatPolynomialToString(cubic_coeffs) << ": " << cubic_rel.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "   Relation Error: " << e.what() << std::endl;
    }

    // 6. Form Polynomial from Roots
    std::cout << "\n6. Form Polynomial from Roots:" << std::endl;
    std::vector<double> roots_to_form = {1.0, 2.0, 3.0};
    FormedPolynomial formed1 = formPolynomialFromRoots(roots_to_form, 1.0, "y");
    std::cout << "   From roots {1,2,3}, k=1: " << formed1.toString() << std::endl;

    std::vector<double> roots_to_form2 = {2.0, 2.0};
    FormedPolynomial formed2 = formPolynomialFromRoots(roots_to_form2, 2.0, "z"); // 2(z-2)^2
    std::cout << "   From roots {2,2}, k=2: " << formed2.toString() << std::endl;

    return 0;
}