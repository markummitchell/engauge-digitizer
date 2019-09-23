/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CoordSymbol.h"
#include "EngaugeAssert.h"
#include "FormatDegreesMinutesSecondsPolarTheta.h"
#include "Logger.h"
#include <qmath.h>
#include <QRegExp>
#include <QStringList>

const int DECIMAL_TO_MINUTES = 60.0;

FormatDegreesMinutesSecondsPolarTheta::FormatDegreesMinutesSecondsPolarTheta()
{
}

QString FormatDegreesMinutesSecondsPolarTheta::formatOutput (CoordUnitsPolarTheta coordUnits,
                                                             double value,
                                                             bool isNsHemisphere) const
{
  //LOG4CPP_INFO_S ((*mainCat)) << "FormatDegreesMinutesSecondsPolarTheta::formatOutput";

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
  //LOG4CPP_INFO_S ((*mainCat)) << "FormatDegreesMinutesSecondsPolarTheta::formatOutputDegrees";

  // Since version 6 there has been no number-only option (=without degrees symbol) for theta in CoordUnitsPolarTheta.
  // The degrees symbol causes more problems than it is worth for COORD_UNITS_POLAR_THETA_DEGREES, so we output only
  // the number and skip the degrees symbol here
  return QString ("%1")
           .arg (value);
}

QString FormatDegreesMinutesSecondsPolarTheta::formatOutputDegreesMinutes (double value) const
{
  //LOG4CPP_INFO_S ((*mainCat)) << "FormatDegreesMinutesSecondsPolarTheta::formatOutputDegreesMinutes";

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
