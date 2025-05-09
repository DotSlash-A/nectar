package michu.fr.threedgeometry.models;

import java.util.List;
// import java.util.Objects;
import java.util.Collections;

public class CollinearityResult {
    private final boolean areCollinear;
    private final String reason;
    private final List<Point3D> points; // Or could be List<Object> if mixing points/vectors

    public CollinearityResult(boolean areCollinear, String reason, List<Point3D> points) {
        this.areCollinear = areCollinear;
        this.reason = reason;
        this.points = Collections.unmodifiableList(points);
    }

    public boolean areCollinear() { return areCollinear; }
    public String getReason() { return reason; }
    public List<Point3D> getPoints() { return points; }

    @Override
    public String toString() {
        return "CollinearityResult{" +
               "areCollinear=" + areCollinear +
               ", reason='" + reason + '\'' +
               ", points=" + points +
               '}';
    }
    // equals and hashCode
}