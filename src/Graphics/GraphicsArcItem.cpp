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

void GraphicsArcItem::paint (QPainter *painter,
                             const QStyleOptionGraphicsItem * /* option */,
                             QWidget * /* widget */)
{
  painter->setPen (pen ());
  painter->drawArc (rect(),
                    startAngle (),
                    spanAngle());
}
