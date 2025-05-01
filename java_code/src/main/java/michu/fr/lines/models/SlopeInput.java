package michu.fr.lines.models;

import java.util.Map;
import java.util.Objects;

public class SlopeInput {
    private final Double x1;
    private final Double y1;
    private final Double x2;
    private final Double y2;
    private final Double m; // Slope (can be angle in degrees or tangent value depending on context)

    public SlopeInput(Double x1, Double y1, Double x2, Double y2, Double m) {
        this.x1 = x1;
        this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;
        this.m = m;
    }

    // --- Getters ---
    public Double getX1() { return x1; }
    public Double getY1() { return y1; }
    public Double getX2() { return x2; }
    public Double getY2() { return y2; }
    public Double getM() { return m; }


    // Helper factory method to create from a Map if needed (similar to Python dict)
    public static SlopeInput fromMap(Map<String, Double> knownValues) {
        return new SlopeInput(
            knownValues.get("x1"),
            knownValues.get("y1"),
            knownValues.get("x2"),
            knownValues.get("y2"),
            knownValues.get("m")
        );
    }

     @Override
     public boolean equals(Object o) {
         if (this == o) return true;
         if (o == null || getClass() != o.getClass()) return false;
         SlopeInput that = (SlopeInput) o;
         return Objects.equals(x1, that.x1) &&
                Objects.equals(y1, that.y1) &&
                Objects.equals(x2, that.x2) &&
                Objects.equals(y2, that.y2) &&
                Objects.equals(m, that.m);
     }

     @Override
     public int hashCode() {
         return Objects.hash(x1, y1, x2, y2, m);
     }

     @Override
     public String toString() {
         return "SlopeInput{" +
                "x1=" + x1 +
                ", y1=" + y1 +
                ", x2=" + x2 +
                ", y2=" + y2 +
                ", m=" + m +
                '}';
     }
}
