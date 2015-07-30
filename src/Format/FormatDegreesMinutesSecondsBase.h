#ifndef FORMAT_DEGREES_MINUTES_SECONDS_BASE_H
#define FORMAT_DEGREES_MINUTES_SECONDS_BASE_H

#include <QString>

/// Common input parsing and output formatting for degrees/minutes/seconds values
class FormatDegreesMinutesSecondsBase {
 public:
  /// Single constructor
  FormatDegreesMinutesSecondsBase();
  ~FormatDegreesMinutesSecondsBase();

  /// Parse the input string into a number value. Success flag is false if the parsing failed. Either signed
  /// values or hemisphere (North, South, East, West) values can be accepted irregardless of the output format
  /// selected by the user
  double parseInput (const QString &string,
                     bool &success) const;

 protected:

  /// Format as degrees, minutes and seconds without hemisphere
  QString formatOutputDegreesMinutesSeconds (double value) const;

  /// Format as degrees, minutes and seconds with hemisphere
  QString formatOutputDegreesMinutesSecondsNsew (double value,
                                                 bool isNsHemisphere) const;
};

#endif // FORMAT_DEGREES_MINUTES_SECONDS_BASE_H
