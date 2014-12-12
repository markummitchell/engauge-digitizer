#ifndef DLG_DIVIDER_H
#define DLG_DIVIDER_H

#include <QGraphicsRectItem>

class QGraphicsLineItem;
class QGraphicsScene;

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
              int sceneHeight,
              int xAnchor,
              int yCenter);

  /// Intercept changes so divider movement can be restricted to horizontal direction only.
  virtual QVariant itemChange (GraphicsItemChange change, const QVariant &value);

  /// Set the position by specifying the new x coordinate.
  void setX (int x);

private:
  DlgDivider ();

  int m_xAnchor;
  int m_yCenter;

  QGraphicsLineItem *m_divider;
  QGraphicsRectItem *m_shadedArea;
};

#endif // DLG_DIVIDER_H
