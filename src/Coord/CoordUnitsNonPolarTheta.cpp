#include "CoordUnitsNonPolarTheta.h"

const QString POLAR_UNITS_DEGREES_MINUTES_SECONDS = QString("Degrees Minutes Seconds (DDD") + QChar(0260) +
                                                    QString(" MM") + QChar(0x2032) +
                                                    QString(" SS.S") + QChar(0x2033) + QString(")");

QString coordUnitsNonPolarThetaToString (CoordUnitsNonPolarTheta coordUnitsNonPolarTheta)
{
  switch (coordUnitsNonPolarTheta) {

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
