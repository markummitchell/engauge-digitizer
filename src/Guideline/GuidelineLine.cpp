/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "GuidelineFormat.h"
#include "GuidelineLine.h"
#include "Guidelines.h"
#include "GuidelineStateContext.h"
#include "Logger.h"
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QLineF>
#include <qmath.h>
#include <QMouseEvent>
#include <QPen>
#include <QWidget>
#include "ZValues.h"

GuidelineLine::GuidelineLine(QGraphicsScene &scene,
                             Guidelines &guidelines,
                             GuidelineState guidelineStateInitial) :
  GuidelineAbstract (scene)
{
  // Create context after all virtual methods have been created. The transition
  // into the initial state will position the line if it is a template guideline
  setContext (new GuidelineStateContext (*this,
                                         guidelines,
                                         guidelineStateInitial));

  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, QVariant (GRAPHICS_ITEM_TYPE_GUIDELINE));

  scene.addItem (this);
}

GuidelineLine::~GuidelineLine ()
{
}

QGraphicsItem::GraphicsItemFlags GuidelineLine::graphicsItemFlags () const
{
  return QGraphicsLineItem::flags ();
}

void GuidelineLine::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
  handleHoverEnterEvent ();

  QGraphicsLineItem::hoverEnterEvent (event);    
}

void GuidelineLine::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
  handleHoverLeaveEvent ();

  QGraphicsLineItem::hoverLeaveEvent (event);  
}

void GuidelineLine::mouseMoveEvent (QGraphicsSceneMouseEvent *event)
{
  handleMouseMoveEvent (event->scenePos ());
  
  QGraphicsLineItem::mouseMoveEvent (event);
}

void GuidelineLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineLine::mousePressEvent state=" << context()->state ().toLatin1().data();

  handleMousePressEvent (event->scenePos ());
  
  QGraphicsLineItem::mousePressEvent (event);

  context()->handleMousePress(event->scenePos());
}

void GuidelineLine::mouseReleaseEvent (QGraphicsSceneMouseEvent *event)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineLine::mouseReleaseEvent state=" << context()->state ().toLatin1().data();

  handleMouseReleaseEvent ();
  
  QGraphicsLineItem::mouseReleaseEvent (event);

  context()->handleMouseRelease ();
}

void GuidelineLine::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget)
{
  if (context()->doPaint ()) {

    QGraphicsLineItem::paint (painter,
                              option,
                              widget);
  }
}

void GuidelineLine::removeFromScene (QGraphicsScene *scene)
{
  scene->removeItem (this);
}

void GuidelineLine::setGraphicsItemAcceptHoverEvents (bool accept)
{
  QGraphicsLineItem::setAcceptHoverEvents (accept);
}

void GuidelineLine::setGraphicsItemFlags (QGraphicsItem::GraphicsItemFlags flags)
{
  QGraphicsLineItem::setFlags (flags);
}

void GuidelineLine::setGraphicsItemLine (const QLineF &line)
{
  QGraphicsLineItem::setLine (line);
}

void GuidelineLine::setGraphicsItemPen (const QColor &color,
                                        double lineWidth)
{
  QBrush brush (color);

  setPen (QPen (brush,
                lineWidth));
}

void GuidelineLine::setGraphicsItemVisible (bool visible)
{
  QGraphicsLineItem::setVisible (visible);
}

void GuidelineLine::setGraphicsItemZValue (double z)
{
  QGraphicsLineItem::setZValue (z);
}

void GuidelineLine::updateGeometry (const QPointF &posScreen)
{
  // If graph transformation is known then we draw the line along a graph axis, otherwise
  // along a screen axis
  QLineF line = context()->lineFromPoint (posScreen);

  setLine (line);
}
