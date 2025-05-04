package michu.fr.progressions.models;

import java.util.List;
import java.util.Objects;

/**
 * Holds the results of inserting Geometric Means between two numbers.
 */
public class GPInsertMeansResult {
    private final double commonRatio;
    private final List<Double> geometricMeans;

    public GPInsertMeansResult(double commonRatio, List<Double> geometricMeans) {
        this.commonRatio = commonRatio;
        this.geometricMeans = Objects.requireNonNull(geometricMeans, "geometricMeans cannot be null");
    }

    public double getCommonRatio() {
        return commonRatio;
    }

    public List<Double> getGeometricMeans() {
        return geometricMeans; // Consider returning an immutable list copy
    }

     @Override
    public String toString() {
        return "GPInsertMeansResult{" +
               "commonRatio=" + commonRatio +
               ", geometricMeans=" + geometricMeans +
               '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        GPInsertMeansResult that = (GPInsertMeansResult) o;
        return Double.compare(that.commonRatio, commonRatio) == 0 &&
               Objects.equals(geometricMeans, that.geometricMeans);
    }

    @Override
    public int hashCode() {
        return Objects.hash(commonRatio, geometricMeans);
    }
}