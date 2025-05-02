package michu.fr.matrix.models;
import java.util.List;
import java.util.Objects;
public class ConstructedMatrixResponse {
    private final int rows;
    private final int columns;
    private final String formulaUsed;
    private final List<List<Double>> constructedMatrix;
    public ConstructedMatrixResponse(int rows, int columns, String formulaUsed, List<List<Double>> constructedMatrix) {
        this.rows = rows;
        this.columns = columns;
        this.formulaUsed = Objects.requireNonNull(formulaUsed);
        this.constructedMatrix = Objects.requireNonNull(constructedMatrix);
    }
    public int getRows() { return rows; }
    public int getColumns() { return columns; }
    public String getFormulaUsed() { return formulaUsed; }
    public List<List<Double>> getConstructedMatrix() { return constructedMatrix; }
     // Add equals, hashCode, toString if needed
}
