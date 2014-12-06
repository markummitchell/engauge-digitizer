#ifndef GRAPHICS_POINT_POLYGON_H
#define GRAPHICS_POINT_POLYGON_H

#include "GraphicsPointAbstractBase.h"
#include <QGraphicsPolygonItem>
#include <QPolygonF>

/// Polygon graphics item for displaying a single Point.
class GraphicsPointPolygon : public GraphicsPointAbstractBase, public QGraphicsPolygonItem
{
public:
  /// Single constructor.
  GraphicsPointPolygon(const QString &identifier,
                       const QPointF &posScreen,
                       const QColor &color,
                       const QPolygonF &polygon);

  /// Intercept moves by dragging so moved items can be identified. This replaces unreliable hit tests.
  QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
  GraphicsPointPolygon();

  QGraphicsPolygonItem *m_shadowZeroWidth; // Shadow item overlays the superclass instance to ensure visibility
};

#endif // GRAPHICS_POINT_POLYGON_H
