#include <iostream>
#include <cmath>
using namespace std;

// Function to solve linear equation ax + b = 0
void solve_linear(double a, double b) {
    cout << "The polynomial you entered is " << a << "*x + " << b << " = 0" << endl;
    if (a != 0) {
        double res = -b / a;
        cout << "The zero of this polynomial is " << res << endl;
    } else {
        cout << "Coefficient 'a' cannot be zero for a linear polynomial." << endl;
    }
}

void is_it_a_root(int coeffs[], int root) {
    int subs = (coeffs[0] * root * root) + coeffs[1] * root + coeffs[2];
    if (subs == 0) {
        cout << "It is a root" << endl;
    } else {
        cout << "Uh oh!" << endl;
    }
}

// Function to solve quadratic equation ax^2 + bx + c = 0
void solve_quadratic(double a, double b, double c) {
    cout << "The polynomial you entered is " << a << "*x^2 + " << b << "*x + " << c << " = 0" << endl;
    if (a == 0) {
        cout << "Coefficient 'a' cannot be zero for a quadratic polynomial." << endl;
        return;
    }
    double discriminant = b * b - 4 * a * c;
    if (discriminant > 0) {
        double root1 = (-b + sqrt(discriminant)) / (2 * a);
        double root2 = (-b - sqrt(discriminant)) / (2 * a);
        cout << "The roots of the polynomial are " << root1 << " and " << root2 << endl;

        // Verification
        double sum = root1 + root2;
        double prod = root1 * root2;
        cout << "root1 + root2 = " << sum << endl;
        cout << "root1 * root2 = " << prod << endl;
        double sum_from_coeff = -b / a;
        double prod_from_coeff = c / a;
        cout << "Sum from coefficients: -b/a = " << sum_from_coeff << endl;
        cout << "Product from coefficients: c/a = " << prod_from_coeff << endl;

        if (fabs(sum - sum_from_coeff) < 1e-6 && fabs(prod - prod_from_coeff) < 1e-6) {
            cout << "Relationship verified!" << endl;
        } else {
            cout << "There is a mismatch in the relationship." << endl;
        }
    } else if (discriminant == 0) {
        double root = -b / (2 * a);
        cout << "The polynomial has one real root: " << root << endl;
    } else {
        double real = -b / (2 * a);
        double imag = sqrt(-discriminant) / (2 * a);
        cout << "The polynomial has complex roots: " << real << " + " << imag << "i and " << real << " - " << imag << "i" << endl;
    }
}

void make_eqns(double alpha, double beta) {
    double sum = alpha + beta;
    double prod = alpha * beta;
    cout << "Equation of the roots " << alpha << " and " << beta << " is x^2 - (" << sum << ")*x + " << prod << " = 0" << endl;
}

int main() {
    int degree;
    int coeffs[3] = {1, 7, 10};
    cout << "Enter the degree of the polynomial: ";
    cin >> degree;

    if (degree == 1) {
        double a, b;
        cout << "Enter the coefficients of the linear polynomial (a b): ";
        cin >> a >> b;
        solve_linear(a, b);
    } else if (degree == 2) {
        double a, b, c;
        cout << "Enter the coefficients of the quadratic polynomial (a b c): ";
        cin >> a >> b >> c;
        solve_quadratic(a, b, c);
    } else {
        cout << "This calculator currently supports only degree 1 and 2 polynomials." << endl;
    }

    is_it_a_root(coeffs, -2);
    make_eqns(3, 4);

    return 0;
}
