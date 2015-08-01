#ifndef FORMAT_DATE_TIME_H
#define FORMAT_DATE_TIME_H

#include "CoordUnitsDate.h"
#include "CoordUnitsTime.h"
#include <QDateTime>
#include <QHash>
#include <QString>
#include <QStringList>
#include <QValidator>

typedef QHash<CoordUnitsDate, QString> FormatDate;
typedef QHash<CoordUnitsTime, QString> FormatTime;

typedef QHash<CoordUnitsDate, QStringList> FormatsDate;
typedef QHash<CoordUnitsTime, QStringList> FormatsTime;

/// Input parsing and output formatting for date/time values
class FormatDateTime {
 public:
  /// Single constructor
  FormatDateTime();

  /// Format the date/time value according to date/time format settings
  QString formatOutput (CoordUnitsDate coordUnitsDate,
                        CoordUnitsTime coordUnitsTime,
                        double value) const;
  
  /// Parse the input string into a time value. Success flag is false if parsing failed.
  /// Leading/trailing spaces are trimmed (=ignored)
  QValidator::State parseInput (CoordUnitsDate coordUnitsDate,
                                CoordUnitsTime coordUnitsTime,
                                const QString &stringUntrimmed,
                                double &value) const;
  
 private:

  bool ambiguityBetweenDateAndTime (CoordUnitsDate coordUnitsDate,
                                    CoordUnitsTime coordUnitsTime,
                                    const QString &string) const;
  void dateTimeLookup (const FormatsDate &formatsDate,
                       const FormatsTime &formatsTime,
                       CoordUnitsDate coordUnitsDate,
                       CoordUnitsTime coordUnitsTime,
                       const QString &string,
                       bool useQDateTimeElseQRegExp,
                       double &value, // Set only if useQDateTimeElseQRegExp=success=true
                       bool &success) const;
  void loadFormatsFormat();
  void loadFormatsParseAcceptable();
  void loadFormatsParseIncomplete();

  // For formatting output
  FormatDate m_formatsDateFormat;
  FormatTime m_formatsTimeFormat;

  // For parsing input, using built in Qt date/time parsing according to QDateTime
  FormatsDate m_formatsDateParseAcceptable;
  FormatsTime m_formatsTimeParseAcceptable;

  // For parsing input, after input has been found to not be Acceptable. Regular expressions are used since Qt date/time
  // parsing of Intermediate strings does not work. Example, 'J' and 'Ja' would be rejected although they are typed
  // in the process of entering 'Jan' for the month
  FormatsDate m_formatsDateParseIncomplete;
  FormatsTime m_formatsTimeParseIncomplete;
};

#endif // FORMAT_DATE_TIME_H
