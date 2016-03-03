#include "GridCoordDisable.h"
#include <QObject>

QString gridCoordDisableToString(GridCoordDisable gridCoordDisable) {
  switch (gridCoordDisable) {
  case GRID_COORD_DISABLE_COUNT:
    return QObject::tr("Count");

  case GRID_COORD_DISABLE_START:
    return QObject::tr("Start");

  case GRID_COORD_DISABLE_STEP:
    return QObject::tr("Step");

  case GRID_COORD_DISABLE_STOP:
    return QObject::tr("Stop");

  default:
    return QObject::tr("Unknown");
  }
}
