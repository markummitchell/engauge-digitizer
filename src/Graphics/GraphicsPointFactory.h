#ifndef GRAPHICS_POINT_FACTORY_H
#define GRAPHICS_POINT_FACTORY_H

#include "PointShape.h"

class GraphicsPointAbstractBase;
class PointStyle;
class QPointF;

/// Factor for generating GraphicsPointAbstractBase class objects.
class GraphicsPointFactory
{
public:
  /// Single constructor.
  GraphicsPointFactory();

  /// Create circle or polygon point according to the PointStyle.
  GraphicsPointAbstractBase *createPoint (const QString &identifier,
                                          const QPointF &posScreen,
                                          const PointStyle &pointStyle,
                                          int ordinal);
};

#endif // GRAPHICS_POINT_FACTORY_H
