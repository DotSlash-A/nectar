package michu.fr.matrix.models;
import java.util.List;
import java.util.Objects;
public class AdjInvResponse {
    private final List<List<Double>> inputMatrix;
    private final String dimensions;
    private final Double determinant; // Made Double to allow null representation easily
    private final boolean isInvertible;
    private final List<List<Double>> adjointMatrix; // Null if not applicable? No, always calculable.
    private final List<List<Double>> inverseMatrix; // Can be null
    public AdjInvResponse(List<List<Double>> inputMatrix, String dimensions, Double determinant, boolean isInvertible, List<List<Double>> adjointMatrix, List<List<Double>> inverseMatrix) {
        this.inputMatrix = Objects.requireNonNull(inputMatrix);
        this.dimensions = Objects.requireNonNull(dimensions);
        this.determinant = determinant; // Allow null if determinant wasn't calculated or needed
        this.isInvertible = isInvertible;
        this.adjointMatrix = Objects.requireNonNull(adjointMatrix);
        // Inverse matrix can be null if not invertible
        if (isInvertible && inverseMatrix == null) {
             throw new IllegalArgumentException("Inverse matrix cannot be null if matrix is invertible.");
        }
        this.inverseMatrix = inverseMatrix;
    }
    public List<List<Double>> getInputMatrix() { return inputMatrix; }
    public String getDimensions() { return dimensions; }
    public Double getDeterminant() { return determinant; }
    public boolean isInvertible() { return isInvertible; }
    public List<List<Double>> getAdjointMatrix() { return adjointMatrix; }
    public List<List<Double>> getInverseMatrix() { return inverseMatrix; } // Returns null if not invertible
     // Add equals, hashCode, toString if needed
}