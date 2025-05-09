package michu.fr.threedgeometry.models;

// import java.util.Objects;

public class ShortestDistanceResult {
    private final LineEquationResult line1; // Or just their definitions
    private final LineEquationResult line2;
    private final double distance;
    private final String relationship; // e.g., "skew", "parallel", "intersecting"
    private final Point3D pointOnLine1; // Point where SD segment starts on line1 (optional)
    private final Point3D pointOnLine2; // Point where SD segment ends on line2 (optional)

    public ShortestDistanceResult(LineEquationResult line1, LineEquationResult line2, double distance, String relationship, Point3D pointOnLine1, Point3D pointOnLine2) {
        this.line1 = line1;
        this.line2 = line2;
        this.distance = distance;
        this.relationship = relationship;
        this.pointOnLine1 = pointOnLine1;
        this.pointOnLine2 = pointOnLine2;
    }
    
    public LineEquationResult getLine1() { return line1; }
    public LineEquationResult getLine2() { return line2; }
    public double getDistance() { return distance; }
    public String getRelationship() { return relationship; }
    public Point3D getPointOnLine1() { return pointOnLine1; }
    public Point3D getPointOnLine2() { return pointOnLine2; }


    @Override
    public String toString() {
        return "ShortestDistanceResult{" +
               "distance=" + String.format("%.4f", distance) +
               ", relationship='" + relationship + '\'' +
               (pointOnLine1 != null ? ", onLine1_at=" + pointOnLine1 : "") +
               (pointOnLine2 != null ? ", onLine2_at=" + pointOnLine2 : "") +
              // ", line1=" + line1.getEquationStr() + // Could be too verbose
              // ", line2=" + line2.getEquationStr() +
               '}';
    }
    // equals and hashCode
}