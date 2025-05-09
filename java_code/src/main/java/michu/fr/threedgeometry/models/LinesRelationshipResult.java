package michu.fr.threedgeometry.models;

import java.util.Objects;

public class LinesRelationshipResult {
    private final LineEquationResult line1Definition; // Or more abstract definition
    private final LineEquationResult line2Definition;
    private final String relationship; // "parallel_distinct", "collinear", "intersecting", "skew"
    private final Point3D intersectionPoint; // Nullable
    private final Double shortestDistance; // Nullable, mainly for skew/parallel

    public LinesRelationshipResult(LineEquationResult line1Definition, LineEquationResult line2Definition, String relationship, Point3D intersectionPoint, Double shortestDistance) {
        this.line1Definition = line1Definition;
        this.line2Definition = line2Definition;
        this.relationship = relationship;
        this.intersectionPoint = intersectionPoint;
        this.shortestDistance = shortestDistance;
    }
    
    public LineEquationResult getLine1Definition() { return line1Definition; }
    public LineEquationResult getLine2Definition() { return line2Definition; }
    public String getRelationship() { return relationship; }
    public Point3D getIntersectionPoint() { return intersectionPoint; }
    public Double getShortestDistance() { return shortestDistance; }

    @Override
    public String toString() {
        return "LinesRelationshipResult{" +
               "relationship='" + relationship + '\'' +
               (intersectionPoint != null ? ", intersectionPoint=" + intersectionPoint : "") +
               (shortestDistance != null ? ", shortestDistance=" + String.format("%.4f", shortestDistance) : "") +
              // ", line1=" + line1Definition.getEquationStr() +
              // ", line2=" + line2Definition.getEquationStr() +
               '}';
    }
    // equals and hashCode
}