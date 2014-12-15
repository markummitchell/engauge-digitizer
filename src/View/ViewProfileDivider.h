#ifndef VIEW_PROFILE_DIVIDER_H
#define VIEW_PROFILE_DIVIDER_H

#include <QGraphicsRectItem>
#include <QObject>

class QGraphicsLineItem;
class QGraphicsScene;
class QGraphicsPolygonItem;
class QGraphicsView;

/// Divider that can be dragged, in a dialog QGraphicsView. Click on the paddle to drag.
/// There are three parts:
/// -# Paddle which is the superclass of this class, since we catch its events so dragging works
/// -# Divider which is a vertical line
/// -# Shaded area that extends from xAnchor to the divider
class ViewProfileDivider : public QObject, public QGraphicsRectItem
{
  Q_OBJECT;

public:
  /// Single constructor.
  ViewProfileDivider (QGraphicsScene &scene,
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
  void setX (double x,
             double xLow,
             double xHigh);

private slots:
  /// Notify other divider this one moved.
  void slotOtherMoved(double xSceneOther);

signals:
  /// Signal used when divider is dragged and m_isLowerBoundary is true.
  void signalMovedLow (double xSceneOther);

  /// Signal used when divider is dragged and m_isLowerBoundary is false.
  void signalMovedHigh (double xSceneOther);

private:
  ViewProfileDivider ();

  void sendSignalMoved ();

  // Update geoemtries since one of the dividers (this or the other) moved
  void updateGeometryDivider ();
  void updateGeometryNonPaddle ();
  void updateGeometryPaddle ();

  QGraphicsView &m_view;
  int m_yCenter;
  double m_xScene; // X coordinae of this divider
  double m_xSceneOther; // X coordinate of other divider. Used when the two dividers have moved past each other so there
                        // are two unshaded areas
  QGraphicsLineItem *m_divider;
  QGraphicsRectItem *m_shadedArea;
  QGraphicsPolygonItem *m_arrow;
  int m_sceneWidth;
  int m_sceneHeight;
  bool m_isLowerBoundary;

  QPointF m_startDragPos;
};

#endif // VIEW_PROFILE_DIVIDER_H
