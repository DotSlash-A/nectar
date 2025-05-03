// cpp_code/circles/circle_utils.cc
#include "circle_utils.h"
#include "../matrix/matrix_utils.h" // For determinant
#include <cmath>        // std::sqrt, std::fabs, std::pow
#include <stdexcept>    // std::runtime_error, std::invalid_argument
#include <sstream>      // std::ostringstream
#include <iomanip>      // std::fixed, std::setprecision
#include <limits>       // std::numeric_limits
#include <regex>        // std::regex, std::smatch, std::regex_search, std::regex_replace

namespace geometry {
namespace circles {

// --- Constants ---
const double EPSILON = 1e-9; // Tolerance for floating-point comparisons

// --- Helper Functions ---

// Formats a double nicely for equations
std::string formatDouble(double val, int precision = 4) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << val;
    std::string str = oss.str();
    // Remove trailing zeros and possibly the decimal point
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    if (str.back() == '.') {
        str.pop_back();
    }
    return str;
}

// Helper to append a term like "+ 5x" or "- y" or "+ 6"
void appendTerm(std::ostream& oss, double coeff, const std::string& var, bool isFirstTerm) {
    if (std::fabs(coeff) < EPSILON) return; // Skip zero terms

    double absCoeff = std::fabs(coeff);
    bool coeffIsOne = std::fabs(absCoeff - 1.0) < EPSILON;

    // Add sign (+ or -), skipping '+' for the very first term
    if (!isFirstTerm) {
        oss << ((coeff < 0) ? " - " : " + ");
    } else if (coeff < 0) {
        oss << "-"; // Negative first term
    }

    // Add coefficient value unless it's 1 and there's a variable
    if (!coeffIsOne || var.empty()) {
        oss << formatDouble(absCoeff);
        if (!var.empty()) { // Add multiplication sign if coeff and var are present
            oss << "*";
        }
    }

    // Add variable part
    oss << var;
}

// Formats a general equation Ax^2 + By^2 + Cx + Dy + E = 0
std::string formatGeneralEquation(double a, double b, double c, double d, double e) {
    std::ostringstream oss;
    bool first = true;

    if (std::fabs(a) > EPSILON) { appendTerm(oss, a, "x^2", first); first = false; }
    if (std::fabs(b) > EPSILON) { appendTerm(oss, b, "y^2", first); first = false; }
    if (std::fabs(c) > EPSILON) { appendTerm(oss, c, "x", first);   first = false; }
    if (std::fabs(d) > EPSILON) { appendTerm(oss, d, "y", first);   first = false; }
    if (std::fabs(e) > EPSILON) { appendTerm(oss, e, "", first);    first = false; }

    if (first) { // If no terms were added
        oss << "0";
    }

    oss << " = 0";
    return oss.str();
}

// VERY BASIC Regex-based parser for Ax^2+By^2+Cx+Dy+E=0
// HIGHLY RECOMMENDED to use a dedicated parsing library or pass coefficients directly
CircleCoeffs parseGeneralCircleEquation(const std::string& equationString) {
    CircleCoeffs coeffs = {0.0, 0.0, 0.0, 0.0, 0.0};
    std::string eq = equationString;

    // Preprocessing: remove spaces, make implicit '+' explicit
    eq.erase(std::remove_if(eq.begin(), eq.end(), ::isspace), eq.end());
    eq = std::regex_replace(eq, std::regex("([+-])"), " $1"); // Add space before sign
    eq = std::regex_replace(eq, std::regex("^\\+"), "");      // Remove leading +
    if (eq.find('=') == std::string::npos) {
        throw std::invalid_argument("Equation must contain '=' sign (e.g., '... = 0')");
    }
    eq = eq.substr(0, eq.find('=')); // Keep only LHS

    // Regex for terms (simplified - might miss complex cases)
    std::regex term_regex(
        "([+-]?)(\\d*\\.?\\d+)?(?:\\*?([xy])(?:\\^([2]))?)?");
        // Group 1: Sign (+/-)
        // Group 2: Coefficient number (optional)
        // Group 3: Variable (x or y) (optional)
        // Group 4: Exponent (only '2') (optional)

    auto terms_begin = std::sregex_iterator(eq.begin(), eq.end(), term_regex);
    auto terms_end = std::sregex_iterator();

    for (std::sregex_iterator i = terms_begin; i != terms_end; ++i) {
        std::smatch match = *i;
        if (match.str().empty()) continue; // Skip empty matches

        double sign = (match[1].str() == "-") ? -1.0 : 1.0;
        double coeff_val = 1.0; // Default for implicit coefficients like 'x' or '-y^2'
        if (match[2].matched) { // If coefficient number is present
            try {
                 coeff_val = std::stod(match[2].str());
            } catch (const std::out_of_range& oor) {
                 throw std::runtime_error("Coefficient out of range: " + match[2].str());
            } catch (const std::invalid_argument& ia) {
                 // This might happen if regex is imperfect, handle gracefully
                 if (match[3].matched) { // If variable exists, likely implicit 1
                     coeff_val = 1.0;
                 } else { // Likely just a constant term matched poorly
                     try { // Try parsing the whole match as constant
                          coeff_val = std::stod(match.str());
                          coeffs.e += coeff_val; // Add to constant if it looks like one
                          continue; // Move to next match
                     } catch(...) {
                          throw std::invalid_argument("Cannot parse term coefficient: " + match.str());
                     }
                 }
            }

        } else if (!match[3].matched) {
            // No coefficient number AND no variable, might be a constant term missed earlier
             try {
                 coeff_val = std::stod(match.str()); // Try parsing whole match
             } catch(...) {
                 throw std::invalid_argument("Cannot parse constant term: " + match.str());
             }
             coeffs.e += coeff_val;
             continue;
        }


        double value = sign * coeff_val;

        if (match[3].matched) { // Variable part exists
            std::string var = match[3].str();
            bool is_squared = match[4].matched && match[4].str() == "2";

            if (var == "x") {
                if (is_squared) coeffs.a += value; else coeffs.c += value;
            } else if (var == "y") {
                if (is_squared) coeffs.b += value; else coeffs.d += value;
            }
        } else { // No variable part, it's a constant
            coeffs.e += value;
        }
    }

    return coeffs;
}


// --- Function Implementations ---

CircleEqnResponse getCircleEquationsFromCenterRadius(const CircleGeneralInput& input) {
    if (input.r < 0) {
        throw std::invalid_argument("Radius cannot be negative.");
    }

    double h = input.h;
    double k = input.k;
    double r = input.r;
    double rSquared = r * r;

    // Standard Form: (x - h)^2 + (y - k)^2 = r^2
    std::ostringstream ss_standard;
    ss_standard << "(x " << (h < 0 ? "+ " : "- ") << formatDouble(std::fabs(h)) << ")^2 + "
                << "(y " << (k < 0 ? "+ " : "- ") << formatDouble(std::fabs(k)) << ")^2 = "
                << formatDouble(rSquared);

    // General Form: x^2 + y^2 + Cx + Dy + E = 0
    double coeffC = -2 * h;
    double coeffD = -2 * k;
    double coeffE = h * h + k * k - rSquared;
    std::string generalForm = formatGeneralEquation(1.0, 1.0, coeffC, coeffD, coeffE);

    return {ss_standard.str(), generalForm, h, k, r, 1.0, 1.0, coeffC, coeffD, coeffE};
}

CircleDetailsResponse getCircleDetailsFromCoeffs(const CircleCoeffs& coeffs, const std::string& inputEqStr) {
     double A = coeffs.a;
     double B = coeffs.b;
     double C = coeffs.c;
     double D = coeffs.d;
     double E = coeffs.e;

     // --- Validate if it's a circle ---
     if (std::fabs(A) < EPSILON || std::fabs(B) < EPSILON) {
         throw std::invalid_argument("Not a valid circle/ellipse equation (A or B is zero).");
     }
     if (std::fabs(A - B) > EPSILON) {
        std::ostringstream oss;
        oss << "Not a circle equation (coeff x^2 (" << formatDouble(A) << ") != coeff y^2 (" << formatDouble(B) << ")).";
         throw std::invalid_argument(oss.str());
     }

     // --- Normalize coefficients (divide by A if A is not 1) ---
     std::optional<std::string> normalizedEqStrOpt = std::nullopt;
     double normC = C, normD = D, normE = E;

     if (std::fabs(A - 1.0) > EPSILON) {
         normC /= A;
         normD /= A;
         normE /= A;
         normalizedEqStrOpt = formatGeneralEquation(1.0, 1.0, normC, normD, normE);
     } else {
          // Already normalized or A=1, format original normalized form
          normalizedEqStrOpt = formatGeneralEquation(A, B, C, D, E);
     }

     // --- Calculate center (h, k) --- (Using normalized coefficients)
     double h = -normC / 2.0;
     double k = -normD / 2.0;

     // --- Calculate radius (r) --- (Using normalized E)
     double radiusSquared = h * h + k * k - normE;

     if (radiusSquared < -EPSILON) { // Allow for small negative due to precision
        std::ostringstream oss;
        oss << "Not a real circle (radius squared = " << formatDouble(radiusSquared) << " is negative).";
         throw std::invalid_argument(oss.str());
     }
      if (radiusSquared < 0) {
          radiusSquared = 0; // Treat very small negative as zero radius
      }

     double r = std::sqrt(radiusSquared);

     return {h, k, r, inputEqStr, normalizedEqStrOpt};
}

CircleDetailsResponse getCircleDetailsFromGeneralForm(const CircleGeneralFormInput& data) {
     // WARNING: Using basic parser, may fail on complex inputs
     try {
         CircleCoeffs coeffs = parseGeneralCircleEquation(data.equation);
         return getCircleDetailsFromCoeffs(coeffs, data.equation);
     } catch (const std::exception& e) {
         // Re-throw with context
          throw std::runtime_error("Failed to get details from equation string '" + data.equation + "': " + e.what());
     }
}

// CircleEquationOnlyResponse getCircleFromThreePoints(const CircleWThreePointsInput& data) {
//     double x1 = data.p.x, y1 = data.p.y;
//     double x2 = data.q.x, y2 = data.q.y;
//     double x3 = data.r.x, y3 = data.r.y;

//     double c1 = -(x1 * x1 + y1 * y1);
//     double c2 = -(x2 * x2 + y2 * y2);
//     double c3 = -(x3 * x3 + y3 * y3);

//     // Use matrix_utils for determinant
//     double aDet = matrix::determinant3x3(x1, y1, 1, x2, y2, 1, x3, y3, 1);
//     double bDet = matrix::determinant3x3(c1, y1, 1, c2, y2, 1, c3, y3, 1);
//     double cDet = matrix::determinant3x3(x1, c1, 1, x2, c2, 1, x3, c3, 1);
//     double dDet = matrix::determinant3x3(x1, y1, c1, x2, y2, c2, x3, y3, c3);

//     if (std::fabs(aDet) < EPSILON) {
//         throw std::invalid_argument("Points are collinear, cannot form a unique circle.");
//     }

//     // Coefficients for Ax^2 + Ay^2 + Dx + Ey + F = 0
//     double coeffA = aDet;
//     double coeffD_gen = bDet; // Renamed to avoid confusion with local D
//     double coeffE_gen = cDet; // Renamed
//     double coeffF_gen = dDet; // Renamed

//     // Normalize by dividing by coeffA
//     double normD = coeffD_gen / coeffA;
//     double normE = coeffE_gen / coeffA;
//     double normF = coeffF_gen / coeffA;

//     std::string equation = formatGeneralEquation(1.0, 1.0, normD, normE, normF);
//     return {equation};
// }

// CircleEquationOnlyResponse getCircleCenterOnLine(const Coordinates& p,
//                                                  const Coordinates& q,
//                                                  const GeneralLineInput& line) {
//     double x1 = p.x, y1 = p.y;
//     double x2 = q.x, y2 = q.y;
//     double A = line.a, B = line.b, C_line = line.c; // Rename C to avoid conflict

//     if (std::fabs(x1 - x2) < EPSILON && std::fabs(y1 - y2) < EPSILON) {
//         throw std::invalid_argument("Points p and q cannot be the same.");
//     }

//     // Solve system for g, f, c in x^2+y^2+2gx+2fy+c=0 using Cramer's Rule
//     // M = [ 2*x1, 2*y1, 1 ]
//     //     [ 2*x2, 2*y2, 1 ]
//     //     [ -A,   -B,   0 ]
//     double detM = matrix::determinant3x3(2*x1, 2*y1, 1, 2*x2, 2*y2, 1, -A, -B, 0);

//     if (std::fabs(detM) < EPSILON) {
//         throw std::runtime_error("Could not find a unique solution (determinant is zero). Check points and line.");
//     }

//     // K = [ -(x1^2+y1^2) ]
//     //     [ -(x2^2+y2^2) ]
//     //     [ -C_line       ]
//     double k1 = -(x1*x1 + y1*y1);
//     double k2 = -(x2*x2 + y2*y2);
//     double k3 = -C_line;

//     double detMg = matrix::determinant3x3(k1, 2*y1, 1, k2, 2*y2, 1, k3, -B, 0);
//     double detMf = matrix::determinant3x3(2*x1, k1, 1, 2*x2, k2, 1, -A, k3, 0);
//     double detMc = matrix::determinant3x3(2*x1, 2*y1, k1, 2*x2, 2*y2, k2, -A, -B, k3);

//     double g = detMg / detM;
//     double f = detMf / detM;
//     double c_circle = detMc / detM; // Rename 'c'

//     // Eq: x^2 + y^2 + (2g)x + (2f)y + c_circle = 0
//     std::string equation = formatGeneralEquation(1.0, 1.0, 2 * g, 2 * f, c_circle);
//     return {equation};
// }

ParametricCircleResponse getCircleParametricFromCoeffs(const CircleCoeffs& coeffs) {
    // 1. Get center and radius
    // Pass empty string as inputEqStr since we don't have it here
    CircleDetailsResponse details = getCircleDetailsFromCoeffs(coeffs, "");
    double h = details.centerH;
    double k = details.centerK;
    double r = details.radius;

    // 2. Format parametric strings
    std::ostringstream ossX, ossY;
    ossX << formatDouble(h) << (r >= 0 ? " + " : " - ") << formatDouble(std::fabs(r)) << "*cos(t)";
    ossY << formatDouble(k) << (r >= 0 ? " + " : " - ") << formatDouble(std::fabs(r)) << "*sin(t)";

    return {ossX.str(), ossY.str(), h, k, r};
}


ParametricCircleResponse getCircleParametric(const EquationInput& data) {
    try {
        // 1. Get details (includes parsing)
        CircleDetailsResponse details = getCircleDetailsFromGeneralForm({data.equation});
        // 2. Generate parametric strings from details
        double h = details.centerH;
        double k = details.centerK;
        double r = details.radius;

        std::ostringstream ossX, ossY;
        ossX << formatDouble(h) << (r >= 0 ? " + " : " - ") << formatDouble(std::fabs(r)) << "*cos(t)";
        ossY << formatDouble(k) << (r >= 0 ? " + " : " - ") << formatDouble(std::fabs(r)) << "*sin(t)";

        return {ossX.str(), ossY.str(), h, k, r};
    } catch (const std::exception& e) {
         throw std::runtime_error("Failed to get parametric equations from '" + data.equation + "': " + e.what());
    }
}

CircleEquationOnlyResponse getCircleFromDiameter(const Coordinates& p, const Coordinates& q) {
    double x1 = p.x, y1 = p.y;
    double x2 = q.x, y2 = q.y;

    // Eq: x^2 + y^2 - (x1+x2)x - (y1+y2)y + (x1*x2 + y1*y2) = 0
    double coeffC = -(x1 + x2);
    double coeffD = -(y1 + y2);
    double coeffE = (x1 * x2) + (y1 * y2);

    std::string equation = formatGeneralEquation(1.0, 1.0, coeffC, coeffD, coeffE);
    return {equation};
}


PointPositionResponse getPointPositionRelativeToCircle(const CircleCoeffs& coeffs, const Coordinates& point) {
     // 1. Get center and radius
     // Pass empty string as inputEqStr since we don't have it here
     CircleDetailsResponse details = getCircleDetailsFromCoeffs(coeffs, "");
     double h = details.centerH;
     double k = details.centerK;
     double r = details.radius;
     double rSquared = r * r;

     // 2. Calculate squared distance
     double px = point.x;
     double py = point.y;
     double distSq = std::pow(px - h, 2) + std::pow(py - k, 2);

     // 3. Compare
     if (std::fabs(distSq - rSquared) < EPSILON) {
         return {"on"};
     } else if (distSq < rSquared) {
         return {"inside"};
     } else {
         return {"outside"};
     }
}


PointPositionResponse getPointPositionRelativeToCircle(const EquationInput& data, const Coordinates& point) {
    try {
        // 1. Get details (includes parsing)
        CircleDetailsResponse details = getCircleDetailsFromGeneralForm({data.equation});
        double h = details.centerH;
        double k = details.centerK;
        double r = details.radius;
        double rSquared = r * r;

        // 2. Calculate squared distance
        double px = point.x;
        double py = point.y;
        double distSq = std::pow(px - h, 2) + std::pow(py - k, 2);

        // 3. Compare
        if (std::fabs(distSq - rSquared) < EPSILON) {
             return {"on"};
         } else if (distSq < rSquared) {
             return {"inside"};
         } else {
             return {"outside"};
         }
    } catch (const std::exception& e) {
         throw std::runtime_error("Failed to get point position from equation '" + data.equation + "': " + e.what());
    }
}


} // namespace circles
} // namespace geometry



