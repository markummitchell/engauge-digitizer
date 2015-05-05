#ifndef GRAPHICS_POINT_ELLIPSE_H
#define GRAPHICS_POINT_ELLIPSE_H

#include <QGraphicsEllipseItem>
#include <QPointF>

class GraphicsPoint;

/// This class add event handling to QGraphicsEllipseItem
class GraphicsPointEllipse : public QGraphicsEllipseItem
{
public:
  /// Single constructor
  GraphicsPointEllipse(GraphicsPoint &graphicsPoint,
                       const QRect &rect);

  /// Intercept moves by dragging so moved items can be identified. This replaces unreliable hit tests.
  QVariant itemChange(GraphicsItemChange change, const QVariant &value);
  /// Update the radius
  void setRadius(int radius);

private:
  GraphicsPointEllipse();

  // Reference to the GraphicsPoint that this class belongs to
  GraphicsPoint &m_graphicsPoint;
};

#endif // GRAPHICS_POINT_ELLIPSE_H
