// src/main/java/michu/fr/geometry/models/DiagonalResult.java
package michu.fr.geometry.models;
import java.util.Objects;
public class DiagonalResult {
    private final String shape;
    private final String dimensionsString;
    private final double diagonal;

    public DiagonalResult(String shape, String dimensionsString, double diagonal) {
        this.shape = Objects.requireNonNull(shape);
        this.dimensionsString = Objects.requireNonNull(dimensionsString);
        this.diagonal = diagonal;
    }
    public String getShape() { return shape; }
    public String getDimensionsString() { return dimensionsString; }
    public double getDiagonal() { return diagonal; }
    @Override
    public String toString() {
        return "DiagonalResult{shape='" + shape + '\'' +
               ", dimensions={" + dimensionsString + '}' +
               ", diagonal=" + String.format("%.4f",diagonal) +
               '}';
    }
}