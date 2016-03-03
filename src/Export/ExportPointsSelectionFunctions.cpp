#include "ExportPointsSelectionFunctions.h"
#include <QObject>

QString exportPointsSelectionFunctionsToString(
    ExportPointsSelectionFunctions exportPointsSelectionFunctions) {
  switch (exportPointsSelectionFunctions) {
  case EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_ALL_CURVES:
    return QObject::tr("InterpolateAllCurves");

  case EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_FIRST_CURVE:
    return QObject::tr("InterpolateFirstCurve");

  case EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_PERIODIC:
    return QObject::tr("InterpolatePeriodic");

  case EXPORT_POINTS_SELECTION_FUNCTIONS_RAW:
    return QObject::tr("Raw");

  default:
    return QObject::tr("Unknown");
  }
}
