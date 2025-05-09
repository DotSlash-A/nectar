package michu.fr.threedgeometry.models;

import java.util.Collections;
import java.util.Map;
// import java.util.Objects;

public class AreaTriangleResult {
    private final double area;
    private final Map<String, String> context; // e.g., vertices or vectors used

    public AreaTriangleResult(double area, Map<String, String> context) {
        this.area = area;
        this.context = (context != null) ? Collections.unmodifiableMap(context) : Collections.emptyMap();
    }

    public double getArea() { return area; }
    public Map<String, String> getContext() { return context; }

    @Override
    public String toString() {
        return "AreaTriangleResult{" +
               "area=" + String.format("%.4f", area) +
               ", context=" + context +
               '}';
    }
    // equals and hashCode
}