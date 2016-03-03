#include "CoordUnitsTime.h"
#include <QObject>

QString coordUnitsTimeToString(CoordUnitsTime coordUnits) {
  switch (coordUnits) {
  case COORD_UNITS_TIME_HOUR_MINUTE:
    return QObject::tr("HH:MM");

  case COORD_UNITS_TIME_HOUR_MINUTE_SECOND:
    return QObject::tr("HH:MM:SS");

  case COORD_UNITS_TIME_SKIP:
    return "";

  default:
    return QObject::tr("unknown");
  }
}
