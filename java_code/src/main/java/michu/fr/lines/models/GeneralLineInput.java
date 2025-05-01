package michu.fr.lines.models;

import java.util.Objects;

public class GeneralLineInput {
    private final double a;
    private final double b;
    private final double c;

    public GeneralLineInput(double a, double b, double c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }

    // --- Getters ---
    public double getA() { return a; }
    public double getB() { return b; }
    public double getC() { return c; }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        GeneralLineInput that = (GeneralLineInput) o;
        return Double.compare(that.a, a) == 0 &&
               Double.compare(that.b, b) == 0 &&
               Double.compare(that.c, c) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(a, b, c);
    }

    @Override
    public String toString() {
        return "GeneralLineInput{" +
               "a=" + a +
               ", b=" + b +
               ", c=" + c +
               '}';
    }
}