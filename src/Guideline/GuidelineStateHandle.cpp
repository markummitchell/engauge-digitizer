/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GraphicsScene.h"
#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateHandle.h"
#include "Logger.h"
#include <QPen>
#include "ZValues.h"

GuidelineStateHandle::GuidelineStateHandle (GuidelineStateContext &context) :
  GuidelineStateAbstractBase (context)
{
}

GuidelineStateHandle::~GuidelineStateHandle ()
{
}

void GuidelineStateHandle::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateHandle::begin";

  context().guideline().setZValue (Z_VALUE_GUIDELINE_HANDLE);
  context().guideline().setVisible (true);
  // ItemIsSelectable is overkill, and in special cases adds ugly selected dashes
  context().guideline().setFlags (QGraphicsItem::ItemIsFocusable |
                                  QGraphicsItem::ItemIsMovable);
  context().guideline().setAcceptHoverEvents (false);
  context().guideline().setPenColor (Qt::transparent);
}

bool GuidelineStateHandle::doPaint () const
{
  return false;
}

void GuidelineStateHandle::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateHandle::end";
}

void GuidelineStateHandle::handleHoverEnterEvent ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandle::handleHoverEnterEvent";

  // Noop
}

void GuidelineStateHandle::handleHoverLeaveEvent ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandle::handleHoverEnterEvent";

  // Noop
}

void GuidelineStateHandle::handleMousePress (const QPointF & /* posScene */)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandle::handleMousePress";

  // Noop
}

void GuidelineStateHandle::handleMouseRelease ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandle::handleMouseRelease";

  Guideline *guidelineReplacement = context().createGuideline (context().stateReplacement ());

  guidelineReplacement->setAcceptHoverEvents (true);

  // Go dark. This is not a significant memory leak (versus immediately deleting this object)
  // since the Guideline states are extremely lightweight (few bytes), and there are so few of
  // them (max expected to be well below 100). Plus, whenever the scene is closed (on exit or
  // before loading a new Document) all Guidelines get deleted
  context().requestStateTransition (GUIDELINE_STATE_NULL);
}

void GuidelineStateHandle::handleShowHide (bool /* show */)
{
}

QLineF GuidelineStateHandle::lineFromPoint (const QPointF &/* point */) const
{
  return QLineF (QPointF (0, 0),
                 QPointF (0, 0));
}

QString GuidelineStateHandle::state () const
{
  return ("GuidelineStateHandle");
}
