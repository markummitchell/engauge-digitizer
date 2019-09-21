/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "GuidelineAbstract.h"
#include "GuidelineAbstract.h"
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
#include "Transformation.h"
#include "ZValues.h"

GuidelineAbstract::GuidelineAbstract(QGraphicsScene &scene) :
  m_scene (scene),
  m_context (nullptr),
  m_guidelineVisible (nullptr)
{
}

GuidelineAbstract::~GuidelineAbstract ()
{
  delete m_context;
}

void GuidelineAbstract::bindGuidelineVisible (GuidelineAbstract *guidelineVisible)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineAbstract::bindGuidelineVisible state=" << m_context->state ().toLatin1().data();

  m_guidelineVisible = guidelineVisible;

  connect (this, SIGNAL (signalHandleMoved (QPointF)),
           guidelineVisible, SLOT (slotHandleMoved (QPointF)));
}

GuidelineStateContext *GuidelineAbstract::context ()
{
  return m_context;
}

void GuidelineAbstract::handleHoverEnterEvent()
{
  m_context->handleHoverEnterEvent ();
}

void GuidelineAbstract::handleHoverLeaveEvent()
{
  m_context->handleHoverLeaveEvent ();
}

void GuidelineAbstract::handleMouseMoveEvent (const QPointF &posScene)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineAbstract::handleMouseMoveEvent";

  // Skip if there is no bound visible Guideline
  if (m_guidelineVisible != nullptr) {

    emit signalHandleMoved (posScene);
  }

  // Save the graph value for later
  QPointF posGraph;
  context()->transformation().transformScreenToRawGraph (posScene,
                                                         posGraph);
  context()->setPointGraph (posGraph);

}

void GuidelineAbstract::handleMousePressEvent(const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineAbstract::handleMousePressEvent state=" << m_context->state ().toLatin1().data();

  m_context->handleMousePress(posScene);
}

void GuidelineAbstract::handleMouseReleaseEvent ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineAbstract::handleMouseReleaseEvent state=" << m_context->state ().toLatin1().data();

  m_context->handleMouseRelease ();
}

void GuidelineAbstract::handleShowHide (bool show)
{
  m_context->handleShowHide (show);
}

QGraphicsScene &GuidelineAbstract::scene ()
{
  return m_scene;
}

void GuidelineAbstract::setContext (GuidelineStateContext *context)
{
  m_context = context;
}

void GuidelineAbstract::slotHandleMoved (QPointF posScreen)
{
   updateGeometry (posScreen);
}

void GuidelineAbstract::updateWithLatestTransformation ()
{
  m_context->updateWithLatestTransformation ();
}
