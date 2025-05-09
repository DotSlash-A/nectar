#include <stdio.h>
#include "three_d_geometry/three_d_geometry_utils.h" // Only 3D geometry headers

// Helper to print section titles
void print_section_title_3d(const char* title) {
    printf("\n--- %s ---\n", title);
}

int main() {
    printf("--- 3D Geometry C Module Examples ---\n");
    // int ret; // For checking return codes (if you implement error checks in main)

    // --- 3D Geometry Examples ---
    print_section_title_3d("Vector Algebra");
    Point3D_C pA, pB, pC;
    Vector3D_C v1, v2, v_res;
    
    point3d_c_init(&pA, 1, 0, 1);
    point3d_c_init(&pB, 3, 2, -1);
    char pA_s[MAX_STRING_LEN], pB_s[MAX_STRING_LEN];
    printf("Point pA: %s\n", point3d_c_to_string(&pA, pA_s, sizeof(pA_s)));
    printf("Point pB: %s\n", point3d_c_to_string(&pB, pB_s, sizeof(pB_s)));

    vector3d_c_init(&v1, 1, 2, 3);
    vector3d_c_init(&v2, 4, -1, 2);
    char v1_s[MAX_STRING_LEN], v2_s[MAX_STRING_LEN];
    printf("Vector v1: %s\n", vector3d_c_to_string(&v1, v1_s, sizeof(v1_s)));
    printf("Vector v2: %s\n", vector3d_c_to_string(&v2, v2_s, sizeof(v2_s)));

    v_res = vector3d_c_add(&v1, &v2);
    printf("v1 + v2: %s\n", vector3d_c_to_string(&v_res, v1_s, sizeof(v1_s))); // reuse buffer

    MagnitudeResult_C mag_res;
    tdg_vector_magnitude(&v1, &mag_res);
    printf("Magnitude of v1: %s\n", magnitude_result_c_to_string(&mag_res));

    UnitVectorResult_C unit_res;
    tdg_unit_vector(&v1, &unit_res);
    printf("Unit vector of v1: %s\n", unit_vector_result_c_to_string(&unit_res));
    
    tdg_vector_from_two_points(&pA, &pB, &v_res);
    printf("Vector P_A P_B: %s\n", vector3d_c_to_string(&v_res, v1_s, sizeof(v1_s)));

    SectionFormulaResult_C sec_res;
    tdg_section_formula(&pA, &pB, 1, 2, true, &sec_res);
    printf("Section formula (internal 1:2 for pA,pB): %s\n", section_formula_result_c_to_string(&sec_res));

    Point3D_C points_col[] = {{1,1,1}, {2,2,2}, {3,3,3}};
    CollinearityResult_C coll_res;
    tdg_check_collinearity_points(points_col, 3, &coll_res);
    printf("Collinearity (collinear): %s\n", collinearity_result_c_to_string(&coll_res));


    print_section_title_3d("Dot and Cross Products");
    DotProductResult_C dp_res;
    tdg_dot_product(&v1, &v2, &dp_res); // v1=(1,2,3), v2=(4,-1,2) -> 4-2+6 = 8
    printf("Dot Product (v1.v2): %s\n", dot_product_result_c_to_string(&dp_res));

    ProjectionResult_C proj_res;
    tdg_projection_vector_on_vector(&v1, &v2, &proj_res);
    printf("Projection of v1 on v2: %s\n", projection_result_c_to_string(&proj_res));

    CrossProductResult_C cp_res;
    tdg_cross_product(&v1, &v2, &cp_res); // (1,2,3)x(4,-1,2) = (7, 10, -9)
    printf("Cross Product (v1 x v2): %s\n", cross_product_result_c_to_string(&cp_res));

    point3d_c_init(&pA, 1,1,0); point3d_c_init(&pB, 3,1,0); point3d_c_init(&pC, 1,3,0);
    AreaTriangleResult_C area_res;
    tdg_area_triangle_points(&pA, &pB, &pC, &area_res);
    printf("Area of Triangle (points): %s\n", area_triangle_result_c_to_string(&area_res));
    
    Vector3D_C i_vec,j_vec,k_vec;
    vector3d_c_init(&i_vec,1,0,0); vector3d_c_init(&j_vec,0,1,0); vector3d_c_init(&k_vec,0,0,1);
    ScalarTripleProductResult_C stp_res;
    tdg_scalar_triple_product(&i_vec, &j_vec, &k_vec, &stp_res);
    printf("Scalar Triple Product [i j k]: %s\n", scalar_triple_product_result_c_to_string(&stp_res));


    print_section_title_3d("Direction Cosines and Ratios");
    Vector3D_C dir_example_v; vector3d_c_init(&dir_example_v, 3,4,0);
    DirectionRatios_C dr_example;
    tdg_direction_ratios_from_vector(&dir_example_v, &dr_example);
    printf("DR for (3,4,0): %s\n", direction_ratios_c_to_string(&dr_example));
    DirectionCosines_C dc_example;
    tdg_direction_cosines_from_ratios(&dr_example, &dc_example);
    printf("DC from DRs: %s\n", direction_cosines_c_to_string(&dc_example));


    print_section_title_3d("Straight Line");
    Point3D_C line_p0; point3d_c_init(&line_p0, 1,2,3);
    Vector3D_C line_dv; vector3d_c_init(&line_dv, 2,-1,2);
    LineEquationResult_C line_eq_res;
    tdg_line_eq_vector_form(&line_p0, &line_dv, &line_eq_res);
    printf("Line (Vector Form): %s\n", line_equation_result_c_to_string(&line_eq_res));
    
    DirectionRatios_C line_dr_cart; line_dr_cart.a=2; line_dr_cart.b=0; line_dr_cart.c=-3;
    tdg_line_eq_cartesian_symmetric(&line_p0, &line_dr_cart, &line_eq_res);
    printf("Line (Cartesian Symm): %s\n", line_equation_result_c_to_string(&line_eq_res));

    AngleBetweenLinesResult_C abl_res;
    tdg_angle_between_lines(&v1, &v2, &abl_res); // Use existing v1, v2
    printf("Angle between v1 and v2: %s\n", angle_between_lines_result_c_to_string(&abl_res));

    // Examples for other line functions (mostly stubbed)
    LinesRelationshipResult_C lines_rel_res;
    tdg_lines_relationship(&line_p0, &line_dv, &pA, &v1, &lines_rel_res); // using some existing vars
    printf("Lines Relationship (STUB): %s\n", lines_relationship_result_c_to_string(&lines_rel_res));

    DistancePointLineResult_C dpl_res;
    tdg_distance_point_line(&pA, &line_p0, &line_dv, &dpl_res);
    printf("Distance Point to Line (STUB): %s\n", distance_point_line_result_c_to_string(&dpl_res));

    ImagePointResult_C img_line_res;
    tdg_image_of_point_in_line(&pA, &line_eq_res, &img_line_res);
    printf("Image of Point in Line (STUB): %s\n", image_point_result_c_to_string(&img_line_res));


    print_section_title_3d("Plane (most operations are STUBBED)");
    PlaneEquationCoefficients_C plane_coeffs_ex;
    plane_coeffs_ex.a = 1; plane_coeffs_ex.b = 1; plane_coeffs_ex.c = 1; plane_coeffs_ex.d_lhs = -3; // x+y+z-3=0
    char plane_coeffs_s[MAX_STRING_LEN];
    // Use the specific toString for PlaneEquationCoefficients_C which is not a stub
    printf("Plane Coeffs: %s\n", plane_equation_coefficients_c_to_string_impl(&plane_coeffs_ex));

    PlaneEquationResult_C plane_res;
    tdg_plane_eq_from_coeffs(&plane_coeffs_ex, &plane_res);
    printf("Plane from Coeffs: %s\n", plane_equation_result_c_to_string(&plane_res));
    
    tdg_plane_eq_cartesian_from_normal_point(&v1, &pA, &plane_res); // Using v1 as normal, pA as point
    printf("Plane from Normal & Point (STUB): %s\n", plane_equation_result_c_to_string(&plane_res));

    // Call a few more stubbed functions to ensure they link and run
    Point3D_C test_pt_plane; point3d_c_init(&test_pt_plane, 4,4,4);
    ImagePointResult_C img_plane_res;
    tdg_image_of_point_in_plane(&test_pt_plane, &plane_coeffs_ex, &img_plane_res);
    printf("Image of Point in Plane (STUB): %s\n", image_point_result_c_to_string(&img_plane_res));

    IntersectionTwoPlanesResult_C i2p_res;
    PlaneEquationCoefficients_C plane_coeffs_ex2 = {2, -1, 1, -5}; // Another plane
    tdg_intersection_two_planes(&plane_coeffs_ex, &plane_coeffs_ex2, &i2p_res);
    printf("Intersection of Two Planes (STUB): %s\n", intersection_two_planes_result_c_to_string(&i2p_res));

    printf("\n--- End of 3D Geometry C Module Examples ---\n");
    return 0;
}