// src/main/java/michu/fr/geometry/models/HemisphereDimensions.java
package michu.fr.geometry.models;
public class HemisphereDimensions { // Same as Sphere for input
    public final double radius;
    public HemisphereDimensions(double radius) {
        if (radius <= 0) throw new IllegalArgumentException("Radius must be positive.");
        this.radius = radius;
    }
     @Override public String toString() { return String.format("radius=%.2f", radius); }
}