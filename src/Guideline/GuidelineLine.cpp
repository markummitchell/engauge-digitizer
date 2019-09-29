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

bool GuidelineLine::getGraphicsItemAcceptHover () const
{
  return acceptHoverEvents();
}

bool GuidelineLine::getGraphicsItemSelected () const
{
  return QGraphicsLineItem::isSelected();
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

  handleMouseReleaseEvent (event->scenePos ());
  
  QGraphicsLineItem::mouseReleaseEvent (event);

  context()->handleMouseRelease (event->scenePos ());
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

void GuidelineLine::updateColor ()
{
  // Apply color to brush and pen defined in setGraphicsItemPen.
  // Alpha from alphaF() on QColor on QBrush is unused

  QPen p = QGraphicsLineItem::pen();
  QBrush br = p.brush();
  double alphaF = br.color().alphaF();
  double lineWidth = p.width ();

  QColor color = ColorPaletteToQColor (context()->color());
  color.setAlphaF (alphaF);

  setGraphicsItemPen (color,
                      lineWidth);
}

void GuidelineLine::updateGeometry (const QPointF &posScreen)
{
  QLineF line = context()->pointToLine (posScreen);

  setLine (line);

  // Save the graph value for later
  QPointF posGraph;
  context()->transformation().transformScreenToRawGraph (posScreen,
                                                         posGraph);
  context()->setPosCursorGraph (posGraph);
}
