#include "ExportPointsIntervalUnits.h"
#include <QObject>

QString exportPointsIntervalUnitsToString (ExportPointsIntervalUnits exportPointsIntervalUnits)
{
  switch (exportPointsIntervalUnits) {
  case EXPORT_POINTS_INTERVAL_UNITS_GRAPH:
    return QObject::tr ("Graph Units");

  case EXPORT_POINTS_INTERVAL_UNITS_SCREEN:
    return QObject::tr ("Pixels");

  default:
    return QObject::tr ("Unknown");
  }
}
