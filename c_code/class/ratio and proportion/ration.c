#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double epsilon = 1e-9;

// Function to check if two ratios are (approximately) equal
void is_in_proportion(double a, double b, double c, double d) {
    double ratio1 = a / b;
    double ratio2 = c / d;
    if (fabs(ratio1 - ratio2) < epsilon) {
        printf("The ratios %.2f/%.2f and %.2f/%.2f are equal\n", a, b, c, d);
    } else {
        printf("The ratios %.2f/%.2f and %.2f/%.2f are not equal\n", a, b, c, d);
    }
}

// Find two numbers in a given ratio whose sum is 'sum'
void find_ratio_given_sum(double a, double b, double sum){
    double x = sum / (a + b);
    double num1 = a * x;
    double num2 = b * x;
    printf("Numbers in ratio %.2f:%.2f with sum %.2f are: %.2f and %.2f\n", a, b, sum, num1, num2);
}

// Find the fourth proportional: a:b = c:x => x = (b*c)/a
void fourth_proportional(double a, double b, double c){
    double x = (b * c) / a;
    printf("Fourth proportional for %.2f:%.2f = %.2f:x is x = %.2f\n", a, b, c, x);
}

// Find the third proportional: a:b = b:x => x = (b*b)/a
void third_proportional(double a, double b){
    double x = (b * b) / a;
    printf("Third proportional for %.2f:%.2f = %.2f:x is x = %.2f\n", a, b, b, x);
}

// Find equivalent ratio
void equivalent_ratio(double a, double b, int num){
    double eq1_num = a * num;
    double eq1_denom = b * num;
    printf("Equivalent ratio to %.2f:%.2f with multiplier %d is %.2f:%.2f\n", a, b, num, eq1_num, eq1_denom);
}

// Find b given total and a
void find_b_given_total(double total, double a){
    double b = total - a;
    printf("If total is %.2f and a is %.2f, then b is %.2f (ratio: %.2f:%.2f)\n", total, a, b, a, b);
}

// Function to parse a fraction string like "3/4" into integers a and b
int parse_fraction(const char *input, int *a, int *b) {
    return sscanf(input, "%d/%d", a, b) == 2;
}

int main() {
    // 1. Parse a fraction string
    char input[] = "3/4";
    int a, b;
    if (parse_fraction(input, &a, &b)) {
        printf("Parsed ratio is: %d/%d\n", a, b);

        // 2. Check if 3/4 and 6/8 are in proportion
        is_in_proportion(a, b, 6, 8);

        // 3. Find two numbers in ratio 3:4 whose sum is 70
        find_ratio_given_sum(a, b, 70);

        // 4. Find fourth proportional for 3:4 = 9:x
        fourth_proportional(3, 4, 9);

        // 5. Find third proportional for 3:4 = 4:x
        third_proportional(3, 4);

        // 6. Find equivalent ratio to 3:4 with multiplier 5
        equivalent_ratio(3, 4, 5);

        // 7. Find b given total 100 and a = 30
        find_b_given_total(100, 30);

        // 8. Parse another ratio and check proportion
        char input2[] = "9/12";
        int c, d;
        if (parse_fraction(input2, &c, &d)) {
            is_in_proportion(a, b, c, d);
        }
    } else {
        printf("Invalid input format!\n");
    }
    return 0;
}















// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>

// double epsilon = 1e-9;

// // Function to check if two ratios are (approximately) equal
// void is_in_proportion(double a, double b, double c, double d) {
//     double ratio1 = a / b;
//     double ratio2 = c / d;
//     if (fabs(ratio1 - ratio2) < epsilon) {
//         printf("The ratios are equal\n");
//     } else {
//         printf("The ratios are not equal\n");
//     }
// }

// // Function to parse a fraction string like "3/4" into integers a and b
// int parse_fraction(const char *input, int *a, int *b) {
//     return sscanf(input, "%d/%d", a, b) == 2;
// }

// int main() {
//     char input[] = "3/4"; // Example input
//     int a, b;
//     if (parse_fraction(input, &a, &b)) {
//         printf("Parsed ratio is: %d/%d\n", a, b); // Output: 3 4

//         // Example: check if 3/4 and 6/8 are in proportion
//         is_in_proportion(a, b, 6, 8);
//     } else {
//         printf("Invalid input format!\n");
//     }
//     return 0;
// }
