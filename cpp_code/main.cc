#include "lines/slope.h" // Use relative path from project root
#include "lines/geometry_types.h"

#include "matrix_utils.h" 
#include <iostream>
#include <vector>
#include <optional>
#include <iomanip> // For std::setprecision

// Bring the namespace into scope for convenience
using namespace LineGeometry;

int main() {
    std::cout << "--- C++ Line Calculations ---" << std::endl;

    Coordinates p1 = {1.0, 2.0};
    Coordinates p2 = {4.0, 8.0};
    Coordinates p_vert1 = {1.0, 5.0};
    Coordinates p_horz1 = {5.0, 2.0};

    // Example 1: Calculate Slope
    try {
        double slope = calculate_slope(p1, p2);
        std::cout << "Slope between " << p1 << " and " << p2 << ": " << std::fixed << std::setprecision(2) << slope << std::endl; // Output: 2.00
    } catch (const std::exception& e) {
        std::cerr << "Error calculating slope: " << e.what() << std::endl;
    }
     try {
        calculate_slope(p1, p_vert1); // Vertical line
     } catch (const std::exception& e) {
          std::cerr << "Error calculating slope (expected): " << e.what() << std::endl;
     }


    // Example 2: Find Missing Variable (tangent 'm')
    SlopeInput input_find_y2;
    input_find_y2.x1 = 1.0;
    input_find_y2.y1 = 2.0;
    input_find_y2.x2 = 4.0;
    input_find_y2.m = 2.0; // tangent value
    try {
        double y2 = find_missing_slope_variable("y2", input_find_y2);
        std::cout << "Find y2 (m=tangent): Given x1=1, y1=2, x2=4, m=2 -> y2 = " << y2 << std::endl; // Output: 8.0
    } catch (const std::exception& e) {
         std::cerr << "Error finding variable: " << e.what() << std::endl;
    }

     // Example 2b: Find Missing Variable (angle 'm')
    SlopeInput input_find_y2_angle;
    input_find_y2_angle.x1 = 0.0;
    input_find_y2_angle.y1 = 0.0;
    input_find_y2_angle.x2 = 5.0;
    input_find_y2_angle.m = 45.0; // angle in degrees
    try {
        double y2_angle = find_missing_slope_variable_angle("y2", input_find_y2_angle);
        std::cout << "Find y2 (m=angle): Given x1=0, y1=0, x2=5, m=45deg -> y2 = " << y2_angle << std::endl; // Output: 5.0
    } catch (const std::exception& e) {
         std::cerr << "Error finding variable angle: " << e.what() << std::endl;
    }


    // Example 3: Slope-Intercept Form from 2 points
    try {
        LineEquationResult result = calculate_slope_intercept_form(p1, p2, std::nullopt);
        std::cout << "Slope-Intercept from " << p1 << " and " << p2 << ": " << result.equation << std::endl; // y = 2.00x
    } catch (const std::exception& e) {
        std::cerr << "Error getting slope-intercept: " << e.what() << std::endl;
    }

    // Example 4: Two-Point Form
    try {
        std::string twoPointEq = get_two_point_form(p1, p2);
        std::cout << "Two-Point form for " << p1 << " and " << p2 << ": " << twoPointEq << std::endl; // y - 2.00 = 2.00(x - 1.00)
    } catch (const std::exception& e) {
         std::cerr << "Error getting two-point form: " << e.what() << std::endl;
    }

    // Example 5: Perpendicular Line
    try {
        LineEquationResult perpResult = calculate_perpendicular_line(5.0, p1, p2, std::nullopt); // New y-intercept = 5
        std::cout << "Perpendicular to line through " << p1 << ", " << p2 << " with y-int=5: " << perpResult.equation << std::endl; // y = -0.50x + 5.00
    } catch (const std::exception& e) {
        std::cerr << "Error getting perpendicular line: " << e.what() << std::endl;
    }
     try {
         // Perpendicular to horizontal line (should fail for slope-intercept)
         calculate_perpendicular_line(1.0, p1, p_horz1, std::nullopt);
     } catch (const std::exception& e) {
          std::cerr << "Error getting perpendicular line (expected): " << e.what() << std::endl;
     }

    // Example 6: Transform General to Slope-Intercept
    GeneralLineInput generalInput = {2.0, 4.0, -8.0}; // 2x + 4y - 8 = 0
    try {
        std::string slopeInterceptEq = transform_general_to_slope_intercept(generalInput);
        std::cout << "General " << generalInput << " to Slope-Intercept: " << slopeInterceptEq << std::endl; // y = -0.50x + 2.00
    } catch (const std::exception& e) {
         std::cerr << "Error transforming to slope-intercept: " << e.what() << std::endl;
    }

    // Example 7: Transform General to Intercept
    try {
       std::string interceptEq = transform_general_to_intercept_form(generalInput);
        std::cout << "General " << generalInput << " to Intercept: " << interceptEq << std::endl; // x / 4.00 + y / 2.00 = 1
    } catch (const std::exception& e) {
         std::cerr << "Error transforming to intercept form: " << e.what() << std::endl;
    }

    // Example 8: Normal Form
    try {
        // Line 3x + 4y - 10 = 0 -> Normal is (3/5)x + (4/5)y = 2
        // cos(alpha) = 3/5, sin(alpha) = 4/5 => alpha approx 53.1 deg, p=2
        std::string normalEq = get_normal_form(53.13, 2.0, std::nullopt); // Provide p
        std::cout << "Normal Form (alpha=53.13, p=2): " << normalEq << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error getting normal form: " << e.what() << std::endl;
    }

    return 0;
}