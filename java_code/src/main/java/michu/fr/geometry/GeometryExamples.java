// src/main/java/michu/fr/geometry/GeometryExamples.java
package michu.fr.geometry;

import michu.fr.geometry.models.*; // Import all models

public class GeometryExamples {
    public static void main(String[] args) {
        System.out.println("--- Solid Geometry Examples ---");

        // Cuboid
        CuboidDimensions cuboid = new CuboidDimensions(5, 4, 3);
        System.out.println("Cuboid SA: " + SolidGeometryUtils.cuboidSurfaceAreas(cuboid));
        System.out.println("Cuboid Volume: " + SolidGeometryUtils.cuboidVolume(cuboid));
        System.out.println("Cuboid Diagonal: " + SolidGeometryUtils.cuboidDiagonal(cuboid));

        // Cube
        CubeDimensions cube = new CubeDimensions(4);
        System.out.println("\nCube SA: " + SolidGeometryUtils.cubeSurfaceAreas(cube));
        System.out.println("Cube Volume: " + SolidGeometryUtils.cubeVolume(cube));
        System.out.println("Cube Diagonal: " + SolidGeometryUtils.cubeDiagonal(cube));

        // Cylinder
        CylinderDimensions cylinder = new CylinderDimensions(3, 7);
        System.out.println("\nCylinder SA: " + SolidGeometryUtils.cylinderSurfaceAreas(cylinder));
        System.out.println("Cylinder Volume: " + SolidGeometryUtils.cylinderVolume(cylinder));

        // Cone
        ConeDimensions cone = new ConeDimensions(3, 4); // radius 3, height 4 => slant height 5
        System.out.println("\nCone SA: " + SolidGeometryUtils.coneSurfaceAreas(cone));
        System.out.println("Cone Volume: " + SolidGeometryUtils.coneVolume(cone));

        // Sphere
        SphereDimensions sphere = new SphereDimensions(5);
        System.out.println("\nSphere SA: " + SolidGeometryUtils.sphereSurfaceArea(sphere));
        System.out.println("Sphere Volume: " + SolidGeometryUtils.sphereVolume(sphere));

        // Hemisphere
        HemisphereDimensions hemisphere = new HemisphereDimensions(5);
        System.out.println("\nHemisphere SA: " + SolidGeometryUtils.hemisphereSurfaceAreas(hemisphere));
        System.out.println("Hemisphere Volume: " + SolidGeometryUtils.hemisphereVolume(hemisphere));

        // Frustum
        try {
             FrustumDimensions frustum = new FrustumDimensions(6, 5, 2); // h, R, r
             System.out.println("\nFrustum SA: " + SolidGeometryUtils.frustumSurfaceAreas(frustum));
             System.out.println("Frustum Volume: " + SolidGeometryUtils.frustumVolume(frustum));
        } catch (IllegalArgumentException e) {
            System.err.println("Error creating frustum: " + e.getMessage());
        }
    }
}