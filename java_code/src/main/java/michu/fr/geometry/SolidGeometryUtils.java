// src/main/java/michu/fr/geometry/SolidGeometryUtils.java
package michu.fr.geometry;

import michu.fr.geometry.models.*; // Import all your dimension and result models

public final class SolidGeometryUtils {

    private SolidGeometryUtils() {
         throw new UnsupportedOperationException("This is a utility class and cannot be instantiated");
    }

    // --- Cuboid ---
    public static SurfaceAreaResult cuboidSurfaceAreas(CuboidDimensions dims) {
        double lsa = 2 * (dims.length + dims.breadth) * dims.height;
        double tsa = 2 * ((dims.length * dims.breadth) + (dims.breadth * dims.height) + (dims.height * dims.length));
        return new SurfaceAreaResult("Cuboid", dims.toString(), lsa, tsa, null);
    }

    public static VolumeResult cuboidVolume(CuboidDimensions dims) {
        double volume = dims.length * dims.breadth * dims.height;
        return new VolumeResult("Cuboid", dims.toString(), volume);
    }

    public static DiagonalResult cuboidDiagonal(CuboidDimensions dims) {
        double diagonal = Math.sqrt(dims.length*dims.length + dims.breadth*dims.breadth + dims.height*dims.height);
        return new DiagonalResult("Cuboid", dims.toString(), diagonal);
    }

    // --- Cube ---
    public static SurfaceAreaResult cubeSurfaceAreas(CubeDimensions dims) {
        double lsa = 4 * dims.side * dims.side;
        double tsa = 6 * dims.side * dims.side;
        return new SurfaceAreaResult("Cube", dims.toString(), lsa, tsa, null);
    }

    public static VolumeResult cubeVolume(CubeDimensions dims) {
        return new VolumeResult("Cube", dims.toString(), Math.pow(dims.side, 3));
    }

    public static DiagonalResult cubeDiagonal(CubeDimensions dims) {
        return new DiagonalResult("Cube", dims.toString(), dims.side * Math.sqrt(3));
    }

    // --- Right Circular Cylinder ---
    public static SurfaceAreaResult cylinderSurfaceAreas(CylinderDimensions dims) {
        double csa = 2 * Math.PI * dims.radius * dims.height;
        double tsa = 2 * Math.PI * dims.radius * (dims.height + dims.radius);
        return new SurfaceAreaResult("Cylinder", dims.toString(), csa, tsa, null);
    }

    public static VolumeResult cylinderVolume(CylinderDimensions dims) {
        return new VolumeResult("Cylinder", dims.toString(), Math.PI * dims.radius * dims.radius * dims.height);
    }

    // --- Right Circular Cone ---
    private static double coneSlantHeight(double radius, double height) {
        return Math.sqrt(radius*radius + height*height);
    }

    public static SurfaceAreaResult coneSurfaceAreas(ConeDimensions dims) {
        double slantHeight = coneSlantHeight(dims.radius, dims.height);
        double csa = Math.PI * dims.radius * slantHeight;
        double tsa = Math.PI * dims.radius * (slantHeight + dims.radius);
        return new SurfaceAreaResult("Cone", dims.toString(), csa, tsa, slantHeight);
    }

    public static VolumeResult coneVolume(ConeDimensions dims) {
        return new VolumeResult("Cone", dims.toString(), (1.0/3.0) * Math.PI * dims.radius * dims.radius * dims.height);
    }

    // --- Sphere ---
    public static SurfaceAreaResult sphereSurfaceArea(SphereDimensions dims) {
        double sa = 4 * Math.PI * dims.radius * dims.radius;
        return new SurfaceAreaResult("Sphere", dims.toString(), sa);
    }

    public static VolumeResult sphereVolume(SphereDimensions dims) {
        return new VolumeResult("Sphere", dims.toString(), (4.0/3.0) * Math.PI * Math.pow(dims.radius, 3));
    }

    // --- Hemisphere ---
    public static SurfaceAreaResult hemisphereSurfaceAreas(HemisphereDimensions dims) {
        double csa = 2 * Math.PI * dims.radius * dims.radius;
        double tsa = 3 * Math.PI * dims.radius * dims.radius;
        return new SurfaceAreaResult("Hemisphere", dims.toString(), csa, tsa, null);
    }

    public static VolumeResult hemisphereVolume(HemisphereDimensions dims) {
        return new VolumeResult("Hemisphere", dims.toString(), (2.0/3.0) * Math.PI * Math.pow(dims.radius, 3));
    }

    // --- Frustum of a Cone ---
    private static double frustumSlantHeight(double height, double R, double r) {
         return Math.sqrt(height*height + Math.pow(R - r, 2));
    }
    public static SurfaceAreaResult frustumSurfaceAreas(FrustumDimensions dims) {
        // R = radius1, r = radius2 (assuming convention R >= r from FrustumDimensions constructor)
        double R = dims.radius1;
        double r = dims.radius2;
        double h = dims.height;
        double slantHeight = frustumSlantHeight(h, R, r);

        double csa = Math.PI * slantHeight * (R + r);
        double tsa = csa + (Math.PI * R * R) + (Math.PI * r * r);
        return new SurfaceAreaResult("Frustum", dims.toString(), csa, tsa, slantHeight);
    }

    public static VolumeResult frustumVolume(FrustumDimensions dims) {
        double R = dims.radius1;
        double r = dims.radius2;
        double h = dims.height;
        double volume = (1.0/3.0) * Math.PI * h * (R*R + r*r + R*r);
        return new VolumeResult("Frustum", dims.toString(), volume);
    }
}