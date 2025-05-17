#include <stdio.h>
#include <math.h>
#include <stdlib.h> // For malloc, perror, free, atoi
#include <string.h> // for strtok (if used, not directly in this fix but good to have if planned)

// Forward declarations
char* simplest_form(int a, int b); // <-- ADD THIS LINE
double find_hyp(double perp, double base);
int gcd(int a, int b);
void all_ratios_given_two_sides(double op, double adj);


// Global variables to store the trigonometric ratios as strings
char* sin_val_str = NULL; // Initialize to NULL
char* cos_val_str = NULL;
char* tan_val_str = NULL;
char* cosec_val_str = NULL;
char* sec_val_str = NULL;
char* cot_val_str = NULL;

// Function to find the hypotenuse
double find_hyp(double perp, double base) {
    if (perp < 0 || base < 0) { // Sides should be non-negative
        // fprintf(stderr, "Error: Sides cannot be negative for hypotenuse calculation.\n");
        return -1.0; // Indicate error
    }
    return sqrt(perp * perp + base * base);
}

// Function to calculate all trigonometric ratios and store them in global strings
void all_ratios_given_two_sides(double op, double adj) {
    if (op < 0 || adj < 0) {
        // fprintf(stderr, "Error: Opposite or adjacent side cannot be negative.\n");
        return; // Or handle error appropriately by setting strings to error messages
    }

    double hyp = find_hyp(op, adj);

    if (hyp <= 0) { // Check for valid hypotenuse (e.g., from find_hyp error or op=0, adj=0)
        // fprintf(stderr, "Error: Invalid hypotenuse (%.2f) for calculating ratios.\n", hyp);
        // Potentially set global strings to "Error" or NULL them if already NULL
        return;
    }

    // Free previous strings if they exist (important if this function is called multiple times)
    if (sin_val_str) { free(sin_val_str); sin_val_str = NULL; }
    if (cos_val_str) { free(cos_val_str); cos_val_str = NULL; }
    if (tan_val_str) { free(tan_val_str); tan_val_str = NULL; }
    if (cosec_val_str) { free(cosec_val_str); cosec_val_str = NULL; }
    if (sec_val_str) { free(sec_val_str); sec_val_str = NULL; }
    if (cot_val_str) { free(cot_val_str); cot_val_str = NULL; }

    // Use simplest_form to get the string representation of each ratio
    // Ensure inputs to simplest_form are integers.
    // Rounding might be needed if op, adj, hyp are not perfect integers for ratios.
    // For Pythagorean triples like (3,4,5), direct casting is fine.
    sin_val_str = simplest_form((int)round(op), (int)round(hyp));
    cos_val_str = simplest_form((int)round(adj), (int)round(hyp));
    tan_val_str = simplest_form((int)round(op), (int)round(adj));

    // For cosec, sec, cot, check for division by zero for op and adj
    if (op != 0) {
        cosec_val_str = simplest_form((int)round(hyp), (int)round(op));
    } else {
        cosec_val_str = strdup("Undefined (div by 0)"); // strdup allocates memory
    }

    if (adj != 0) {
        sec_val_str = simplest_form((int)round(hyp), (int)round(adj));
    } else {
        sec_val_str = strdup("Undefined (div by 0)");
    }

    if (op != 0) { // cot is adj/op
        cot_val_str = simplest_form((int)round(adj), (int)round(op));
    } else {
        cot_val_str = strdup("Undefined (div by 0)");
    }
}

int gcd(int a, int b) {
    a = abs(a); // Ensure positive inputs for GCD logic if numerators/denominators can be negative
    b = abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a == 0 ? 1 : a; // GCD of 0,x is x. If both are 0, gcd is undefined, return 1 to avoid div by zero.
}

char* simplest_form(int a, int b) {
    if (b == 0) {
        // This case should ideally be handled before calling simplest_form
        // for ratios like tan(90) where adj=0, or cot(0) where op=0.
        // However, if called directly:
        char* err_msg = (char*)malloc(strlen("Undefined (div by 0)") + 1);
        if (err_msg) strcpy(err_msg, "Undefined (div by 0)");
        return err_msg; // Caller must free this
    }

    int common_divisor = gcd(a, b);
    if (common_divisor == 0) common_divisor = 1; // Should not happen if b!=0

    int num = a / common_divisor;
    int den = b / common_divisor;

    // Handle sign: traditionally, denominator is positive.
    if (den < 0) {
        num = -num;
        den = -den;
    }
    // If fraction is -0/x, represent as 0/x
    if (num == 0 && den != 0) { // e.g. -0/5 should be 0/5
        // num is already 0
    }


    int length = snprintf(NULL, 0, "%d/%d", num, den);
    char* frac_string = (char*)malloc(length + 1); // +1 for null terminator

    if (frac_string == NULL) {
        perror("Failed to allocate memory for fraction string");
        return NULL; // Or a static error string, but NULL is clearer for malloc failure
    }

    snprintf(frac_string, length + 1, "%d/%d", num, den);
    return frac_string;
}

int main() {
    double perp_input = 3.0;
    double base_input = 4.0;

    printf("Calculating ratios for perpendicular = %.1f, base = %.1f\n", perp_input, base_input);

    // Calculate trigonometric ratios and store them in global strings
    all_ratios_given_two_sides(perp_input, base_input);

    // Print the ratios. Check for NULL before printing.
    printf("Sin = %s\n", sin_val_str ? sin_val_str : "Error/Null");
    printf("Cos = %s\n", cos_val_str ? cos_val_str : "Error/Null");
    printf("Tan = %s\n", tan_val_str ? tan_val_str : "Error/Null");
    printf("Cosec = %s\n", cosec_val_str ? cosec_val_str : "Error/Null");
    printf("Sec = %s\n", sec_val_str ? sec_val_str : "Error/Null");
    printf("Cot = %s\n", cot_val_str ? cot_val_str : "Error/Null");

    // IMPORTANT: Free all dynamically allocated strings
    if (sin_val_str) free(sin_val_str);
    if (cos_val_str) free(cos_val_str);
    if (tan_val_str) free(tan_val_str);
    if (cosec_val_str) free(cosec_val_str);
    if (sec_val_str) free(sec_val_str);
    if (cot_val_str) free(cot_val_str);

    printf("\nCalculating ratios for perpendicular = %.1f, base = %.1f (where tan/cot might be undefined)\n", 5.0, 0.0);
    all_ratios_given_two_sides(5.0, 0.0); // Example where adj = 0
    printf("Sin = %s\n", sin_val_str ? sin_val_str : "Error/Null");
    printf("Cos = %s\n", cos_val_str ? cos_val_str : "Error/Null");
    printf("Tan = %s\n", tan_val_str ? tan_val_str : "Error/Null");
    printf("Cosec = %s\n", cosec_val_str ? cosec_val_str : "Error/Null");
    printf("Sec = %s\n", sec_val_str ? sec_val_str : "Error/Null");
    printf("Cot = %s\n", cot_val_str ? cot_val_str : "Error/Null");

    if (sin_val_str) free(sin_val_str);
    if (cos_val_str) free(cos_val_str);
    if (tan_val_str) free(tan_val_str);
    if (cosec_val_str) free(cosec_val_str);
    if (sec_val_str) free(sec_val_str);
    if (cot_val_str) free(cot_val_str);


    return 0;
}
