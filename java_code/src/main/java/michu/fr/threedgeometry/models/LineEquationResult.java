package michu.fr.threedgeometry.models;

// import java.util.Objects;

public class LineEquationResult {
    private final String type; // e.g., "vector_form", "cartesian_symmetric_form"
    private final String equationStr;
    private final Point3D pointOnLine; // Optional, but useful
    private final Vector3D directionVector; // Optional, but useful

    public LineEquationResult(String type, String equationStr, Point3D pointOnLine, Vector3D directionVector) {
        this.type = type;
        this.equationStr = equationStr;
        this.pointOnLine = pointOnLine;
        this.directionVector = directionVector;
    }

    public String getType() { return type; }
    public String getEquationStr() { return equationStr; }
    public Point3D getPointOnLine() { return pointOnLine; }
    public Vector3D getDirectionVector() { return directionVector; }

    @Override
    public String toString() {
        return "LineEquationResult{" +
               "type='" + type + '\'' +
               ", equationStr='" + equationStr + '\'' +
               (pointOnLine != null ? ", pointOnLine=" + pointOnLine : "") +
               (directionVector != null ? ", directionVector=" + directionVector : "") +
               '}';
    }
    // equals and hashCode
}