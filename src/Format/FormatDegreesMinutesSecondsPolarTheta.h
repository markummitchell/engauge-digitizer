#ifndef FORMAT_DEGREES_MINUTES_SECONDS_POLAR_THETA_H
#define FORMAT_DEGREES_MINUTES_SECONDS_POLAR_THETA_H

#include "CoordUnitsPolarTheta.h"
#include "FormatDegreesMinutesSecondsBase.h"
#include <QString>

/// Angular units according to CoordUnitsPolarTheta
class FormatDegreesMinutesSecondsPolarTheta : public FormatDegreesMinutesSecondsBase
{
 public:
  /// Single constructor
  FormatDegreesMinutesSecondsPolarTheta();

  /// Format the degrees/minutes/seconds value when CoordUnitsPolarTheta is not 
  /// COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW, which does not involve hemispheres
  QString formatOutput (CoordUnitsPolarTheta coordUnits,
                        double value) const;

  /// Format the degrees/minutes/seconds value when CoordUnitsPolarTheta is
  /// COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW, which involves hemispheres
  QString formatOutputNsew (CoordUnitsPolarTheta coordUnits,
                            double value,
                            bool isNsHemisphere) const;

 private:

  QString formatOutputDegrees (double value) const;
  QString formatOutputDegreesMinutes (double value) const;
};

#endif // FORMAT_DEGREES_MINUTES_SECONDS_POLAR_THETA_H
