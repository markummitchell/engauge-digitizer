#include "ExportPointsSelectionRelations.h"
#include <QObject>

extern QString exportPointsSelectionRelationsToString(
    ExportPointsSelectionRelations exportPointsSelectionRelations) {
  switch (exportPointsSelectionRelations) {
  case EXPORT_POINTS_SELECTION_RELATIONS_INTERPOLATE:
    return QObject::tr("Interpolate");

  case EXPORT_POINTS_SELECTION_RELATIONS_RAW:
    return QObject::tr("Raw");

  default:
    return QObject::tr("Unknown");
  }
}
