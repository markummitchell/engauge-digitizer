/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CoordSymbol.h"
#include "FormatDegreesMinutesSecondsBase.h"
#include "Logger.h"
#include <QDoubleValidator>
#include <qmath.h>
#include <QRegExp>
#include <QStringList>
#include <QValidator>

const double DEGREES_TO_MINUTES = 60.0;
const double MINUTES_TO_SECONDS = 60.0;
const double DEGREES_TO_SECONDS = DEGREES_TO_MINUTES * MINUTES_TO_SECONDS;
const double MINUTES_TO_DEGREES = 1.0 / DEGREES_TO_MINUTES;
const double SECONDS_TO_DEGREES = 1.0 / (DEGREES_TO_MINUTES * MINUTES_TO_SECONDS);

FormatDegreesMinutesSecondsBase::FormatDegreesMinutesSecondsBase()
{
}

FormatDegreesMinutesSecondsBase::~FormatDegreesMinutesSecondsBase()
{
}

QString FormatDegreesMinutesSecondsBase::formatOutputDegreesMinutesSeconds (double value) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatDegreesMinutesSecondsBase::formatOutputDegreesMinutesSeconds"
                              << " value=" << value;

  // Only smallest resolution value is floating point
  bool negative = (value < 0);
  value = qAbs (value);
  int degrees = qFloor (value);
  value -= degrees;
  int minutes = qFloor (value * DEGREES_TO_MINUTES);
  value -= minutes * MINUTES_TO_DEGREES;
  double seconds = value * DEGREES_TO_SECONDS;
  degrees *= (negative ? -1.0 : 1.0);

  return QString ("%1%2 %3%4 %5%6")
    .arg (degrees)
    .arg (QChar (COORD_SYMBOL_DEGREES))
    .arg (minutes)
    .arg (QChar (COORD_SYMBOL_MINUTES_PRIME))
    .arg (seconds)
    .arg (QChar (COORD_SYMBOL_SECONDS_DOUBLE_PRIME));
}

QString FormatDegreesMinutesSecondsBase::formatOutputDegreesMinutesSecondsNsew (double value,
                                                                                bool isNsHemisphere) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatDegreesMinutesSecondsBase::formatOutputDegreesMinutesSecondsNsew"
                              << " value=" << value
                              << " isNsHemisphere=" << (isNsHemisphere ? "true" : "false");

  // Only smallest resolution value is floating point
  bool negative = (value < 0);
  value = qAbs (value);
  int degrees = qFloor (value);
  value -= degrees;
  int minutes = qFloor (value * DEGREES_TO_MINUTES);
  value -= minutes * MINUTES_TO_DEGREES;
  double seconds = value * DEGREES_TO_SECONDS;

  QString hemisphere;
  if (isNsHemisphere) {
    hemisphere = (negative ? "S" : "N");
  } else {
    hemisphere = (negative ? "W" : "E");
  }

  return QString ("%1%2 %3%4 %5%6 %7")
    .arg (degrees)
    .arg (QChar (COORD_SYMBOL_DEGREES))
    .arg (minutes)
    .arg (QChar (COORD_SYMBOL_MINUTES_PRIME))
    .arg (seconds)
    .arg (QChar (COORD_SYMBOL_SECONDS_DOUBLE_PRIME))
    .arg (hemisphere);
}

