package michu.fr.threedgeometry.models;

// import java.util.Objects;

public class DistancePointPlaneResult {
    private final Point3D point;
    private final PlaneEquationResult planeDefinition;
    private final double distance;
    private final Point3D footOfPerpendicular; // Nullable

    public DistancePointPlaneResult(Point3D point, PlaneEquationResult planeDefinition, double distance, Point3D footOfPerpendicular) {
        this.point = point;
        this.planeDefinition = planeDefinition;
        this.distance = distance;
        this.footOfPerpendicular = footOfPerpendicular;
    }
    
    public Point3D getPoint() { return point; }
    public PlaneEquationResult getPlaneDefinition() { return planeDefinition; }
    public double getDistance() { return distance; }
    public Point3D getFootOfPerpendicular() { return footOfPerpendicular; }

    @Override
    public String toString() {
        return "DistancePointPlaneResult{" +
               "point=" + point +
               ", plane=" + planeDefinition.getEquationStr() +
               ", distance=" + String.format("%.4f", distance) +
               (footOfPerpendicular != null ? ", footOfPerpendicular=" + footOfPerpendicular : "") +
               '}';
    }
    // equals and hashCode
}