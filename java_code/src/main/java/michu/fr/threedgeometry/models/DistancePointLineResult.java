package michu.fr.threedgeometry.models;

// import java.util.Objects;

public class DistancePointLineResult {
    private final Point3D point;
    private final LineEquationResult lineDefinition;
    private final double distance;
    private final Point3D footOfPerpendicular; // Nullable

    public DistancePointLineResult(Point3D point, LineEquationResult lineDefinition, double distance, Point3D footOfPerpendicular) {
        this.point = point;
        this.lineDefinition = lineDefinition;
        this.distance = distance;
        this.footOfPerpendicular = footOfPerpendicular;
    }
    
    public Point3D getPoint() { return point; }
    public LineEquationResult getLineDefinition() { return lineDefinition; }
    public double getDistance() { return distance; }
    public Point3D getFootOfPerpendicular() { return footOfPerpendicular; }

    @Override
    public String toString() {
        return "DistancePointLineResult{" +
               "point=" + point +
               ", line=" + lineDefinition.getEquationStr() +
               ", distance=" + String.format("%.4f", distance) +
               (footOfPerpendicular != null ? ", footOfPerpendicular=" + footOfPerpendicular : "") +
               '}';
    }
    // equals and hashCode
}