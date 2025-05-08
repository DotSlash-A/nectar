// src/main/java/michu/fr/polynomials/models/RootsCoefficientsRelation.java
package michu.fr.polynomials.models;

import java.util.Map;
import java.util.Objects;

public class RootsCoefficientsRelation {
    private final String polynomialString;
    private final int degree;
    private final Map<String, Object> relations; // e.g., "sum_of_roots": value
    private final String verificationNote;

    public RootsCoefficientsRelation(String polynomialString, int degree, Map<String, Object> relations, String verificationNote) {
        this.polynomialString = Objects.requireNonNull(polynomialString);
        this.degree = degree;
        this.relations = Objects.requireNonNull(relations);
        this.verificationNote = verificationNote; // Can be null
    }

    public String getPolynomialString() { return polynomialString; }
    public int getDegree() { return degree; }
    public Map<String, Object> getRelations() { return relations; }
    public String getVerificationNote() { return verificationNote; }

    @Override
    public String toString() {
        return "RootsCoefficientsRelation{" +
               "polynomial='" + polynomialString + '\'' +
               ", degree=" + degree +
               ", relations=" + relations +
               (verificationNote != null ? ", note='" + verificationNote + '\'' : "") +
               '}';
    }
    // Add equals and hashCode if needed
}