// ---main
// cpp_code/main.cc
// #include "lines/geometry_types.h" // Assuming Coordinates is here
// #include "circles/circle_utils.h" // Include the circle utils header
// #include <iostream>
// #include <vector>
// #include <iomanip> // For std::fixed, std::setprecision

// // Need << operator for Coordinates if not defined in its header
// namespace geometry {
//     std::ostream& operator<<(std::ostream& os, const Coordinates& p) {
//         os << "(" << p.x << ", " << p.y << ")";
//         return os;
//     }
// }

// int main() {
//     std::cout << std::fixed << std::setprecision(4); // Set default output precision

//     std::cout << "--- Circle Calculations ---" << std::endl;

//     // Using namespaces for brevity
//     using namespace geometry;
//     using namespace geometry::circles;

//     // Example C1: Circle Eq from Center/Radius
//     try {
//         CircleGeneralInput c1_input = {2.0, -3.0, 5.0}; // h=2, k=-3, r=5
//         CircleEqnResponse c1_eqs = getCircleEquationsFromCenterRadius(c1_input);
//         std::cout << "C1: Circle from h=2, k=-3, r=5:" << std::endl;
//         std::cout << "  Standard: " << c1_eqs.standardForm << std::endl;
//         std::cout << "  General:  " << c1_eqs.generalForm << std::endl;
//         std::cout << "  Center: (" << c1_eqs.centerH << ", " << c1_eqs.centerK << ")" << std::endl;
//         std::cout << "  Radius: " << c1_eqs.radius << std::endl;
//     } catch (const std::exception& e) {
//         std::cerr << "Error C1: " << e.what() << std::endl;
//     }
//     std::cout << std::endl;

