package michu.fr.linearequations.models;

import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Collections;

public class ReducibleSolutionResult extends SolutionResult {
    private final Double originalSolutionX;
    private final Double originalSolutionY;
    private final String originalSolutionXString;
    private final String originalSolutionYString;
    private final Map<String, String> substitutionDetails; // e.g., "u_represents": "1/x"

    public ReducibleSolutionResult(EquationCoefficients substitutedEquations, String consistencyType, String description,
                                   Double solutionU, Double solutionV, // u is like x, v is like y for the substituted system
                                   String solutionUString, String solutionVString,
                                   Double originalSolutionX, Double originalSolutionY,
                                   String originalSolutionXString, String originalSolutionYString,
                                   String methodUsed, List<String> steps,
                                   Map<String, String> substitutionDetails) {
        super(substitutedEquations, consistencyType, description, solutionU, solutionV, methodUsed, steps);
        // For SolutionResult part, if solutionU/V are not unique, use the string constructor of super
        // This constructor is a bit complex, might need refinement based on usage.
        // Let's simplify by assuming if numeric u,v are null, strings u,v are provided.

        this.originalSolutionX = originalSolutionX;
        this.originalSolutionY = originalSolutionY;
        this.originalSolutionXString = originalSolutionXString;
        this.originalSolutionYString = originalSolutionYString;
        this.substitutionDetails = (substitutionDetails != null) ? Collections.unmodifiableMap(substitutionDetails) : Collections.emptyMap();
    }
    
    // Constructor for non-unique u,v solutions
     public ReducibleSolutionResult(EquationCoefficients substitutedEquations, String consistencyType, String description,
                                   String solutionUString, String solutionVString, // For "Infinite", etc.
                                   String originalSolutionXString, String originalSolutionYString,
                                   String methodUsed, List<String> steps,
                                   Map<String, String> substitutionDetails) {
        super(substitutedEquations, consistencyType, description, solutionUString, solutionVString, methodUsed, steps);
        this.originalSolutionX = null;
        this.originalSolutionY = null;
        this.originalSolutionXString = originalSolutionXString;
        this.originalSolutionYString = originalSolutionYString;
        this.substitutionDetails = (substitutionDetails != null) ? Collections.unmodifiableMap(substitutionDetails) : Collections.emptyMap();
    }


    public Double getOriginalSolutionX() { return originalSolutionX; }
    public Double getOriginalSolutionY() { return originalSolutionY; }
    public String getOriginalSolutionXString() { return originalSolutionXString; }
    public String getOriginalSolutionYString() { return originalSolutionYString; }
    public Map<String, String> getSubstitutionDetails() { return substitutionDetails; }

    @Override
    public String toString() {
        String origX = (originalSolutionX != null) ? String.format("%.4f", originalSolutionX) : originalSolutionXString;
        String origY = (originalSolutionY != null) ? String.format("%.4f", originalSolutionY) : originalSolutionYString;
        return "ReducibleSolutionResult{" +
               "substitutedSystem=" + super.toString() +
               ", originalSolutionX=" + origX +
               ", originalSolutionY=" + origY +
               ", substitutionDetails=" + substitutionDetails +
               '}';
    }
    
    // equals and hashCode would need to consider superclass fields and new fields
     @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false; // Check superclass equality
        ReducibleSolutionResult that = (ReducibleSolutionResult) o;
        return Objects.equals(originalSolutionX, that.originalSolutionX) &&
               Objects.equals(originalSolutionY, that.originalSolutionY) &&
               Objects.equals(originalSolutionXString, that.originalSolutionXString) &&
               Objects.equals(originalSolutionYString, that.originalSolutionYString) &&
               Objects.equals(substitutionDetails, that.substitutionDetails);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), originalSolutionX, originalSolutionY, originalSolutionXString, originalSolutionYString, substitutionDetails);
    }
}