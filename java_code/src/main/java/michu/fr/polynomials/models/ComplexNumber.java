// src/main/java/michu/fr/polynomials/models/ComplexNumber.java
package michu.fr.polynomials.models;

import java.util.Objects;

public class ComplexNumber {
    private final double real;
    private final double imaginary;

    public ComplexNumber(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    public double getReal() {
        return real;
    }

    public double getImaginary() {
        return imaginary;
    }

    @Override
    public String toString() {
        if (Math.abs(imaginary) < 1e-9) {
            return String.format("%.4f", real).replaceAll("\\.?0+$", "");
        }
        if (Math.abs(real) < 1e-9) {
            return String.format("%.4fj", imaginary).replaceAll("\\.?0+(?=j)", "");
        }
        return String.format("%.4f %c %.4fj",
                real,
                imaginary < 0 ? '-' : '+',
                Math.abs(imaginary))
                .replaceAll("\\.?0+(?=[ \\c])", "") // Clean trailing zeros for numbers before space or sign
                .replaceAll("\\.?0+(?=j)", "");    // Clean trailing zeros for numbers before j
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        ComplexNumber that = (ComplexNumber) o;
        return Math.abs(that.real - real) < 1e-9 &&
               Math.abs(that.imaginary - imaginary) < 1e-9;
    }

    @Override
    public int hashCode() {
        return Objects.hash(real, imaginary); // Approximate hash based on double values
    }
}