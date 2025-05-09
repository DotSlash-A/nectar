#include <stdio.h>
#include "polynomials_quadratics/polynomial_utils.h"
#include "polynomials_quadratics/quadratic_utils.h"

int main() {
    printf("--- C Polynomials & Quadratics Examples ---\n");
    int ret;

    // 1. Polynomial Formatting
    printf("\n1. Polynomial Formatting:\n");
    double p1_coeffs[] = {2.0, -3.0, 0.0, 5.0}; // 2x^3 - 3x^2 + 5
    char p1_str[PQ_MAX_STRING_LEN];
    ret = poly_format_to_string(p1_coeffs, sizeof(p1_coeffs)/sizeof(double), 'x', p1_str, sizeof(p1_str));
    if (ret == PQ_SUCCESS) printf("   P1(x) = %s\n", p1_str); else printf("Error formatting P1\n");

    double p_zero_coeffs[] = {0.0,0.0,0.0};
    char p_zero_str[PQ_MAX_STRING_LEN];
    ret = poly_format_to_string(p_zero_coeffs, sizeof(p_zero_coeffs)/sizeof(double), 'y', p_zero_str, sizeof(p_zero_str));
    if (ret == PQ_SUCCESS) printf("   P_zero(y) = %s\n", p_zero_str); else printf("Error formatting P_zero\n");


    // 2. Polynomial Evaluation
    printf("\n2. Polynomial Evaluation:\n");
    double eval_res;
    ret = poly_evaluate(p1_coeffs, sizeof(p1_coeffs)/sizeof(double), 2.0, &eval_res);
    if (ret == PQ_SUCCESS) printf("   P1(2) = %.4f\n", eval_res); // Expected: 9

    // 3. Polynomial Division
    printf("\n3. Polynomial Division:\n");
    PolynomialDivisionResult_C div_res;
    double dividend1[] = {1.0, -5.0, 6.0};    // x^2 - 5x + 6
    double divisor1[]  = {1.0, -2.0};       // x - 2
    ret = poly_division(dividend1, 3, divisor1, 2, &div_res);
    if (ret == PQ_SUCCESS) pq_print_polynomial_division_result(&div_res);
    else printf("   Division Error 1: %d\n", ret);

    double dividend2[] = {1.0, 0.0, 0.0, -1.0}; // x^3 - 1
    double divisor2[]  = {1.0, -1.0};      // x - 1
    ret = poly_division(dividend2, 4, divisor2, 2, &div_res);
    if (ret == PQ_SUCCESS) pq_print_polynomial_division_result(&div_res);
     else printf("   Division Error 2: %d\n", ret);


    // 4. Quadratic Equation Solving
    printf("\n4. Quadratic Equation Solving:\n");
    QuadraticSolution_C quad_sol;
    ret = quad_solve_equation(1, -5, 6, &quad_sol); // x^2-5x+6=0
    if (ret == PQ_SUCCESS) pq_print_quadratic_solution(&quad_sol);
    
    ret = quad_solve_equation(1, 2, 5, &quad_sol); // x^2+2x+5=0 (complex roots)
    if (ret == PQ_SUCCESS) pq_print_quadratic_solution(&quad_sol);

    ret = quad_solve_equation(0, 2, -4, &quad_sol); // 2x-4=0 (linear)
    if (ret == PQ_SUCCESS) pq_print_quadratic_solution(&quad_sol);


    // 5. Rational Roots (Simplified Stub Example)
    printf("\n5. Rational Roots (Stub):\n");
    double poly_rr[] = {1.0, -6.0, 11.0, -6.0}; // (x-1)(x-2)(x-3)
    double found_roots[PQ_MAX_ROOTS];
    int num_found;
    ret = poly_find_rational_roots(poly_rr, 4, found_roots, PQ_MAX_ROOTS, &num_found);
    if (ret == PQ_SUCCESS) {
        printf("   Rational roots of x^3-6x^2+11x-6: [");
        for(int i=0; i<num_found; ++i) printf("%.2f%s", found_roots[i], (i==num_found-1?"":", "));
        printf("] (Note: stub may not find all)\n");
    }


    // 6. Roots-Coefficients Relations
    printf("\n6. Roots-Coefficients Relations:\n");
    RootsCoefficientsRelation_C rel_res;
    double q_coeffs[] = {1.0, -7.0, 10.0};
    ret = poly_relation_roots_coeffs_quadratic(q_coeffs, 3, &rel_res);
    if(ret == PQ_SUCCESS) pq_print_roots_coefficients_relation(&rel_res);

    double c_coeffs[] = {1.0, -6.0, 11.0, -6.0};
    ret = poly_relation_roots_coeffs_cubic(c_coeffs, 4, &rel_res);
    if(ret == PQ_SUCCESS) pq_print_roots_coefficients_relation(&rel_res);


    // 7. Form Polynomial from Roots
    printf("\n7. Form Polynomial from Roots:\n");
    FormedPolynomial_C formed_poly;
    double roots_for_poly[] = {1.0, 2.0, 3.0};
    ret = poly_form_from_roots(roots_for_poly, 3, 1.0, 'y', &formed_poly);
    if(ret == PQ_SUCCESS) pq_print_formed_polynomial(&formed_poly);

    return 0;
}