#ifndef EXPORT_POINTS_SELECTION_RELATIONS_H
#define EXPORT_POINTS_SELECTION_RELATIONS_H

#include <QString>

enum ExportPointsSelectionRelations {
  EXPORT_POINTS_SELECTION_RELATIONS_INTERPOLATE,
  EXPORT_POINTS_SELECTION_RELATIONS_RAW
};

extern QString exportPointsSelectionRelationsToString (ExportPointsSelectionRelations exportPointsSelectionRelations);

#endif // EXPORT_POINTS_SELECTION_RELATIONS_H
