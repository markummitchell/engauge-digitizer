#ifndef FORMAT_DEGREES_MINUTES_SECONDS_H
#define FORMAT_DEGREES_MINUTES_SECONDS_H

#include <QString>

/// Input parsing and output formatting for degrees/minutes/seconds values
class FormatDegreesMinutesSeconds {
 public:
  /// Single constructor
  FormatDegreesMinutesSeconds();

  /// Parse the string into a number value. Success flag is false if the parsing failed
  double parse (const QString &string,
                bool &success) const;
};

#endif // FORMAT_DEGREES_MINUTES_SECONDS_H
