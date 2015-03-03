#ifndef GRID_COORD_DISABLE_H
#define GRID_COORD_DISABLE_H

#include <QString>

enum GridCoordDisable {
  GRID_COORD_DISABLE_COUNT,
  GRID_COORD_DISABLE_START,
  GRID_COORD_DISABLE_STEP,
  GRID_COORD_DISABLE_STOP
};

extern QString gridCoordDisableToString (GridCoordDisable gridCoordDisable);

#endif // GRID_COORD_DISABLE_H
