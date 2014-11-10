#include "ViewProfileDivider.h"
#include <QBrush>
#include <QCursor>
#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QRgb>
#include "ViewProfile.h"
#include "ViewProfileParameters.h"

const double BUTTON_HEIGHT = 12;
const double BUTTON_WIDTH = 12;
const double OPACITY_DIVIDER = 1.0;
const double PEN_WIDTH = 0.2;
const double Z_VALUE_DIVIDER = 2.0;

ViewProfileDivider::ViewProfileDivider(QGraphicsScene *scene,
                                       ViewProfile &viewProfile,
                                       double xCenter,
                                       double yCenter,
                                       bool isLower) :
  QGraphicsRectItem(QRect (xCenter - BUTTON_WIDTH / 2,
                           yCenter - BUTTON_HEIGHT / 2,
                           BUTTON_WIDTH,
                           BUTTON_HEIGHT)),
  m_viewProfile (viewProfile),
  m_isLower (isLower)
{
  setFlags (QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemSendsGeometryChanges);
  setCursor (QCursor (Qt::PointingHandCursor));
  setZValue (Z_VALUE_DIVIDER);
  setOpacity (OPACITY_DIVIDER);

  scene->addItem (this);
}

QVariant ViewProfileDivider::itemChange(GraphicsItemChange change,
                                        const QVariant &value)
{
  if (change == ItemPositionChange) {

    // The new position seems to be value plus the position at the mouse down, and the various map
    // functions do not apply. For example, to prevent all y movement we force the y component to stay zero.
    Q_ASSERT (VIEW_PROFILE_X_MIN == 0.0);
    double xLow = -1 * m_mousePressPos.x();
    double xHigh = VIEW_PROFILE_X_MAX - m_mousePressPos.x();
    QPointF posMove = value.toPointF();
    if (posMove.x() < xLow) {
      posMove.setX (xLow);
    }
    if (posMove.x() > xHigh) {
      posMove.setX (xHigh);
    }
    posMove.setY (0.0);

    QPointF posScene (posMove.x() + rect().x() + rect().width() / 2,
                      posMove.y() + rect().y() + rect().width() / 2);
    emit signalDividerMoved (m_isLower, posScene);

    return posMove;
  }

  return QGraphicsItem::itemChange (change,
                                    value);
}

void ViewProfileDivider::mousePressEvent(QGraphicsSceneMouseEvent *)
{
  // We do not care about the current cursor position, but rather care about the centroid of the handle,
  // so event->pos() is ignored
  m_mousePressPos = QPointF (rect().x () + rect().width() / 2,
                             rect().y () + rect().height() / 2);
}

void ViewProfileDivider::paint (QPainter *painter,
                                const QStyleOptionGraphicsItem *option,
                                QWidget *widget)
{
  painter->fillRect (boundingRect(), QBrush (Qt::green));

  double xLeft = boundingRect().left() + boundingRect().width() / 4;
  double xRight = boundingRect().right() - boundingRect().width() / 4;
  double yTop = boundingRect().top() + boundingRect().height() / 4;
  double yBottom = boundingRect().bottom() - boundingRect().height() / 4;
  double yMiddle = (yTop + yBottom) / 2;

  // Draw a triangle
  QPolygonF triangle;
  if (m_isLower) {
    triangle << QPointF (xLeft, yTop);
    triangle << QPointF (xLeft, yBottom);
    triangle << QPointF (xRight, yMiddle);
  } else {
    triangle << QPointF (xRight, yTop);
    triangle << QPointF (xRight, yBottom);
    triangle << QPointF (xLeft, yMiddle);
  }
  painter->setPen (QPen (QBrush (Qt::black), PEN_WIDTH));
  painter->setBrush (QBrush (QColor (128, 255, 128)));
  painter->drawPolygon (triangle);

  QGraphicsRectItem::paint (painter,
                            option,
                            widget);
}
