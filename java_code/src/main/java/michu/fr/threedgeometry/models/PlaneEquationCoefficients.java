package michu.fr.threedgeometry.models;

import java.util.Objects;

// Represents Ax + By + Cz + D = 0 or Ax + By + Cz = D_rhs
public class PlaneEquationCoefficients {
    public final double a;
    public final double b;
    public final double c;
    public final Double dLhs; // For Ax + By + Cz + D_lhs = 0
    public final Double dRhs; // For Ax + By + Cz = D_rhs

    // Constructor for Ax + By + Cz + D_lhs = 0
    public PlaneEquationCoefficients(double a, double b, double c, double dLhs) {
        this.a = a;
        this.b = b;
        this.c = c;
        this.dLhs = dLhs;
        this.dRhs = null; // Or -dLhs if you want to always have it
    }

    // Constructor for Ax + By + Cz = D_rhs (specify which D is being given)
    public PlaneEquationCoefficients(double a, double b, double c, double dRhs, boolean isDRhs) {
        if (!isDRhs) throw new IllegalArgumentException("Use the other constructor for D_lhs or ensure isDRhs is true.");
        this.a = a;
        this.b = b;
        this.c = c;
        this.dRhs = dRhs;
        this.dLhs = null; // Or -dRhs
    }
    
    public double getDForAxByCzPlusDlhsEqualsZero() {
        if (dLhs != null) return dLhs;
        if (dRhs != null) return -dRhs;
        throw new IllegalStateException("D constant not properly initialized.");
    }

     public double getDForAxByCzEqualsDrhs() {
        if (dRhs != null) return dRhs;
        if (dLhs != null) return -dLhs;
        throw new IllegalStateException("D constant not properly initialized.");
    }


    @Override
    public String toString() {
        if (dLhs != null) {
            return String.format("%.2fx + %.2fy + %.2fz + %.2f = 0", a, b, c, dLhs);
        } else if (dRhs != null) {
            return String.format("%.2fx + %.2fy + %.2fz = %.2f", a, b, c, dRhs);
        }
        return "Invalid PlaneEquationCoefficients state";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        PlaneEquationCoefficients that = (PlaneEquationCoefficients) o;
        // Compare based on the Ax+By+Cz+D_lhs=0 form for consistency
        double thisDlhs = getDForAxByCzPlusDlhsEqualsZero();
        double thatDlhs = that.getDForAxByCzPlusDlhsEqualsZero();
        return Double.compare(that.a, a) == 0 &&
               Double.compare(that.b, b) == 0 &&
               Double.compare(that.c, c) == 0 &&
               Double.compare(thatDlhs, thisDlhs) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(a, b, c, getDForAxByCzPlusDlhsEqualsZero());
    }
}