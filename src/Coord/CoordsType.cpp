#include "CoordsType.h"

QString coordsTypeToString (CoordsType coordsType)
{
  switch (coordsType) {
    case COORDS_TYPE_CARTESIAN:
      return "Cartesian";

     case COORDS_TYPE_POLAR:
      return "Polar";

    default:
      return "Unknown";
  }
}
