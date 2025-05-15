#include <stdio.h>
#include <math.h>

// Function to solve linear equation ax + b = 0
void solve_linear(double a, double b) {
    printf("The polynomial you entered is %.2lf*x + %.2lf = 0\n", a, b);
    if (a != 0) {
        double res = -b / a;
        printf("The zero of this polynomial is %.2lf\n", res);
    } else {
        printf("Coefficient 'a' cannot be zero for a linear polynomial.\n");
    }
}

void is_it_a_root(int coeffs[], int root){
    int subs=(coeffs[0]*root*root)+coeffs[1]*root+coeffs[2];
    if (subs==0){
        printf("it is a root");
    }
    else{
        printf("uh oh!");
    }
}
// Function to solve quadratic equation ax^2 + bx + c = 0
void solve_quadratic(double a, double b, double c) {
    printf("The polynomial you entered is %.2lf*x^2 + %.2lf*x + %.2lf = 0\n", a, b, c);
    if (a == 0) {
        printf("Coefficient 'a' cannot be zero for a quadratic polynomial.\n");
        return;
    }
    double discriminant = b*b - 4*a*c;
    if (discriminant > 0) {
        double root1 = (-b + sqrt(discriminant)) / (2*a);
        double root2 = (-b - sqrt(discriminant)) / (2*a);
        printf("The roots of the polynomial are %.2lf and %.2lf\n", root1, root2);

        // Verification
        double sum = root1 + root2;
        double prod = root1 * root2;
        printf("root1 + root2 = %.2lf\n", sum);
        printf("root1 * root2 = %.2lf\n", prod);
        double sum_from_coeff = -b / a;
        double prod_from_coeff = c / a;
        printf("Sum from coefficients: -b/a = %.2lf\n", sum_from_coeff);
        printf("Product from coefficients: c/a = %.2lf\n", prod_from_coeff);

        if (fabs(sum - sum_from_coeff) < 1e-6 && fabs(prod - prod_from_coeff) < 1e-6) {
            printf("Relationship verified!\n");
        } else {
            printf("There is a mismatch in the relationship.\n");
        }
    } else if (discriminant == 0) {
        double root = -b / (2*a);
        printf("The polynomial has one real root: %.2lf\n", root);
    } else {
        double real = -b / (2*a);
        double imag = sqrt(-discriminant) / (2*a);
        printf("The polynomial has complex roots: %.2lf + %.2lfi and %.2lf - %.2lfi\n", real, imag, real, imag);
    }
}

void make_eqns(double alpha, double beta){
    int sum=alpha+beta
    int prod=alpha*beta
    printf("equation of the roots %.2lf and %.2lf is x^2 + (%.2lf)*x + %.2lf", alpha, beta, sum , prod )
}
int main() {
    int degree;
    int coeffs[3]={1,7,10};
    printf("Enter the degree of the polynomial: ");
    scanf("%d", &degree);

    if (degree == 1) {
        double a, b;
        printf("Enter the coefficients of the linear polynomial (a b): ");
        scanf("%lf %lf", &a, &b);
        solve_linear(a, b);
    } else if (degree == 2) {
        double a, b, c;
        printf("Enter the coefficients of the quadratic polynomial (a b c): ");
        scanf("%lf %lf %lf", &a, &b, &c);
        solve_quadratic(a, b, c);
    } else {
        printf("This calculator currently supports only degree 1 and 2 polynomials.\n");
    }
    
    
    is_it_a_root(coeffs,-2);
    make_eqn(3,4)
    
    
    
    return 0;
}
