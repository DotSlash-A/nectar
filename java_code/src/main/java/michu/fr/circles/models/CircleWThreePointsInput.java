package michu.fr.circles.models;

import michu.fr.lines.models.Coordinates; // Reuse Coordinates model
import java.util.Objects;

// Corresponds to Python's circleWThreePointsInput
public class CircleWThreePointsInput {
    private final Coordinates p;
    private final Coordinates q;
    private final Coordinates r;

    public CircleWThreePointsInput(Coordinates p, Coordinates q, Coordinates r) {
        this.p = Objects.requireNonNull(p, "Point p cannot be null");
        this.q = Objects.requireNonNull(q, "Point q cannot be null");
        this.r = Objects.requireNonNull(r, "Point r cannot be null");
    }

    // Getters
    public Coordinates getP() { return p; }
    public Coordinates getQ() { return q; }
    public Coordinates getR() { return r; }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        CircleWThreePointsInput that = (CircleWThreePointsInput) o;
        return Objects.equals(p, that.p) && Objects.equals(q, that.q) && Objects.equals(r, that.r);
    }

    @Override
    public int hashCode() {
        return Objects.hash(p, q, r);
    }

    @Override
    public String toString() {
        return "CircleWThreePointsInput{" + "p=" + p + ", q=" + q + ", r=" + r + '}';
    }
}