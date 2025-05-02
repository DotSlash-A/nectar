// File: src/main/java/michu/fr/limits/models/LimitResponse.java
package michu.fr.limits.models;

import java.util.Objects;

public class LimitResponse {
    private final String expression;
    private final String variable;
    private final String tendingTo;
    private final String limitResult; // Stores the numerical result, "Infinity", "NaN", etc.
    private final String explanation; // Brief explanation/status

    public LimitResponse(String expression, String variable, String tendingTo, String limitResult, String explanation) {
        this.expression = Objects.requireNonNull(expression);
        this.variable = Objects.requireNonNull(variable);
        this.tendingTo = Objects.requireNonNull(tendingTo);
        this.limitResult = Objects.requireNonNull(limitResult);
        this.explanation = Objects.requireNonNull(explanation);
    }

    public String getExpression() { return expression; }
    public String getVariable() { return variable; }
    public String getTendingTo() { return tendingTo; }
    public String getLimitResult() { return limitResult; }
    public String getExplanation() { return explanation; }

     @Override
    public String toString() {
        return "LimitResponse{" +
               "expression='" + expression + '\'' +
               ", variable='" + variable + '\'' +
               ", tendingTo='" + tendingTo + '\'' +
               ", limitResult='" + limitResult + '\'' +
               ", explanation='" + explanation + '\'' +
               '}';
    }
     // Add equals/hashCode if needed
}