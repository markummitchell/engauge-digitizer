#ifndef VIEW_PROFILE_DIVIDER_H
#define VIEW_PROFILE_DIVIDER_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QPointF>

class QGraphicsRectItem;
class QGraphicsScene;
class QPainter;
class ViewProfile;

/// Movable divider in ViewProfile. This displays a selectable button, with a vertical divider line.
class ViewProfileDivider : public QObject, public QGraphicsRectItem
{
  Q_OBJECT;

public:
  /// Single constructor.
  explicit ViewProfileDivider(QGraphicsScene *scene,
                              ViewProfile &viewProfile,
                              double xCenter,
                              double yCenter,
                              bool isLower);

  /// Limit movement to x coordinate when user drags the handle around.
  virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

  /// Save starting location of itemChange movements
  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

  /// Paint the handle so we can add an arrow on the inside, and add some color.
  virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
  /// Share the drag with the shades.
  void signalDividerMoved(bool isLower, QPointF pos);

private:
  ViewProfileDivider();

  void createShade(double xCenter);

  ViewProfile &m_viewProfile;
  QPointF m_mousePressPos; // This is used to manually implement dragging so the y coordinates can be kept constant
  bool m_isLower;
};

#endif // VIEW_PROFILE_DIVIDER_H
