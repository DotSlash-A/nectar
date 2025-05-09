#include <iostream>
#include <stdexcept>
#include "geometry/solid_geometry_utils.h"

int main() {
    std::cout << "--- Solid Geometry C++ Examples ---" << std::endl;

    using namespace michu_fr::geometry;

    try {
        // Cuboid
        std::cout << "\n-- Cuboid --" << std::endl;
        CuboidDimensions cuboid(5, 4, 3);
        std::cout << "   " << cuboidSurfaceAreas(cuboid).toString() << std::endl;
        std::cout << "   " << cuboidVolume(cuboid).toString() << std::endl;
        std::cout << "   " << cuboidDiagonal(cuboid).toString() << std::endl;

        // Cube
        std::cout << "\n-- Cube --" << std::endl;
        CubeDimensions cube(4);
        std::cout << "   " << cubeSurfaceAreas(cube).toString() << std::endl;
        std::cout << "   " << cubeVolume(cube).toString() << std::endl;
        std::cout << "   " << cubeDiagonal(cube).toString() << std::endl;

        // Cylinder
        std::cout << "\n-- Cylinder --" << std::endl;
        CylinderDimensions cylinder(3, 7);
        std::cout << "   " << cylinderSurfaceAreas(cylinder).toString() << std::endl;
        std::cout << "   " << cylinderVolume(cylinder).toString() << std::endl;

        // Cone
        std::cout << "\n-- Cone --" << std::endl;
        ConeDimensions cone(3, 4); // r=3, h=4 => slant=5
        std::cout << "   " << coneSurfaceAreas(cone).toString() << std::endl;
        std::cout << "   " << coneVolume(cone).toString() << std::endl;

        // Sphere
        std::cout << "\n-- Sphere --" << std::endl;
        SphereDimensions sphere(5);
        std::cout << "   " << sphereSurfaceArea(sphere).toString() << std::endl;
        std::cout << "   " << sphereVolume(sphere).toString() << std::endl;

        // Hemisphere
        std::cout << "\n-- Hemisphere --" << std::endl;
        HemisphereDimensions hemisphere(5);
        std::cout << "   " << hemisphereSurfaceAreas(hemisphere).toString() << std::endl;
        std::cout << "   " << hemisphereVolume(hemisphere).toString() << std::endl;

        // Frustum
        std::cout << "\n-- Frustum --" << std::endl;
        FrustumDimensions frustum(6, 5, 2); // h=6, R=5, r=2
        std::cout << "   " << frustumSurfaceAreas(frustum).toString() << std::endl;
        std::cout << "   " << frustumVolume(frustum).toString() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Geometry Error: " << e.what() << std::endl;
    }

    return 0;
}