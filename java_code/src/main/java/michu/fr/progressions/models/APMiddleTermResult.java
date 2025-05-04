package michu.fr.progressions.models;

import java.util.List;
import java.util.Objects;

/**
 * Holds the results of finding the middle term(s) of an Arithmetic Progression.
 */
public class APMiddleTermResult {
    private final int numberOfTerms;
    private final List<Integer> middleIndices; // 1-based indices
    private final List<Double> middleValues;

    public APMiddleTermResult(int numberOfTerms, List<Integer> middleIndices, List<Double> middleValues) {
        this.numberOfTerms = numberOfTerms;
        // Ensure lists are not null, prefer immutable copies if possible, but direct assignment is simpler here
        this.middleIndices = Objects.requireNonNull(middleIndices, "middleIndices cannot be null");
        this.middleValues = Objects.requireNonNull(middleValues, "middleValues cannot be null");
    }

    public int getNumberOfTerms() {
        return numberOfTerms;
    }

    public List<Integer> getMiddleIndices() {
        return middleIndices; // Consider returning an immutable list copy
    }

    public List<Double> getMiddleValues() {
        return middleValues; // Consider returning an immutable list copy
    }

    @Override
    public String toString() {
        return "APMiddleTermResult{" +
               "numberOfTerms=" + numberOfTerms +
               ", middleIndices=" + middleIndices +
               ", middleValues=" + middleValues +
               '}';
    }

     @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        APMiddleTermResult that = (APMiddleTermResult) o;
        return numberOfTerms == that.numberOfTerms &&
               Objects.equals(middleIndices, that.middleIndices) &&
               Objects.equals(middleValues, that.middleValues);
    }

    @Override
    public int hashCode() {
        return Objects.hash(numberOfTerms, middleIndices, middleValues);
    }
}
