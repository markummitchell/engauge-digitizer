/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DocumentModelGeneral.h"
#include "EngaugeAssert.h"
#include "FormatCoordsUnitsStrategyPolarTheta.h"
#include "FormatDegreesMinutesSecondsPolarTheta.h"
#include "Logger.h"
#include <QLocale>

FormatCoordsUnitsStrategyPolarTheta::FormatCoordsUnitsStrategyPolarTheta ()
{
}

double FormatCoordsUnitsStrategyPolarTheta::formattedToUnformatted (const QString &string,
                                                                    const QLocale &locale,
                                                                    CoordUnitsPolarTheta coordUnits) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "FormatCoordsUnitsStrategyPolarTheta::formattedToUnformatted";

  double value;

  switch (coordUnits) {
    case COORD_UNITS_POLAR_THETA_DEGREES:
    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES:
    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS:
    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW:
      {
        FormatDegreesMinutesSecondsPolarTheta format;
        ENGAUGE_ASSERT (format.parseInput (string,
                                           value) == QValidator::Acceptable);
      }
      break;

    case COORD_UNITS_POLAR_THETA_GRADIANS:
    case COORD_UNITS_POLAR_THETA_RADIANS:
    case COORD_UNITS_POLAR_THETA_TURNS:
      value = locale.toDouble (string);
      break;

    default:
      LOG4CPP_ERROR_S ((*mainCat)) << "FormatCoordsUnitsStrategyPolarTheta::unformattedToFormattedStrategyPolarTheta";
      ENGAUGE_ASSERT (false);
      break;
  }

  return value;
}

QString FormatCoordsUnitsStrategyPolarTheta::unformattedToFormatted (double valueUnformatted,
                                                                     const QLocale &locale,
                                                                     CoordUnitsPolarTheta coordUnits,
                                                                     const DocumentModelGeneral &modelGeneral,
                                                                     const Transformation &transformation,
                                                                     double valueUnformattedOther) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "FormatCoordsUnitsStrategyPolarTheta::unformattedToFormatted";

  const char FORMAT ('g');
  const bool IS_X_THETA = true;

  QString valueFormatted;

  switch (coordUnits) {
    case COORD_UNITS_POLAR_THETA_DEGREES:
    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES:
    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS:
    case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW:
      {
        FormatDegreesMinutesSecondsPolarTheta format;
        valueFormatted = format.formatOutput (coordUnits,
                                              valueUnformatted,
                                              IS_X_THETA);
      }
      break;

    case COORD_UNITS_POLAR_THETA_GRADIANS:
    case COORD_UNITS_POLAR_THETA_RADIANS:
    case COORD_UNITS_POLAR_THETA_TURNS:
      valueFormatted = locale.toString (valueUnformatted,
                                        FORMAT,
                                        precisionDigitsForRawNumber (valueUnformatted,
                                                                     valueUnformattedOther,
                                                                     IS_X_THETA,
                                                                     modelGeneral,
                                                                     transformation));
      break;

    default:
      LOG4CPP_ERROR_S ((*mainCat)) << "FormatCoordsUnitsStrategyPolarTheta::unformattedToFormattedStrategyPolarTheta";
      ENGAUGE_ASSERT (false);
      break;
  }

  return valueFormatted;
}
