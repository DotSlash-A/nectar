package michu.fr.matrix.models;


import java.util.List;
import java.util.Objects;

public class MinorsCofactorsResponse {
    private final List<List<Double>> inputMatrix;
    private final String dimensions;
    private final List<List<Double>> matrixOfMinors;
    private final List<List<Double>> matrixOfCofactors;
    private final Double determinant;

    public MinorsCofactorsResponse(List<List<Double>> inputMatrix, String dimensions, List<List<Double>> matrixOfMinors, List<List<Double>> matrixOfCofactors, Double determinant) {
        this.inputMatrix = Objects.requireNonNull(inputMatrix, "Input matrix cannot be null");
        this.dimensions = Objects.requireNonNull(dimensions, "Dimensions cannot be null");
        this.matrixOfMinors = Objects.requireNonNull(matrixOfMinors, "Matrix of minors cannot be null");
        this.matrixOfCofactors = Objects.requireNonNull(matrixOfCofactors, "Matrix of cofactors cannot be null");
        this.determinant = Objects.requireNonNull(determinant, "Determinant cannot be null");
    }
    public List<List<Double>> getInputMatrix() {
        return inputMatrix;
    }
    public String getDimensions() {
        return dimensions;
    }
    public List<List<Double>> getMatrixOfMinors() {
        return matrixOfMinors;
    }
    public List<List<Double>> getMatrixOfCofactors() {
        return matrixOfCofactors;
    }
    public Double getDeterminant() {
        return determinant;
    }
}
