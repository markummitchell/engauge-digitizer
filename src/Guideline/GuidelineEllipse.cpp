/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "GuidelineEllipse.h"
#include "GuidelineFormat.h"
#include "Guidelines.h"
#include "GuidelineStateContext.h"
#include "Logger.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QLineF>
#include <qmath.h>
#include <QMouseEvent>
#include <QPen>
#include <QWidget>
#include "ZValues.h"

GuidelineEllipse::GuidelineEllipse(QGraphicsScene &scene,
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

GuidelineEllipse::~GuidelineEllipse ()
{
}

QGraphicsItem::GraphicsItemFlags GuidelineEllipse::graphicsItemFlags () const
{
  return QGraphicsEllipseItem::flags ();
}

void GuidelineEllipse::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
  handleHoverEnterEvent ();

  QGraphicsEllipseItem::hoverEnterEvent (event);    
}

void GuidelineEllipse::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
  handleHoverLeaveEvent ();

  QGraphicsEllipseItem::hoverLeaveEvent (event);  
}

void GuidelineEllipse::mouseMoveEvent (QGraphicsSceneMouseEvent *event)
{
  handleMouseMoveEvent (event->scenePos ());
  
  QGraphicsEllipseItem::mouseMoveEvent (event);
}

void GuidelineEllipse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineEllipse::mousePressEvent state=" << context()->state ().toLatin1().data();

  handleMousePressEvent (event->scenePos ());
  
  QGraphicsEllipseItem::mousePressEvent (event);

  context()->handleMousePress(event->scenePos());
}

void GuidelineEllipse::mouseReleaseEvent (QGraphicsSceneMouseEvent *event)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineEllipse::mouseReleaseEvent state=" << context()->state ().toLatin1().data();

  handleMouseReleaseEvent ();
  
  QGraphicsEllipseItem::mouseReleaseEvent (event);

  context()->handleMouseRelease ();
}

void GuidelineEllipse::paint(QPainter *painter,
                             const QStyleOptionGraphicsItem *option,
                             QWidget *widget)
{
  if (context()->doPaint ()) {

    QGraphicsEllipseItem::paint (painter,
                                 option,
                                 widget);
  }
}

void GuidelineEllipse::removeFromScene (QGraphicsScene *scene)
{
  scene->removeItem (this);
}

void GuidelineEllipse::setGraphicsItemAcceptHoverEvents (bool accept)
{
  QGraphicsEllipseItem::setAcceptHoverEvents (accept);
}

void GuidelineEllipse::setGraphicsItemFlags (QGraphicsItem::GraphicsItemFlags flags)
{
  QGraphicsEllipseItem::setFlags (flags);
}

void GuidelineEllipse::setGraphicsItemLine (const QLineF & /* line */)
{
  // Noop
}

void GuidelineEllipse::setGraphicsItemPen (const QColor &color,
                                           double lineWidth)
{
  QBrush brush (color);

  setPen (QPen (brush,
                lineWidth));
}

void GuidelineEllipse::setGraphicsItemVisible (bool visible)
{
  QGraphicsEllipseItem::setVisible (visible);
}

void GuidelineEllipse::setGraphicsItemZValue (double z)
{
  QGraphicsEllipseItem::setZValue (z);
}

void GuidelineEllipse::updateGeometry (const QPointF &posScreen)
{
  EllipseParameters ellipseParameters = context()->pointToEllipse (posScreen);

  QPointF posCenter = ellipseParameters.posCenter();
  double a = ellipseParameters.a();
  double b=  ellipseParameters.b();

  setRect (QRectF (posCenter - QPointF (a, b),
                   posCenter + QPointF (a, b)));

  // Rotate
  setTransformOriginPoint (posCenter);
  setRotation (ellipseParameters.angleRadians());
}
