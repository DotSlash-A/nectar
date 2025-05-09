package michu.fr.threedgeometry.models;

// import java.util.Objects;

public class CrossProductResult {
    private final Vector3D vector1;
    private final Vector3D vector2;
    private final Vector3D crossProductVector;
    private final Double magnitudeOfCrossProduct; // Also area of parallelogram
    private final Double areaOfParallelogram;

    public CrossProductResult(Vector3D vector1, Vector3D vector2, Vector3D crossProductVector, Double magnitudeOfCrossProduct) {
        this.vector1 = vector1;
        this.vector2 = vector2;
        this.crossProductVector = crossProductVector;
        this.magnitudeOfCrossProduct = magnitudeOfCrossProduct;
        this.areaOfParallelogram = magnitudeOfCrossProduct; // They are the same
    }
    
    public Vector3D getVector1() { return vector1; }
    public Vector3D getVector2() { return vector2; }
    public Vector3D getCrossProductVector() { return crossProductVector; }
    public Double getMagnitudeOfCrossProduct() { return magnitudeOfCrossProduct; }
    public Double getAreaOfParallelogram() { return areaOfParallelogram; }

    @Override
    public String toString() {
        return "CrossProductResult{" +
               "vector1=" + vector1 +
               ", vector2=" + vector2 +
               ", crossProductVector=" + crossProductVector +
               (magnitudeOfCrossProduct != null ? ", areaOfParallelogram=" + String.format("%.4f", magnitudeOfCrossProduct) : "") +
               '}';
    }
    // equals and hashCode
}