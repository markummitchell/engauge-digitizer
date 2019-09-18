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
#include "GuidelineFormat.h"
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

Guideline::Guideline(QGraphicsScene &scene,
                     Guidelines &guidelines,
                     GuidelineState guidelineStateInitial) :
  m_guidelineVisible (nullptr)
{
  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, QVariant (GRAPHICS_ITEM_TYPE_GUIDELINE));

  scene.addItem (this);

  // Create context after registering with the scene. The transition
  // into the initial state will position the line if it is a template guideline
  m_context = new GuidelineStateContext (*this,
                                         guidelines,
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

void Guideline::handleShowHide (bool show)
{
  m_context->handleShowHide (show);
}

void Guideline::hoverEnterEvent(QGraphicsSceneHoverEvent * /* event */)
{
  m_context->handleHoverEnterEvent ();
}

void Guideline::hoverLeaveEvent(QGraphicsSceneHoverEvent * /* event */)
{
  m_context->handleHoverLeaveEvent ();
}

void Guideline::mouseMoveEvent (QGraphicsSceneMouseEvent *event)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Guideline::mouseMoveEvent";

  // Skip if there is no bound visible Guideline
  if (m_guidelineVisible != nullptr) {

    // Send the position of this event
    QPointF pos = event->scenePos ();
    emit signalHandleMoved (pos);
  }

  QGraphicsLineItem::mouseMoveEvent (event);
}

void Guideline::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "Guideline::mousePressEvent state=" << m_context->state ().toLatin1().data();

  QGraphicsLineItem::mousePressEvent(event);

  m_context->handleMousePress(event->scenePos());
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
  if (m_context->doPaint ()) {

    QGraphicsLineItem::paint (painter,
                              option,
                              widget);
  }
}

void Guideline::setPenColor (const QColor &color,
                             double lineWidth)
{
  QBrush brush (color);

  setPen (QPen (brush,
                lineWidth));
}

void Guideline::slotHandleMoved (QPointF posScreen)
{
   updateGeometry (posScreen);
}

void Guideline::updateGeometry (const QPointF &poscreen)
{
  // If graph transformation is known then we draw the line along a graph axis, otherwise
  // along a screen axis
  QLineF line = m_context->lineFromPoint (poscreen);

  setLine (line);
}
