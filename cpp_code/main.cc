// #include <iostream>
// #include <vector>
// #include <map>
// #include <stdexcept> // For std::exception
// #include "real_numbers/real_numbers_utils.h"       // Existing
// #include "linear_equations/linear_equations_utils.h" // New

// // Helper to print maps (if not already present from RealNumbers part)
// template<typename K, typename V>
// void printMapIfNotThere(const std::map<K, V>& m, const std::string& map_name = "Map") {
//     std::cout << map_name << ": {";
//     bool first = true;
//     for (const auto& pair : m) {
//         if (!first) {
//             std::cout << ", ";
//         }
//         std::cout << pair.first << ":" << pair.second;
//         first = false;
//     }
//     std::cout << "}";
// }


// int main() {
//     std::cout << "--- Math C++ Examples (C++17) ---" << std::endl;

//     // --- REAL NUMBERS EXAMPLES (Keep these from previous version) ---
//     std::cout << "\n\n--- Real Numbers Examples ---" << std::endl;
//     using namespace michu_fr::real_numbers; // For Real Numbers

//     // ... (Keep all your Real Numbers examples here as before) ...
//     // Example:
//     std::cout << "\n1. Euclid's Division Lemma (Real Numbers):" << std::endl;
//     try {
//         EuclidLemmaResult lemma1 = euclidsDivisionLemma(455, 42);
//         std::cout << "   " << lemma1.toString() << std::endl;
//     } catch (const std::exception& e) {
//         std::cerr << "   Error: " << e.what() << std::endl;
//     }
//     // ... (and so on for all other Real Numbers examples) ...
//     std::cout << "\n7. Polynomial Analysis (Real Numbers):" << std::endl;
//     std::vector<double> p1_coeffs = {1.0, -5.0, 6.0}; // x^2 - 5x + 6
//     PolynomialAnalysisResult poly_res1 = analyzePolynomial(p1_coeffs);
//     std::cout << "   Poly {1, -5, 6}: " << poly_res1.toString() << std::endl;


//     // --- LINEAR EQUATIONS EXAMPLES ---
//     std::cout << "\n\n--- Pair of Linear Equations Examples ---" << std::endl;
//     using namespace michu_fr::linear_equations; // For Linear Equations

//     // Example Equations (a1x + b1y = c1, a2x + b2y = c2)
//     double a1_uniq=1, b1_uniq=1, c1_uniq=5;
//     double a2_uniq=2, b2_uniq=-3, c2_uniq=4; // Unique: x=3.8, y=1.2

//     double a1_inf=2, b1_inf=3, c1_inf=9;
//     double a2_inf=4, b2_inf=6, c2_inf=18; // Infinite

//     double a1_par=1, b1_par=2, c1_par=4;
//     double a2_par=2, b2_par=4, c2_par=12; // Parallel

//     std::cout << "\n1. Consistency Check (Linear Equations):" << std::endl;
//     ConsistencyCheckResult cc1 = checkConsistency(a1_uniq, b1_uniq, c1_uniq, a2_uniq, b2_uniq, c2_uniq);
//     std::cout << "   Unique Sys: " << cc1.toString() << std::endl;

//     ConsistencyCheckResult cc2 = checkConsistency(a1_inf, b1_inf, c1_inf, a2_inf, b2_inf, c2_inf);
//     std::cout << "   Infinite Sys: " << cc2.toString() << std::endl;

//     ConsistencyCheckResult cc3 = checkConsistency(a1_par, b1_par, c1_par, a2_par, b2_par, c2_par);
//     std::cout << "   Parallel Sys: " << cc3.toString() << std::endl;


//     std::cout << "\n2. General Solver (Linear Equations):" << std::endl;
//     SolutionResult sol_gen1 = solveGeneral(a1_uniq, b1_uniq, c1_uniq, a2_uniq, b2_uniq, c2_uniq);
//     std::cout << "   Unique Sys (General): " << sol_gen1.toString() << std::endl;
//     if (!sol_gen1.steps.empty()) std::cout << "     Steps: " << sol_gen1.steps[0] << "..." << std::endl;


//     SolutionResult sol_gen2 = solveGeneral(a1_inf, b1_inf, c1_inf, a2_inf, b2_inf, c2_inf);
//     std::cout << "   Infinite Sys (General): " << sol_gen2.toString() << std::endl;

//     std::cout << "\n3. Solver by Substitution (Linear Equations):" << std::endl;
//     // Example: x + 2y = 3  (1,2,3)
//     //          7x - 15y = 2 (7,-15,2)
//     // x = 3-2y => 7(3-2y) - 15y = 2 => 21 - 14y - 15y = 2 => 21 - 29y = 2 => -29y = -19 => y = 19/29
//     // x = 3 - 2(19/29) = (87-38)/29 = 49/29
//     SolutionResult sol_sub1 = solveBySubstitution(1, 2, 3, 7, -15, 2);
//     std::cout << "   Solve 1x+2y=3, 7x-15y=2 (Substitution): " << sol_sub1.toString() << std::endl;
//     for(const auto& step : sol_sub1.steps) { std::cout << "      Step: " << step << std::endl;}

//     std::cout << "\n4. Solver by Elimination (Linear Equations):" << std::endl;
//     // Example: 9x - 4y = 2000
//     //          7x - 3y = 2000
//     // (27x - 12y = 6000) - (28x - 12y = 8000) => -x = -2000 => x = 2000
//     // 9(2000) - 4y = 2000 => 18000 - 4y = 2000 => 16000 = 4y => y = 4000
//     SolutionResult sol_elim1 = solveByElimination(9, -4, 2000, 7, -3, 2000);
//     std::cout << "   Solve 9x-4y=2000, 7x-3y=2000 (Elimination): " << sol_elim1.toString() << std::endl;
//     for(const auto& step : sol_elim1.steps) { std::cout << "      Step: " << step << std::endl;}


//     std::cout << "\n5. Solver by Cross-Multiplication (Linear Equations):" << std::endl;
//     // Example: 2x + y = 5  => 2x + y - 5 = 0  (c_form = -5)
//     //          3x + 2y = 8 => 3x + 2y - 8 = 0 (c_form = -8)
//     // Solution: x=2, y=1
//     SolutionResult sol_cross1 = solveByCrossMultiplication(2, 1, -5, 3, 2, -8);
//     std::cout << "   Solve 2x+y-5=0, 3x+2y-8=0 (Cross-Mult): " << sol_cross1.toString() << std::endl;
//     for(const auto& step : sol_cross1.steps) { std::cout << "      Step: " << step << std::endl;}


//     std::cout << "\n6. Reducible Equations Solver (Linear Equations):" << std::endl;
//     // Example: 2/x + 3/y = 13. Let u=1/x, v=1/y. So, 2u + 3v = 13
//     //          5/x - 4/y = -2.                         5u - 4v = -2
//     // Solving for u,v: u=2, v=3. So x=1/2, y=1/3.
//     ReducibleSolutionResult red_sol1 = solveReducible(
//             2, 3, 13,
//             5, -4, -2,
//             "1/x", "1/y"
//     );
//     std::cout << "   Reducible 2/x+3/y=13, 5/x-4/y=-2:\n" << red_sol1.toString() << std::endl;

//     return 0;
// }