package michu.fr.threedgeometry.models;

// import java.util.Objects;

public class MagnitudeResult {
    private final Vector3D vector;
    private final double magnitude;

    public MagnitudeResult(Vector3D vector, double magnitude) {
        this.vector = vector;
        this.magnitude = magnitude;
    }

    public Vector3D getVector() { return vector; }
    public double getMagnitude() { return magnitude; }

    @Override
    public String toString() {
        return "MagnitudeResult{" +
               "vector=" + vector +
               ", magnitude=" + String.format("%.4f", magnitude) +
               '}';
    }
    // equals and hashCode
}