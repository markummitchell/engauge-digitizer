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
                        unsigned long value) const;
  
  /// Parse the input string into a time value. Success flag is false if parsing failed
  QValidator::State parseInput (CoordUnitsDate coordUnitsDate,
                                CoordUnitsTime coordUnitsTime,
                                const QString &string,
                                unsigned long &value) const;
  
 private:

  void dateTimeLookup (const FormatsDate &formatsDate,
                       const FormatsTime &formatsTime,
                       CoordUnitsDate coordUnitsDate,
                       CoordUnitsTime coordUnitsTime,
                       const QString &string,
                       unsigned long &value,
                       bool &success) const;
  void loadFormatsFormat();
  void loadFormatsParseAcceptable();
  void loadFormatsParseIncomplete();

  // For formatting output
  FormatDate m_formatsDateFormat;
  FormatTime m_formatsTimeFormat;

  // For parsing input
  FormatsDate m_formatsDateParseAcceptable;
  FormatsDate m_formatsDateParseIncomplete;
  FormatsTime m_formatsTimeParseAcceptable;
  FormatsTime m_formatsTimeParseIncomplete;

};

#endif // FORMAT_DATE_TIME_H
