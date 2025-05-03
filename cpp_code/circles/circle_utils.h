// cpp_code/circles/circle_utils.h
#ifndef CIRCLE_UTILS_H
#define CIRCLE_UTILS_H

#include "circles_types.h"
#include "../lines/geometry_types.h" // Include Coordinates, GeneralLineInput

namespace geometry {
namespace circles {

// --- Function Declarations ---

// Calculate standard/general equations from center/radius
CircleEqnResponse getCircleEquationsFromCenterRadius(const CircleGeneralInput& input);

// Calculate center/radius from general form coefficients
CircleDetailsResponse getCircleDetailsFromCoeffs(const CircleCoeffs& coeffs, const std::string& inputEqStr = "");

// Calculate center/radius from general form equation string (USE WITH CAUTION - basic parsing)
CircleDetailsResponse getCircleDetailsFromGeneralForm(const CircleGeneralFormInput& data);

// Calculate circle equation from three points
CircleEquationOnlyResponse getCircleFromThreePoints(const CircleWThreePointsInput& data);

// Calculate circle passing through p, q with center on line Ax+By+C=0
CircleEquationOnlyResponse getCircleCenterOnLine(const Coordinates& p,
                                                 const Coordinates& q,
                                                 const GeneralLineInput& line);

// Calculate parametric equations from coefficients (preferred over string input)
ParametricCircleResponse getCircleParametricFromCoeffs(const CircleCoeffs& coeffs);

// Calculate parametric equations from general form string (calls details function)
ParametricCircleResponse getCircleParametric(const EquationInput& data);

// Calculate circle equation from diameter endpoints
CircleEquationOnlyResponse getCircleFromDiameter(const Coordinates& p, const Coordinates& q);

// Determine point position relative to circle defined by coefficients (preferred)
PointPositionResponse getPointPositionRelativeToCircle(const CircleCoeffs& coeffs, const Coordinates& point);

// Determine point position relative to circle from general equation string (calls details)
PointPositionResponse getPointPositionRelativeToCircle(const EquationInput& data, const Coordinates& point);


} // namespace circles
} // namespace geometry

#endif // CIRCLE_UTILS_H