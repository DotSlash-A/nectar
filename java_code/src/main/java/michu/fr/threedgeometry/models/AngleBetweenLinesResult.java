package michu.fr.threedgeometry.models;

// import java.util.Objects;

public class AngleBetweenLinesResult {
    private final Vector3D direction1;
    private final Vector3D direction2;
    private final double angleDegrees;
    private final double angleRadians;

    public AngleBetweenLinesResult(Vector3D direction1, Vector3D direction2, double angleRadians, double angleDegrees) {
        this.direction1 = direction1;
        this.direction2 = direction2;
        this.angleRadians = angleRadians;
        this.angleDegrees = angleDegrees;
    }
    
    public Vector3D getDirection1() { return direction1; }
    public Vector3D getDirection2() { return direction2; }
    public double getAngleDegrees() { return angleDegrees; }
    public double getAngleRadians() { return angleRadians; }

    @Override
    public String toString() {
        return "AngleBetweenLinesResult{" +
               "direction1=" + direction1 +
               ", direction2=" + direction2 +
               ", angleDegrees=" + String.format("%.2f", angleDegrees) +
               ", angleRadians=" + String.format("%.4f", angleRadians) +
               '}';
    }
    // equals and hashCode
}