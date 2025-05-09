package michu.fr.threedgeometry.models;

import java.util.Map; // For coefficients A,B,C,D
// import java.util.Objects;

public class PlaneEquationResult {
    private final String type; // e.g., "vector_normal_form", "cartesian_form"
    private final String equationStr;
    private final Vector3D normalVector; // Optional
    private final Double distanceFromOrigin; // Optional, for normal form
    private final Map<String, Double> cartesianCoefficients; // For Ax+By+Cz+D=0, stores A,B,C,D

    public PlaneEquationResult(String type, String equationStr, Vector3D normalVector, Double distanceFromOrigin, Map<String, Double> cartesianCoefficients) {
        this.type = type;
        this.equationStr = equationStr;
        this.normalVector = normalVector;
        this.distanceFromOrigin = distanceFromOrigin;
        this.cartesianCoefficients = cartesianCoefficients; // Should be made unmodifiable if passed in
    }
    
    public String getType() { return type; }
    public String getEquationStr() { return equationStr; }
    public Vector3D getNormalVector() { return normalVector; }
    public Double getDistanceFromOrigin() { return distanceFromOrigin; }
    public Map<String, Double> getCartesianCoefficients() { return cartesianCoefficients; }


    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("PlaneEquationResult{type='").append(type).append('\'');
        sb.append(", equationStr='").append(equationStr).append('\'');
        if (normalVector != null) sb.append(", normalVector=").append(normalVector);
        if (distanceFromOrigin != null) sb.append(", distanceFromOrigin=").append(String.format("%.4f", distanceFromOrigin));
        if (cartesianCoefficients != null) sb.append(", coeffs(Ax+By+Cz+D=0)=").append(cartesianCoefficients);
        sb.append('}');
        return sb.toString();
    }
    // equals and hashCode
}