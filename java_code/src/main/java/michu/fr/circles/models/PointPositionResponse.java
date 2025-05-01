package michu.fr.circles.models;

import java.util.Objects;

public class PointPositionResponse {
    private final String position; // "inside", "on", "outside"

    public PointPositionResponse(String position) {
        this.position = Objects.requireNonNull(position);
    }

    public String getPosition() {
        return position;
    }

     @Override
     public boolean equals(Object o) {
         if (this == o) return true;
         if (o == null || getClass() != o.getClass()) return false;
         PointPositionResponse that = (PointPositionResponse) o;
         return Objects.equals(position, that.position);
     }

     @Override
     public int hashCode() {
         return Objects.hash(position);
     }

    @Override
    public String toString() {
        return "PointPositionResponse{" + "position='" + position + '\'' + '}';
    }
}