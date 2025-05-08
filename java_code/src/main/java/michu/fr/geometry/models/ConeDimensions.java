// src/main/java/michu/fr/geometry/models/ConeDimensions.java
package michu.fr.geometry.models;
public class ConeDimensions {
    public final double radius;
    public final double height;
    public ConeDimensions(double radius, double height) {
        if (radius <= 0 || height <= 0) throw new IllegalArgumentException("Radius and height must be positive.");
        this.radius = radius; this.height = height;
    }
    @Override public String toString() { return String.format("radius=%.2f, height=%.2f", radius, height); }
}