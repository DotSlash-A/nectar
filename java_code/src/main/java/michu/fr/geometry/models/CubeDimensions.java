// ... Create similar specific dimension classes for other shapes ...
// Example: CubeDimensions(double side), CylinderDimensions(double radius, double height) etc.
// Or a more generic `Map<String, Double>` for dimensions in results.
// For now, let's assume individual dimension classes for type safety in utility methods.

 // src/main/java/michu/fr/geometry/models/CubeDimensions.java
 package michu.fr.geometry.models;
 public class CubeDimensions {
     public final double side;
     public CubeDimensions(double side) {
         if (side <= 0) throw new IllegalArgumentException("Side must be positive.");
         this.side = side;
     }
      @Override public String toString() { return String.format("side=%.2f", side); }
 }