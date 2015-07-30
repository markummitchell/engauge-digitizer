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

  /// Format the degrees/minutes/seconds value. Distinguishing x/theta versus y/radius is required for N/S/E/W hemispheres
  QString formatOutput (CoordUnitsPolarTheta coordUnits,
                        double value,
                        bool isXTheta) const;

 private:

  QString formatOutputDegrees (double value) const;
  QString formatOutputDegreesMinutes (double value) const;
};

#endif // FORMAT_DEGREES_MINUTES_SECONDS_POLAR_THETA_H
