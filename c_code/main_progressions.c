#include <stdio.h>
#include "progressions/arithmetic_progression_utils.h"
#include "progressions/geometric_progression_utils.h"

void print_line_sep_c() {
    printf("----------------------------------------\n");
}

int main() {
    printf("--- C Progressions Examples & Tests ---\n");
    print_line_sep_c();
    int ret;

    // --- Arithmetic Progression ---
    printf("--- Arithmetic Progression (AP) ---\n");
    APResult_C ap_res;
    double ap_term_from_last;
    APMiddleTermResult_C ap_mid_res;

    ret = ap_calculate_term_and_sum(2.0, 3.0, 10, &ap_res);
    if (ret == PROG_SUCCESS) prog_print_ap_result(&ap_res);
    else printf("Error AP Basic: %d\n", ret);

    ret = ap_calculate_nth_term_from_last(29.0, 3.0, 3, &ap_term_from_last);
    if (ret == PROG_SUCCESS) printf("AP Nth from Last (l=29,d=3,n=3): %.4f\n", ap_term_from_last);
    else printf("Error AP Nth From Last: %d\n", ret);

    ret = ap_find_middle_terms(2.0, 3.0, 29.0, &ap_mid_res); // Even number of terms
    if (ret == PROG_SUCCESS) prog_print_ap_middle_term_result(&ap_mid_res);
    else printf("Error AP Middle Terms (Even): %d\n", ret);

    ret = ap_find_middle_terms(1.0, 2.0, 9.0, &ap_mid_res); // Odd number of terms
    if (ret == PROG_SUCCESS) prog_print_ap_middle_term_result(&ap_mid_res);
    else printf("Error AP Middle Terms (Odd): %d\n", ret);
    print_line_sep_c();

    // --- Geometric Progression ---
    printf("--- Geometric Progression (GP) ---\n");
    GPResult_C gp_res;
    double gp_sum_inf;
    double gp_gm;
    GPInsertMeansResult_C gp_ins_res;

    ret = gp_calculate_term_and_sum(3.0, 2.0, 5, &gp_res);
    if (ret == PROG_SUCCESS) prog_print_gp_result(&gp_res);
    else printf("Error GP Basic: %d\n", ret);

    ret = gp_calculate_sum_to_infinity(10.0, 0.5, &gp_sum_inf);
    if (ret == PROG_SUCCESS) printf("GP Sum to Infinity (a=10,r=0.5): %.4f\n", gp_sum_inf);
    else printf("Error GP Sum Inf: %d\n", ret);

    ret = gp_calculate_geometric_mean(4.0, 9.0, &gp_gm);
    if (ret == PROG_SUCCESS) printf("GP Geometric Mean (4,9): %.4f\n", gp_gm);
    else printf("Error GP GM: %d\n", ret);

    ret = gp_insert_geometric_means(2.0, 162.0, 3, &gp_ins_res);
    if (ret == PROG_SUCCESS) prog_print_gp_insert_means_result(&gp_ins_res);
    else printf("Error GP Insert Means (pos r): %d\n", ret);
    
    ret = gp_insert_geometric_means(1.0, -8.0, 2, &gp_ins_res); // r=-2
    if (ret == PROG_SUCCESS) prog_print_gp_insert_means_result(&gp_ins_res);
    else printf("Error GP Insert Means (neg r): %d\n", ret);
    print_line_sep_c();

    // --- Testing Error Cases ---
    printf("--- Testing Expected Errors ---\n");
    ret = ap_calculate_term_and_sum(1,1,0, &ap_res);
    if (ret != PROG_SUCCESS) printf("Caught AP Error (n=0): Code %d\n", ret);

    ret = ap_find_middle_terms(1,0,5, &ap_mid_res);
    if (ret != PROG_SUCCESS) printf("Caught AP Error (d=0, a!=l): Code %d\n", ret);

    ret = gp_calculate_sum_to_infinity(10, 1.5, &gp_sum_inf);
    if (ret != PROG_SUCCESS) printf("Caught GP Error (sum_inf |r|>=1): Code %d\n", ret);

    ret = gp_insert_geometric_means(1, -16, 3, &gp_ins_res); // r^4 = -16 (even root of neg)
    if (ret != PROG_SUCCESS) printf("Caught GP Error (insert means, even root of neg): Code %d\n", ret);

    print_line_sep_c();
    printf("--- End of Examples & Tests ---\n");

    return 0;
}