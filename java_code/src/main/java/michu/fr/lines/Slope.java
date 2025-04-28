package michu.fr.lines;

public class Slope {
    private double x1, y1, x2, y2;

    public Slope(double x1, double y1, double x2, double y2) {
        this.x1 = x1;
        this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;
    }

    public double getSlope() {
        if (x2 - x1 == 0) {
            throw new ArithmeticException("Slope is undefined (vertical line)");
        }
        return (y2 - y1) / (x2 - x1);
    }

    public static void main(String[] args) {
        Slope line = new Slope(0, 0, 4, 4);
        System.out.println("Slope: " + line.getSlope());
    }
    public double getX1() {
        return x1;
    }
}
