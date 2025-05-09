package michu.fr.threedgeometry.models;

// import java.util.Objects;

public class ScalarTripleProductResult {
    private final Vector3D vectorA;
    private final Vector3D vectorB;
    private final Vector3D vectorC;
    private final double scalarTripleProduct; // Volume of parallelepiped
    private final boolean areCoplanar;

    public ScalarTripleProductResult(Vector3D vectorA, Vector3D vectorB, Vector3D vectorC, double scalarTripleProduct, boolean areCoplanar) {
        this.vectorA = vectorA;
        this.vectorB = vectorB;
        this.vectorC = vectorC;
        this.scalarTripleProduct = scalarTripleProduct;
        this.areCoplanar = areCoplanar;
    }
    
    public Vector3D getVectorA() { return vectorA; }
    public Vector3D getVectorB() { return vectorB; }
    public Vector3D getVectorC() { return vectorC; }
    public double getScalarTripleProduct() { return scalarTripleProduct; }
    public boolean areCoplanar() { return areCoplanar; }

    @Override
    public String toString() {
        return "ScalarTripleProductResult{" +
               "vectorA=" + vectorA +
               ", vectorB=" + vectorB +
               ", vectorC=" + vectorC +
               ", stp (volume)=" + String.format("%.4f", scalarTripleProduct) +
               ", areCoplanar=" + areCoplanar +
               '}';
    }
    // equals and hashCode
}