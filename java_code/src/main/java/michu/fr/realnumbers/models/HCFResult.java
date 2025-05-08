package michu.fr.realnumbers.models;

import java.util.Objects;

public class HCFResult {
    private final int num1;
    private final int num2;
    private final int hcf;

    public HCFResult(int num1, int num2, int hcf) {
        this.num1 = num1;
        this.num2 = num2;
        this.hcf = hcf;
    }

    public int getNum1() { return num1; }
    public int getNum2() { return num2; }
    public int getHcf() { return hcf; }

    @Override
    public String toString() {
        return "HCFResult{" +
               "num1=" + num1 +
               ", num2=" + num2 +
               ", hcf=" + hcf +
               '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        HCFResult hcfResult = (HCFResult) o;
        return num1 == hcfResult.num1 && num2 == hcfResult.num2 && hcf == hcfResult.hcf;
    }

    @Override
    public int hashCode() {
        return Objects.hash(num1, num2, hcf);
    }
}