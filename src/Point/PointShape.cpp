#include "PointShape.h"
#include <QObject>

QString pointShapeToString(PointShape pointShape) {
  switch (pointShape) {
  case POINT_SHAPE_CIRCLE:
    return QObject::tr("Circle");

  case POINT_SHAPE_CROSS:
    return QObject::tr("Cross");

  case POINT_SHAPE_DIAMOND:
    return QObject::tr("Diamond");

  case POINT_SHAPE_SQUARE:
    return QObject::tr("Square");

  case POINT_SHAPE_TRIANGLE:
    return QObject::tr("Triangle");

  case POINT_SHAPE_X:
    return QObject::tr("X");

  default:
    return QObject::tr("Unknown");
  }
}
