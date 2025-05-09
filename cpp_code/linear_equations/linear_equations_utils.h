#ifndef LINEAR_EQUATIONS_UTILS_H
#define LINEAR_EQUATIONS_UTILS_H

#include "linear_equations_types.h" // Our types

namespace michu_fr {
namespace linear_equations {

// Constants for consistency types
extern const std::string CONSISTENT_UNIQUE;
extern const std::string CONSISTENT_INFINITE;
extern const std::string INCONSISTENT_PARALLEL;

// Function declarations
ConsistencyCheckResult checkConsistency(double a1, double b1, double c1, double a2, double b2, double c2);

SolutionResult solveGeneral(double a1, double b1, double c1, double a2, double b2, double c2);

SolutionResult solveBySubstitution(double a1, double b1, double c1, double a2, double b2, double c2);

SolutionResult solveByElimination(double a1, double b1, double c1, double a2, double b2, double c2);

SolutionResult solveByCrossMultiplication(double a1, double b1, double c1_form_axbyc0,
                                          double a2, double b2, double c2_form_axbyc0);

ReducibleSolutionResult solveReducible(
    double u_coeff1, double v_coeff1, double const1,
    double u_coeff2, double v_coeff2, double const2,
    const std::string& u_represents, const std::string& v_represents);

} // namespace linear_equations
} // namespace michu_fr

#endif // LINEAR_EQUATIONS_UTILS_H