#ifndef ARITHMETIC_PROGRESSION_UTILS_H
#define ARITHMETIC_PROGRESSION_UTILS_H

#include "progressions_types.h"
#include <vector>

namespace michu_fr {
namespace progressions {

APResult calculateAPTermAndSum(double a, double d, int n);
double calculateNthTermFromLastAP(double l, double d, int n);
APMiddleTermResult findMiddleTermsAP(double a, double d, double last_term);

} // namespace progressions
} // namespace michu_fr

#endif // ARITHMETIC_PROGRESSION_UTILS_H