/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRAPHICS_POINT_POLYGON_H
#define GRAPHICS_POINT_POLYGON_H

#include <QGraphicsPolygonItem>
#include <QObject>
#include <QPointF>

class GraphicsPoint;

/// This class add event handling to QGraphicsPolygonItem
class GraphicsPointPolygon : public QObject, public QGraphicsPolygonItem
{
  Q_OBJECT;

public:
  /// Single constructor
  GraphicsPointPolygon(GraphicsPoint &graphicsPoint,
                       const QPolygonF &polygon);

  /// Intercept moves by dragging so moved items can be identified. This replaces unreliable hit tests.
  QVariant itemChange(GraphicsItemChange change, const QVariant &value);

  /// Accept hover so point can be highlighted when cursor is over it as a guide to user
  virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

  /// Unhighlight this point
  virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

  /// Update the radius
  void setRadius(int radius);

  /// Bind this graphics item to its shadow
  void setShadow (GraphicsPointPolygon *shadow);

signals:

  /// Signal for geometry window to highlight the current point upon hover enter
  void signalPointHoverEnter (QString);

  /// Signal for geometry window to unhighlight the current point upon hover leave
  void signalPointHoverLeave (QString);

private:
  GraphicsPointPolygon();

  void setOpacityForSubtree (double opacity);

  // Reference to the GraphicsPoint that this class belongs to
  GraphicsPoint &m_graphicsPoint;

  GraphicsPointPolygon *m_shadow;
};

#endif // GRAPHICS_POINT_POLYGON_H
