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
#include <QTextStream>
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

void GuidelineAbstract::bindGuidelineVisibleToInvisible (GuidelineAbstract *guidelineVisible)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineAbstract::bindGuidelineVisibleToInvisible";

  m_guidelineVisible = guidelineVisible;

  connect (this, SIGNAL (signalHandleMoved (QPointF)),
           guidelineVisible, SLOT (slotHandleMoved (QPointF)));
}

GuidelineStateContext *GuidelineAbstract::context ()
{
  return m_context;
}

const GuidelineStateContext *GuidelineAbstract::context () const
{
  return m_context;
}

void GuidelineAbstract::handleActiveChange (bool active)
{
  m_context->handleActiveChange (active);
}

void GuidelineAbstract::handleGuidelineMode (bool visible,
                                             bool locked)
{
  m_context->handleGuidelineMode (visible,
                                  locked);
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
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineAbstract::handleMouseMoveEvent ("
                              << posScene.x() << ", " << posScene.y() << ")";

  // Skip if there is no bound visible Guideline
  if (m_guidelineVisible != nullptr) {

    emit signalHandleMoved (posScene);
  }
}

void GuidelineAbstract::handleMousePressEvent(const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineAbstract::handleMousePressEvent";

  m_context->handleMousePress(posScene);
}

void GuidelineAbstract::handleMouseReleaseEvent (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineAbstract::handleMouseReleaseEvent";

  m_context->handleMouseRelease (posScene);
}

void GuidelineAbstract::sacrificeHandleAndVisibleGuidelines (const QPointF &posScene,
                                                             GuidelineState guidelineStateForReplacement)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineAbstract::sacrificeHandleAndVisibleGuidelines"
                               << " keeping identifier=" << identifier().toLatin1().data()
                               << " in " << stateName ().toLatin1().data();

  if (m_guidelineVisible != nullptr) {

    // If scene position is off-screen then user is removing the visible Guideline
    bool offscreen = !m_scene.sceneRect().contains (posScene);

    // Remove transient Guideline, which was never registered with Guidelines
    LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineAbstract::sacrificeHandleAndVisibleGuidelines identifierDeleting="
                                 << m_guidelineVisible->identifier().toLatin1().data();
    disconnect (this, SIGNAL (signalHandleMoved (QPointF)),
                m_guidelineVisible, SLOT (slotHandleMoved (QPointF)));
    m_guidelineVisible->removeFromScene (&m_scene);
    delete m_guidelineVisible;
    m_guidelineVisible = nullptr;

    // Update Guideline value from cursor position
    double value = context()->convertScreenPointToGraphCoordinate (posScene);

    emit signalGuidelineDragged(identifier (),
                                value,
                                offscreen,
                                guidelineStateForReplacement);
  }
}

QGraphicsScene &GuidelineAbstract::scene ()
{
  return m_scene;
}

QPointF GuidelineAbstract::posCursorGraph () const
{
  return m_context->posCursorGraph ();
}

void GuidelineAbstract::setContext (GuidelineStateContext *context)
{
  m_context = context;
}

void GuidelineAbstract::slotHandleMoved (QPointF posScreen)
{
  // Update geometry
  updateGeometry (posScreen);
}

QString GuidelineAbstract::stateDump () const
{
  // This is used by Guidelines::stateDump and GuidelineStateContext::stateDump
  QString out;
  QTextStream str (&out);

  str << " " << m_context->stateName ();
  str << " (";
  str << (getGraphicsItemSelected() ? "selected" : "unselected") << " ";
  str << (getGraphicsItemAcceptHover() ? "hoverable" : "unhoverable") << " ";
  str << ((graphicsItemFlags () & QGraphicsItem::ItemIsFocusable ) != 0 ? "focusable"  : "unfocusable") << " ";
  str << ((graphicsItemFlags () & QGraphicsItem::ItemIsMovable   ) != 0 ? "movable"    : "unmovable") << " ";
  str << ((graphicsItemFlags () & QGraphicsItem::ItemIsSelectable) != 0 ? "selectable" : "unselectable") << " ";
  str << ")";

  return out;
}

QString GuidelineAbstract::stateName () const
{
  return m_context->stateName ();
}

void GuidelineAbstract::updateWithLatestTransformation ()
{
  m_context->updateWithLatestTransformation ();
}
