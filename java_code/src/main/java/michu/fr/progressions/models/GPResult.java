package michu.fr.progressions.models;

import java.util.Objects;

/**
 * Holds the results of basic Geometric Progression calculations.
 */
public class GPResult {
    private final double nthTerm;
    private final double sumNTerms;

    public GPResult(double nthTerm, double sumNTerms) {
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
        return "GPResult{" +
               "nthTerm=" + nthTerm +
               ", sumNTerms=" + sumNTerms +
               '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        GPResult gpResult = (GPResult) o;
        return Double.compare(gpResult.nthTerm, nthTerm) == 0 &&
               Double.compare(gpResult.sumNTerms, sumNTerms) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(nthTerm, sumNTerms);
    }
}
