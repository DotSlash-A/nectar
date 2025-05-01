package michu.fr.lines.models;

import java.util.Objects;

public class LineEquationResult {
    private final Double slope;
    private final Double yIntercept;
    private final Double xIntercept; // Added for completeness if needed
    private final String equation;

    // Full constructor
    public LineEquationResult(Double slope, Double yIntercept, Double xIntercept, String equation) {
        this.slope = slope;
        this.yIntercept = yIntercept;
        this.xIntercept = xIntercept;
        this.equation = equation; // Could add null check if required
    }

    // Constructor for simple slope-intercept results
    public LineEquationResult(Double slope, Double yIntercept, String equation) {
        this(slope, yIntercept, null, equation);
    }

    // --- Getters ---
    public Double getSlope() {
        return slope;
    }

    public Double getYIntercept() {
        return yIntercept;
    }

    public Double getXIntercept() {
        return xIntercept;
    }

    public String getEquation() {
        return equation;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        LineEquationResult that = (LineEquationResult) o;
        return Objects.equals(slope, that.slope) &&
               Objects.equals(yIntercept, that.yIntercept) &&
               Objects.equals(xIntercept, that.xIntercept) &&
               Objects.equals(equation, that.equation);
    }

    @Override
    public int hashCode() {
        return Objects.hash(slope, yIntercept, xIntercept, equation);
    }

    @Override
    public String toString() {
        return "LineEquationResult{" +
               "slope=" + slope +
               ", yIntercept=" + yIntercept +
               ", xIntercept=" + xIntercept +
               ", equation='" + equation + '\'' +
               '}';
    }
}
