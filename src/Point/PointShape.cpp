#include "PointShape.h"

QString pointShapeToString (PointShape pointShape)
{
  switch (pointShape) {
    case POINT_SHAPE_CIRCLE:
      return "Circle";

    case POINT_SHAPE_CROSS:
      return "Cross";

    case POINT_SHAPE_DIAMOND:
      return "Diamond";

    case POINT_SHAPE_SQUARE:
      return "Square";

    case POINT_SHAPE_TRIANGLE:
      return "Triangle";

    case POINT_SHAPE_X:
      return "X";

    default:
      return "Unknown";
  }
}
