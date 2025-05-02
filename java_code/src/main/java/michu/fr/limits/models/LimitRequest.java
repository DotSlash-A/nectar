package michu.fr.limits.models;

import java.util.Objects;

public class LimitRequest {
    private final String expression;
    private final String variable; // Name of the variable, e.g., "x"
    private final String tendingTo; // String representation, e.g., "1", "inf", "pi/2"

    public LimitRequest(String expression, String variable, String tendingTo) {
        this.expression = Objects.requireNonNull(expression, "Expression cannot be null");
        this.variable = Objects.requireNonNull(variable, "Variable cannot be null");
        this.tendingTo = Objects.requireNonNull(tendingTo, "TendingTo cannot be null");
        // Basic validation for variable name
        if (!variable.matches("^[a-zA-Z_][a-zA-Z0-9_]*$")) {
            throw new IllegalArgumentException("Invalid variable name format: " + variable);
        }
    }

    public String getExpression() { return expression; }
    public String getVariable() { return variable; }
    public String getTendingTo() { return tendingTo; }

    @Override
    public String toString() {
        return "LimitRequest{" +
               "expression='" + expression + '\'' +
               ", variable='" + variable + '\'' +
               ", tendingTo='" + tendingTo + '\'' +
               '}';
    }
    // Add equals/hashCode if needed
}