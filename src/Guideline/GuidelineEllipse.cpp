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
                                   GuidelineState guidelineStateInitial,
                                   const QString &identifier) :
  GuidelineAbstract (scene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineEllipse::GuidelineEllipse identifier=" << identifier.toLatin1().data();

  // Create context after all virtual methods have been created. The transition
  // into the initial state will position the line if it was created by a button press
  setContext (new GuidelineStateContext (*this,
                                         guidelines,
                                         guidelineStateInitial));

  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, QVariant (GRAPHICS_ITEM_TYPE_GUIDELINE));
  setData (DATA_KEY_IDENTIFIER, QVariant (identifier));

  scene.addItem (this);
}

GuidelineEllipse::~GuidelineEllipse ()
{
}

bool GuidelineEllipse::collidesWithPath (const QPainterPath &path,
                                         Qt::ItemSelectionMode mode) const
{
  const double RATIO = 1000.0; // Ratio of many pixels to few pixels, for preventing divide by zero
  bool collides = false;

  if (QGraphicsEllipseItem::collidesWithPath (path,
                                              mode)) {

    // Slow test to not count interior region

    GuidelineFormat guidelineFormat (context ()->color ());

    // Bounding box of ellipse
    double a = rect().width() / 2.0;
    double b = rect().height() / 2.0;

    // Loop through points in path polygon
    QPolygonF poly = path.toFillPolygon();
    QPolygonF::const_iterator itr;
    for (itr = poly.begin(); (itr != poly.end()) && !collides; itr++) {

      // This point is for the ellipse that has already been rotated to be aligned with axes
      const QPointF &pointAligned = *itr;

      // Project point onto ellipse. The projection is assumed to be the closest ellipse portion to that point.
      // Starting with (x/a)^2+(y/b)^2=1 with x=r cos(Theta) and y=r sin(Theta), we can solve to get r^2 (cT^2/a^2 + sT2/b^2) = 1
      double xGot = pointAligned.x();
      double yGot = pointAligned.y();
      double rGot = qSqrt (xGot * xGot + yGot * yGot);
      if (rGot * RATIO > qAbs (xGot) || rGot * RATIO > qAbs (yGot)) {

        // Check for divide by zero passed so keep going
        double cTheta = xGot / rGot;
        double sTheta = yGot / rGot;
        double rProjected = qSqrt (1.0 / (cTheta * cTheta / a / a + sTheta * sTheta / b / b));
        double xProjected = rProjected * cTheta;
        double yProjected = rProjected * sTheta;

        // Distance to projection
        double distance = qSqrt ((xProjected - xGot) * (xProjected - xGot) +
                                 (yProjected - yGot) * (yProjected - yGot));

        if (distance < guidelineFormat.lineWidthHover()) {

          // This will make the loop exit immediately for speed
          collides = true;
        }
      }
    }
  }

  return collides;
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

QString GuidelineEllipse::identifier () const
{
  return data (DATA_KEY_IDENTIFIER).toString ();
}

void GuidelineEllipse::mouseMoveEvent (QGraphicsSceneMouseEvent *event)
{
  handleMouseMoveEvent (event->scenePos ());
  
  QGraphicsEllipseItem::mouseMoveEvent (event);
}

void GuidelineEllipse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineEllipse::mousePressEvent";

  QGraphicsEllipseItem::mousePressEvent (event);

  handleMousePressEvent (event->scenePos ());

  context()->handleMousePress(event->scenePos());
}

void GuidelineEllipse::mouseReleaseEvent (QGraphicsSceneMouseEvent *event)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineEllipse::mouseReleaseEvent";

  handleMouseReleaseEvent (event->scenePos());

  QGraphicsEllipseItem::mouseReleaseEvent (event);
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
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineLine::removeFromScene identifier="
                               << identifier().toLatin1().data();

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

void GuidelineEllipse::updateGeometry (double valueGraph)
{
  // Convert single graph coordinate, which is range, into screen point pair,
  // then update with the screen point
  updateGeometry (context ()->convertGraphCoordinateToScreenPoint (valueGraph));
}

void GuidelineEllipse::updateGeometry (const QPointF &posScreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineEllipse::updateGeometry scale=" << scale()
                              << " rotation(deg)=" << rotation();

  EllipseParameters ellipseParameters = context()->pointToEllipse (posScreen);

  QPointF posCenter = ellipseParameters.posCenter();

  double a = ellipseParameters.a();
  double b = ellipseParameters.b();

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
