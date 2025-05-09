package michu.fr.threedgeometry.models;

// import java.util.Objects;

public class SectionFormulaResult {
    private final Point3D resultingPoint;
    private final Point3D p1;
    private final Point3D p2;
    private final double ratioM;
    private final double ratioN;
    private final String divisionType; // "internal" or "external"

    public SectionFormulaResult(Point3D resultingPoint, Point3D p1, Point3D p2, double ratioM, double ratioN, String divisionType) {
        this.resultingPoint = resultingPoint;
        this.p1 = p1;
        this.p2 = p2;
        this.ratioM = ratioM;
        this.ratioN = ratioN;
        this.divisionType = divisionType;
    }

    public Point3D getResultingPoint() { return resultingPoint; }
    public Point3D getP1() { return p1; }
    public Point3D getP2() { return p2; }
    public double getRatioM() { return ratioM; }
    public double getRatioN() { return ratioN; }
    public String getDivisionType() { return divisionType; }

    @Override
    public String toString() {
        return "SectionFormulaResult{" +
               "resultingPoint=" + resultingPoint +
               ", p1=" + p1 +
               ", p2=" + p2 +
               ", ratioM=" + ratioM +
               ", ratioN=" + ratioN +
               ", divisionType='" + divisionType + '\'' +
               '}';
    }
    // equals and hashCode
}