QValidator::State FormatDegreesMinutesSecondsBase::parseInput (const QString &stringUntrimmed,
                                                               double &value) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatDegreesMinutesSecondsBase::parseInput"
                              << " string=" << stringUntrimmed.toLatin1().data();

  const QString string = stringUntrimmed.trimmed ();

  if (string.isEmpty()) {

    return QValidator::Intermediate;
  }

  // Split on spaces
  QStringList fields = string.split (QRegExp ("\\s+"),
                                     QString::SkipEmptyParts);

  QString field0, field1, field2; // Degrees, minutes and seconds components
  if (fields.count() == 0) {
    return QValidator::Invalid; // Empty
  } else {
    field0 = fields.at(0);
    if (fields.count() > 1) {
      field1 = fields.at(1);
      if (fields.count() > 2) {
        field2 = fields.at(2);
        if (fields.count() > 3) {
          return QValidator::Invalid; // Too many values
        }
      }
    }
  }
  
  stripSymbols (field0,
                field1,
                field2);

  int pos;

  // Validators
  QDoubleValidator valDegrees;
  QDoubleValidator valMinutesOrSeconds;
  valMinutesOrSeconds.setBottom (0);

  double valueDegrees = 0, valueMinutes = 0, valueSeconds = 0;

  // Required degrees
  QValidator::State state = valDegrees.validate (field0,
                                                 pos);
  if (state == QValidator::Acceptable) {

    valueDegrees = field0.toDouble();
    
    if (fields.count() > 1) {

      // Optional minutes
      state = valMinutesOrSeconds.validate (field1,
                                            pos);
      if (state == QValidator::Acceptable) {

        valueMinutes = field1.toDouble();

        if (fields.count() > 2) {
          
          // Optional seconds
          state = valMinutesOrSeconds.validate (field2,
                                                pos);
          if (state == QValidator::Acceptable) {

            valueSeconds = field2.toDouble();

          }
        }
      }
    }
  }

  if (state == QValidator::Acceptable) {
    if (valueDegrees < 0) {

      // Apply the negative sign on the degrees components to minutes and seconds components also
      value = valueDegrees - valueMinutes * MINUTES_TO_DEGREES - valueSeconds * SECONDS_TO_DEGREES;
      
    } else {
      
      // All components are positive
      value = valueDegrees + valueMinutes * MINUTES_TO_DEGREES + valueSeconds * SECONDS_TO_DEGREES;
      
    }
  }

  return state;
}

void FormatDegreesMinutesSecondsBase::stripSymbols (QString &field0,
                                                    QString &field1,
                                                    QString &field2) const
{
  const int FIELD_WIDTH = 0, BASE_8 = 8, BASE_16 = 16;

  // Clean up degrees symbols (167 or 248 in base 10 which are 247 and 370 in base 8) and single quotes
  QString strExpDegrees = QString (".*\\0%1$")
                          .arg (COORD_SYMBOL_DEGREES, FIELD_WIDTH, BASE_8);

  QRegExp regExpDegrees (strExpDegrees);

  if (regExpDegrees.exactMatch (field0)) {
    field0 = field0.left (field0.count() - 1);
  }

  // Clean up minutes
  QString strExpMinutes = QString (".*[\\0%1\\x%2]$")
      .arg (COORD_SYMBOL_MINUTES_APOSTROPHE, FIELD_WIDTH, BASE_8)
      .arg (COORD_SYMBOL_MINUTES_PRIME, FIELD_WIDTH, BASE_16);

  QRegExp regExpMinutes (strExpMinutes);

  if (regExpMinutes.exactMatch (field1)) {
    field1 = field1.left (field1.count() - 1);
  }

  // Clean up seconds
  QString strExpSeconds1Char = QString (".*[\\x%1\\x%2]$")
      .arg (COORD_SYMBOL_SECONDS_DOUBLE_PRIME, FIELD_WIDTH, BASE_16)
      .arg (COORD_SYMBOL_SECONDS_QUOTATIONS, FIELD_WIDTH, BASE_16);
  QString strExpSeconds2Chars = QString (".*\\0%1\\0%2$")
      .arg (COORD_SYMBOL_MINUTES_PRIME, FIELD_WIDTH, BASE_8)
      .arg (COORD_SYMBOL_MINUTES_PRIME, FIELD_WIDTH, BASE_8);

  QRegExp regExpSeconds1Char (strExpSeconds1Char), regExpSeconds2Chars (strExpSeconds2Chars);

  if (regExpSeconds1Char.exactMatch (field2)) {
    field2 = field2.left (field2.count() - 1);
  }
  if (regExpSeconds2Chars.exactMatch (field2)) {
    field2 = field2.left (field2.count() - 2);
  }
}
