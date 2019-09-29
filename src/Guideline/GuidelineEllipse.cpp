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

bool GuidelineEllipse::getGraphicsItemAcceptHover () const
{
  return acceptHoverEvents();
}

bool GuidelineEllipse::getGraphicsItemSelected () const
{
  return QGraphicsEllipseItem::isSelected ();
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

  QGraphicsEllipseItem::mousePressEvent (event);

  handleMousePressEvent (event->scenePos ());

  context()->handleMousePress(event->scenePos());
}

void GuidelineEllipse::mouseReleaseEvent (QGraphicsSceneMouseEvent *event)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineEllipse::mouseReleaseEvent state=" << context()->state ().toLatin1().data();

  handleMouseReleaseEvent (event->scenePos());

  QGraphicsEllipseItem::mouseReleaseEvent (event);

  context()->handleMouseRelease (event->scenePos ());
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

void GuidelineEllipse::updateColor ()
{
  // Apply color to brush and pen defined in setGraphicsItemPen.

  QPen p = QGraphicsEllipseItem::pen();
  QBrush br = p.brush();
  double alphaF = br.color().alphaF();
  double lineWidth = p.width ();

  QColor color = ColorPaletteToQColor (context()->color());
  color.setAlphaF (alphaF);

  setGraphicsItemPen (color,
                      lineWidth);
}

void GuidelineEllipse::updateGeometry (const QPointF &posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineEllipse::updateGeometry scale=" << scale()
                              << " rotation(deg)=" << rotation();

  EllipseParameters ellipseParameters = context()->pointToEllipse (posScreen);

  QPointF posCenter = ellipseParameters.posCenter();

  double a = ellipseParameters.a();
  double b=  ellipseParameters.b();

  setRect (QRectF (- QPointF (a, b),
                   + QPointF (a, b)));

  // Rotate. Originally the rectangle was centered at posCenter, the rotation center
  // was set using setTransformOriginPoint to posCenter, but the resulting shape was not right
  setRotation (qRadiansToDegrees (ellipseParameters.angleRadians()));
  setPos (posCenter);

  // Save the graph value for later
  QPointF posGraph;
  context()->transformation().transformScreenToRawGraph (posScreen,
                                                         posGraph);
  context()->setPosCursorGraph (posGraph);
}
