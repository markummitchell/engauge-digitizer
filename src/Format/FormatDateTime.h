#ifndef FORMAT_DATE_TIME_H
#define FORMAT_DATE_TIME_H

#include "CoordUnitsDate.h"
#include "CoordUnitsTime.h"
#include <QDateTime>
#include <QHash>
#include <QString>
#include <QStringList>

typedef QHash<CoordUnitsDate, QStringList> FormatsDate;
typedef QHash<CoordUnitsTime, QStringList> FormatsTime;

/// Input parsing and output formatting for date/time values
class FormatDateTime {
 public:
  /// Single constructor
  FormatDateTime();

  /// Parse the string into a QDateTime value. Value is invalid if the parsing failed
  QDateTime parse (CoordUnitsDate coordUnitsDate,
                   CoordUnitsTime coordUnitsTime,
                   const QString &string) const;

  FormatsDate m_formatsDate;
  FormatsTime m_formatsTime;
};

#endif // FORMAT_DATE_TIME_H
