#include "CoordSymbol.h"
#include "EngaugeAssert.h"
#include "FormatDegreesMinutesSecondsPolarTheta.h"
#include "Logger.h"
#include <qmath.h>
#include <QRegExp>
#include <QStringList>

const int DECIMAL_TO_MINUTES = 60.0;
const int DECIMAL_TO_SECONDS = 60.0;

FormatDegreesMinutesSecondsPolarTheta::FormatDegreesMinutesSecondsPolarTheta()
{
}

QString FormatDegreesMinutesSecondsPolarTheta::formatOutput (CoordUnitsPolarTheta coordUnits,
                                                             double value,
                                                             bool isNsHemisphere) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatDegreesMinutesSecondsPolarTheta::formatOutput";

  // See if similar method with hemisphere argument should have been called
  ENGAUGE_ASSERT (coordUnits != COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW);

  switch (coordUnits) {
    case COORD_UNITS_POLAR_THETA_DEGREES:
      return formatOutputDegrees (value);

    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES:
      return formatOutputDegreesMinutes (value);

    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS:
      return formatOutputDegreesMinutesSeconds (value);

    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW:
      return formatOutputDegreesMinutesSecondsNsew (value,
                                                    isNsHemisphere);

    default:
      break;
  }

  LOG4CPP_ERROR_S ((*mainCat)) << "FormatDegreesMinutesSecondsPolarTheta::formatOutput";
  ENGAUGE_ASSERT (false);

  return "";
}

QString FormatDegreesMinutesSecondsPolarTheta::formatOutputDegrees (double value) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatDegreesMinutesSecondsPolarTheta::formatOutputDegrees";

  // Even for just degrees we include the degrees symbol since user would have picked regular numbers if that symbol was unwanted
  return QString ("%1%2")
           .arg (value)
           .arg (QChar (COORD_SYMBOL_DEGREES));
}

QString FormatDegreesMinutesSecondsPolarTheta::formatOutputDegreesMinutes (double value) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatDegreesMinutesSecondsPolarTheta::formatOutputDegreesMinutes";

  // Only smallest resolution value is floating point
  bool negative = (value < 0);
  value = qAbs (value);
  int degrees = qFloor (value);
  value -= degrees;
  double minutes = value * DECIMAL_TO_MINUTES;
  degrees *= (negative ? -1.0 : 1.0);

  return QString ("%1%2 %3%4")
    .arg (degrees)
    .arg (QChar (COORD_SYMBOL_DEGREES))
    .arg (minutes)
    .arg (QChar (COORD_SYMBOL_MINUTES_PRIME));
}
