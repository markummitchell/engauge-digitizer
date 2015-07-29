#include "FormatDegreesMinutesSeconds.h"
#include <QDoubleValidator>
#include <QRegExp>
#include <QStringList>

FormatDegreesMinutesSeconds::FormatDegreesMinutesSeconds()
{
}

double FormatDegreesMinutesSeconds::parse (const QString &string,
                                           bool &success) const
{
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

