// src/main/java/michu/fr/geometry/models/FrustumDimensions.java
package michu.fr.geometry.models;
public class FrustumDimensions {
    public final double height;
    public final double radius1; // Larger radius R
    public final double radius2; // Smaller radius r
    public FrustumDimensions(double height, double radius1, double radius2) {
        if (height <= 0 || radius1 < 0 || radius2 < 0) throw new IllegalArgumentException("Height positive, radii non-negative.");
        if (radius1 < radius2) throw new IllegalArgumentException("radius1 should be greater than or equal to radius2 for convention (R >= r).");
        this.height = height; this.radius1 = radius1; this.radius2 = radius2;
    }
    @Override public String toString() { return String.format("height=%.2f, R=%.2f, r=%.2f", height, radius1, radius2); }
}