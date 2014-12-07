#ifndef GRAPHICS_POINT_CIRCLE_H
#define GRAPHICS_POINT_CIRCLE_H

#include "GraphicsPointAbstractBase.h"
#include <QGraphicsEllipseItem>
#include <QPointF>

/// Circular graphics item for displaying a single Point.
class GraphicsPointCircle : public GraphicsPointAbstractBase, public QGraphicsEllipseItem
{
public:
  /// Single constructor.
  GraphicsPointCircle(const QString &identifier,
                      const QPointF &posScreen,
                      const QColor &color,
                      unsigned int radius,
                      double lineWidth);

  /// Intercept moves by dragging so moved items can be identified. This replaces unreliable hit tests.
  QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
  GraphicsPointCircle();

  QGraphicsEllipseItem *m_shadowZeroWidth; // Shadow item overlays the superclass instance to ensure visibility
};

#endif // GRAPHICS_POINT_CIRCLE_H
