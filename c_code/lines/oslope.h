#ifndef SLOPE_H
#define SLOPE_H

#include <stdbool.h> // To use 'bool', 'true', 'false'
#include <math.h>    // For NAN, INFINITY, trig functions, fabs


typedef struct {
    double x1, y1, x2, y2;
} SlopeCoordinates;

typedef struct{
    double x;
    double y;
} Point;

typedef struct{
    Point p1;
    Point p2;
} SlopePoints;

typedef struct{
    double A;
    double B;
    double C;
} GeneralLineForm;

typedef struct {
    double *x1;
    double *y1;
    double *x2;
    double *y2;
    double *m; // Pointer to the slope value
    double result; // To store the calculated missing value
    bool error;    // Flag to indicate if an error occurred during calculation
    char error_message[100]; // Store error details
} SolveSlopeParams;

double slopecoordinates(SlopeCoordinates coords);

#endif
