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
  setZValue (Z_VALUE_CURVE);
  setVisible (true);
  setFlags (QGraphicsItem::ItemIsFocusable |
            QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable);

  // Create context after registering with the scene. The transition
  // into the initial state will position the line if it is a template guideline
  m_context = new GuidelineStateContext (*this,
                                         guidelineStateInitial);
}

Guideline::~Guideline ()
{
  delete m_context;
}

void Guideline::bindGuidelineVisible (Guideline *guidelineVisible)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Guideline::hoverEnterEvent state=" << m_context->state ().toLatin1().data();

  m_guidelineVisible = guidelineVisible;

  connect (this, SIGNAL (signalHandleMoved (QPointF)),
           guidelineVisible, SLOT (slotHandleMoved (QPointF)));
}

void Guideline::hoverEnterEvent(QGraphicsSceneHoverEvent * /* event */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Guideline::hoverEnterEvent state=" << m_context->state ().toLatin1().data();

  m_context->handleHoverEnterEvent ();
}

void Guideline::hoverLeaveEvent(QGraphicsSceneHoverEvent * /* event */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Guideline::hoverLeaveEvent state=" << m_context->state ().toLatin1().data();

  m_context->handleHoverLeaveEvent ();
}

double Guideline::lineWidthTemplate () const
{
  return GUIDELINE_LINEWIDTH_TEMPLATE;
}

void Guideline::mouseMoveEvent (QGraphicsSceneMouseEvent *event)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Guideline::mouseMoveEvent state=" << m_context->state ().toLatin1().data()
                              << " pos=(" << event->pos().x() << "," << event->pos().y() << ") "
                              << " scenePos=(" << event->scenePos().x() << "," << event->scenePos().y() << ")";

  // This may be the visible Guideline which does not have its own bound visible Guideline
  if (m_guidelineVisible != nullptr) {

    // Direct call to QGraphicsLineItem::setPos here does nothing (maybe only one object can move at the same time)
    // so signal is sent
    emit signalHandleMoved (event->scenePos ());
  }

  QGraphicsLineItem::mouseMoveEvent (event);
}

void Guideline::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "Guideline::mousePressEvent state=" << m_context->state ().toLatin1().data();

  QGraphicsLineItem::mousePressEvent(event);

  m_context->handleMousePress();
}

void Guideline::mouseReleaseEvent (QGraphicsSceneMouseEvent *event)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "Guideline::mouseReleaseEvent state=" << m_context->state ().toLatin1().data();

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

void Guideline::slotHandleMoved (QPointF pos)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "Guideline::slotHandleMoved pos=(" << pos.x() << ", " << pos.y() << ")";

  setPos (pos);
}
