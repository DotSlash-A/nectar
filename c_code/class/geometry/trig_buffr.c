#include <stdio.h>
#include <math.h>
#include <stdlib.h> // <-- Added for malloc, perror
#include <string.h>


double find_hyp(double perp, double base) {
    double hyp = sqrt(perp * perp + base * base);
    return hyp;
}

double all_ratios_given_two_sides(double op, double adj) {
    double hyp = find_hyp(op, adj); // Returning hyp, not all ratios
    sin_val=simplest_form(op,hyp);
    cos_val=simplest_form(adj,hyp);
    tan_val=simplest_form(op,adj);
    cosec_val=simplest_form(hyp,op);
    sec_val=simplest_form(hyp,adj);
    cot_val=simplest_form(adj,op);
}




int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

char* simplest_form(int a, int b) {
    if (b == 0) {
       
        fprintf(stderr, "Error: Denominator cannot be zero in simplest_form.\n");
        // For consistency, let's try to return a string that indicates error
        // or handle it as per requirements. For now, returning NULL.
        return NULL; 
    }
    int common_divisor = gcd(a, b);
    int num = a / common_divisor;
    int den = b / common_divisor;

    int length = snprintf(NULL, 0, "%d/%d", num, den);
    char* frac_string = (char*)malloc(length + 1); // +1 for null terminator

    if (frac_string == NULL) {
        perror("Failed to allocate memory for fraction string");
        return NULL;
    }

    snprintf(frac_string, length + 1, "%d/%d", num, den);
    return frac_string;
}

int main() {
    double res_hyp;
    int gcd_val;

    res_hyp = all_ratios_given_two_sides(3.0, 4.0); // Using doubles as inputs
    printf("Hypotenuse from all_ratios_given_two_sides(3.0, 4.0): %.1lf\n", res_hyp);

    gcd_val = gcd(8, 18);
    printf("GCD of 8 and 18: %d\n", gcd_val);

    // Example 1 for simplest_form
    char* fraction1 = simplest_form(8, 18);
    if (fraction1 != NULL) {
        printf("Simplest form of 8/18: %s\n", fraction1);
        free(fraction1); // IMPORTANT: Free allocated memory
        fraction1 = NULL;  // Good practice: avoid dangling pointer
    }

    // Define perpendicular and base for trigonometric ratio example
    int perp_val = 3; // This was 'op' in your original attempt
    int base_val = 4; // This was 'base' in your original attempt

    // Calculate hypotenuse using these integer values
    // find_hyp expects doubles, so cast them.
    // The result of find_hyp is double, cast to int if an integer hypotenuse is expected
    // (be mindful of precision loss if hyp is not a whole number, e.g., for sides 1,1 -> hyp is sqrt(2))
    int hyp_int_val;
    if (perp_val >= 0 && base_val >=0) { // Ensure non-negative sides for physical triangle
        double hyp_double_val = find_hyp((double)perp_val, (double)base_val);
        hyp_int_val = (int)round(hyp_double_val); // round before casting if sides form Pythagorean triple
                                                  // or just (int)hyp_double_val if truncation is fine
        printf("For triangle with perpendicular = %d, base = %d, hypotenuse = %d (rounded from %.2f)\n",
               perp_val, base_val, hyp_int_val, hyp_double_val);

        // Calculate sin fraction (perp/hyp)
        // Ensure hypotenuse is not zero before calling simplest_form
        if (hyp_int_val > 0) {
            char* sin_frac = simplest_form(perp_val, hyp_int_val);
            if (sin_frac != NULL) { // Check if simplest_form succeeded
                printf("Sin fraction (%d/%d) in simplest form: %s\n", perp_val, hyp_int_val, sin_frac);
                char* token=strtok(sin_frac,"/");
                int numerator=atoi(token);
                token=strtok(NULL,"/");
                int denominator=atoi(token);
                printf("unpacked %d/%d",numerator, denominator);
                free(sin_frac); // IMPORTANT: Free allocated memory
                sin_frac = NULL;  // Good practice
            }
        } else {
            printf("Cannot calculate sin fraction: hypotenuse is zero or invalid.\n");
        }
    } else {
        printf("Perpendicular and base values must be non-negative.\n");
    }
    

    return 0;
}
