#include <stdio.h>
#include <math.h>

int main() {
    int a = 9, b = -15, c = 6;
    printf("The obtained equation is %dx^2 %+dx %+d = 0\n", a, b, c);

    // Step 1: Make coefficient of x^2 as 1
    double b1 = (double)b / a;
    double c1 = (double)c / a;
    printf("Step 1: Divide both sides by %d to make coefficient of x^2 as 1:\n", a);
    printf("x^2 %+0.2lfx %+0.2lf = 0\n", b1, c1);

    // Step 2: Move constant to right side
    printf("Step 2: Move constant to the right side:\n");
    printf("x^2 %+0.2lfx = %+0.2lf\n", b1, -c1);

    // Step 3: Complete the square
    double half_b1 = b1 / 2;
    double square_half_b1 = half_b1 * half_b1;
    printf("Step 3: Add (%.2lf/2)^2 = %.3lf to both sides to complete the square:\n", b1, square_half_b1);
    printf("x^2 %+0.2lfx %+0.3lf = %+0.2lf %+0.3lf\n", b1, square_half_b1, -c1, square_half_b1);

    // Step 4: Simplify right side
    double right = -c1 + square_half_b1;
    printf("x^2 %+0.2lfx %+0.3lf = %.3lf\n", b1, square_half_b1, right);

    // Step 5: Write as perfect square
    printf("Step 4: Write left side as a perfect square:\n");
    printf("(x %+0.3lf)^2 = %.3lf\n", half_b1, right);

    // Step 6: Take square roots
    if (right < 0) {
        printf("No real solutions (right side is negative).\n");
    } else {
        double sqrt_right = sqrt(right);
        printf("Step 5: Take square roots:\n");
        printf("x %+0.3lf = ±%.3lf\n", half_b1, sqrt_right);

        // Step 7: Solve for x
        double x1 = -half_b1 + sqrt_right;
        double x2 = -half_b1 - sqrt_right;
        printf("Step 6: Solve for x:\n");
        printf("x1 = %.3lf\n", x1);
        printf("x2 = %.3lf\n", x2);
    }

    return 0;
}
