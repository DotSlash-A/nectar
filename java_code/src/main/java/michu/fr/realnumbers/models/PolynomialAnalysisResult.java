package michu.fr.realnumbers.models;

import java.util.List;
import java.util.Objects;
import java.util.Collections;

// This class might need Symja or similar for full functionality (especially roots)
public class PolynomialAnalysisResult {
    private final String expression;
    private final int degree;
    private final List<String> coefficients; // Coefficients as strings to handle various types
    private final List<String> roots;        // Roots as strings
    private final String sumOfRootsViete;
    private final String productOfRootsViete;

    public PolynomialAnalysisResult(String expression, int degree, List<String> coefficients,
                                    List<String> roots, String sumOfRootsViete, String productOfRootsViete) {
        this.expression = expression;
        this.degree = degree;
        this.coefficients = Collections.unmodifiableList(coefficients);
        this.roots = Collections.unmodifiableList(roots);
        this.sumOfRootsViete = sumOfRootsViete;
        this.productOfRootsViete = productOfRootsViete;
    }

    public String getExpression() { return expression; }
    public int getDegree() { return degree; }
    public List<String> getCoefficients() { return coefficients; }
    public List<String> getRoots() { return roots; }
    public String getSumOfRootsViete() { return sumOfRootsViete; }
    public String getProductOfRootsViete() { return productOfRootsViete; }

    @Override
    public String toString() {
        return "PolynomialAnalysisResult{" +
               "expression='" + expression + '\'' +
               ", degree=" + degree +
               ", coefficients=" + coefficients +
               ", roots=" + roots +
               ", sumOfRootsViete='" + sumOfRootsViete + '\'' +
               ", productOfRootsViete='" + productOfRootsViete + '\'' +
               '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        PolynomialAnalysisResult that = (PolynomialAnalysisResult) o;
        return degree == that.degree &&
               Objects.equals(expression, that.expression) &&
               Objects.equals(coefficients, that.coefficients) &&
               Objects.equals(roots, that.roots) &&
               Objects.equals(sumOfRootsViete, that.sumOfRootsViete) &&
               Objects.equals(productOfRootsViete, that.productOfRootsViete);
    }

    @Override
    public int hashCode() {
        return Objects.hash(expression, degree, coefficients, roots, sumOfRootsViete, productOfRootsViete);
    }
}