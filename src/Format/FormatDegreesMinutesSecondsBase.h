/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef FORMAT_DEGREES_MINUTES_SECONDS_BASE_H
#define FORMAT_DEGREES_MINUTES_SECONDS_BASE_H

#include <QString>
#include <QValidator>

/// Common input parsing and output formatting for degrees/minutes/seconds values
class FormatDegreesMinutesSecondsBase {
 public:
  /// Single constructor
  FormatDegreesMinutesSecondsBase();
  ~FormatDegreesMinutesSecondsBase();

  /// Parse the input string into a number value. Success flag is false if the parsing failed. Either signed
  /// values or hemisphere (North, South, East, West) values can be accepted irregardless of the output format
  /// selected by the user. Leading/trailing spaces are trimmed. Leading/trailing spaces are trimmed (=ignored)
  QValidator::State parseInput (const QString &stringUntrimmed,
                                double &value) const;

 protected:

  /// Format as degrees, minutes and seconds without hemisphere
  QString formatOutputDegreesMinutesSeconds (double value) const;

  /// Format as degrees, minutes and seconds with hemisphere
  QString formatOutputDegreesMinutesSecondsNsew (double value,
                                                 bool isNsHemisphere) const;

 private:

  void stripSymbols (QString &field0,
                     QString &field1,
                     QString &field2) const;
};

#endif // FORMAT_DEGREES_MINUTES_SECONDS_BASE_H
