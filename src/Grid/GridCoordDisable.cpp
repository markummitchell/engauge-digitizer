#include "GridCoordDisable.h"

QString gridCoordDisableToString (GridCoordDisable gridCoordDisable)
{
  switch (gridCoordDisable) {
    case GRID_COORD_DISABLE_COUNT:
      return "Count";

    case GRID_COORD_DISABLE_START:
      return "Start";

    case GRID_COORD_DISABLE_STEP:
      return "Step";

    case GRID_COORD_DISABLE_STOP:
      return "Stop";

    default:
      return "Unknown";
  }
}
