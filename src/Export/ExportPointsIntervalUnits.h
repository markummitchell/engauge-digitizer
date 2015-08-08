#ifndef EXPORT_POINTS_INTERVAL_UNITS_H
#define EXPORT_POINTS_INTERVAL_UNITS_H

#include <QString>

enum ExportPointsIntervalUnits {
  EXPORT_POINTS_INTERVAL_UNITS_GRAPH,
  EXPORT_POINTS_INTERVAL_UNITS_PIXELS
};

extern QString exportPointsIntervalUnitsToString (ExportPointsIntervalUnits exportPointsIntervalUnits);

#endif // EXPORT_POINTS_INTERVAL_UNITS_H
