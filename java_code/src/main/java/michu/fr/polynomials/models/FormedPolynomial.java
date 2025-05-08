 // src/main/java/michu/fr/polynomials/models/FormedPolynomial.java
 package michu.fr.polynomials.models;

 import java.util.List;
 import java.util.Objects;

 public class FormedPolynomial {
     private final List<Double> polynomialCoefficients; // Assuming real coefficients for now
     private final String polynomialString;
     private final List<Double> rootsProvided; // Assuming real roots
     private final double leadingCoefficientUsed;

     public FormedPolynomial(List<Double> polynomialCoefficients, String polynomialString, List<Double> rootsProvided, double leadingCoefficientUsed) {
         this.polynomialCoefficients = Objects.requireNonNull(polynomialCoefficients);
         this.polynomialString = Objects.requireNonNull(polynomialString);
         this.rootsProvided = Objects.requireNonNull(rootsProvided);
         this.leadingCoefficientUsed = leadingCoefficientUsed;
     }

     public List<Double> getPolynomialCoefficients() { return polynomialCoefficients; }
     public String getPolynomialString() { return polynomialString; }
     public List<Double> getRootsProvided() { return rootsProvided; }
     public double getLeadingCoefficientUsed() { return leadingCoefficientUsed; }

     @Override
     public String toString() {
         return "FormedPolynomial{" +
                "polynomialCoefficients=" + polynomialCoefficients +
                ", polynomialString='" + polynomialString + '\'' +
                ", rootsProvided=" + rootsProvided +
                ", leadingCoefficientUsed=" + leadingCoefficientUsed +
                '}';
     }
     // Add equals and hashCode if needed
 }