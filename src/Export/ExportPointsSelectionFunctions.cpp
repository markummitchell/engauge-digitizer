#include "ExportPointsSelectionFunctions.h"

QString exportPointsSelectionFunctionsToString (ExportPointsSelectionFunctions exportPointsSelectionFunctions)
{
  switch (exportPointsSelectionFunctions) {
    case EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_ALL_CURVES:
      return "InterpolateAllCurves";

    case EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_FIRST_CURVE:
      return "InterpolateFirstCurve";

    case EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_PERIODIC:
      return "InterpolatePeriodic";

    case EXPORT_POINTS_SELECTION_FUNCTIONS_RAW:
      return "Raw";

    default:
      return "Unknown";
  }
}
