package michu.fr.circles.models;

import java.util.Objects;

// Corresponds to Python's EqnInput (used in /circle/parametric)
public class EquationInput {
    private final String equation;

    public EquationInput(String equation) {
        this.equation = Objects.requireNonNull(equation, "Equation cannot be null");
    }

    public String getEquation() {
        return equation;
    }

     @Override
     public boolean equals(Object o) {
         if (this == o) return true;
         if (o == null || getClass() != o.getClass()) return false;
         EquationInput that = (EquationInput) o;
         return Objects.equals(equation, that.equation);
     }

     @Override
     public int hashCode() {
         return Objects.hash(equation);
     }

    @Override
    public String toString() {
        return "EquationInput{" + "equation='" + equation + '\'' + '}';
    }
}