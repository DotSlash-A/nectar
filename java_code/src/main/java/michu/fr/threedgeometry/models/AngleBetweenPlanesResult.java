package michu.fr.threedgeometry.models;

// import java.util.Objects;

public class AngleBetweenPlanesResult {
    private final PlaneEquationResult plane1; // Or just their normals
    private final PlaneEquationResult plane2;
    private final double angleDegrees;
    private final double angleRadians;

    public AngleBetweenPlanesResult(PlaneEquationResult plane1, PlaneEquationResult plane2, double angleRadians, double angleDegrees) {
        this.plane1 = plane1;
        this.plane2 = plane2;
        this.angleRadians = angleRadians;
        this.angleDegrees = angleDegrees;
    }
    
    public PlaneEquationResult getPlane1() { return plane1; }
    public PlaneEquationResult getPlane2() { return plane2; }
    public double getAngleDegrees() { return angleDegrees; }
    public double getAngleRadians() { return angleRadians; }

    @Override
    public String toString() {
        return "AngleBetweenPlanesResult{" +
               "angleDegrees=" + String.format("%.2f", angleDegrees) +
            //   ", plane1Normal=" + (plane1.getNormalVector() != null ? plane1.getNormalVector() : "N/A") +
            //   ", plane2Normal=" + (plane2.getNormalVector() != null ? plane2.getNormalVector() : "N/A") +
               '}';
    }
    // equals and hashCode
}