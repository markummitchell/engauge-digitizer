#ifndef DLG_DIVIDER_H
#define DLG_DIVIDER_H

#include <QGraphicsRectItem>

class QGraphicsLineItem;
class QGraphicsScene;
class QGraphicsView;

/// Divider that can be dragged, in a dialog QGraphicsView. Click on the paddle to drag.
/// There are three parts:
/// -# Paddle which is the superclass of this class, since we catch its events so dragging works
/// -# Divider which is a vertical line
/// -# Shaded area that extends from xAnchor to the divider
class DlgDivider : public QGraphicsRectItem
{
public:
  /// Single constructor.
  DlgDivider (QGraphicsScene &scene,
              QGraphicsView &view,
              int sceneWidth,
              int sceneHeight,
              int yCenter,
              bool isLowerBoundary);

  /// Intercept changes so divider movement can be restricted to horizontal direction only.
  virtual QVariant itemChange (GraphicsItemChange change, const QVariant &value);

  /// Save paddle position at start of click-and-drag.
  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

  /// Set the position by specifying the new x coordinate.
  void setX (int x);

private:
  DlgDivider ();

  QGraphicsView &m_view;
  int m_yCenter;
  QGraphicsLineItem *m_divider;
  QGraphicsRectItem *m_shadedArea;
  int m_sceneWidth;
  int m_sceneHeight;
  bool m_isLowerBoundary;

  QPointF m_startDragPos;
};

#endif // DLG_DIVIDER_H