//     // Example C2: Circle Details from General Form String (Using Basic Parser)
//     try {
//         CircleGeneralFormInput c2_input = {"2*x^2 + 2*y^2 + 8*x - 12*y + 6 = 0"};
//         CircleDetailsResponse c2_details = getCircleDetailsFromGeneralForm(c2_input);
//         std::cout << "C2: Details from '" << c2_input.equation << "':" << std::endl;
//         std::cout << "  Center (h, k): (" << c2_details.centerH << ", " << c2_details.centerK << ")" << std::endl;
//         std::cout << "  Radius r:      " << c2_details.radius << std::endl;
//         if (c2_details.normalizedEquation) {
//              std::cout << "  Normalized Eq: " << *c2_details.normalizedEquation << std::endl;
//         }
//     } catch (const std::exception& e) {
//         std::cerr << "Error C2: " << e.what() << std::endl;
//     }
//      std::cout << std::endl;

//     // Example C3: Circle from 3 Points
//     try {
//         CircleWThreePointsInput c3_input = {{1, 1}, {2, 4}, {5, 3}}; // p, q, r
//         CircleEquationOnlyResponse c3_eq = getCircleFromThreePoints(c3_input);
//         std::cout << "C3: Circle from " << c3_input.p << ", " << c3_input.q << ", " << c3_input.r << ":" << std::endl;
//         std::cout << "  Equation: " << c3_eq.circleEquation << std::endl;
//          // Expected: x^2 + y^2 - 6.0000*x - 2.0000*y + 5.0000 = 0
//     } catch (const std::exception& e) {
//         std::cerr << "Error C3: " << e.what() << std::endl;
//     }
//     std::cout << std::endl;

