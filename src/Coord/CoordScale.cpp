#include "CoordScale.h"

QString coordScaleToString (CoordScale coordScale)
{
  switch (coordScale) {
    case COORD_SCALE_LINEAR:
      return "Linear";

    case COORD_SCALE_LOG:
      return "Log";

    default:
      return "Unknown";
  }
}
