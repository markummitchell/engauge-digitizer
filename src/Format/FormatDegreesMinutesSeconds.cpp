#include "FormatDegreesMinutesSeconds.h"
#include "Logger.h"
#include <QDoubleValidator>
#include <qmath.h>
#include <QRegExp>
#include <QStringList>

const int DECIMAL_TO_MINUTES = 60.0;
const int DECIMAL_TO_SECONDS = 60.0;

FormatDegreesMinutesSeconds::FormatDegreesMinutesSeconds()
{
}

QString FormatDegreesMinutesSeconds::formatOutput (CoordUnitsPolarTheta coordUnits,
                                                   double value) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatDegreesMinutesSeconds::formatOutput";

  QString result;

  switch (coordUnits) {
  case COORD_UNITS_POLAR_THETA_DEGREES:
    {
      // For just degrees, we do not include a degrees symbol since raw numbers are probably much more useful
      result = QString::number (coordUnits);
    }
    break;

  case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES:
    {
      // Only smallest resolution value is floating point
      bool negative = (value < 0);
      value = qAbs (value);
      int degrees = qFloor (value);
      value -= degrees;
      double minutes = value * DECIMAL_TO_MINUTES;
      degrees *= (negative ? -1.0 : 1.0);

      result = QString ("%1\\0247 %2'")
        .arg (degrees)
        .arg (minutes);
    }
    break;

  case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS:
    {
      // Only smallest resolution value is floating point
      bool negative = (value < 0);
      value = qAbs (value);
      int degrees = qFloor (value);
      value -= degrees;
      int minutes = value * DECIMAL_TO_MINUTES;
      value -= minutes;
      double seconds = value * DECIMAL_TO_SECONDS;
      degrees *= (negative ? -1.0 : 1.0);

      result = QString ("%1\\0247 %2' %3''")
        .arg (degrees)
        .arg (minutes)
        .arg (seconds);
    }
    break;
    
  default:
    // Gradians, radians and turns are handled as regular numbers so this class should not have been called
    LOG4CPP_ERROR_S ((*mainCat)) << "FormatDegreesMinutesSeconds::formatOutput";
    exit (-1);
  }
}

double FormatDegreesMinutesSeconds::parseInput (const QString &string,
                                                bool &success) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatDegreesMinutesSeconds::parseInput"
                              << " string=" << string.toLatin1().data();

  // Split on spaces
  QStringList fields = string.split (QRegExp ("\\s+"),
                                     QString::SkipEmptyParts);

  QString field0, field1, field2; // Degrees, minutes and seconds components
  if (fields.count() == 0) {
    return false; // Empty
  } else {
    field0 = fields.at(0);
    if (fields.count() > 1) {
      field1 = fields.at(1);
      if (fields.count() > 2) {
        field2 = fields.at(2);
        if (fields.count() > 3) {
          return false;
        }
      }
    }
  }
  
  // Clean up degrees symbols (167 or 248 in base 10 which are 247 and 370 in base 8) and single quotes
  QRegExp regExpDegrees ("[\\0247\\0370]$");
  if (regExpDegrees.exactMatch (field0)) {
    field0 = field0.left (field0.count() - 1);
  }

  // Clean up single quotes
  QRegExp regExpQuote ("'$"), regExpQuotes ("''$");
  if (regExpQuote.exactMatch (field1)) {
    field1 = field1.left (field1.count() - 1);
  }
  if (regExpQuotes.exactMatch (field2)) {
    field2 = field2.left (field2.count() - 1);
  }

  int pos;

  // Validators
  QDoubleValidator valDegrees;
  QDoubleValidator valMinutesOrSeconds;
  valMinutesOrSeconds.setBottom (0);

  double valueDegrees = 0, valueMinutes = 0, valueSeconds = 0;

  // Required degrees
  success = (valDegrees.validate (field0,
                                  pos) == QValidator::Acceptable);
  if (success) {

    valueDegrees = field0.toDouble();
    
    if (fields.count() > 1) {

      // Optional minutes
      success = (valMinutesOrSeconds.validate (field1,
                                               pos) == QValidator::Acceptable);
      if (success) {

        valueMinutes = field1.toDouble();

        if (fields.count() > 2) {
          
          // Optional seconds
          success = (valMinutesOrSeconds.validate (field2,
                                                   pos) == QValidator::Acceptable);
          if (success) {

            valueSeconds = field2.toDouble();

          }
        }
      }
    }
  }

  if (valueDegrees < 0) {

    // Apply the negative sign on the degrees components to minutes and seconds components also
    return valueDegrees - valueMinutes - valueSeconds;

  } else {

    // All components are positive
    return valueDegrees + valueMinutes + valueSeconds;

  }
}

