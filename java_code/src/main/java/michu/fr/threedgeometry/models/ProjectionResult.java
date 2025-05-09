package michu.fr.threedgeometry.models;

// import java.util.Objects;

public class ProjectionResult {
    private final Vector3D vectorA; // Vector being projected
    private final Vector3D vectorB; // Vector onto which A is projected
    private final double scalarProjection;
    private final Vector3D vectorProjection;

    public ProjectionResult(Vector3D vectorA, Vector3D vectorB, double scalarProjection, Vector3D vectorProjection) {
        this.vectorA = vectorA;
        this.vectorB = vectorB;
        this.scalarProjection = scalarProjection;
        this.vectorProjection = vectorProjection;
    }

    public Vector3D getVectorA() { return vectorA; }
    public Vector3D getVectorB() { return vectorB; }
    public double getScalarProjection() { return scalarProjection; }
    public Vector3D getVectorProjection() { return vectorProjection; }

    @Override
    public String toString() {
        return "ProjectionResult{" +
               "vectorA=" + vectorA +
               ", vectorB=" + vectorB +
               ", scalarProjection=" + String.format("%.4f", scalarProjection) +
               ", vectorProjection=" + vectorProjection +
               '}';
    }
    // equals and hashCode
}