package michu.fr.threedgeometry.models;

// import java.util.Objects;

public class DirectionRatios {
    public final double a;
    public final double b;
    public final double c;

    public DirectionRatios(double a, double b, double c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }

    @Override
    public String toString() {
        return String.format("<%.2f, %.2f, %.2f>", a, b, c);
    }
    // equals and hashCode
}