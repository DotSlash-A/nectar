// src/main/java/michu/fr/polynomials/models/PolynomialDivisionResult.java
package michu.fr.polynomials.models;

import java.util.List;
import java.util.Objects;

public class PolynomialDivisionResult {
    private final List<Double> quotientCoefficients;
    private final List<Double> remainderCoefficients;
    private final String quotientString;
    private final String remainderString;
    private final String equationString; // p(x) = d(x)q(x) + r(x)


    public PolynomialDivisionResult(List<Double> quotientCoefficients, List<Double> remainderCoefficients,
                                    String quotientString, String remainderString, String equationString) {
        this.quotientCoefficients = Objects.requireNonNull(quotientCoefficients);
        this.remainderCoefficients = Objects.requireNonNull(remainderCoefficients);
        this.quotientString = Objects.requireNonNull(quotientString);
        this.remainderString = Objects.requireNonNull(remainderString);
        this.equationString = Objects.requireNonNull(equationString);
    }

    public List<Double> getQuotientCoefficients() {
        return quotientCoefficients;
    }

    public List<Double> getRemainderCoefficients() {
        return remainderCoefficients;
    }

    public String getQuotientString() { return quotientString; }

    public String getRemainderString() { return remainderString; }

    public String getEquationString() { return equationString; }

    @Override
    public String toString() {
        return "PolynomialDivisionResult{" +
               "quotient=" + quotientString +
               ", remainder=" + remainderString +
               ", equation='" + equationString + '\'' +
               '}';
    }
    // Add equals and hashCode if needed
}