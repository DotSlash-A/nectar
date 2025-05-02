package michu.fr.matrix.models;

import java.util.List;
import java.util.Objects;

public class MatrixInputAPI {
    private final List<List<Double>> matrix;

    public MatrixInputAPI(List<List<Double>> matrix) {
        this.matrix = Objects.requireNonNull(matrix, "Matrix cannot be null");
    }

    public List<List<Double>> getMatrix() {
        return matrix;
    }
    
}
