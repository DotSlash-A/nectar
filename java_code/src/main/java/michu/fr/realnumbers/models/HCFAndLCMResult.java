package michu.fr.realnumbers.models;

import java.util.Collections;
import java.util.Map;
import java.util.Objects;
import java.util.TreeMap;

public class HCFAndLCMResult {
    private final int num1;
    private final int num2;
    private final Map<Integer, Integer> primeFactorizationNum1;
    private final Map<Integer, Integer> primeFactorizationNum2;
    private final int hcf;
    private final long lcm; // LCM can exceed Integer.MAX_VALUE

    public HCFAndLCMResult(int num1, int num2, Map<Integer, Integer> primeFactorizationNum1, Map<Integer, Integer> primeFactorizationNum2, int hcf, long lcm) {
        this.num1 = num1;
        this.num2 = num2;
        this.primeFactorizationNum1 = Collections.unmodifiableMap(new TreeMap<>(primeFactorizationNum1));
        this.primeFactorizationNum2 = Collections.unmodifiableMap(new TreeMap<>(primeFactorizationNum2));
        this.hcf = hcf;
        this.lcm = lcm;
    }

    public int getNum1() { return num1; }
    public int getNum2() { return num2; }
    public Map<Integer, Integer> getPrimeFactorizationNum1() { return primeFactorizationNum1; }
    public Map<Integer, Integer> getPrimeFactorizationNum2() { return primeFactorizationNum2; }
    public int getHcf() { return hcf; }
    public long getLcm() { return lcm; }

    @Override
    public String toString() {
        return "HCFAndLCMResult{" +
               "num1=" + num1 +
               ", num2=" + num2 +
               ", primeFactorizationNum1=" + primeFactorizationNum1 +
               ", primeFactorizationNum2=" + primeFactorizationNum2 +
               ", hcf=" + hcf +
               ", lcm=" + lcm +
               '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        HCFAndLCMResult that = (HCFAndLCMResult) o;
        return num1 == that.num1 && num2 == that.num2 && hcf == that.hcf && lcm == that.lcm &&
               Objects.equals(primeFactorizationNum1, that.primeFactorizationNum1) &&
               Objects.equals(primeFactorizationNum2, that.primeFactorizationNum2);
    }

    @Override
    public int hashCode() {
        return Objects.hash(num1, num2, primeFactorizationNum1, primeFactorizationNum2, hcf, lcm);
    }
}