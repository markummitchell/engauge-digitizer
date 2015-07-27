#include "CoordUnitsNonPolarTheta.h"

const QString POLAR_UNITS_DEGREES_MINUTES_SECONDS = QString("Degrees Minutes Seconds (DDD") + QChar(0260) +
                                                    QString(" MM") + QChar(0x2032) +
                                                    QString(" SS.S") + QChar(0x2033) + QString(")");

QString coordUnitsDateToString (CoordUnitsDate coordUnits)
{
  switch (coordUnits) {
    case COORD_UNITS_DATE_DAY_MONTH_YEAR:
      return "DD/MM/YY";

    case COORD_UNITS_DATE_MONTH_DAY_YEAR:
      return "MM/DD/YY";

    case COORD_UNITS_DATE_YEAR_MONTH_DAY:
      return "YYYY/MM/DD";

    case COORD_UNITS_DATE_SKIP:
      return "";

    default:
      return "unknown";
  }
}

QString coordUnitsTimeToString (CoordUnitsTime coordUnits)
{
  switch (coordUnits) {
    case COORD_UNITS_TIME_HOUR_MINUTE:
      return "HH:MM";

    case COORD_UNITS_TIME_HOUR_MINUTE_PM:
      return "HH:MM PM";

    case COORD_UNITS_TIME_HOUR_MINUTE_SECOND:
      return "HH:MM:SS";

    case COORD_UNITS_TIME_HOUR_MINUTE_SECOND_PM:
      return "HH:MM:SS PM";

    case COORD_UNITS_DATE_SKIP:
      return "";

    default:
      return "unknown";
  }
}

QString coordUnitsNonPolarThetaToString (CoordUnitsNonPolarTheta coordUnits)
{
  switch (coordUnits) {

  case COORD_UNITS_NON_POLAR_THETA_DATE_TIME:
    return "Date/Time";
    
  case COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS:
    return POLAR_UNITS_DEGREES_MINUTES_SECONDS;
    
  case COORD_UNITS_NON_POLAR_THETA_NUMBER:
    return "Number";

  default:
    return "Unknown";
  }
}
