#include "quadratic_utils.h"
#include "polynomial_utils.h" // For formatting the equation string
#include <vector>
#include <cmath>     // For std::sqrt
#include <optional>  // For std::optional

namespace michu_fr {
namespace polynomials_quadratics {

QuadraticSolution solveQuadraticEquation(double a, double b, double c) {
    std::string eq_str = formatPolynomialToString({a, b, c}) + " = 0";
    std::optional<double> disc_val;
    std::string nature;
    std::vector<ComplexNumber> roots_c;
    std::vector<double> roots_r;

    if (std::abs(a) < EPSILON) { // Linear or trivial
        if (std::abs(b) < EPSILON) { // c = 0
            if (std::abs(c) < EPSILON) {
                nature = "Identity (0x + 0 = 0)";
                // Roots represented by nature string
            } else {
                nature = "Contradiction (0 = non-zero)";
            }
        } else { // bx + c = 0
            nature = "Linear equation";
            roots_r.push_back(-c / b);
            roots_c.push_back(ComplexNumber(-c/b, 0.0));
        }
    } else { // Quadratic
        double discriminant = b * b - 4 * a * c;
        disc_val = discriminant;

        if (discriminant > EPSILON) {
            nature = "Two distinct real roots";
            double sqrt_D = std::sqrt(discriminant);
            double r1 = (-b + sqrt_D) / (2 * a);
            double r2 = (-b - sqrt_D) / (2 * a);
            roots_r.push_back(r1);
            roots_r.push_back(r2);
            roots_c.push_back(ComplexNumber(r1));
            roots_c.push_back(ComplexNumber(r2));
        } else if (std::abs(discriminant) < EPSILON) {
            nature = "Two equal real roots (repeated root)";
            double r_val = -b / (2 * a);
            roots_r.push_back(r_val);
            // roots_r.push_back(r_val); // or just one
            roots_c.push_back(ComplexNumber(r_val));
        } else { // D < 0
            nature = "Two complex conjugate roots";
            double sqrt_neg_D = std::sqrt(-discriminant);
            double real_part = -b / (2 * a);
            double imag_part = sqrt_neg_D / (2 * a);
            roots_c.push_back(ComplexNumber(real_part, imag_part));
            roots_c.push_back(ComplexNumber(real_part, -imag_part));
        }
    }
    return QuadraticSolution(eq_str, a, b, c, disc_val, nature, roots_c, roots_r);
}

} // namespace polynomials_quadratics
} // namespace michu_fr