package michu.fr.matrix.models;
import java.util.List;
import java.util.Objects;
public class TwoMatrixInput {
    private final List<List<Double>> matrixA;
    private final List<List<Double>> matrixB;
    public TwoMatrixInput(List<List<Double>> matrixA, List<List<Double>> matrixB) {
        this.matrixA = Objects.requireNonNull(matrixA);
        this.matrixB = Objects.requireNonNull(matrixB);
    }
    public List<List<Double>> getMatrixA() { return matrixA; }
    public List<List<Double>> getMatrixB() { return matrixB; }
    // Add equals, hashCode, toString if needed
}