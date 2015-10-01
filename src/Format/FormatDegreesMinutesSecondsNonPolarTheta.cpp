#include "CoordSymbol.h"
#include "EngaugeAssert.h"
#include "FormatDegreesMinutesSecondsNonPolarTheta.h"
#include "Logger.h"
#include <qmath.h>
#include <QRegExp>
#include <QStringList>

const int DECIMAL_TO_MINUTES = 60.0;
const int DECIMAL_TO_SECONDS = 60.0;

FormatDegreesMinutesSecondsNonPolarTheta::FormatDegreesMinutesSecondsNonPolarTheta()
{
}

QString FormatDegreesMinutesSecondsNonPolarTheta::formatOutput (CoordUnitsNonPolarTheta coordUnits,
                                                                double value,
                                                                bool isNsHemisphere) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatDegreesMinutesSecondsNonPolarTheta::formatOutput";

  // See if similar method with hemisphere argument should have been called
  ENGAUGE_ASSERT (coordUnits != COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW);

  switch (coordUnits) {
    case COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS:
      return formatOutputDegreesMinutesSeconds (value);

    case COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW:
      return formatOutputDegreesMinutesSecondsNsew (value,
                                                    isNsHemisphere);

    default:
      break;
  }

  LOG4CPP_ERROR_S ((*mainCat)) << "FormatDegreesMinutesSecondsNonPolarTheta::formatOutput";
  ENGAUGE_ASSERT (false);
  return "";
}

