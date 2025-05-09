package michu.fr.threedgeometry.models;

import java.util.Objects;

public class UnitVectorResult {
    private final Vector3D originalVector;
    private final Vector3D unitVector;
    private final double calculatedMagnitude; // Should be 1.0

    public UnitVectorResult(Vector3D originalVector, Vector3D unitVector) {
        this.originalVector = originalVector;
        this.unitVector = unitVector;
        this.calculatedMagnitude = unitVector.magnitude();
    }

    public Vector3D getOriginalVector() { return originalVector; }
    public Vector3D getUnitVector() { return unitVector; }
    public double getCalculatedMagnitude() { return calculatedMagnitude; }

    @Override
    public String toString() {
        return "UnitVectorResult{" +
               "originalVector=" + originalVector +
               ", unitVector=" + unitVector +
               ", calculatedMagnitude=" + String.format("%.4f", calculatedMagnitude) +
               '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        UnitVectorResult that = (UnitVectorResult) o;
        return Objects.equals(originalVector, that.originalVector) &&
               Objects.equals(unitVector, that.unitVector);
    }

    @Override
    public int hashCode() {
        return Objects.hash(originalVector, unitVector);
    }
}