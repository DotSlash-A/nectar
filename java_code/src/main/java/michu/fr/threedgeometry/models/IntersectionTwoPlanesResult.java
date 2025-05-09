package michu.fr.threedgeometry.models;

import java.util.Objects;

public class IntersectionTwoPlanesResult {
    private final PlaneEquationResult plane1;
    private final PlaneEquationResult plane2;
    private final boolean intersectsInLine; // True if not parallel, or if coincident
    private final LineEquationResult lineOfIntersection; // Nullable if parallel & distinct
    private final String message; // "parallel_distinct", "coincident", "intersects_in_line"

    public IntersectionTwoPlanesResult(PlaneEquationResult plane1, PlaneEquationResult plane2, boolean intersectsInLine, LineEquationResult lineOfIntersection, String message) {
        this.plane1 = plane1;
        this.plane2 = plane2;
        this.intersectsInLine = intersectsInLine;
        this.lineOfIntersection = lineOfIntersection;
        this.message = message;
    }
    
    public PlaneEquationResult getPlane1() { return plane1; }
    public PlaneEquationResult getPlane2() { return plane2; }
    public boolean isIntersectsInLine() { return intersectsInLine; }
    public LineEquationResult getLineOfIntersection() { return lineOfIntersection; }
    public String getMessage() { return message; }

    @Override
    public String toString() {
        return "IntersectionTwoPlanesResult{" +
               "intersectsInLine=" + intersectsInLine +
               (lineOfIntersection != null ? ", lineOfIntersection=" + lineOfIntersection.getEquationStr() : "") +
               ", message='" + message + '\'' +
               '}';
    }
    // equals and hashCode
}