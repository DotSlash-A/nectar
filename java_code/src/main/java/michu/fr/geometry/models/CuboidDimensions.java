// src/main/java/michu/fr/geometry/models/CuboidDimensions.java
package michu.fr.geometry.models;

// import java.util.Objects;

public class CuboidDimensions {
    public final double length;
    public final double breadth;
    public final double height;

    public CuboidDimensions(double length, double breadth, double height) {
        if (length <= 0 || breadth <= 0 || height <= 0) {
            throw new IllegalArgumentException("Dimensions must be positive.");
        }
        this.length = length;
        this.breadth = breadth;
        this.height = height;
    }
    // Getters can be added if needed, or keep fields public final for simple DTOs
     @Override
     public String toString() {
         return String.format("length=%.2f, breadth=%.2f, height=%.2f", length, breadth, height);
     }
}