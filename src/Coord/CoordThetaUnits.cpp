#include "CoordThetaUnits.h"

const QChar THETA (QChar(0x98, 0x03));

const QString POLAR_UNITS_DEGREES = QString("Degrees (DDD.DDDDD") + QChar(0260) + QString (")");
const QString POLAR_UNITS_DEGREES_MINUTES = QString("Degrees Minutes (DDD") + QChar(0260) +
                                            QString(" MM.MMM") + QChar(0x2032) +
                                            QString(")");
const QString POLAR_UNITS_DEGREES_MINUTES_SECONDS = QString("Degrees Minutes Seconds (DDD") + QChar(0260) +
                                                    QString(" MM") + QChar(0x2032) +
                                                    QString(" SS.S") + QChar(0x2033) + QString(")");
const QString POLAR_UNITS_GRADIANS = "Gradians";
const QString POLAR_UNITS_RADIANS = "Radians";
const QString POLAR_UNITS_TURNS = "Turns";

QString coordThetaUnitsToString (CoordThetaUnits coordThetaUnits)
{
  switch (coordThetaUnits) {
    case COORD_THETA_UNITS_DEGREES:
      return POLAR_UNITS_DEGREES;

    case COORD_THETA_UNITS_DEGREES_MINUTES:
      return POLAR_UNITS_DEGREES_MINUTES;

    case COORD_THETA_UNITS_DEGREES_MINUTES_SECONDS:
      return POLAR_UNITS_DEGREES_MINUTES_SECONDS;

    case COORD_THETA_UNITS_GRADIANS:
      return POLAR_UNITS_GRADIANS;

    case COORD_THETA_UNITS_RADIANS:
      return POLAR_UNITS_RADIANS;

    case COORD_THETA_UNITS_TURNS:
      return POLAR_UNITS_TURNS;

    default:
      return "Unknown";
  }
}
