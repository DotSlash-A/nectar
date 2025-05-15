#include <stdio.h>

int main() {
    int a1=2, b1=3, c1=8;
    int a2=1, b2=-1, c2=1;
    double xsol, ysol;

    printf("Eqn1: %dx+%dy=%d\n", a1, b1, c1);
    printf("Eqn2: %dx+%dy=%d\n", a2, b2, c2);

    printf("Express y: y=(%d-%dx)/(%d)\n", c1, a1, b1);
    printf("Substitute y in Eqn2: %dx+(%d)*((%d-%dx)/%d)=%d\n", a2, b2, c1, a1, b1, c2);

    // Calculate denominator and numerator for x
    double denominator = a2 * b1 - b2 * a1;
    double numerator = c2 * b1 - b2 * c1;

    printf("x = (%.2lf) / (%.2lf)\n", numerator, denominator);

    if(denominator != 0) {
        xsol = numerator / denominator;
        printf("x = %.2lf\n", xsol);

        // Now substitute x to get y
        ysol = (c1 - a1 * xsol) / (double)b1;
        printf("y = %.2lf\n", ysol);
    } else {
        printf("No unique solution (lines are parallel or coincident).\n");
    }

    return 0;
}
