#include "MigrateToVersion6.h"

MigrateToVersion6::MigrateToVersion6 ()
{
}

ColorPalette MigrateToVersion6::colorPalette (int preVersion6) const
{
  switch (preVersion6) {
    case 0:
      return COLOR_PALETTE_BLACK;

    case 1:
      return COLOR_PALETTE_BLUE;

    case 2:
      return COLOR_PALETTE_CYAN;

    case 3:
      return COLOR_PALETTE_GOLD;

    case 4:
      return COLOR_PALETTE_GREEN;

    case 5:
      return COLOR_PALETTE_MAGENTA;

    case 6:
      return COLOR_PALETTE_RED;

    case 7:
      return COLOR_PALETTE_TRANSPARENT;

    case 8:
      return COLOR_PALETTE_YELLOW;

    default:
      return COLOR_PALETTE_BLACK;
  }
}

CurveConnectAs MigrateToVersion6::curveConnectAs (int preVersion6) const
{
  switch (preVersion6) {
    case 0:
      return CONNECT_AS_FUNCTION_STRAIGHT;

    case 1:
      return CONNECT_AS_RELATION_STRAIGHT;

    default:
      return CONNECT_AS_FUNCTION_STRAIGHT;
  }
}

PointShape MigrateToVersion6::pointShape (int preVersion6) const
{
  switch (preVersion6) {
    case 0:
      return POINT_SHAPE_CROSS;

    case 1:
      return POINT_SHAPE_X;

    case 2:
      return POINT_SHAPE_DIAMOND;

    case 3:
      return POINT_SHAPE_SQUARE;

    case 4:
      return POINT_SHAPE_TRIANGLE;

    default:
      return POINT_SHAPE_CROSS;
  }
}

int MigrateToVersion6::pointRadius (int preVersion6) const
{
  // From pointsetstyles.h
  return 2 * (preVersion6 + 1);
}
