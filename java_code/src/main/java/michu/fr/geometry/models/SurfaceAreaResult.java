// src/main/java/michu/fr/geometry/models/SurfaceAreaResult.java
package michu.fr.geometry.models;

// import java.util.Map;
import java.util.Objects;

public class SurfaceAreaResult {
    private final String shape;
    private final String dimensionsString; // String representation of dimensions
    private final Double lateralOrCurvedSurfaceArea; // LSA for cuboid/cube, CSA for cylinder/cone/hemisphere/frustum
    private final Double totalSurfaceArea;           // TSA for all except sphere
    private final Double surfaceArea;                // Specific for sphere
    private final Double calculatedSlantHeight;      // For cone/frustum if calculated

    // Constructor for shapes with LSA/CSA and TSA
    public SurfaceAreaResult(String shape, String dimensionsString, Double lateralOrCurvedSurfaceArea, Double totalSurfaceArea, Double calculatedSlantHeight) {
        this.shape = Objects.requireNonNull(shape);
        this.dimensionsString = Objects.requireNonNull(dimensionsString);
        this.lateralOrCurvedSurfaceArea = lateralOrCurvedSurfaceArea;
        this.totalSurfaceArea = totalSurfaceArea;
        this.surfaceArea = null; // Not for these shapes
        this.calculatedSlantHeight = calculatedSlantHeight;
    }

    // Constructor for Sphere
    public SurfaceAreaResult(String shape, String dimensionsString, Double surfaceArea) {
        this.shape = Objects.requireNonNull(shape);
        this.dimensionsString = Objects.requireNonNull(dimensionsString);
        this.surfaceArea = surfaceArea;
        this.lateralOrCurvedSurfaceArea = null;
        this.totalSurfaceArea = null;
        this.calculatedSlantHeight = null;
    }


    public String getShape() { return shape; }
    public String getDimensionsString() { return dimensionsString; }
    public Double getLateralOrCurvedSurfaceArea() { return lateralOrCurvedSurfaceArea; }
    public Double getTotalSurfaceArea() { return totalSurfaceArea; }
    public Double getSurfaceArea() { return surfaceArea; }
    public Double getCalculatedSlantHeight() { return calculatedSlantHeight; }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("SurfaceAreaResult{shape='").append(shape).append('\'');
        sb.append(", dimensions={").append(dimensionsString).append('}');
        if (lateralOrCurvedSurfaceArea != null) sb.append(", LSA/CSA=").append(String.format("%.4f",lateralOrCurvedSurfaceArea));
        if (totalSurfaceArea != null) sb.append(", TSA=").append(String.format("%.4f",totalSurfaceArea));
        if (surfaceArea != null) sb.append(", SA=").append(String.format("%.4f",surfaceArea));
        if (calculatedSlantHeight != null) sb.append(", SlantHeight(calc)=").append(String.format("%.4f",calculatedSlantHeight));
        sb.append('}');
        return sb.toString();
    }
}