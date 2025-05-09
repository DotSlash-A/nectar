package michu.fr.threedgeometry.models;

import java.util.Objects;

public class IntersectionLinePlaneResult {
    private final LineEquationResult line;
    private final PlaneEquationResult plane;
    private final boolean intersects;
    private final Point3D intersectionPoint; // Nullable if parallel or line in plane
    private final String message;

    public IntersectionLinePlaneResult(LineEquationResult line, PlaneEquationResult plane, boolean intersects, Point3D intersectionPoint, String message) {
        this.line = line;
        this.plane = plane;
        this.intersects = intersects;
        this.intersectionPoint = intersectionPoint;
        this.message = message;
    }
    
    public LineEquationResult getLine() { return line; }
    public PlaneEquationResult getPlane() { return plane; }
    public boolean isIntersects() { return intersects; }
    public Point3D getIntersectionPoint() { return intersectionPoint; }
    public String getMessage() { return message; }

    @Override
    public String toString() {
        return "IntersectionLinePlaneResult{" +
               "intersects=" + intersects +
               (intersectionPoint != null ? ", intersectionPoint=" + intersectionPoint : "") +
               ", message='" + message + '\'' +
               '}';
    }
    // equals and hashCode
}