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

QRectF GraphicsArcItem::boundingRect() const
{
  // Untransformed bounding rectangle is worthless since there will be, if there was any shear or rotation,
  // parts of the curve left after this graphics item is hidden. Trying to compute the actual extent is surprisingly
  // hard when startAngle, spanAngle, shear and rotation are all considered.
  //
  // Since the GraphicsArcItem should ideally have spanned most of the image (for the most accurate digitizing
  // results), we simply mark the whole image as part of the boundingRect
  return scene()->sceneRect();
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
