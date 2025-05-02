package michu.fr.matrix.models;

import java.util.Objects;
import java.util.List;


public class DetInput {
    private final List<List<Double>> matrix;
    public DetInput(List<List<Double>> matrix) {
        this.matrix = Objects.requireNonNull(matrix, "Matrix cannot be null");
    }
    public List<List<Double>> getMatrix() {
        return matrix;
    }
    
}
