#ifndef FORMAT_DEGREES_MINUTES_SECONDS_NON_POLAR_THETA_H
#define FORMAT_DEGREES_MINUTES_SECONDS_NON_POLAR_THETA_H

#include "CoordUnitsNonPolarTheta.h"
#include "FormatDegreesMinutesSecondsBase.h"
#include <QString>

/// Angular units according to CoordUnitsNonPolarTheta
class FormatDegreesMinutesSecondsNonPolarTheta : public FormatDegreesMinutesSecondsBase
{
 public:
  /// Single constructor
  FormatDegreesMinutesSecondsNonPolarTheta();

  /// Format the degrees/minutes/seconds value when CoordUnitsNonPolarTheta is not 
  /// COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW, which does not involve hemisphere
  QString formatOutput (CoordUnitsNonPolarTheta coordUnits,
                        double value) const;

  /// Format the degrees/minutes/seconds value when CoordUnitsNonPolarTheta is 
  /// COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW, which involves hemispheres
  QString formatOutputNsew (CoordUnitsNonPolarTheta coordUnits,
                            double value,
                            bool isNsHemisphere) const;
};

#endif // FORMAT_DEGREES_MINUTES_SECONDS_NON_POLAR_THETA_H
