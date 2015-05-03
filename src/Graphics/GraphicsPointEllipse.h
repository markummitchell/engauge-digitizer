#ifndef GRAPHICS_POINT_ELLIPSE_H
#define GRAPHICS_POINT_ELLIPSE_H

#include <QGraphicsEllipseItem>
#include <QPointF>

class GraphicsPoint;
class QTextStream;

/// This class add event handling to QGraphicsEllipseItem
class GraphicsPointEllipse : public QGraphicsEllipseItem
{
public:
  /// Single constructor
  GraphicsPointEllipse(GraphicsPoint &graphicsPoint,
                       const QRect &rect);

  /// Intercept moves by dragging so moved items can be identified. This replaces unreliable hit tests.
  QVariant itemChange(GraphicsItemChange change, const QVariant &value);

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QTextStream &str) const;

  /// Update the radius
  void setRadius(int radius);

private:
  GraphicsPointEllipse();

  // Reference to the GraphicsPoint that this class belongs to
  GraphicsPoint &m_graphicsPoint;
};

#endif // GRAPHICS_POINT_ELLIPSE_H
