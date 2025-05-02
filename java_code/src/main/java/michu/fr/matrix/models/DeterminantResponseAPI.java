package michu.fr.matrix.models;


import java.util.List;
import java.util.Objects;

public class DeterminantResponseAPI {

    private final List<List<Double>> inputMatrix;
    private final double determinant;

    public DeterminantResponseAPI(List<List<Double>> inputMatrix, double determinant) {
        this.inputMatrix = Objects.requireNonNull(inputMatrix, "Input matrix cannot be null");
        this.determinant = determinant;
    }
    public List<List<Double>> getInputMatrix() {
        return inputMatrix;
    }
    public double getDeterminant() {
        return determinant;
    }
    
}
