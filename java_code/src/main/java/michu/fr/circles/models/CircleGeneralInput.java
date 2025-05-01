package michu.fr.circles.models;

import java.util.Objects;

// Corresponds to Python's circleGenral
public class CircleGeneralInput {
    // Using Double wrappers to allow null, matching Optional in Pydantic
    private final Double r; // Radius
    private final Double h; // Center x
    private final Double k; // Center y
    // x, y for a point on the circle aren't used in the circle_eqn function directly
    // private final Double x;
    // private final Double y;

    public CircleGeneralInput(Double h, Double k, Double r) {
        this.h = h;
        this.k = k;
        this.r = r;
    }

    // Getters
    public Double getR() { return r; }
    public Double getH() { return h; }
    public Double getK() { return k; }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        CircleGeneralInput that = (CircleGeneralInput) o;
        return Objects.equals(r, that.r) && Objects.equals(h, that.h) && Objects.equals(k, that.k);
    }

    @Override
    public int hashCode() {
        return Objects.hash(r, h, k);
    }

    @Override
    public String toString() {
        return "CircleGeneralInput{" + "r=" + r + ", h=" + h + ", k=" + k + '}';
    }
}