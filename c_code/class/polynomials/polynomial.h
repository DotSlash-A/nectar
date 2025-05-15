#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

// Structure to represent a polynomial
// Example: 3x^2 - 2x + 5
// degree = 2
// coeffs[0] = 5 (constant term, for x^0)
// coeffs[1] = -2 (coefficient of x^1)
// coeffs[2] = 3 (coefficient of x^2)
typedef struct {
    int degree;       // Highest power of x
    double *coeffs;   // Pointer to an array of coefficients (double for precision)
} Polynomial;

// 
// Polynomial* createPolynomial(int degree.)

#endif