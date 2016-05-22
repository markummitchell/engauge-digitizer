/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GraphicsArcItem.h"
#include <QDebug>
#include <QPainter>
#include <QGraphicsScene>

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
