package michu.fr.circles.models;

import java.util.Objects;

// Corresponds to Python's CircleGeneralFormInput
public class CircleGeneralFormInput {
    private final String equation;

    public CircleGeneralFormInput(String equation) {
        Objects.requireNonNull(equation, "Equation string cannot be null");
        this.equation = equation;
    }

    public String getEquation() {
        return equation;
    }

     @Override
     public boolean equals(Object o) {
         if (this == o) return true;
         if (o == null || getClass() != o.getClass()) return false;
         CircleGeneralFormInput that = (CircleGeneralFormInput) o;
         return Objects.equals(equation, that.equation);
     }

     @Override
     public int hashCode() {
         return Objects.hash(equation);
     }

     @Override
     public String toString() {
         return "CircleGeneralFormInput{" + "equation='" + equation + '\'' + '}';
     }
}