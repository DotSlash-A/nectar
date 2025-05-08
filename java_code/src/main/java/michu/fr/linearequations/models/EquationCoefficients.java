package michu.fr.linearequations.models;

import java.util.Objects;

public class EquationCoefficients {
    public final double a1, b1, c1; // For eq1: a1x + b1y = c1
    public final double a2, b2, c2; // For eq2: a2x + b2y = c2

    public EquationCoefficients(double a1, double b1, double c1, double a2, double b2, double c2) {
        this.a1 = a1; this.b1 = b1; this.c1 = c1;
        this.a2 = a2; this.b2 = b2; this.c2 = c2;
    }

    public String eq1ToString() {
        return String.format("%.2fx + %.2fy = %.2f", a1, b1, c1);
    }

    public String eq2ToString() {
        return String.format("%.2fx + %.2fy = %.2f", a2, b2, c2);
    }

    @Override
    public String toString() {
        return "Equations: [" + eq1ToString() + "; " + eq2ToString() + "]";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        EquationCoefficients that = (EquationCoefficients) o;
        return Double.compare(that.a1, a1) == 0 && Double.compare(that.b1, b1) == 0 && Double.compare(that.c1, c1) == 0 &&
               Double.compare(that.a2, a2) == 0 && Double.compare(that.b2, b2) == 0 && Double.compare(that.c2, c2) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(a1, b1, c1, a2, b2, c2);
    }
}