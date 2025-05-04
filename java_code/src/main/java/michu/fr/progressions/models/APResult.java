// src/main/java/michu/fr/progressions/models/APResult.java
package michu.fr.progressions.models;

import java.util.Objects;

/**
 * Holds the results of basic Arithmetic Progression calculations.
 */
public class APResult {
    private final double nthTerm;
    private final double sumNTerms;

    public APResult(double nthTerm, double sumNTerms) {
        this.nthTerm = nthTerm;
        this.sumNTerms = sumNTerms;
    }

    public double getNthTerm() {
        return nthTerm;
    }

    public double getSumNTerms() {
        return sumNTerms;
    }

    @Override
    public String toString() {
        return "APResult{" +
               "nthTerm=" + nthTerm +
               ", sumNTerms=" + sumNTerms +
               '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        APResult apResult = (APResult) o;
        return Double.compare(apResult.nthTerm, nthTerm) == 0 &&
               Double.compare(apResult.sumNTerms, sumNTerms) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(nthTerm, sumNTerms);
    }
}