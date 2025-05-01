package michu.fr.circles.models;

import java.util.Objects;

// Corresponds to Python's CircleDetailsResponse
public class CircleDetailsResponse {
    private final double centerH;
    private final double centerK;
    private final double radius;
    private final String inputEquation;
    private final String normalizedEquation; // Can be null

    public CircleDetailsResponse(double centerH, double centerK, double radius, String inputEquation, String normalizedEquation) {
        this.centerH = centerH;
        this.centerK = centerK;
        this.radius = radius;
        this.inputEquation = inputEquation;
        this.normalizedEquation = normalizedEquation;
    }

    // Getters
    public double getCenterH() { return centerH; }
    public double getCenterK() { return centerK; }
    public double getRadius() { return radius; }
    public String getInputEquation() { return inputEquation; }
    public String getNormalizedEquation() { return normalizedEquation; } // Can return null


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        CircleDetailsResponse that = (CircleDetailsResponse) o;
        return Double.compare(that.centerH, centerH) == 0 && Double.compare(that.centerK, centerK) == 0 && Double.compare(that.radius, radius) == 0 && Objects.equals(inputEquation, that.inputEquation) && Objects.equals(normalizedEquation, that.normalizedEquation);
    }

    @Override
    public int hashCode() {
        return Objects.hash(centerH, centerK, radius, inputEquation, normalizedEquation);
    }

    @Override
    public String toString() {
        return "CircleDetailsResponse{" + "centerH=" + centerH + ", centerK=" + centerK + ", radius=" + radius + ", inputEquation='" + inputEquation + '\'' + ", normalizedEquation='" + normalizedEquation + '\'' + '}';
    }
}