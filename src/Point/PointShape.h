#ifndef POINT_SHAPE_H
#define POINT_SHAPE_H

#include <QString>

enum PointShape {
  POINT_SHAPE_CIRCLE,
  POINT_SHAPE_CROSS,
  POINT_SHAPE_DIAMOND,
  POINT_SHAPE_SQUARE,
  POINT_SHAPE_TRIANGLE,
  POINT_SHAPE_X
};

extern QString pointShapeToString (PointShape pointShape);

#endif // POINT_SHAPE_H
