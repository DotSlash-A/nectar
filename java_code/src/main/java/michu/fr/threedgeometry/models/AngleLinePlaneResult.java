package michu.fr.threedgeometry.models;

// import java.util.Objects;

public class AngleLinePlaneResult {
    private final LineEquationResult line;
    private final PlaneEquationResult plane;
    private final double angleDegrees;
    private final double angleRadians;

    public AngleLinePlaneResult(LineEquationResult line, PlaneEquationResult plane, double angleRadians, double angleDegrees) {
        this.line = line;
        this.plane = plane;
        this.angleRadians = angleRadians;
        this.angleDegrees = angleDegrees;
    }
    
    public LineEquationResult getLine() { return line; }
    public PlaneEquationResult getPlane() { return plane; }
    public double getAngleDegrees() { return angleDegrees; }
    public double getAngleRadians() { return angleRadians; }

    @Override
    public String toString() {
        return "AngleLinePlaneResult{" +
               "angleDegrees=" + String.format("%.2f", angleDegrees) +
            //   ", lineDir=" + (line.getDirectionVector() != null ? line.getDirectionVector() : "N/A") +
            //   ", planeNormal=" + (plane.getNormalVector() != null ? plane.getNormalVector() : "N/A") +
               '}';
    }
    // equals and hashCode
}