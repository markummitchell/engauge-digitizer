#ifndef GRAPHICS_POINT_FACTORY_H
#define GRAPHICS_POINT_FACTORY_H

#include "PointShape.h"

class GraphicsPoint;
class PointStyle;
class QGraphicsScene;
class QPointF;

/// Factor for generating GraphicsPointAbstractBase class objects.
class GraphicsPointFactory
{
public:
  /// Single constructor.
  GraphicsPointFactory();

  /// Create circle or polygon point according to the PointStyle.
  GraphicsPoint *createPoint (QGraphicsScene &scene,
                              const QString &identifier,
                              const QPointF &posScreen,
                              const PointStyle &pointStyle);
};

#endif // GRAPHICS_POINT_FACTORY_H
