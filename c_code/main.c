#include "lines/slope.h" // Use relative path
#include "lines/geometry_types.h"
#include <stdio.h> // For printf, fprintf

#include "matrix/matrix_utils.h" // Include matrix headers
#include <stdio.h>        // For printf, fprintf
#include <stdlib.h>       // For exit (if needed)
int main() {
    printf("--- C Line Calculations ---\n");

    Line_Coordinates p1 = {1.0, 2.0};
    Line_Coordinates p2 = {4.0, 8.0};
    Line_Coordinates p_vert1 = {1.0, 5.0};

    // Buffer for equation strings
    char eq_buffer[LINE_EQUATION_MAX_LEN];
    int status; // To store return codes

    // Example 1: Calculate Slope
    double slope_result;
    status = Line_calculate_slope(&p1, &p2, &slope_result);
    if (status == LINE_SUCCESS) {
        printf("Slope between (%.1f, %.1f) and (%.1f, %.1f): %.2f\n",
               p1.x, p1.y, p2.x, p2.y, slope_result);
    } else {
        fprintf(stderr, "Error calculating slope (code %d)\n", status);
    }

    status = Line_calculate_slope(&p1, &p_vert1, &slope_result);
    if (status != LINE_SUCCESS) {
         fprintf(stderr, "Error calculating slope for vertical line (expected, code %d)\n", status);
    }


    // Example 2: Slope-Intercept Form from 2 points
    Line_EquationResult eq_res;
    status = Line_calculate_slope_intercept_form(&p1, &p2, NULL, &eq_res); // Pass NULL for slope
    if (status == LINE_SUCCESS) {
         printf("Slope-Intercept from (%.1f, %.1f) and (%.1f, %.1f):\n", p1.x, p1.y, p2.x, p2.y);
         printf("  Slope: ");
         if(eq_res.has_slope) printf("%.2f\n", eq_res.slope); else printf("N/A\n");
         printf("  Y-Int: ");
         if(eq_res.has_y_intercept) printf("%.2f\n", eq_res.y_intercept); else printf("N/A\n");
         printf("  Equation: %s\n", eq_res.equation);
    } else {
         fprintf(stderr, "Error getting slope-intercept (code %d)\n", status);
         if (status == LINE_ERR_MATH && eq_res.equation[0] != '\0') {
             // Check if the function populated the equation for special cases like vertical
             fprintf(stderr, "  Equation (special case): %s\n", eq_res.equation);
         }
    }

    // Example 3: Two-Point Form
    status = Line_get_two_point_form(&p1, &p2, eq_buffer, sizeof(eq_buffer));
    if (status == LINE_SUCCESS) {
         printf("Two-Point form for (%.1f, %.1f) and (%.1f, %.1f): %s\n",
                p1.x, p1.y, p2.x, p2.y, eq_buffer);
    } else {
         fprintf(stderr, "Error getting two-point form (code %d)\n", status);
    }

    // Example 4: Find missing variable
    double x1_find = 1.0, y1_find = 2.0, x2_find = 4.0, m_find = 2.0; // Knowns
    double found_y2;
    Line_SlopeInput find_input;
    find_input.x1 = &x1_find; // Pass addresses of knowns
    find_input.y1 = &y1_find;
    find_input.x2 = &x2_find;
    find_input.y2 = NULL;     // Unknown
    find_input.m = &m_find;

    status = Line_find_missing_slope_variable("y2", &find_input, &found_y2);
     if (status == LINE_SUCCESS) {
         printf("Find y2: Given x1=%.1f, y1=%.1f, x2=%.1f, m=%.1f -> y2 = %.2f\n",
                x1_find, y1_find, x2_find, m_find, found_y2);
    } else {
        fprintf(stderr, "Error finding variable 'y2' (code %d)\n", status);
    }


    // ... Add more examples calling other functions ...

// Return 0 from main on successful execution

    printf("--- C Line Calculations ---\n");

    // ... (Your existing Line Calculation examples) ...
    printf("\n"); // Add a separator

    // --- Matrix Calculations ---
    printf("--- C Matrix Calculations ---\n");

    MatrixC *mat1 = NULL, *mat2 = NULL, *matA = NULL, *matB = NULL, *matC = NULL;
    MatrixC *addA = NULL, *addB = NULL;
    MatrixC *mulA = NULL, *mulB = NULL;
    MatrixC *scalarMat = NULL;
    MatrixC *transMat = NULL;
    MatrixC *minorMat = NULL;
    MatrixC *invMat = NULL;
    MatrixC *resultMat = NULL; // For MatrixResponseC results

    int status;

    // Create sample matrices (Remember to destroy them!)
    mat1 = create_matrix(2, 2);
    mat2 = create_matrix(3, 3);
    if (!mat1 || !mat2) { fprintf(stderr, "Failed to create initial matrices\n"); goto cleanup; }
    mat1->data[0][0]=1.0; mat1->data[0][1]=2.0; mat1->data[1][0]=3.0; mat1->data[1][1]=4.0;
    mat2->data[0][0]=6.0; mat2->data[0][1]=1.0; mat2->data[0][2]=1.0;
    mat2->data[1][0]=4.0; mat2->data[1][1]=-2.0;mat2->data[1][2]=5.0;
    mat2->data[2][0]=2.0; mat2->data[2][1]=8.0; mat2->data[2][2]=7.0;

    // Example M1: Determinant
    DeterminantResponseC detResp1, detResp2;
    MatrixInputC inputM1 = {mat1};
    MatrixInputC inputM2 = {mat2};
    status = matrix_calculate_determinant(&inputM1, &detResp1);
    if (status == MATRIX_SUCCESS) {
        matrix_print("Matrix A (Det)", mat1);
        printf("Determinant of A: %.4f\n", detResp1.determinant); // Exp: -2.0
    } else { fprintf(stderr, "Error M1a: det failed (code %d)\n", status); }

    status = matrix_calculate_determinant(&inputM2, &detResp2);
     if (status == MATRIX_SUCCESS) {
        matrix_print("Matrix B (Det)", mat2);
        printf("Determinant of B: %.4f\n", detResp2.determinant); // Exp: -306.0
    } else { fprintf(stderr, "Error M1b: det failed (code %d)\n", status); }
    printf("\n");


    // Example M2: Compare Matrices
    matA = create_matrix(2, 2); matA->data[0][0]=1.0; matA->data[1][1]=1.0;
    matB = create_matrix(2, 2); matB->data[0][0]=1.0; matB->data[1][1]=1.0;
    matC = create_matrix(2, 2); matC->data[0][0]=1.0; matC->data[1][1]=2.0;
    if (!matA || !matB || !matC) { fprintf(stderr, "Failed to create M2 matrices\n"); goto cleanup; }

    MatrixEqualityResponseC eqRespAB, eqRespAC;
    TwoMatrixInputC inputAB = {matA, matB};
    TwoMatrixInputC inputAC = {matA, matC};

    matrix_compare_matrices(&inputAB, &eqRespAB); // This function itself doesn't return error code here
    printf("Compare A vs B: %s (%s)\n", eqRespAB.are_equal ? "true" : "false", eqRespAB.reason);

    matrix_compare_matrices(&inputAC, &eqRespAC);
    printf("Compare A vs C: %s (%s)\n", eqRespAC.are_equal ? "true" : "false", eqRespAC.reason);
    printf("\n");


    // Example M4: Addition
    addA = create_matrix(2, 2); addA->data[0][0]=1.0; addA->data[0][1]=2.0; addA->data[1][0]=3.0; addA->data[1][1]=4.0;
    addB = create_matrix(2, 2); addB->data[0][0]=5.0; addB->data[0][1]=6.0; addB->data[1][0]=7.0; addB->data[1][1]=8.0;
    if (!addA || !addB) { fprintf(stderr, "Failed to create M4 matrices\n"); goto cleanup; }

    MatrixResponseC addResp = {NULL};
    TwoMatrixInputC addInput = {addA, addB};
    status = matrix_add_api(&addInput, &addResp);
    if (status == MATRIX_SUCCESS && addResp.result_matrix) {
        matrix_print("Add A", addA);
        matrix_print("Add B", addB);
        matrix_print("A + B", addResp.result_matrix);
    } else { fprintf(stderr, "Error M4: add failed (code %d)\n", status); }
    printf("\n");


    // Example M6: Matrix Multiply
    mulA = create_matrix(1, 2); mulA->data[0][0]=1.0; mulA->data[0][1]=2.0;
    mulB = create_matrix(2, 1); mulB->data[0][0]=3.0; mulB->data[1][0]=4.0;
     if (!mulA || !mulB) { fprintf(stderr, "Failed to create M6 matrices\n"); goto cleanup; }

    MatrixResponseC mulResp = {NULL};
    TwoMatrixInputC mulInput = {mulA, mulB};
    status = matrix_multiply_matrices_api(&mulInput, &mulResp);
     if (status == MATRIX_SUCCESS && mulResp.result_matrix) {
        matrix_print("Mul A (1x2)", mulA);
        matrix_print("Mul B (2x1)", mulB);
        matrix_print("A * B (1x1)", mulResp.result_matrix);
    } else { fprintf(stderr, "Error M6: multiply failed (code %d)\n", status); }
    printf("\n");


    // Example M8: Minors/Cofactors
    minorMat = create_matrix(3, 3);
    if (!minorMat) { fprintf(stderr, "Failed to create M8 matrix\n"); goto cleanup; }
    minorMat->data[0][0]=1.0; minorMat->data[0][1]=2.0; minorMat->data[0][2]=3.0;
    minorMat->data[1][0]=0.0; minorMat->data[1][1]=4.0; minorMat->data[1][2]=5.0;
    minorMat->data[2][0]=1.0; minorMat->data[2][1]=0.0; minorMat->data[2][2]=6.0;

    MinorsCofactorsResponseC minorResp = {NULL, NULL, 0.0}; // Initialize pointers
    MatrixInputC minorInput = {minorMat};
    status = matrix_calculate_minors_cofactors(&minorInput, &minorResp);
    if (status == MATRIX_SUCCESS) {
        matrix_print("Input for Min/Cof", minorMat);
        printf("  Dimensions: %s\n", minorResp.dimensions);
        matrix_print("  Minors", minorResp.matrix_of_minors);
        matrix_print("  Cofactors", minorResp.matrix_of_cofactors);
        printf("  Determinant: %.4f\n", minorResp.determinant);
    } else { fprintf(stderr, "Error M8: minors/cofactors failed (code %d)\n", status); }
    printf("\n");

    // Example M9: Adjoint/Inverse
    invMat = create_matrix(3, 3);
    if (!invMat) { fprintf(stderr, "Failed to create M9 matrix\n"); goto cleanup; }
    invMat->data[0][0]=1.0; invMat->data[0][1]=2.0; invMat->data[0][2]=3.0;
    invMat->data[1][0]=0.0; invMat->data[1][1]=4.0; invMat->data[1][2]=5.0;
    invMat->data[2][0]=1.0; invMat->data[2][1]=0.0; invMat->data[2][2]=6.0; // Det=22

    AdjInvResponseC invResp = {NULL, NULL, 0.0, false, NULL, NULL}; // Initialize pointers
    MatrixInputC invInput = {invMat};
    status = matrix_calculate_adjoint_inverse(&invInput, &invResp);
     if (status == MATRIX_SUCCESS) {
        matrix_print("Input for Adj/Inv", invMat);
        printf("  Dimensions: %s\n", invResp.dimensions);
        printf("  Determinant: %.4f\n", invResp.determinant);
        printf("  Is Invertible: %s\n", invResp.is_invertible ? "true" : "false");
        matrix_print("  Adjoint", invResp.adjoint_matrix);
        if (invResp.is_invertible && invResp.inverse_matrix) {
            matrix_print("  Inverse", invResp.inverse_matrix);
        } else {
            printf("  Inverse: Not calculated or matrix not invertible.\n");
        }
    } else { fprintf(stderr, "Error M9: adjoint/inverse failed (code %d)\n", status); }
    printf("\n");


cleanup: // Label for jumping to cleanup code
    printf("Cleaning up matrices...\n");
    // IMPORTANT: Free all allocated matrices
    destroy_matrix(mat1);
    destroy_matrix(mat2);
    destroy_matrix(matA);
    destroy_matrix(matB);
    destroy_matrix(matC);
    destroy_matrix(addA);
    destroy_matrix(addB);
    destroy_matrix(mulA);
    destroy_matrix(mulB);
    destroy_matrix(scalarMat); // Was never assigned, safe to call destroy_matrix(NULL)
    destroy_matrix(transMat); // Was never assigned
    destroy_matrix(minorMat);
    destroy_matrix(invMat);

    // Free matrices returned in response structs
    destroy_matrix(addResp.result_matrix);
    destroy_matrix(mulResp.result_matrix);
    destroy_matrix(minorResp.matrix_of_minors);
    destroy_matrix(minorResp.matrix_of_cofactors);
    destroy_matrix(invResp.adjoint_matrix);
    destroy_matrix(invResp.inverse_matrix); // destroy_matrix handles NULL safely


    return 0 ;

}

// int main() {
//     printf("Hello, C World!\n"); // Print text to the console
//     SlopeCoordinates coords = {1.0, 2.0, 3.0, 6.0};
//     double slope = slopecoordinates(coords);
//     printf("Slope: %f\n", slope);
//     return 0;
// }