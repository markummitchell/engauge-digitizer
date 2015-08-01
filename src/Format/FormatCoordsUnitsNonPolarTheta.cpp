#include "EngaugeAssert.h"
#include "FormatCoordsUnitsNonPolarTheta.h"
#include "FormatDateTime.h"
#include "FormatDegreesMinutesSecondsNonPolarTheta.h"
#include "Logger.h"

FormatCoordsUnitsNonPolarTheta::FormatCoordsUnitsNonPolarTheta ()
{
}

double FormatCoordsUnitsNonPolarTheta::formattedToUnformatted (const QString &string,
                                                               CoordUnitsNonPolarTheta coordUnits,
                                                               CoordUnitsDate coordUnitsDate,
                                                               CoordUnitsTime coordUnitsTime,
                                                               bool isXTheta) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatCoordsUnitsNonPolarTheta::formattedToUnformatted";

  return 0.0;
}

QString FormatCoordsUnitsNonPolarTheta::unformattedToFormatted (const double *initialValue,
                                                                CoordUnitsNonPolarTheta coordUnits,
                                                                CoordUnitsDate coordUnitsDate,
                                                                CoordUnitsTime coordUnitsTime,
                                                                bool isXTheta) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatCoordsUnitsNonPolarTheta::unformattedToFormatted";

  QString rtn;

  if (initialValue != 0) {

    switch (coordUnits) {
      case COORD_UNITS_NON_POLAR_THETA_DATE_TIME:
        {
          FormatDateTime format;
          rtn = format.formatOutput (coordUnitsDate,
                                     coordUnitsTime,
                                     *initialValue);
        }
        break;

      case COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS:
      case COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW:
        {
          FormatDegreesMinutesSecondsNonPolarTheta format;
          rtn = format.formatOutput (coordUnits,
                                     *initialValue,
                                     isXTheta);
        }
        break;

      case COORD_UNITS_NON_POLAR_THETA_NUMBER:
        rtn = QString::number (*initialValue);
        break;

      default:
        LOG4CPP_ERROR_S ((*mainCat)) << "FormatCoordsUnitsNonPolarTheta::unformattedToFormatted";
        ENGAUGE_ASSERT (false);
        break;
    }
  }

  return rtn;
}
