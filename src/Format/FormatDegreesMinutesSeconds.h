#ifndef FORMAT_DEGREES_MINUTES_SECONDS_H
#define FORMAT_DEGREES_MINUTES_SECONDS_H

#include "CoordUnitsPolarTheta.h"
#include <QString>

/// Input parsing and output formatting for degrees/minutes/seconds values
class FormatDegreesMinutesSeconds {
 public:
  /// Single constructor
  FormatDegreesMinutesSeconds();

  /// Format the degrees/minutes/seconds value according to degrees/minutes/seconds format settings
  QString formatOutput (CoordUnitsPolarTheta coordUnits,
                        double value) const;

  /// Parse the input string into a number value. Success flag is false if the parsing failed
  double parseInput (const QString &string,
                     bool &success) const;
};

#endif // FORMAT_DEGREES_MINUTES_SECONDS_H
