package michu.fr.realnumbers; // Assuming App.java is here, or place it in michu.fr.realnumbers

// import michu.fr.realnumbers.RealNumberUtils;
import michu.fr.realnumbers.models.*; // Import all models from the realnumbers.models package

import java.util.Map;

public class RealNumbersExamples {

    public static void main(String[] args) {
        System.out.println("--- Real Numbers Examples ---");

        // 1. Euclid's Division Lemma
        System.out.println("\n1. Euclid's Division Lemma:");
        try {
            EuclidLemmaResult lemma1 = RealNumberUtils.euclidsDivisionLemma(455, 42);
            System.out.println("   455 divided by 42: " + lemma1); // Uses toString() of the model
            EuclidLemmaResult lemma2 = RealNumberUtils.euclidsDivisionLemma(10, 3);
            System.out.println("   10 divided by 3: " + lemma2.getEquation()); // Access specific field
        } catch (IllegalArgumentException e) {
            System.err.println("   Error: " + e.getMessage());
        }

        // 2. Euclid's Algorithm for HCF
        System.out.println("\n2. Euclid's Algorithm for HCF:");
        HCFResult hcf1 = RealNumberUtils.euclidsAlgorithmHCF(455, 42);
        System.out.println("   HCF(455, 42): " + hcf1.getHcf());
        HCFResult hcf2 = RealNumberUtils.euclidsAlgorithmHCF(96, 404);
        System.out.println("   HCF(96, 404): " + hcf2.getHcf());
        HCFResult hcf3 = RealNumberUtils.euclidsAlgorithmHCF(17, 0);
        System.out.println("   HCF(17, 0): " + hcf3.getHcf());

        // 3. Prime Factorization
        System.out.println("\n3. Prime Factorization:");
        try {
            PrimeFactorizationResult pf1 = RealNumberUtils.getPrimeFactorization(3825);
            System.out.println("   Prime factors of 3825: " + pf1.getFactors());
            PrimeFactorizationResult pf2 = RealNumberUtils.getPrimeFactorization(96);
            System.out.println("   Prime factors of 96: " + pf2.getFactors());
             // Example showing direct access to factors map
            System.out.print("   Factors of 12: ");
            PrimeFactorizationResult pf12 = RealNumberUtils.getPrimeFactorization(12);
            for (Map.Entry<Integer, Integer> entry : pf12.getFactors().entrySet()) {
                System.out.print(entry.getKey() + "^" + entry.getValue() + " ");
            }
            System.out.println();

        } catch (IllegalArgumentException e) {
            System.err.println("   Error: " + e.getMessage());
        }


        // 4. HCF and LCM (using prime factorization results and direct formula)
        System.out.println("\n4. HCF and LCM Details:");
        try {
            HCFAndLCMResult hcfLcmDetails1 = RealNumberUtils.getHCFAndLCMDetails(96, 404);
            System.out.println("   Details for 96 and 404: " + hcfLcmDetails1);
            
            // Using individual methods
            PrimeFactorizationResult pf96 = RealNumberUtils.getPrimeFactorization(96);
            PrimeFactorizationResult pf404 = RealNumberUtils.getPrimeFactorization(404);
            int hcfFromPf = RealNumberUtils.hcfFromPrimeFactorization(pf96.getFactors(), pf404.getFactors());
            long lcmFromPf = RealNumberUtils.lcmFromPrimeFactorization(pf96.getFactors(), pf404.getFactors());
            System.out.println("   HCF(96,404) from PF: " + hcfFromPf);
            System.out.println("   LCM(96,404) from PF: " + lcmFromPf);

            long lcmDirect = RealNumberUtils.calculateLCM(90, 144);
            System.out.println("   LCM(90, 144) direct: " + lcmDirect);


        } catch (IllegalArgumentException | ArithmeticException e) {
            System.err.println("   Error: " + e.getMessage());
        }

        // 5. Irrationality Check (for sqrt)
        System.out.println("\n5. Irrationality Check (sqrt):");
        IrrationalityCheckResult irr1 = RealNumberUtils.checkSqrtIrrationality(5);
        System.out.println("   sqrt(5): " + irr1);
        IrrationalityCheckResult irr2 = RealNumberUtils.checkSqrtIrrationality(9);
        System.out.println("   sqrt(9): " + irr2);
        IrrationalityCheckResult irr3 = RealNumberUtils.checkSqrtIrrationality(6);
        System.out.println("   sqrt(6): " + irr3);

        // 6. Decimal Expansion Type
        System.out.println("\n6. Decimal Expansion Type:");
        try {
            DecimalExpansionResult de1 = RealNumberUtils.getDecimalExpansionType(13, 3125); // Terminating
            System.out.println("   13/3125: " + de1);
            DecimalExpansionResult de2 = RealNumberUtils.getDecimalExpansionType(64, 455); // Non-terminating recurring
            System.out.println("   64/455: " + de2);
            DecimalExpansionResult de3 = RealNumberUtils.getDecimalExpansionType(17, 8); // Terminating
            System.out.println("   17/8: " + de3);
            DecimalExpansionResult de4 = RealNumberUtils.getDecimalExpansionType(1, 7); // Non-terminating recurring
            System.out.println("   1/7: " + de4);
             DecimalExpansionResult de5 = RealNumberUtils.getDecimalExpansionType(77, 210); // 11/30 -> Non-terminating recurring
            System.out.println("   77/210: " + de5);


        } catch (IllegalArgumentException e) {
            System.err.println("   Error: " + e.getMessage());
        }
        
    }
        
}