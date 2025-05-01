package michu.fr.circles.models;

import java.util.Objects;

public class ParametricCircleResponse {
    private final String parametricX;
    private final String parametricY;
    private final double centerH;
    private final double centerK;
    private final double radius;

    public ParametricCircleResponse(String parametricX, String parametricY, double centerH, double centerK, double radius) {
        this.parametricX = parametricX;
        this.parametricY = parametricY;
        this.centerH = centerH;
        this.centerK = centerK;
        this.radius = radius;
    }

    // Getters
    public String getParametricX() { return parametricX; }
    public String getParametricY() { return parametricY; }
    public double getCenterH() { return centerH; }
    public double getCenterK() { return centerK; }
    public double getRadius() { return radius; }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        ParametricCircleResponse that = (ParametricCircleResponse) o;
        return Double.compare(that.centerH, centerH) == 0 && Double.compare(that.centerK, centerK) == 0 && Double.compare(that.radius, radius) == 0 && Objects.equals(parametricX, that.parametricX) && Objects.equals(parametricY, that.parametricY);
    }

    @Override
    public int hashCode() {
        return Objects.hash(parametricX, parametricY, centerH, centerK, radius);
    }

    @Override
    public String toString() {
        return "ParametricCircleResponse{" + "parametricX='" + parametricX + '\'' + ", parametricY='" + parametricY + '\'' + ", centerH=" + centerH + ", centerK=" + centerK + ", radius=" + radius + '}';
    }
}