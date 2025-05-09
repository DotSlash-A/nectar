package michu.fr.threedgeometry.models;

// import java.util.Objects;

public class CoplanarityLinesResult {
    private final LineEquationResult line1Definition;
    private final LineEquationResult line2Definition;
    private final boolean areCoplanar;
    private final PlaneEquationResult planeContainingLines; // Nullable
    private final String reason; // e.g. "Lines are skew", "Lines are parallel and coplanar", "Lines intersect and are coplanar"

    public CoplanarityLinesResult(LineEquationResult line1Definition, LineEquationResult line2Definition, boolean areCoplanar, PlaneEquationResult planeContainingLines, String reason) {
        this.line1Definition = line1Definition;
        this.line2Definition = line2Definition;
        this.areCoplanar = areCoplanar;
        this.planeContainingLines = planeContainingLines;
        this.reason = reason;
    }
    
    public LineEquationResult getLine1Definition() { return line1Definition; }
    public LineEquationResult getLine2Definition() { return line2Definition; }
    public boolean areCoplanar() { return areCoplanar; }
    public PlaneEquationResult getPlaneContainingLines() { return planeContainingLines; }
    public String getReason() { return reason; }

    @Override
    public String toString() {
        return "CoplanarityLinesResult{" +
               "areCoplanar=" + areCoplanar +
               ", reason='" + reason + '\'' +
               (planeContainingLines != null ? ", planeEq=" + planeContainingLines.getEquationStr() : "") +
               '}';
    }
    // equals and hashCode
}