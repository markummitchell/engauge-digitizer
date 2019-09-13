/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "Logger.h"
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QLineF>
#include <QMouseEvent>
#include <QPen>
#include <QWidget>
#include "ZValues.h"

// Template guidelines are thicker so they can be easily clicked on for dragging
const double GUIDELINE_LINEWIDTH_TEMPLATE = 2;

// Cloned guidelines are as thin as possible so their measurements are as precise as possible
//const double GUIDELINE_LINEWIDTH_CLONE = -1;

Guideline::Guideline(QGraphicsScene  &scene,
                     GuidelineState guidelineStateInitial) :
  m_guidelineVisible (nullptr)
{
  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, QVariant (GRAPHICS_ITEM_TYPE_GUIDELINE));

  // Make this transparent now, but always visible so hover events work
  scene.addItem (this);
  setPen (QPen (QBrush (Qt::transparent),
                GUIDELINE_LINEWIDTH_TEMPLATE));
  setZValue (Z_VALUE_CURVE);
  setVisible (true);
  setFlags (QGraphicsItem::ItemIsFocusable |
            QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable);

  // Create context after registering with the scene. The transition
  // into the initial state will position the line if it is a template guideline
  m_context = new GuidelineStateContext (*this,
                                         guidelineStateInitial);

  // Final step is to enable/disable hover events
  setAcceptHoverEvents (m_context->initialHoverEventsEnable ());
  setHover (false); // Initially the cursor is not hovering over this object. Later a hover event will change this state
}

Guideline::~Guideline ()
{
  delete m_context;
}

void Guideline::bindGuidelineVisible (Guideline *guidelineVisible)
{
  m_guidelineVisible = guidelineVisible;

  setSelected (true); // Make sure this has selection focus for the upcoming move
}

void Guideline::hoverEnterEvent(QGraphicsSceneHoverEvent * /* event */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Guideline::hoverEnterEvent";

  setHover (true);
}

void Guideline::hoverLeaveEvent(QGraphicsSceneHoverEvent * /* event */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Guideline::hoverLeaveEvent";

  setHover (false);
}

double Guideline::lineWidthTemplate () const
{
  return GUIDELINE_LINEWIDTH_TEMPLATE;
}

void Guideline::mouseMoveEvent (QGraphicsSceneMouseEvent *event)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Guideline::mouseMoveEvent event=(" << event->pos().x() << "," << event->pos().y() << ") "
                              << " scenePos=(" << event->scenePos().x() << "," << event->scenePos().y() << ")";

  // This may be the visible Guideline which does not have its own bound visible Guideline
  if (m_guidelineVisible != nullptr) {

    // Direct call to QGraphicsLineItem::setPos here does nothing (maybe only one object can move at the same time)
    // so signal is sent
    emit signalHandleMoved (event->pos ());
  }

  QGraphicsLineItem::mouseMoveEvent (event);
}

void Guideline::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "Guideline::mousePressEvent";

  m_context->handleMousePress();

  QGraphicsLineItem::mousePressEvent(event);
}

void Guideline::mouseReleaseEvent (QGraphicsSceneMouseEvent *event)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "Guideline::mouseReleaseEvent";

  // Handle the event
  QGraphicsLineItem::mouseReleaseEvent (event);

  m_context->handleMouseRelease ();
}

void Guideline::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
  QGraphicsLineItem::paint (painter,
                            option,
                            widget);
}

void Guideline::setHover (bool hover)
{
  if (hover || m_context->alwaysVisible ()) {

    QColor color (Qt::blue);

    setPen (QPen (QBrush (color),
                  GUIDELINE_LINEWIDTH_TEMPLATE));

  } else {

    setPen (QPen (QBrush (Qt::transparent),
                  GUIDELINE_LINEWIDTH_TEMPLATE));

  }
}

void Guideline::slotHandleMoved (QPointF pos)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "Guideline::slotHandleMoved pos=(" << pos.x() << ", " << pos.y() << ")";

  setPos (pos);
}
