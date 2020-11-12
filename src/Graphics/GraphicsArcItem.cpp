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
  // Rotations will be about center point rather than (0,0)
  setTransformOriginPoint (x + width / 2.0,
                           y + height / 2.0);
}

GraphicsArcItem::GraphicsArcItem(const QRectF &rect,
                                 QGraphicsItem *parent) :
  QGraphicsEllipseItem (rect,
                        parent)
{
  // Rotations will be about center point rather than (0,0)
  setTransformOriginPoint (rect.center());
}

void GraphicsArcItem::paint (QPainter *painter,
                             const QStyleOptionGraphicsItem * /* option */,
                             QWidget * /* widget */)
{
  double start = startAngle ();
  double span = spanAngle ();

  painter->setPen (pen ());
  painter->drawArc (rect(),
                    start,
                    span);
}
