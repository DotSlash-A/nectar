// src/main/java/michu/fr/polynomials/models/QuadraticSolution.java
package michu.fr.polynomials.models;

import java.util.List;
import java.util.Objects;

public class QuadraticSolution {
    private final String equationString;
    private final double a, b, c;
    private final double discriminant;
    private final String natureOfRoots;
    private final List<Object> roots; // Can be Double or ComplexNumber or String for "all real numbers"

    public QuadraticSolution(String equationString, double a, double b, double c, double discriminant, String natureOfRoots, List<Object> roots) {
        this.equationString = Objects.requireNonNull(equationString);
        this.a = a;
        this.b = b;
        this.c = c;
        this.discriminant = discriminant;
        this.natureOfRoots = Objects.requireNonNull(natureOfRoots);
        this.roots = Objects.requireNonNull(roots);
    }

    public String getEquationString() { return equationString; }
    public double getA() { return a; }
    public double getB() { return b; }
    public double getC() { return c; }
    public double getDiscriminant() { return discriminant; }
    public String getNatureOfRoots() { return natureOfRoots; }
    public List<Object> getRoots() { return roots; }

    @Override
    public String toString() {
        return "QuadraticSolution{" +
               "equation='" + equationString + '\'' +
               ", discriminant=" + discriminant +
               ", natureOfRoots='" + natureOfRoots + '\'' +
               ", roots=" + roots +
               '}';
    }
    // Add equals and hashCode if needed
}