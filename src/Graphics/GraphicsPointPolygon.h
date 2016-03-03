#ifndef GRAPHICS_POINT_POLYGON_H
#define GRAPHICS_POINT_POLYGON_H

#include <QGraphicsPolygonItem>
#include <QPointF>

class GraphicsPoint;

/// This class add event handling to QGraphicsPolygonItem
class GraphicsPointPolygon : public QGraphicsPolygonItem {
public:
  /// Single constructor
  GraphicsPointPolygon(GraphicsPoint &graphicsPoint, const QPolygonF &polygon);

  /// Intercept moves by dragging so moved items can be identified. This
  /// replaces unreliable hit tests.
  QVariant itemChange(GraphicsItemChange change, const QVariant &value);

  /// Update the radius
  void setRadius(int radius);

private:
  GraphicsPointPolygon();

  // Reference to the GraphicsPoint that this class belongs to
  GraphicsPoint &m_graphicsPoint;
};

#endif // GRAPHICS_POINT_POLYGON_H
