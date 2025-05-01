package michu.fr.circles.models;

import java.util.Objects;

// Corresponds to Python's CircleEqnResponse
public class CircleEqnResponse {
    private final String standardForm;
    private final String generalForm;
    private final double centerH;
    private final double centerK;
    private final double radius;
    private final double coeffA; // Coeff of x^2 in general form
    private final double coeffB; // Coeff of y^2
    private final double coeffC; // Coeff of x
    private final double coeffD; // Coeff of y
    private final double coeffE; // Constant term

    public CircleEqnResponse(String standardForm, String generalForm, double centerH, double centerK, double radius, double coeffA, double coeffB, double coeffC, double coeffD, double coeffE) {
        this.standardForm = standardForm;
        this.generalForm = generalForm;
        this.centerH = centerH;
        this.centerK = centerK;
        this.radius = radius;
        this.coeffA = coeffA;
        this.coeffB = coeffB;
        this.coeffC = coeffC;
        this.coeffD = coeffD;
        this.coeffE = coeffE;
    }

    // Getters
    public String getStandardForm() { return standardForm; }
    public String getGeneralForm() { return generalForm; }
    public double getCenterH() { return centerH; }
    public double getCenterK() { return centerK; }
    public double getRadius() { return radius; }
    public double getCoeffA() { return coeffA; }
    public double getCoeffB() { return coeffB; }
    public double getCoeffC() { return coeffC; }
    public double getCoeffD() { return coeffD; }
    public double getCoeffE() { return coeffE; }

     @Override
     public boolean equals(Object o) {
         if (this == o) return true;
         if (o == null || getClass() != o.getClass()) return false;
         CircleEqnResponse that = (CircleEqnResponse) o;
         return Double.compare(that.centerH, centerH) == 0 && Double.compare(that.centerK, centerK) == 0 && Double.compare(that.radius, radius) == 0 && Double.compare(that.coeffA, coeffA) == 0 && Double.compare(that.coeffB, coeffB) == 0 && Double.compare(that.coeffC, coeffC) == 0 && Double.compare(that.coeffD, coeffD) == 0 && Double.compare(that.coeffE, coeffE) == 0 && Objects.equals(standardForm, that.standardForm) && Objects.equals(generalForm, that.generalForm);
     }

     @Override
     public int hashCode() {
         return Objects.hash(standardForm, generalForm, centerH, centerK, radius, coeffA, coeffB, coeffC, coeffD, coeffE);
     }

    @Override
    public String toString() {
        return "CircleEqnResponse{" + "standardForm='" + standardForm + '\'' + ", generalForm='" + generalForm + '\'' + ", centerH=" + centerH + ", centerK=" + centerK + ", radius=" + radius + ", A=" + coeffA + ", B=" + coeffB + ", C=" + coeffC + ", D=" + coeffD + ", E=" + coeffE + '}';
    }
}
