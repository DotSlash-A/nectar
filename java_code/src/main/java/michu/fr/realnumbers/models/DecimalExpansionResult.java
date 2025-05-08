package michu.fr.realnumbers.models;

import java.util.Objects;

public class DecimalExpansionResult {
    private final int numerator;
    private final int denominator;
    private final String fraction;
    private final String expansionType; // "terminating", "non-terminating recurring", "undefined"
    private final String reason;

    public DecimalExpansionResult(int numerator, int denominator, String expansionType, String reason) {
        this.numerator = numerator;
        this.denominator = denominator;
        this.fraction = numerator + "/" + denominator;
        this.expansionType = expansionType;
        this.reason = reason;
    }

    public int getNumerator() { return numerator; }
    public int getDenominator() { return denominator; }
    public String getFraction() { return fraction; }
    public String getExpansionType() { return expansionType; }
    public String getReason() { return reason; }

    @Override
    public String toString() {
        return "DecimalExpansionResult{" +
               "fraction='" + fraction + '\'' +
               ", expansionType='" + expansionType + '\'' +
               ", reason='" + reason + '\'' +
               '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        DecimalExpansionResult that = (DecimalExpansionResult) o;
        return numerator == that.numerator && denominator == that.denominator &&
               Objects.equals(expansionType, that.expansionType) &&
               Objects.equals(reason, that.reason);
    }

    @Override
    public int hashCode() {
        return Objects.hash(numerator, denominator, expansionType, reason);
    }
}