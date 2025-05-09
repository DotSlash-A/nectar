package michu.fr.threedgeometry.models;

// import java.util.Objects;

public class DotProductResult {
    private final Vector3D vector1;
    private final Vector3D vector2;
    private final double dotProduct;
    private final Double angleDegrees; // Nullable
    private final Double angleRadians; // Nullable

    public DotProductResult(Vector3D vector1, Vector3D vector2, double dotProduct, Double angleRadians, Double angleDegrees) {
        this.vector1 = vector1;
        this.vector2 = vector2;
        this.dotProduct = dotProduct;
        this.angleRadians = angleRadians;
        this.angleDegrees = angleDegrees;
    }

    public Vector3D getVector1() { return vector1; }
    public Vector3D getVector2() { return vector2; }
    public double getDotProduct() { return dotProduct; }
    public Double getAngleDegrees() { return angleDegrees; }
    public Double getAngleRadians() { return angleRadians; }

    @Override
    public String toString() {
        return "DotProductResult{" +
               "vector1=" + vector1 +
               ", vector2=" + vector2 +
               ", dotProduct=" + String.format("%.4f", dotProduct) +
               (angleDegrees != null ? ", angleDegrees=" + String.format("%.2f", angleDegrees) : "") +
               '}';
    }
    // equals and hashCode
}