package michu.fr.threedgeometry.models;

import java.util.Objects;

public class Vector3D {
    public final double x;
    public final double y;
    public final double z;

    public Vector3D(double x, double y, double z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public double getX() { return x; }
    public double getY() { return y; }
    public double getZ() { return z; }

    public double magnitude() {
        return Math.sqrt(x * x + y * y + z * z);
    }

    public Vector3D normalize() {
        double mag = magnitude();
        if (Math.abs(mag) < 1e-9) { // EPSILON check
            throw new ArithmeticException("Cannot normalize a zero vector.");
        }
        return new Vector3D(x / mag, y / mag, z / mag);
    }

    public Vector3D add(Vector3D other) {
        return new Vector3D(this.x + other.x, this.y + other.y, this.z + other.z);
    }

    public Vector3D subtract(Vector3D other) {
        return new Vector3D(this.x - other.x, this.y - other.y, this.z - other.z);
    }

    public Vector3D scalarMultiply(double scalar) {
        return new Vector3D(this.x * scalar, this.y * scalar, this.z * scalar);
    }

    public double dot(Vector3D other) {
        return this.x * other.x + this.y * other.y + this.z * other.z;
    }

    public Vector3D cross(Vector3D other) {
        double cx = this.y * other.z - this.z * other.y;
        double cy = this.z * other.x - this.x * other.z;
        double cz = this.x * other.y - this.y * other.x;
        return new Vector3D(cx, cy, cz);
    }

    // Method to convert this vector to a point (assuming vector starts at origin)
    public Point3D toPoint3D() {
        return new Point3D(x, y, z);
    }
    
    public boolean isZeroVector(double epsilon) {
        return Math.abs(x) < epsilon && Math.abs(y) < epsilon && Math.abs(z) < epsilon;
    }


    @Override
    public String toString() {
        return String.format("%.2fi + %.2fj + %.2fk", x, y, z);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Vector3D vector3D = (Vector3D) o;
        // Use a small epsilon for floating point comparison
        double epsilon = 1e-9;
        return Math.abs(vector3D.x - x) < epsilon &&
               Math.abs(vector3D.y - y) < epsilon &&
               Math.abs(vector3D.z - z) < epsilon;
    }

    @Override
    public int hashCode() {
        // Hashcode for doubles is tricky due to precision.
        // Standard Objects.hash is okay for exact values but might differ for "equal" doubles.
        return Objects.hash(x, y, z);
    }
}