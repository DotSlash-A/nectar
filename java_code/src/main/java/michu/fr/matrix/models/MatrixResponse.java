package michu.fr.matrix.models;
import java.util.List;
import java.util.Objects;
public class MatrixResponse {
    private final List<List<Double>> resultMatrix;
    public MatrixResponse(List<List<Double>> resultMatrix) {
        this.resultMatrix = Objects.requireNonNull(resultMatrix);
    }
    public List<List<Double>> getResultMatrix() { return resultMatrix; }
    // Add equals, hashCode, toString if needed
}