package michu.fr.realnumbers.models;

import java.util.Objects;

public class IrrationalityCheckResult {
    private final String numberForm; // e.g., "sqrt(5)"
    private final boolean isIrrational;
    private final String reason;

    public IrrationalityCheckResult(String numberForm, boolean isIrrational, String reason) {
        this.numberForm = numberForm;
        this.isIrrational = isIrrational;
        this.reason = reason;
    }

    public String getNumberForm() { return numberForm; }
    public boolean isIrrational() { return isIrrational; }
    public String getReason() { return reason; }

    @Override
    public String toString() {
        return "IrrationalityCheckResult{" +
               "numberForm='" + numberForm + '\'' +
               ", isIrrational=" + isIrrational +
               ", reason='" + reason + '\'' +
               '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        IrrationalityCheckResult that = (IrrationalityCheckResult) o;
        return isIrrational == that.isIrrational &&
               Objects.equals(numberForm, that.numberForm) &&
               Objects.equals(reason, that.reason);
    }

    @Override
    public int hashCode() {
        return Objects.hash(numberForm, isIrrational, reason);
    }
}