package michu.fr.matrix.models;
import java.util.Objects;
public class MatrixFormulaInput {
    private final int m; // rows
    private final int n; // cols
    private final String formula;
    public MatrixFormulaInput(int m, int n, String formula) {
        if (m <= 0 || n <= 0) {
            throw new IllegalArgumentException("Matrix dimensions must be positive.");
        }
        this.m = m;
        this.n = n;
        this.formula = Objects.requireNonNull(formula);
    }
    public int getM() { return m; }
    public int getN() { return n; }
    public String getFormula() { return formula; }
     // Add equals, hashCode, toString if needed
}
