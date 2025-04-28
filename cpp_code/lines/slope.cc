#include <stdio.h>

typedef struct {
    double x1, y1, x2, y2;
} SlopeCoordinates;

double slopecoordinates(SlopeCoordinates coords) {
    return (coords.y2 - coords.y1) / (coords.x2 - coords.x1);
}

// int main() {
//     SlopeCoordinates coords = {1.0, 2.0, 3.0, 6.0};
//     double slope = slopecoordinates(coords);
//     printf("Slope: %f\n", slope);
//     return 0;
// }