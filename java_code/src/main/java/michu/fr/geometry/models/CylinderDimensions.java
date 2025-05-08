// src/main/java/michu/fr/geometry/models/CylinderDimensions.java
package michu.fr.geometry.models;
public class CylinderDimensions {
    public final double radius;
    public final double height;
    public CylinderDimensions(double radius, double height) {
        if (radius <= 0 || height <= 0) throw new IllegalArgumentException("Radius and height must be positive.");
        this.radius = radius; this.height = height;
    }
     @Override public String toString() { return String.format("radius=%.2f, height=%.2f", radius, height); }
}
// ... and so on for ConeDimensions, SphereDimensions, HemisphereDimensions, FrustumDimensions ...

// ConeDimensions might include an optional slantHeight passed in, or it's always calculated.
// Let's assume it's calculated if not obvious from context.