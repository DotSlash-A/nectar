// src/main/java/michu/fr/geometry/models/VolumeResult.java
package michu.fr.geometry.models;

import java.util.Objects;

public class VolumeResult {
    private final String shape;
    private final String dimensionsString;
    private final double volume;

    public VolumeResult(String shape, String dimensionsString, double volume) {
        this.shape = Objects.requireNonNull(shape);
        this.dimensionsString = Objects.requireNonNull(dimensionsString);
        this.volume = volume;
    }

    public String getShape() { return shape; }
    public String getDimensionsString() { return dimensionsString; }
    public double getVolume() { return volume; }

    @Override
    public String toString() {
        return "VolumeResult{shape='" + shape + '\'' +
               ", dimensions={" + dimensionsString + '}' +
               ", volume=" + String.format("%.4f",volume) +
               '}';
    }
}