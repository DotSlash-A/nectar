package michu.fr.linearequations.models;

import java.util.List;
import java.util.Objects;
import java.util.Collections;

public class SolutionResult {
    private final EquationCoefficients equations;
    private final String consistencyType;
    private final String description;
    private final Double solutionX; // Nullable if no unique solution
    private final Double solutionY; // Nullable if no unique solution
    private final String solutionXString; // For "Infinite" or error messages
    private final String solutionYString; // For "Infinite" or error messages
    private final String methodUsed;
    private final List<String> steps; // For step-by-step methods

    // Constructor for unique solutions
    public SolutionResult(EquationCoefficients equations, String consistencyType, String description,
                          Double solutionX, Double solutionY, String methodUsed, List<String> steps) {
        this.equations = equations;
        this.consistencyType = consistencyType;
        this.description = description;
        this.solutionX = solutionX;
        this.solutionY = solutionY;
        this.solutionXString = (solutionX != null) ? String.valueOf(solutionX) : "N/A";
        this.solutionYString = (solutionY != null) ? String.valueOf(solutionY) : "N/A";
        this.methodUsed = methodUsed;
        this.steps = (steps != null) ? Collections.unmodifiableList(steps) : Collections.emptyList();
    }

    // Constructor for non-unique solutions or errors
    public SolutionResult(EquationCoefficients equations, String consistencyType, String description,
                          String solutionXString, String solutionYString, String methodUsed, List<String> steps) {
        this.equations = equations;
        this.consistencyType = consistencyType;
        this.description = description;
        this.solutionX = null; // No numeric solutionX
        this.solutionY = null; // No numeric solutionY
        this.solutionXString = solutionXString;
        this.solutionYString = solutionYString;
        this.methodUsed = methodUsed;
        this.steps = (steps != null) ? Collections.unmodifiableList(steps) : Collections.emptyList();
    }


    public EquationCoefficients getEquations() { return equations; }
    public String getConsistencyType() { return consistencyType; }
    public String getDescription() { return description; }
    public Double getSolutionX() { return solutionX; }
    public Double getSolutionY() { return solutionY; }
    public String getSolutionXString() { return solutionXString; }
    public String getSolutionYString() { return solutionYString; }
    public String getMethodUsed() { return methodUsed; }
    public List<String> getSteps() { return steps; }

    @Override
    public String toString() {
        String solX = (solutionX != null) ? String.format("%.4f", solutionX) : solutionXString;
        String solY = (solutionY != null) ? String.format("%.4f", solutionY) : solutionYString;
        return "SolutionResult{" +
               "equations=" + equations +
               ", consistencyType='" + consistencyType + '\'' +
               ", solutionX=" + solX +
               ", solutionY=" + solY +
               ", methodUsed='" + methodUsed + '\'' +
               ((steps != null && !steps.isEmpty()) ? ", steps=" + steps.size() + " steps" : "") +
               '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        SolutionResult that = (SolutionResult) o;
        return Objects.equals(equations, that.equations) &&
               Objects.equals(consistencyType, that.consistencyType) &&
               Objects.equals(description, that.description) &&
               Objects.equals(solutionX, that.solutionX) &&
               Objects.equals(solutionY, that.solutionY) &&
               Objects.equals(solutionXString, that.solutionXString) &&
               Objects.equals(solutionYString, that.solutionYString) &&
               Objects.equals(methodUsed, that.methodUsed) &&
               Objects.equals(steps, that.steps);
    }

    @Override
    public int hashCode() {
        return Objects.hash(equations, consistencyType, description, solutionX, solutionY, solutionXString, solutionYString, methodUsed, steps);
    }
}