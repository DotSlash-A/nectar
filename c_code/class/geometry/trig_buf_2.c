#include <stdio.h>
#include <math.h>
#include <stdlib.h> // For malloc, perror
#include <string.h> // for strtok, atoi

// Function to find the hypotenuse
double find_hyp(double perp, double base) {
    double hyp = sqrt(perp * perp + base * base);
    return hyp;
}

// Declare global variables to store the trigonometric ratios
char* sin_val;
char* cos_val;
char* tan_val;
char* cosec_val;
char* sec_val;
char* cot_val;

// Function to calculate all trigonometric ratios
void all_ratios_given_two_sides(double op, double adj) {
    double hyp = find_hyp(op, adj); // Calculate hypotenuse

    // Use simplest_form to get the string representation of each ratio
    sin_val = simplest_form((int)op, (int)hyp);
    cos_val = simplest_form((int)adj, (int)hyp);
    tan_val = simplest_form((int)op, (int)adj);
    cosec_val = simplest_form((int)hyp, (int)op);
    sec_val = simplest_form((int)hyp, (int)adj);
    cot_val = simplest_form((int)adj, (int)op);
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
        return NULL;
    }
    int common_divisor = gcd(a, b);
    int num = a / common_divisor;
    int den = b / common_divisor;

    int length = snprintf(NULL, 0, "%d/%d", num, den);
    char* frac_string = (char*)malloc(length + 1);

    if (frac_string == NULL) {
        perror("Failed to allocate memory for fraction string");
        return NULL;
    }

    snprintf(frac_string, length + 1, "%d/%d", num, den);
    return frac_string;
}

int main() {
    int perp_val = 3;
    int base_val = 4;
    int hyp_int_val;
    double hyp_double_val;

    // Calculate hypotenuse
    if (perp_val >= 0 && base_val >= 0) {
        hyp_double_val = find_hyp((double)perp_val, (double)base_val);
        hyp_int_val = (int)round(hyp_double_val);

        printf("For triangle with perpendicular = %d, base = %d, hypotenuse = %d (rounded from %.2f)\n",
               perp_val, base_val, hyp_int_val, hyp_double_val);

        // Calculate trigonometric ratios
        all_ratios_given_two_sides((double)perp_val, (double)base_val);

        // Print the ratios.  Check for NULL before printing and freeing.
        if (sin_val != NULL) {
            printf("Sin = %s\n", sin_val);
            free(sin_val);
            sin_val = NULL;
        }
        if (cos_val != NULL) {
            printf("Cos = %s\n", cos_val);
            free(cos_val);
            cos_val = NULL;
        }
        if (tan_val != NULL) {
            printf("Tan = %s\n", tan_val);
            free(tan_val);
            tan_val = NULL;
        }
        if (cosec_val != NULL) {
            printf("Cosec = %s\n", cosec_val);
            free(cosec_val);
            cosec_val = NULL;
        }
        if (sec_val != NULL) {
            printf("Sec = %s\n", sec_val);
            free(sec_val);
            sec_val = NULL;
        }
        if (cot_val != NULL) {
            printf("Cot = %s\n", cot_val);
            free(cot_val);
            cot_val = NULL;
        }
    } else {
        printf("Perpendicular and base values must be non-negative.\n");
    }

    return 0;
}
