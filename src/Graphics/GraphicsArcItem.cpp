#include "GraphicsArcItem.h"
#include <QPainter>

GraphicsArcItem::GraphicsArcItem(double x,
                                 double y,
                                 double width,
                                 double height,
                                 QGraphicsItem *parent) :
  QGraphicsEllipseItem(x,
                       y,
                       width,
                       height,
                       parent)
{
}

GraphicsArcItem::GraphicsArcItem(const QRectF &rect,
                                 QGraphicsItem *parent) :
  QGraphicsEllipseItem (rect,
                        parent)
{
}

QRectF GraphicsArcItem::boundingRect() const
{
  // Untransformed bounding rectangle
  QRectF uBoundingRect = QGraphicsEllipseItem::boundingRect();

  // Bounding rectangle with transform incorporated
  QPointF posTopLeftU =  uBoundingRect.topLeft();
  QPointF posBottomRightU = uBoundingRect.bottomRight();

  // Transformed bounding rectangle
  QPointF posTopLeftT = transform().map(posTopLeftU);
  QPointF posBottomRightT = transform().map(posBottomRightU);

  return QRectF (posTopLeftT,
                 posBottomRightT);
}

void GraphicsArcItem::paint (QPainter *painter,
                             const QStyleOptionGraphicsItem * /* option */,
                             QWidget * /* widget */)
{
  painter->setPen (pen ());
  painter->drawArc (rect(),
                    startAngle (),
                    spanAngle());
}
