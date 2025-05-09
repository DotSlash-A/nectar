#ifndef GEOMETRIC_PROGRESSION_UTILS_H
#define GEOMETRIC_PROGRESSION_UTILS_H

#include "progressions_types.h"
#include <vector>

namespace michu_fr {
namespace progressions {

GPResult calculateGPTermAndSum(double a, double r, int n);
double calculateGPSumToInfinity(double a, double r);
double calculateGeometricMean(double num1, double num2);
GPInsertMeansResult insertGeometricMeans(double a, double b, int k);

} // namespace progressions
} // namespace michu_fr

#endif // GEOMETRIC_PROGRESSION_UTILS_H