//     // Example C4: Circle from Diameter Endpoints
//     try {
//         Coordinates diamP1 = {1, 2};
//         Coordinates diamP2 = {5, 6};
//         CircleEquationOnlyResponse c4_eq = getCircleFromDiameter(diamP1, diamP2);
//         std::cout << "C4: Circle with diameter " << diamP1 << " to " << diamP2 << ":" << std::endl;
//         std::cout << "  Equation: " << c4_eq.circleEquation << std::endl;
//          // Expected: x^2 + y^2 - 6.0000*x - 8.0000*y + 17.0000 = 0
//     } catch (const std::exception& e) {
//         std::cerr << "Error C4: " << e.what() << std::endl;
//     }
//     std::cout << std::endl;

//     // Example C5: Parametric Equations from General Form String
//     try {
//         EquationInput c5_input = {"x^2 + y^2 - 6x - 2y + 5 = 0"};
//         ParametricCircleResponse c5_para = getCircleParametric(c5_input);
//         std::cout << "C5: Parametric for '" << c5_input.equation << "':" << std::endl;
//         std::cout << "  x(t) = " << c5_para.parametricX << std::endl; // Expect 3.0000 + 2.2361*cos(t)
//         std::cout << "  y(t) = " << c5_para.parametricY << std::endl; // Expect 1.0000 + 2.2361*sin(t)
//         std::cout << "  Center: (" << c5_para.centerH << ", " << c5_para.centerK << ")" << std::endl;
//         std::cout << "  Radius: " << c5_para.radius << std::endl;
//     } catch (const std::exception& e) {
//         std::cerr << "Error C5: " << e.what() << std::endl;
//     }
//     std::cout << std::endl;


