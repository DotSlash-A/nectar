package michu.fr.linearequations; // Or michu.fr if App.java is there

import michu.fr.linearequations.models.ConsistencyCheckResult;
import michu.fr.linearequations.models.ReducibleSolutionResult;
import michu.fr.linearequations.models.SolutionResult;

public class LinearEquationsExamples {

    public static void main(String[] args) {
        System.out.println("--- Pair of Linear Equations Examples ---");

        // Example Equations (a1x + b1y = c1, a2x + b2y = c2)
        double a1_uniq=1, b1_uniq=1, c1_uniq=5;
        double a2_uniq=2, b2_uniq=-3, c2_uniq=4; // Unique: x=3.8, y=1.2

        double a1_inf=2, b1_inf=3, c1_inf=9;
        double a2_inf=4, b2_inf=6, c2_inf=18; // Infinite

        double a1_par=1, b1_par=2, c1_par=4;
        double a2_par=2, b2_par=4, c2_par=12; // Parallel

        // 1. Check Consistency
        System.out.println("\n1. Consistency Check:");
        ConsistencyCheckResult cc1 = LinearEquationUtils.checkConsistency(a1_uniq, b1_uniq, c1_uniq, a2_uniq, b2_uniq, c2_uniq);
        System.out.println("   Unique Sol System: " + cc1.getConsistencyType() + " - " + cc1.getGraphicalInterpretation());
        System.out.println("     Ratios: " + cc1.getRatios());
        System.out.println("     Desc: " + cc1.getDescription());


        ConsistencyCheckResult cc2 = LinearEquationUtils.checkConsistency(a1_inf, b1_inf, c1_inf, a2_inf, b2_inf, c2_inf);
        System.out.println("   Infinite Sol System: " + cc2.getConsistencyType() + " - " + cc2.getGraphicalInterpretation());

        ConsistencyCheckResult cc3 = LinearEquationUtils.checkConsistency(a1_par, b1_par, c1_par, a2_par, b2_par, c2_par);
        System.out.println("   Parallel System: " + cc3.getConsistencyType() + " - " + cc3.getGraphicalInterpretation());

        // 2. Solve General (using Apache Commons Math)
        System.out.println("\n2. General Solver:");
        SolutionResult sol_gen1 = LinearEquationUtils.solveGeneral(a1_uniq, b1_uniq, c1_uniq, a2_uniq, b2_uniq, c2_uniq);
        System.out.println("   Unique Sol System (General): " + sol_gen1);

        SolutionResult sol_gen2 = LinearEquationUtils.solveGeneral(a1_inf, b1_inf, c1_inf, a2_inf, b2_inf, c2_inf);
        System.out.println("   Infinite Sol System (General): " + sol_gen2);

        SolutionResult sol_gen3 = LinearEquationUtils.solveGeneral(a1_par, b1_par, c1_par, a2_par, b2_par, c2_par);
        System.out.println("   Parallel System (General): " + sol_gen3);

        // 3. Solve by Substitution (Simplified implementation in Utils)
        System.out.println("\n3. Solver by Substitution:");
        SolutionResult sol_sub1 = LinearEquationUtils.solveBySubstitution(1, 2, 3, 7, -15, 2); // x=49/29, y=19/29
        System.out.println("   Solve 1x+2y=3, 7x-15y=2 (Substitution): " + sol_sub1);
        if (sol_sub1.getSteps() != null) sol_sub1.getSteps().forEach(step -> System.out.println("      Step: " + step));


        // 4. Solve by Elimination (Simplified implementation in Utils)
        System.out.println("\n4. Solver by Elimination:");
        SolutionResult sol_elim1 = LinearEquationUtils.solveByElimination(9, -4, 2000, 7, -3, 2000); // x=2000/(-27 - (-28)) = 2000, y = (9*2k - 7*2k)/ (9*-3 - 7*-4) = 4000
        // x= -2000, y = -11000  (9x-4y=2000, 7x-3y=2000 => x = -2000, y = -5000) No, book example 9x-4y=2000, 7x-3y=2000 -> x=2000, y=4000. This means my mental math is wrong.
        // Actually for that system:
        //  (27x - 12y = 6000) - (28x - 12y = 8000) => -x = -2000 => x=2000
        //  9(2000) - 4y = 2000 => 18000 - 4y = 2000 => 16000 = 4y => y=4000
        System.out.println("   Solve 9x-4y=2000, 7x-3y=2000 (Elimination): " + sol_elim1);
         if (sol_elim1.getSteps() != null) sol_elim1.getSteps().forEach(step -> System.out.println("      Step: " + step));


        // 5. Solve by Cross-Multiplication
        //    Requires equations in form a1x + b1y + C1 = 0. So C1 = -c1
        System.out.println("\n5. Solver by Cross-Multiplication:");
        // Example: 2x + y = 5  => 2x + y - 5 = 0  (C1 = -5)
        //          3x + 2y = 8 => 3x + 2y - 8 = 0 (C2 = -8)
        // Solution: x=2, y=1
        SolutionResult sol_cross1 = LinearEquationUtils.solveByCrossMultiplication(2, 1, -5, 3, 2, -8);
        System.out.println("   Solve 2x+y-5=0, 3x+2y-8=0 (Cross-Mult): " + sol_cross1);
        if (sol_cross1.getSteps() != null) sol_cross1.getSteps().forEach(step -> System.out.println("      Step: " + step));


        // 6. Solve Reducible Equations
        System.out.println("\n6. Reducible Equations Solver:");
        // Example: 2/x + 3/y = 13. Let u=1/x, v=1/y. So, 2u + 3v = 13
        //          5/x - 4/y = -2.                         5u - 4v = -2
        // Solving for u,v: u=2, v=3. So x=1/2, y=1/3.
        ReducibleSolutionResult red_sol1 = LinearEquationUtils.solveReducible(
                2, 3, 13,
                5, -4, -2,
                "1/x", "1/y"
        );
        System.out.println("   Reducible 2/x+3/y=13, 5/x-4/y=-2: ");
        System.out.println("     Substituted system solution u (as X): " + red_sol1.getSolutionXString() + ", v (as Y): " + red_sol1.getSolutionYString());
        System.out.println("     Original system solution x: " + red_sol1.getOriginalSolutionXString() + ", y: " + red_sol1.getOriginalSolutionYString());
        System.out.println("     Substitution details: " + red_sol1.getSubstitutionDetails());

    }
}