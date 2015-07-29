#include "CoordUnitsTime.h"

QString coordUnitsTimeToString (CoordUnitsTime coordUnits)
{
  switch (coordUnits) {
    case COORD_UNITS_TIME_HOUR_MINUTE:
      return "HH:MM";

    case COORD_UNITS_TIME_HOUR_MINUTE_SECOND:
      return "HH:MM:SS";

    case COORD_UNITS_TIME_SKIP:
      return "";

    default:
      return "unknown";
  }
}
