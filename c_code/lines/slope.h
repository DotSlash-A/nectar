#ifndef SLOPE_H
#define SLOPE_H

typedef struct {
    double x1, y1, x2, y2;
} SlopeCoordinates;

double slopecoordinates(SlopeCoordinates coords);

#endif