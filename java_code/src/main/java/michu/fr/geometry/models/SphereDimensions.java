// src/main/java/michu/fr/geometry/models/SphereDimensions.java
package michu.fr.geometry.models;
public class SphereDimensions {
    public final double radius;
    public SphereDimensions(double radius) {
        if (radius <= 0) throw new IllegalArgumentException("Radius must be positive.");
        this.radius = radius;
    }
     @Override public String toString() { return String.format("radius=%.2f", radius); }
}
