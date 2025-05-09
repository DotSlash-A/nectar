package michu.fr.threedgeometry.models;

// import java.util.Objects;

public class DirectionCosines {
    public final double l;
    public final double m;
    public final double n;
    public final boolean isValidSet;

    public DirectionCosines(double l, double m, double n) {
        this.l = l;
        this.m = m;
        this.n = n;
        double sumSq = l*l + m*m + n*n;
        this.isValidSet = Math.abs(sumSq - 1.0) < 1e-9; // Check if l^2+m^2+n^2 = 1
    }
    
    public DirectionCosines(double l, double m, double n, boolean isValid) {
        this.l = l;
        this.m = m;
        this.n = n;
        this.isValidSet = isValid;
    }


    @Override
    public String toString() {
        return String.format("l=%.4f, m=%.4f, n=%.4f (Valid: %b)", l, m, n, isValidSet);
    }
    // equals and hashCode
}