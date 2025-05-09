#ifndef LINEAR_EQUATIONS_TYPES_H
#define LINEAR_EQUATIONS_TYPES_H

#include <string>
#include <vector>
#include <map>
#include <optional>   // For std::optional (C++17)
#include <sstream>    // For std::ostringstream
#include <iomanip>    // For std::fixed, std::setprecision
#include <limits>     // For std::numeric_limits

namespace michu_fr {
namespace linear_equations {

// Represents a pair of equations: a1x + b1y = c1 and a2x + b2y = c2
struct EquationCoefficients {
    double a1, b1, c1;
    double a2, b2, c2;

    EquationCoefficients(double pa1, double pb1, double pc1, double pa2, double pb2, double pc2)
        : a1(pa1), b1(pb1), c1(pc1), a2(pa2), b2(pb2), c2(pc2) {}

    std::string eq1ToString() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << a1 << "x + " << b1 << "y = " << c1;
        return oss.str();
    }

    std::string eq2ToString() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << a2 << "x + " << b2 << "y = " << c2;
        return oss.str();
    }

    std::string toString() const {
        return "Equations: [" + eq1ToString() + "; " + eq2ToString() + "]";
    }
};

struct ConsistencyCheckResult {
    EquationCoefficients equations;
    std::string consistency_type; // "CONSISTENT_UNIQUE", "CONSISTENT_INFINITE", "INCONSISTENT_PARALLEL"
    std::string description;
    std::map<std::string, std::string> ratios;
    std::string graphical_interpretation;

    ConsistencyCheckResult(EquationCoefficients eq_coeffs, std::string ct, std::string desc,
                           std::map<std::string, std::string> r, std::string gi)
        : equations(eq_coeffs), consistency_type(std::move(ct)), description(std::move(desc)),
          ratios(std::move(r)), graphical_interpretation(std::move(gi)) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << "ConsistencyCheckResult{"
            << "equations=" << equations.toString()
            << ", consistencyType='" << consistency_type << '\''
            << ", description='" << description << '\''
            << ", graphicalInterpretation='" << graphical_interpretation << '\''
            << ", ratios={";
        bool first = true;
        for(const auto& pair : ratios) {
            if (!first) oss << ", ";
            oss << pair.first << ":" << pair.second;
            first = false;
        }
        oss << "}}";
        return oss.str();
    }
};

struct SolutionResult {
    EquationCoefficients equations;
    std::string consistency_type;
    std::string description;
    std::optional<double> solution_x;
    std::optional<double> solution_y;
    std::string solution_x_str; // For "Infinite", "None", or numerical value
    std::string solution_y_str; // For "Infinite", "None", or numerical value
    std::string method_used;
    std::vector<std::string> steps;

    SolutionResult(EquationCoefficients eq_coeffs, std::string ct, std::string desc,
                   std::optional<double> sx, std::optional<double> sy,
                   std::string sx_str, std::string sy_str,
                   std::string method, std::vector<std::string> st)
        : equations(eq_coeffs), consistency_type(std::move(ct)), description(std::move(desc)),
          solution_x(sx), solution_y(sy), solution_x_str(std::move(sx_str)), solution_y_str(std::move(sy_str)),
          method_used(std::move(method)), steps(std::move(st)) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << "SolutionResult{"
            << "equations=" << equations.toString()
            << ", consistencyType='" << consistency_type << '\''
            << ", solutionX=" << solution_x_str
            << ", solutionY=" << solution_y_str
            << ", methodUsed='" << method_used << '\'';
        if (!steps.empty()) {
            oss << ", steps_count=" << steps.size();
        }
        // oss << ", description='" << description << '\''; // Can be verbose
        oss << "}";
        return oss.str();
    }
};

struct ReducibleSolutionResult {
    SolutionResult substituted_system_solution; // Solution for u and v
    std::optional<double> original_solution_x;
    std::optional<double> original_solution_y;
    std::string original_solution_x_str;
    std::string original_solution_y_str;
    std::map<std::string, std::string> substitution_details; // e.g., u_represents, v_represents

    ReducibleSolutionResult(SolutionResult sub_sol,
                            std::optional<double> ox, std::optional<double> oy,
                            std::string ox_str, std::string oy_str,
                            std::map<std::string, std::string> sub_details)
        : substituted_system_solution(std::move(sub_sol)),
          original_solution_x(ox), original_solution_y(oy),
          original_solution_x_str(std::move(ox_str)), original_solution_y_str(std::move(oy_str)),
          substitution_details(std::move(sub_details)) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << "ReducibleSolutionResult{"
            << "substitutedSolution=" << substituted_system_solution.toString()
            << ", originalSolutionX=" << original_solution_x_str
            << ", originalSolutionY=" << original_solution_y_str
            << ", substitutionDetails={";
        bool first = true;
        for(const auto& pair : substitution_details) {
            if (!first) oss << ", ";
            oss << pair.first << ":'" << pair.second << "'";
            first = false;
        }
        oss << "}}";
        return oss.str();
    }
};

} // namespace linear_equations
} // namespace michu_fr

#endif // LINEAR_EQUATIONS_TYPES_H