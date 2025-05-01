// Simple response for methods returning just the equation string
package michu.fr.circles.models;

import java.util.Objects;

public class CircleEquationOnlyResponse {
    private final String circleEquation;

    public CircleEquationOnlyResponse(String circleEquation) {
        this.circleEquation = Objects.requireNonNull(circleEquation);
    }

    public String getCircleEquation() {
        return circleEquation;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        CircleEquationOnlyResponse that = (CircleEquationOnlyResponse) o;
        return Objects.equals(circleEquation, that.circleEquation);
    }

    @Override
    public int hashCode() {
        return Objects.hash(circleEquation);
    }

    @Override
    public String toString() {
        return "CircleEquationOnlyResponse{" + "circleEquation='" + circleEquation + '\'' + '}';
    }
}