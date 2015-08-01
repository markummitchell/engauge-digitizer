#include "EngaugeAssert.h"
#include "FormatCoordsUnitsPolarTheta.h"
#include "FormatDegreesMinutesSecondsPolarTheta.h"
#include "Logger.h"

FormatCoordsUnitsPolarTheta::FormatCoordsUnitsPolarTheta ()
{
}

double FormatCoordsUnitsPolarTheta::formattedToUnformatted (const QString &string,
                                                            CoordUnitsPolarTheta coordUnits) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatCoordsUnitsPolarTheta::formattedToUnformatted";

  return 0.0;
}

QString FormatCoordsUnitsPolarTheta::unformattedToFormatted (const double *initialValue,
                                                             CoordUnitsPolarTheta coordUnits) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatCoordsUnitsPolarTheta::unformattedToFormatted";

  const bool IS_X_THETA = true;

  QString rtn;

  if (initialValue != 0) {

    switch (coordUnits) {
      case COORD_UNITS_POLAR_THETA_DEGREES:
      case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES:
      case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS:
      case COORD_UNITS_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW:
        {
          FormatDegreesMinutesSecondsPolarTheta format;
          rtn = format.formatOutput (coordUnits,
                                     *initialValue,
                                     IS_X_THETA);
        }
        break;

      case COORD_UNITS_POLAR_THETA_GRADIANS:
      case COORD_UNITS_POLAR_THETA_RADIANS:
      case COORD_UNITS_POLAR_THETA_TURNS:
        rtn = QString::number (*initialValue);
        break;

      default:
        LOG4CPP_ERROR_S ((*mainCat)) << "FormatCoordsUnitsPolarTheta::unformattedToFormattedPolarTheta";
        ENGAUGE_ASSERT (false);
        break;
    }
  }

  return rtn;
}
