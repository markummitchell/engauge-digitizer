#ifndef DLG_BOUNDARY_H
#define DLG_BOUNDARY_H

#include <QGraphicsRectItem>

class QGraphicsLineItem;
class QGraphicsScene;

/// Boundary that can be dragged, in a dialog QGraphicsView. Click on the paddle to drag.
/// There are three parts:
/// -# Paddle which is the superclass of this class, since we catch its events so dragging works
/// -# Boundary which is a vertical line
/// -# Shaded area that extends from xAnchor to the boundary
class DlgBoundary : public QGraphicsRectItem
{
public:
  /// Single constructor.
  DlgBoundary (QGraphicsScene &scene,
               int sceneHeight,
               int xAnchor,
               int yCenter);

  /// Set the position by specifying the new x coordinate.
  void setX (int x);

private:
  DlgBoundary ();

  int m_xAnchor;
  int m_yCenter;

  QGraphicsLineItem *m_boundary;
  QGraphicsRectItem *m_shadedArea;
};

#endif // DLG_BOUNDARY_H
