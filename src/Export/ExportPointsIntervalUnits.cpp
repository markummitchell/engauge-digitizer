#include "ExportPointsIntervalUnits.h"

QString exportPointsIntervalUnitsToString (ExportPointsIntervalUnits exportPointsIntervalUnits)
{
  switch (exportPointsIntervalUnits) {
  case EXPORT_POINTS_INTERVAL_UNITS_GRAPH:
    return "Graph Units";

  case EXPORT_POINTS_INTERVAL_UNITS_SCREEN:
    return "Pixels";

  default:
    return "Unknown";
  }
}
