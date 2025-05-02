package michu.fr.matrix.models;
import java.util.Objects;
public class MatrixEqualityResponse {
    private final boolean areEqual;
    private final String reason;
    private final String dimensionsA; // Can be "Invalid"
    private final String dimensionsB; // Can be "Invalid"
    public MatrixEqualityResponse(boolean areEqual, String reason, String dimensionsA, String dimensionsB) {
        this.areEqual = areEqual;
        this.reason = Objects.requireNonNull(reason);
        this.dimensionsA = Objects.requireNonNull(dimensionsA);
        this.dimensionsB = Objects.requireNonNull(dimensionsB);
    }
    public boolean areEqual() { return areEqual; } // Getter for boolean often uses "is" or plain name
    public String getReason() { return reason; }
    public String getDimensionsA() { return dimensionsA; }
    public String getDimensionsB() { return dimensionsB; }
    // Add equals, hashCode, toString if needed
}