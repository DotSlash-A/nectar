package michu.fr.realnumbers.models;

import java.util.Collections;
import java.util.Map;
import java.util.Objects;
import java.util.TreeMap; // To keep factors sorted for consistent toString

public class PrimeFactorizationResult {
    private final int number;
    private final Map<Integer, Integer> factors; // prime -> exponent

    public PrimeFactorizationResult(int number, Map<Integer, Integer> factors) {
        this.number = number;
        // Use TreeMap for sorted keys, ensure immutability
        this.factors = Collections.unmodifiableMap(new TreeMap<>(factors));
    }

    public int getNumber() { return number; }
    public Map<Integer, Integer> getFactors() { return factors; } // Already unmodifiable

    @Override
    public String toString() {
        return "PrimeFactorizationResult{" +
               "number=" + number +
               ", factors=" + factors +
               '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        PrimeFactorizationResult that = (PrimeFactorizationResult) o;
        return number == that.number && Objects.equals(factors, that.factors);
    }

    @Override
    public int hashCode() {
        return Objects.hash(number, factors);
    }
}