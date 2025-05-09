package michu.fr.threedgeometry.models;

import java.util.Objects;

public class RelationshipLinePlaneResult {
    private final LineEquationResult lineDefinition;
    private final PlaneEquationResult planeDefinition;
    private final String relationship; // e.g., "line_parallel_to_plane", "line_lies_in_plane", "line_intersects_plane"
    private final Point3D intersectionPoint; // Nullable
    private final Double distanceIfParallel; // Nullable

    public RelationshipLinePlaneResult(LineEquationResult lineDefinition, PlaneEquationResult planeDefinition, String relationship, Point3D intersectionPoint, Double distanceIfParallel) {
        this.lineDefinition = lineDefinition;
        this.planeDefinition = planeDefinition;
        this.relationship = relationship;
        this.intersectionPoint = intersectionPoint;
        this.distanceIfParallel = distanceIfParallel;
    }

    public LineEquationResult getLineDefinition() { return lineDefinition; }
    public PlaneEquationResult getPlaneDefinition() { return planeDefinition; }
    public String getRelationship() { return relationship; }
    public Point3D getIntersectionPoint() { return intersectionPoint; }
    public Double getDistanceIfParallel() { return distanceIfParallel; }


    @Override
    public String toString() {
        return "RelationshipLinePlaneResult{" +
               "relationship='" + relationship + '\'' +
               (intersectionPoint != null ? ", intersectionPoint=" + intersectionPoint : "") +
               (distanceIfParallel != null ? ", distanceIfParallel=" + String.format("%.4f", distanceIfParallel) : "") +
               '}';
    }
    // equals and hashCode
}