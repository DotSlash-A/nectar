#include <stdio.h>
#include "real_numbers/real_numbers_utils.h"     // Existing
#include "linear_equations/linear_equations_utils.h" // New

int main() {
    printf("--- Math C Examples (C99/C11) ---\n");
    int ret; // For checking return codes

    // --- REAL NUMBERS EXAMPLES ---
    printf("\n\n--- Real Numbers Examples ---");
    // (Keep your Real Numbers examples as before)
    // Example:
    printf("\n1. Euclid's Division Lemma (Real Numbers):\n");
    EuclidLemmaResult_C lemma_res;
    ret = rn_euclids_division_lemma(455, 42, &lemma_res);
    if (ret == RN_SUCCESS) print_euclid_lemma_result_c(&lemma_res);
    else printf("   Error: %d\n", ret);
    // ... (all other Real Numbers examples) ...
     printf("\n7. Polynomial Analysis (Real Numbers):\n");
    PolynomialAnalysisResult_C poly_res_rn; // Use a different variable name
    double p1_coeffs_rn[] = {1.0, -5.0, 6.0}; 
    ret = rn_analyze_polynomial(p1_coeffs_rn, sizeof(p1_coeffs_rn)/sizeof(double), &poly_res_rn);
    if (ret == RN_SUCCESS) print_polynomial_analysis_result_c(&poly_res_rn); else printf("Error\n");


    // --- LINEAR EQUATIONS EXAMPLES ---
    printf("\n\n--- Pair of Linear Equations Examples ---");

    // Example Equations (a1x + b1y = c1, a2x + b2y = c2)
    double a1_uniq=1, b1_uniq=1, c1_uniq=5;
    double a2_uniq=2, b2_uniq=-3, c2_uniq=4; // Unique: x=3.8, y=1.2

    double a1_inf=2, b1_inf=3, c1_inf=9;
    double a2_inf=4, b2_inf=6, c2_inf=18; // Infinite

    double a1_par=1, b1_par=2, c1_par=4;
    double a2_par=2, b2_par=4, c2_par=12; // Parallel

    printf("\n1. Consistency Check (Linear Equations):\n");
    ConsistencyCheckResult_C cc_res;
    ret = le_check_consistency(a1_uniq, b1_uniq, c1_uniq, a2_uniq, b2_uniq, c2_uniq, &cc_res);
    if (ret == LE_SUCCESS) print_consistency_check_result_c(&cc_res); else printf("  Error: %d\n", ret);

    ret = le_check_consistency(a1_inf, b1_inf, c1_inf, a2_inf, b2_inf, c2_inf, &cc_res);
    if (ret == LE_SUCCESS) print_consistency_check_result_c(&cc_res); else printf("  Error: %d\n", ret);
    
    printf("\n2. General Solver (Cramer's - Linear Equations):\n");
    SolutionResult_C sol_res;
    ret = le_solve_general_cramer(a1_uniq, b1_uniq, c1_uniq, a2_uniq, b2_uniq, c2_uniq, &sol_res);
    if (ret == LE_SUCCESS) print_solution_result_c(&sol_res); else printf("  Error: %d\n", ret);

    ret = le_solve_general_cramer(a1_inf, b1_inf, c1_inf, a2_inf, b2_inf, c2_inf, &sol_res);
    if (ret == LE_SUCCESS) print_solution_result_c(&sol_res); else printf("  Error: %d\n", ret);

    printf("\n3. Solver by Substitution (Linear Equations - uses Cramer for now):\n");
    ret = le_solve_by_substitution(1, 2, 3, 7, -15, 2, &sol_res);
    if (ret == LE_SUCCESS) print_solution_result_c(&sol_res); else printf("  Error: %d\n", ret);
    
    printf("\n4. Solver by Elimination (Linear Equations - uses Cramer for now):\n");
    ret = le_solve_by_elimination(9, -4, 2000, 7, -3, 2000, &sol_res);
    if (ret == LE_SUCCESS) print_solution_result_c(&sol_res); else printf("  Error: %d\n", ret);

    printf("\n5. Solver by Cross-Multiplication (Linear Equations):\n");
    // Example: 2x + y = 5  => 2x + y - 5 = 0  (c_form = -5)
    //          3x + 2y = 8 => 3x + 2y - 8 = 0 (c_form = -8)
    ret = le_solve_by_cross_multiplication(2, 1, -5, 3, 2, -8, &sol_res);
    if (ret == LE_SUCCESS) print_solution_result_c(&sol_res); else printf("  Error: %d\n", ret);

    printf("\n6. Reducible Equations Solver (Linear Equations):\n");
    ReducibleSolutionResult_C red_sol;
    ret = le_solve_reducible(2, 3, 13, 5, -4, -2, "1/x", "1/y", &red_sol);
    if (ret == LE_SUCCESS) print_reducible_solution_result_c(&red_sol); else printf("  Error: %d\n", ret);

    printf("\n--- End of Examples ---\n");
    return 0;
}