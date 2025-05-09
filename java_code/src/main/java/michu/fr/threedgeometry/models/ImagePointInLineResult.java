package michu.fr.threedgeometry.models;

import java.util.Objects;

public class ImagePointInLineResult {
    private final Point3D originalPoint;
    private final LineEquationResult lineDefinition;
    private final Point3D imagePoint;
    private final Point3D footOfPerpendicular;

    public ImagePointInLineResult(Point3D originalPoint, LineEquationResult lineDefinition, Point3D imagePoint, Point3D footOfPerpendicular) {
        this.originalPoint = originalPoint;
        this.lineDefinition = lineDefinition;
        this.imagePoint = imagePoint;
        this.footOfPerpendicular = footOfPerpendicular;
    }
    
    public Point3D getOriginalPoint() { return originalPoint; }
    public LineEquationResult getLineDefinition() { return lineDefinition; }
    public Point3D getImagePoint() { return imagePoint; }
    public Point3D getFootOfPerpendicular() { return footOfPerpendicular; }

    @Override
    public String toString() {
        return "ImagePointInLineResult{" +
               "originalPoint=" + originalPoint +
               ", imagePoint=" + imagePoint +
               ", footOfPerpendicular=" + footOfPerpendicular +
               ", inLine=" + lineDefinition.getEquationStr() +
               '}';
    }
    // equals and hashCode
}