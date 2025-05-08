package michu.fr.realnumbers.models;

import java.util.Objects;

public class EuclidLemmaResult {
    private final int dividend;
    private final int divisor;
    private final int quotient;
    private final int remainder;
    private final String equation;

    public EuclidLemmaResult(int dividend, int divisor, int quotient, int remainder) {
        this.dividend = dividend;
        this.divisor = divisor;
        this.quotient = quotient;
        this.remainder = remainder;
        this.equation = String.format("%d = %d * %d + %d", dividend, divisor, quotient, remainder);
    }

    public int getDividend() { return dividend; }
    public int getDivisor() { return divisor; }
    public int getQuotient() { return quotient; }
    public int getRemainder() { return remainder; }
    public String getEquation() { return equation; }

    @Override
    public String toString() {
        return "EuclidLemmaResult{" +
               "equation='" + equation + '\'' +
               '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        EuclidLemmaResult that = (EuclidLemmaResult) o;
        return dividend == that.dividend && divisor == that.divisor && quotient == that.quotient && remainder == that.remainder;
    }

    @Override
    public int hashCode() {
        return Objects.hash(dividend, divisor, quotient, remainder);
    }
}