#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int numerator;
    int denominator;
} Fraction;


typedef struct{
    Fraction sinv;
    Fraction cosv;
    Fraction tanv;
    Fraction cosecv;
    Fraction secv;
    Fraction cotv;
}TrigRatios;

Fraction create_fraction(int num, int den){
    Fraction f;
    f.numerator = num;
    f.denominator=den;
    return f;
}

void print_fraction(Fraction f) {
    printf("%d/%d", f.numerator, f.denominator);
}

TrigRatios calculate_trig_ratios_struct(int op, int adj,int hyp){
    TrigRatios ratios;
    ratios.sinv = create_fraction(op, hyp);
    ratios.cosv = create_fraction(adj, hyp);
    ratios.tanv = create_fraction(op, adj);
    ratios.cosecv = create_fraction(hyp, op);
    ratios.secv = create_fraction(hyp, adj);
    ratios.cotv = create_fraction(adj, op);
    
    return ratios;
}

// Forward declarations
char* simplest_form(int a, int b);

double find_hyp(double perp, double base) {
    double hyp = sqrt(perp * perp + base * base);
    return hyp;
}

double all_ratios_given_two_sides(double op, double adj) {
    double hyp = find_hyp(op, adj);
    
    // Convert doubles to ints for simplest_form
    int op_int = (int)round(op);
    int adj_int = (int)round(adj);
    int hyp_int = (int)round(hyp);
    
    // Declare variables to store the ratio strings
    char *sin_val, *cos_val, *tan_val, *cosec_val, *sec_val, *cot_val;
    
    sin_val = simplest_form(op_int, hyp_int);
    cos_val = simplest_form(adj_int, hyp_int);
    tan_val = simplest_form(op_int, adj_int);
    cosec_val = simplest_form(hyp_int, op_int);
    sec_val = simplest_form(hyp_int, adj_int);
    cot_val = simplest_form(adj_int, op_int);
    
    // Print the ratios
    printf("sin = %s\n", sin_val);
    printf("cos = %s\n", cos_val);
    printf("tan = %s\n", tan_val);
    printf("cosec = %s\n", cosec_val);
    printf("sec = %s\n", sec_val);
    printf("cot = %s\n", cot_val);
    
    // Free allocated memory
    free(sin_val);
    free(cos_val);
    free(tan_val);
    free(cosec_val);
    free(sec_val);
    free(cot_val);
    
    return hyp; // Return the hypotenuse value
}

int gcd(int a, int b) {
    // Make sure we're working with absolute values
    a = abs(a);
    b = abs(b);
    
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
    
    // Handle negative numbers properly
    int sign = 1;
    if (a < 0 && b < 0) {
        a = -a;
        b = -b;
    } else if (b < 0) {
        sign = -1;
        b = -b;
        a = -a;
    } else if (a < 0) {
        sign = -1;
        a = -a;
    }
    
    int common_divisor = gcd(a, b);
    int num = sign * (a / common_divisor);
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
    double res_hyp;
    int gcd_val;

    res_hyp = all_ratios_given_two_sides(3.0, 4.0);
    printf("Hypotenuse from all_ratios_given_two_sides(3.0, 4.0): %.1lf\n", res_hyp);

    gcd_val = gcd(8, 18);
    printf("GCD of 8 and 18: %d\n", gcd_val);

    // Example 1 for simplest_form
    char* fraction1 = simplest_form(8, 18);
    if (fraction1 != NULL) {
        printf("Simplest form of 8/18: %s\n", fraction1);
        free(fraction1);
        fraction1 = NULL;
    }

    // Define perpendicular and base for trigonometric ratio example
    int perp_val = 3;
    int base_val = 4;

    if (perp_val >= 0 && base_val >= 0) {
        double hyp_double_val = find_hyp((double)perp_val, (double)base_val);
        int hyp_int_val = (int)round(hyp_double_val);
        
        printf("For triangle with perpendicular = %d, base = %d, hypotenuse = %d (rounded from %.2f)\n",
               perp_val, base_val, hyp_int_val, hyp_double_val);

        if (hyp_int_val > 0) {
            char* sin_frac = simplest_form(perp_val, hyp_int_val);
            if (sin_frac != NULL) {
                printf("Sin fraction (%d/%d) in simplest form: %s\n", perp_val, hyp_int_val, sin_frac);
                
                char* sin_copy = strdup(sin_frac); // Create a copy for strtok
                if (sin_copy != NULL) {
                    char* token = strtok(sin_copy, "/");
                    int numerator = atoi(token);
                    token = strtok(NULL, "/");
                    int denominator = atoi(token);
                    printf("Unpacked: %d/%d\n", numerator, denominator);
                    free(sin_copy);
                }
                
                free(sin_frac);
                sin_frac = NULL;
            }
        } else {
            printf("Cannot calculate sin fraction: hypotenuse is zero or invalid.\n");
        }
    } else {
        printf("Perpendicular and base values must be non-negative.\n");
    }
    
    printf("________________________\n");
    TrigRatios ratios = calculate_trig_ratios_struct(3, 4, 5);
    
    printf("sin = ");
    print_fraction(ratios.sinv);
    printf("\ncos = ");
    print_fraction(ratios.cosv);


    return 0;
}
