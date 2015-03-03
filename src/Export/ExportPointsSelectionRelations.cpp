#include "ExportPointsSelectionRelations.h"

extern QString exportPointsSelectionRelationsToString (ExportPointsSelectionRelations exportPointsSelectionRelations)
{
  switch (exportPointsSelectionRelations) {
    case EXPORT_POINTS_SELECTION_RELATIONS_INTERPOLATE:
      return "Interpolate";

    case EXPORT_POINTS_SELECTION_RELATIONS_RAW:
      return "Raw";

    default:
      return "Unknown";
  }
}
