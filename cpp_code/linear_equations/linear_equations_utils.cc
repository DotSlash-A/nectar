#include "linear_equations_utils.h"
#include <cmath>      // For std::abs, std::sqrt, NAN
#include <stdexcept>  // For std::invalid_argument
#include <iomanip>    // For std::fixed, std::setprecision
#include <limits>     // For std::numeric_limits

namespace michu_fr {
namespace linear_equations {

const std::string CONSISTENT_UNIQUE = "CONSISTENT_UNIQUE";
const std::string CONSISTENT_INFINITE = "CONSISTENT_INFINITE";
const std::string INCONSISTENT_PARALLEL = "INCONSISTENT_PARALLEL";
const double EPSILON = 1e-9; // For floating point comparisons

// Helper to format doubles nicely for ratios and steps
std::string format_double(double val, int precision = 2) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << val;
    std::string s = oss.str();
    // Remove trailing zeros and decimal point if it's effectively an integer
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    if (s.back() == '.') {
        s.pop_back();
    }
    return s;
}


ConsistencyCheckResult checkConsistency(double a1, double b1, double c1, double a2, double b2, double c2) {
    EquationCoefficients coeffs(a1, b1, c1, a2, b2, c2);
    std::map<std::string, std::string> ratio_strings;
    
    ratio_strings["a1/a2"] = (std::abs(a2) > EPSILON) ? format_double(a1/a2, 4) : ((std::abs(a1) < EPSILON) ? "0/0" : "undef (a1/0)");
    ratio_strings["b1/b2"] = (std::abs(b2) > EPSILON) ? format_double(b1/b2, 4) : ((std::abs(b1) < EPSILON) ? "0/0" : "undef (b1/0)");
    ratio_strings["c1/c2"] = (std::abs(c2) > EPSILON) ? format_double(c1/c2, 4) : ((std::abs(c1) < EPSILON) ? "0/0" : "undef (c1/0)");

    std::string consistency_type_val;
    std::string description_val;
    std::string graphical_interpretation_val;

    double determinant = a1 * b2 - a2 * b1;

    if (std::abs(determinant) > EPSILON) {
        consistency_type_val = CONSISTENT_UNIQUE;
        description_val = "System has a unique solution (intersecting lines) because a1*b2 - a2*b1 = " + format_double(determinant, 4) + " != 0.";
        graphical_interpretation_val = "Lines intersect at a single point.";
    } else {
        // Determinant is zero. Check for parallel or coincident lines.
        // D_x' = c1*b2 - c2*b1 (related to x in Cramer's rule)
        // D_y' = a1*c2 - a2*c1 (related to y in Cramer's rule)
        double dx_prime = c1 * b2 - c2 * b1;
        double dy_prime = a1 * c2 - a2 * c1;

        if (std::abs(dx_prime) > EPSILON || std::abs(dy_prime) > EPSILON) {
            // If determinant is 0, but dx' or dy' is not 0, then lines are parallel and distinct (no solution).
            // This also catches 0x+0y=C (C!=0) cases if one equation is like that.
            consistency_type_val = INCONSISTENT_PARALLEL;
            description_val = "System is inconsistent (parallel lines). Determinant is zero, but system cannot satisfy 0=0 for both equations.";
            if ((std::abs(a1) < EPSILON && std::abs(b1) < EPSILON && std::abs(c1) > EPSILON) ||
                (std::abs(a2) < EPSILON && std::abs(b2) < EPSILON && std::abs(c2) > EPSILON)) {
                description_val = "System is inconsistent. One equation is of the form 0x + 0y = C (C!=0).";
            }
            graphical_interpretation_val = "Lines are parallel and distinct.";
        } else {
            // Determinant is 0, AND dx_prime is 0, AND dy_prime is 0.
            // This means lines are coincident (infinitely many solutions).
            // This includes cases like 0x+0y=0.
            consistency_type_val = CONSISTENT_INFINITE;
            description_val = "System has infinitely many solutions (coincident lines). All determinants (D, Dx', Dy') are zero.";
            graphical_interpretation_val = "Lines are coincident (overlap completely).";
        }
    }
     description_val += " Ratios: a1/a2=" + ratio_strings["a1/a2"] +
                       ", b1/b2=" + ratio_strings["b1/b2"] +
                       ", c1/c2=" + ratio_strings["c1/c2"] + ".";

    return ConsistencyCheckResult(coeffs, consistency_type_val, description_val, ratio_strings, graphical_interpretation_val);
}


SolutionResult solveGeneral(double a1, double b1, double c1, double a2, double b2, double c2) {
    EquationCoefficients coeffs(a1, b1, c1, a2, b2, c2);
    std::vector<std::string> steps_vec;
    steps_vec.push_back("Attempting solution using Cramer's Rule / Determinants.");

    ConsistencyCheckResult consistency = checkConsistency(a1, b1, c1, a2, b2, c2);

    if (consistency.consistency_type == CONSISTENT_UNIQUE) {
        double determinant = a1 * b2 - a2 * b1; // Should be non-zero
        double dx = c1 * b2 - c2 * b1;
        double dy = a1 * c2 - a2 * c1;

        double x = dx / determinant;
        double y = dy / determinant;
        steps_vec.push_back("D = a1*b2 - a2*b1 = " + format_double(determinant));
        steps_vec.push_back("Dx = c1*b2 - c2*b1 = " + format_double(dx));
        steps_vec.push_back("Dy = a1*c2 - a2*c1 = " + format_double(dy));
        steps_vec.push_back("x = Dx / D = " + format_double(x));
        steps_vec.push_back("y = Dy / D = " + format_double(y));

        return SolutionResult(coeffs, CONSISTENT_UNIQUE, consistency.description,
                              std::make_optional(x), std::make_optional(y),
                              format_double(x, 4), format_double(y, 4),
                              "General (Cramer's Rule)", steps_vec);
    } else if (consistency.consistency_type == CONSISTENT_INFINITE) {
        steps_vec.push_back("System has infinitely many solutions.");
        return SolutionResult(coeffs, CONSISTENT_INFINITE, consistency.description,
                              std::nullopt, std::nullopt, "Infinite", "Infinite",
                              "General (Analysis)", steps_vec);
    } else { // INCONSISTENT_PARALLEL
        steps_vec.push_back("System has no solution.");
        return SolutionResult(coeffs, INCONSISTENT_PARALLEL, consistency.description,
                              std::nullopt, std::nullopt, "None", "None",
                              "General (Analysis)", steps_vec);
    }
}

SolutionResult solveBySubstitution(double a1, double b1, double c1, double a2, double b2, double c2) {
    EquationCoefficients coeffs(a1, b1, c1, a2, b2, c2);
    std::vector<std::string> steps_vec;
    steps_vec.push_back("Method: Substitution");

    ConsistencyCheckResult consistency = checkConsistency(a1, b1, c1, a2, b2, c2);
    if (consistency.consistency_type != CONSISTENT_UNIQUE) {
        return SolutionResult(coeffs, consistency.consistency_type, consistency.description,
                              std::nullopt, std::nullopt,
                              (consistency.consistency_type == CONSISTENT_INFINITE ? "Infinite" : "None"),
                              (consistency.consistency_type == CONSISTENT_INFINITE ? "Infinite" : "None"),
                              "Substitution (Analysis)", steps_vec);
    }

    // Try to express x from eq1: x = (c1 - b1*y) / a1
    if (std::abs(a1) > EPSILON) {
        steps_vec.push_back("From eq1: " + format_double(a1) + "x = " + format_double(c1) + " - " + format_double(b1) + "y");
        steps_vec.push_back("  => x = (" + format_double(c1) + " - " + format_double(b1) + "y) / " + format_double(a1));
        // Substitute into eq2: a2 * [ (c1 - b1*y) / a1 ] + b2*y = c2
        // Multiply by a1: a2*(c1 - b1*y) + a1*b2*y = a1*c2
        // a2*c1 - a2*b1*y + a1*b2*y = a1*c2
        // (a1*b2 - a2*b1)*y = a1*c2 - a2*c1
        double y_coeff = a1 * b2 - a2 * b1; // This is the determinant
        double y_const = a1 * c2 - a2 * c1; // This is Dy
        steps_vec.push_back("Substitute x into eq2: " + format_double(a2) + " * [(" + format_double(c1) + " - " +
                            format_double(b1) + "y) / " + format_double(a1) + "] + " + format_double(b2) + "y = " + format_double(c2));
        steps_vec.push_back("Simplified: (" + format_double(y_coeff) + ")y = " + format_double(y_const));

        if (std::abs(y_coeff) > EPSILON) { // Should be true if unique solution
            double y = y_const / y_coeff;
            double x = (c1 - b1 * y) / a1;
            steps_vec.push_back("Solved for y: y = " + format_double(y_const) + " / " + format_double(y_coeff) + " = " + format_double(y, 4));
            steps_vec.push_back("Substitute y back to find x: x = (" + format_double(c1) + " - " + format_double(b1) + "*" + format_double(y, 4) + ") / " + format_double(a1) + " = " + format_double(x, 4));
            return SolutionResult(coeffs, CONSISTENT_UNIQUE, consistency.description,
                                  std::make_optional(x), std::make_optional(y),
                                  format_double(x, 4), format_double(y, 4),
                                  "Substitution", steps_vec);
        }
    }
    // Try to express y from eq1: y = (c1 - a1*x) / b1 (if a1 was 0 or previous attempt failed)
    else if (std::abs(b1) > EPSILON) {
        steps_vec.push_back("From eq1 (since a1 is near zero): " + format_double(b1) + "y = " + format_double(c1) + " - " + format_double(a1) + "x");
        steps_vec.push_back("  => y = (" + format_double(c1) + " - " + format_double(a1) + "x) / " + format_double(b1));
        // Substitute into eq2: a2*x + b2 * [ (c1 - a1*x) / b1 ] = c2
        // Multiply by b1: a2*b1*x + b2*(c1 - a1*x) = b1*c2
        // a2*b1*x + b2*c1 - a1*b2*x = b1*c2
        // (a2*b1 - a1*b2)*x = b1*c2 - b2*c1
        double x_coeff = a2 * b1 - a1 * b2; // This is -determinant
        double x_const = b1 * c2 - b2 * c1; // This is -Dx
         steps_vec.push_back("Substitute y into eq2: ... ");
        steps_vec.push_back("Simplified: (" + format_double(x_coeff) + ")x = " + format_double(x_const));

        if (std::abs(x_coeff) > EPSILON) {
            double x = x_const / x_coeff;
            double y = (c1 - a1 * x) / b1;
             steps_vec.push_back("Solved for x: x = " + format_double(x, 4));
             steps_vec.push_back("Substitute x back to find y: y = " + format_double(y, 4));
            return SolutionResult(coeffs, CONSISTENT_UNIQUE, consistency.description,
                                  std::make_optional(x), std::make_optional(y),
                                  format_double(x, 4), format_double(y, 4),
                                  "Substitution", steps_vec);
        }
    }
    // If both a1 and b1 are zero in eq1, eq1 is 0 = c1.
    // This should have been caught by consistency (unless c1=0 making eq1 trivial).
    // For a unique solution, this path implies something went wrong or equations are very simple.
    // Fallback to general solver if simple substitution paths fail for unique case.
    steps_vec.push_back("Simple substitution paths complex or failed. Falling back.");
    return solveGeneral(a1, b1, c1, a2, b2, c2);
}


SolutionResult solveByElimination(double a1, double b1, double c1, double a2, double b2, double c2) {
    EquationCoefficients coeffs(a1, b1, c1, a2, b2, c2);
    std::vector<std::string> steps_vec;
    steps_vec.push_back("Method: Elimination");

    ConsistencyCheckResult consistency = checkConsistency(a1, b1, c1, a2, b2, c2);
    if (consistency.consistency_type != CONSISTENT_UNIQUE) {
        return SolutionResult(coeffs, consistency.consistency_type, consistency.description,
                              std::nullopt, std::nullopt,
                              (consistency.consistency_type == CONSISTENT_INFINITE ? "Infinite" : "None"),
                              (consistency.consistency_type == CONSISTENT_INFINITE ? "Infinite" : "None"),
                              "Elimination (Analysis)", steps_vec);
    }

    // Try to eliminate y:
    // eq1 * b2: a1*b2*x + b1*b2*y = c1*b2
    // eq2 * b1: a2*b1*x + b2*b1*y = c2*b1
    // Subtract: (a1*b2 - a2*b1)*x = c1*b2 - c2*b1
    double x_coeff = a1 * b2 - a2 * b1; // Determinant
    double x_const = c1 * b2 - c2 * b1; // Dx

    steps_vec.push_back("To eliminate y: Multiply eq1 by " + format_double(b2) + " and eq2 by " + format_double(b1) + " (or their negatives if needed).");
    steps_vec.push_back(format_double(a1*b2) + "x + " + format_double(b1*b2) + "y = " + format_double(c1*b2));
    steps_vec.push_back(format_double(a2*b1) + "x + " + format_double(b1*b2) + "y = " + format_double(c2*b1));
    steps_vec.push_back("Subtracting the modified equations yields: (" + format_double(x_coeff) + ")x = " + format_double(x_const));
    
    if (std::abs(x_coeff) > EPSILON) { // Should be true for unique solution
        double x = x_const / x_coeff;
        double y;
        // Substitute x back into one of the original equations to find y
        // Try eq1: a1*x + b1*y = c1 => b1*y = c1 - a1*x
        if (std::abs(b1) > EPSILON) {
            y = (c1 - a1 * x) / b1;
            steps_vec.push_back("Solved for x: x = " + format_double(x, 4));
            steps_vec.push_back("Substitute x into eq1 to find y: y = " + format_double(y, 4));
        } 
        // Else try eq2: a2*x + b2*y = c2 => b2*y = c2 - a2*x
        else if (std::abs(b2) > EPSILON) {
            y = (c2 - a2 * x) / b2;
            steps_vec.push_back("Solved for x: x = " + format_double(x, 4));
            steps_vec.push_back("Substitute x into eq2 (as b1 approx 0) to find y: y = " + format_double(y, 4));
        } else {
            // Both b1 and b2 are zero. Lines are vertical: a1x = c1, a2x = c2.
            // If x_coeff (determinant a1b2-a2b1 = 0) is non-zero here, it's a contradiction with b1=b2=0.
            // This situation means the initial assumption of CONSISTENT_UNIQUE might be based on a != 0,
            // but if y cannot be found, the system might be ill-conditioned or a special case.
            steps_vec.push_back("Cannot easily solve for y as both b1 and b2 are near zero. This implies vertical lines. Check consistency again.");
             return solveGeneral(a1, b1, c1, a2, b2, c2); // Fallback for robustness
        }
        return SolutionResult(coeffs, CONSISTENT_UNIQUE, consistency.description,
                              std::make_optional(x), std::make_optional(y),
                              format_double(x, 4), format_double(y, 4),
                              "Elimination", steps_vec);
    }
    // If x_coeff is 0, implies determinant is 0. This contradicts CONSISTENT_UNIQUE.
    steps_vec.push_back("Elimination led to 0*x = C where C should also be 0 for unique. Fallback.");
    return solveGeneral(a1, b1, c1, a2, b2, c2);
}

SolutionResult solveByCrossMultiplication(double a1, double b1, double c1_form_axbyc0,
                                          double a2, double b2, double c2_form_axbyc0) {
    // Convert c from ax+by+C=0 to c for ax+by=c for consistency check and display
    EquationCoefficients coeffs_display(a1, b1, -c1_form_axbyc0, a2, b2, -c2_form_axbyc0);
    std::vector<std::string> steps_vec;
    steps_vec.push_back("Method: Cross-Multiplication");
    steps_vec.push_back("Equations (form ax+by+c=0): " +
                        format_double(a1) + "x + " + format_double(b1) + "y + " + format_double(c1_form_axbyc0) + " = 0;  " +
                        format_double(a2) + "x + " + format_double(b2) + "y + " + format_double(c2_form_axbyc0) + " = 0");

    ConsistencyCheckResult consistency = checkConsistency(a1, b1, -c1_form_axbyc0, a2, b2, -c2_form_axbyc0);
    if (consistency.consistency_type != CONSISTENT_UNIQUE) {
        return SolutionResult(coeffs_display, consistency.consistency_type, consistency.description,
                              std::nullopt, std::nullopt,
                              (consistency.consistency_type == CONSISTENT_INFINITE ? "Infinite" : "None"),
                              (consistency.consistency_type == CONSISTENT_INFINITE ? "Infinite" : "None"),
                              "Cross-Multiplication (Analysis)", steps_vec);
    }

    // Formula: x / (b1*C2 - b2*C1) = y / (C1*a2 - C2*a1) = 1 / (a1*b2 - a2*b1)
    double den_x_num = b1 * c2_form_axbyc0 - b2 * c1_form_axbyc0;
    double den_y_num = c1_form_axbyc0 * a2 - c2_form_axbyc0 * a1;
    double den_1_val = a1 * b2 - a2 * b1; // This is the main determinant

    steps_vec.push_back("x / (b1*c2 - b2*c1) = x / (" + format_double(b1) + "*" + format_double(c2_form_axbyc0) + " - " + format_double(b2) + "*" + format_double(c1_form_axbyc0) + ") = x / " + format_double(den_x_num));
    steps_vec.push_back("y / (c1*a2 - c2*a1) = y / (" + format_double(c1_form_axbyc0) + "*" + format_double(a2) + " - " + format_double(c2_form_axbyc0) + "*" + format_double(a1) + ") = y / " + format_double(den_y_num));
    steps_vec.push_back("1 / (a1*b2 - a2*b1) = 1 / (" + format_double(a1) + "*" + format_double(b2) + " - " + format_double(a2) + "*" + format_double(b1) + ") = 1 / " + format_double(den_1_val));

    if (std::abs(den_1_val) > EPSILON) { // Should be true if unique
        double x = den_x_num / den_1_val;
        double y = den_y_num / den_1_val;
        steps_vec.push_back("x = " + format_double(den_x_num) + " / " + format_double(den_1_val) + " = " + format_double(x, 4));
        steps_vec.push_back("y = " + format_double(den_y_num) + " / " + format_double(den_1_val) + " = " + format_double(y, 4));
        return SolutionResult(coeffs_display, CONSISTENT_UNIQUE, consistency.description,
                              std::make_optional(x), std::make_optional(y),
                              format_double(x, 4), format_double(y, 4),
                              "Cross-Multiplication", steps_vec);
    }
    // Fallback - should not be reached if consistency check is correct for unique case
    steps_vec.push_back("Denominator (a1b2 - a2b1) is zero. Contradicts unique solution. Fallback.");
    return solveGeneral(a1, b1, -c1_form_axbyc0, a2, b2, -c2_form_axbyc0);
}


ReducibleSolutionResult solveReducible(
    double u_coeff1, double v_coeff1, double const1,
    double u_coeff2, double v_coeff2, double const2,
    const std::string& u_represents, const std::string& v_represents) {

    std::map<std::string, std::string> sub_details_map;
    sub_details_map["u_represents"] = u_represents;
    sub_details_map["v_represents"] = v_represents;
    sub_details_map["substituted_eq1"] = format_double(u_coeff1) + "u + " + format_double(v_coeff1) + "v = " + format_double(const1);
    sub_details_map["substituted_eq2"] = format_double(u_coeff2) + "u + " + format_double(v_coeff2) + "v = " + format_double(const2);

    SolutionResult uv_solution = solveGeneral(u_coeff1, v_coeff1, const1, u_coeff2, v_coeff2, const2);
    sub_details_map["solution_u"] = uv_solution.solution_x_str;
    sub_details_map["solution_v"] = uv_solution.solution_y_str;
    
    std::optional<double> ox = std::nullopt;
    std::optional<double> oy = std::nullopt;
    std::string ox_str = "N/A";
    std::string oy_str = "N/A";

    if (uv_solution.solution_x.has_value()) {
        double u_val = uv_solution.solution_x.value();
        if (u_represents == "1/x") {
            if (std::abs(u_val) > EPSILON) { ox = 1.0 / u_val; ox_str = format_double(ox.value(), 4); }
            else { ox_str = "Error (u=0 for 1/x)"; }
        } else if (u_represents == "x") {
            ox = u_val; ox_str = format_double(ox.value(), 4);
        } else { ox_str = "Cannot determine x from u=" + format_double(u_val); }
    } else { ox_str = "Derived from u: " + uv_solution.solution_x_str; }

    if (uv_solution.solution_y.has_value()) {
        double v_val = uv_solution.solution_y.value();
        if (v_represents == "1/y") {
            if (std::abs(v_val) > EPSILON) { oy = 1.0 / v_val; oy_str = format_double(oy.value(), 4); }
            else { oy_str = "Error (v=0 for 1/y)"; }
        } else if (v_represents == "y") {
            oy = v_val; oy_str = format_double(oy.value(), 4);
        } else { oy_str = "Cannot determine y from v=" + format_double(v_val); }
    } else { oy_str = "Derived from v: " + uv_solution.solution_y_str; }

    return ReducibleSolutionResult(uv_solution, ox, oy, ox_str, oy_str, sub_details_map);
}


} // namespace linear_equations
} // namespace michu_fr