//      // Example C6: Point Position Relative to Circle
//      try {
//          EquationInput c6_eq_input = {"x^2 + y^2 - 4x = 0"}; // Center (2,0), r=2
//          Coordinates p_in = {1, 0};
//          Coordinates p_on = {4, 0};
//          Coordinates p_out = {5, 5};
//          PointPositionResponse pos_in = getPointPositionRelativeToCircle(c6_eq_input, p_in);
//          PointPositionResponse pos_on = getPointPositionRelativeToCircle(c6_eq_input, p_on);
//          PointPositionResponse pos_out = getPointPositionRelativeToCircle(c6_eq_input, p_out);
//          std::cout << "C6: Point " << p_in << " relative to " << c6_eq_input.equation << ": " << pos_in.position << std::endl;
//          std::cout << "C6: Point " << p_on << " relative to " << c6_eq_input.equation << ": " << pos_on.position << std::endl;
//          std::cout << "C6: Point " << p_out << " relative to " << c6_eq_input.equation << ": " << pos_out.position << std::endl;
//      } catch (const std::exception& e) {
//          std::cerr << "Error C6: " << e.what() << std::endl;
//      }
//       std::cout << std::endl;

//      // Example C7: Circle Center On Line
//      try {
//         Coordinates p_c7 = {1, 0};
//         Coordinates q_c7 = {3, 0};
//         GeneralLineInput line_c7 = {0, 1, -2}; // Line y=2
//         CircleEquationOnlyResponse resp_c7 = getCircleCenterOnLine(p_c7, q_c7, line_c7);
//         std::cout << "C7: Circle through " << p_c7 << ", " << q_c7 << " with center on y=2:" << std::endl;
//         std::cout << "  Equation: " << resp_c7.circleEquation << std::endl;
//          // Expected: x^2 + y^2 - 4.0000*x - 4.0000*y + 3.0000 = 0
//      } catch (const std::exception& e) {
//         std::cerr << "Error C7: " << e.what() << std::endl;
//      }
//       std::cout << std::endl;


//     return 0;
// }