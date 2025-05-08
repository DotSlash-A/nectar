package michu.fr.linearequations.models;

import java.util.Collections;
import java.util.Map;
import java.util.Objects;

public class ConsistencyCheckResult {
    private final EquationCoefficients equations;
    private final String consistencyType; // e.g., "CONSISTENT_UNIQUE", "CONSISTENT_INFINITE", "INCONSISTENT_PARALLEL"
    private final String description;
    private final Map<String, String> ratios; // e.g., {"a1/a2": "0.5", "b1/b2": "undefined (b1/0)"}
    private final String graphicalInterpretation;

    public ConsistencyCheckResult(EquationCoefficients equations, String consistencyType, String description,
                                  Map<String, String> ratios, String graphicalInterpretation) {
        this.equations = equations;
        this.consistencyType = consistencyType;
        this.description = description;
        this.ratios = Collections.unmodifiableMap(ratios);
        this.graphicalInterpretation = graphicalInterpretation;
    }

    public EquationCoefficients getEquations() { return equations; }
    public String getConsistencyType() { return consistencyType; }
    public String getDescription() { return description; }
    public Map<String, String> getRatios() { return ratios; }
    public String getGraphicalInterpretation() { return graphicalInterpretation; }

    @Override
    public String toString() {
        return "ConsistencyCheckResult{" +
               "equations=" + equations +
               ", consistencyType='" + consistencyType + '\'' +
               ", description='" + description + '\'' +
               ", ratios=" + ratios +
               ", graphicalInterpretation='" + graphicalInterpretation + '\'' +
               '}';
    }

     @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        ConsistencyCheckResult that = (ConsistencyCheckResult) o;
        return Objects.equals(equations, that.equations) &&
               Objects.equals(consistencyType, that.consistencyType) &&
               Objects.equals(description, that.description) &&
               Objects.equals(ratios, that.ratios) &&
               Objects.equals(graphicalInterpretation, that.graphicalInterpretation);
    }

    @Override
    public int hashCode() {
        return Objects.hash(equations, consistencyType, description, ratios, graphicalInterpretation);
    }
}