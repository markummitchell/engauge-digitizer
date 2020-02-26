/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GraphicsScene.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateHandleAbstract.h"
#include "Logger.h"
#include <QPen>
#include "ZValues.h"

GuidelineStateHandleAbstract::GuidelineStateHandleAbstract (GuidelineStateContext &context) :
  GuidelineStateAbstractBase (context)
{
}

GuidelineStateHandleAbstract::~GuidelineStateHandleAbstract ()
{
}

void GuidelineStateHandleAbstract::beginCommon ()
{
  // The pen color is irrelevant since doPaint=false below prevents pen/brush drawing
  GuidelineFormat guidelineFormat (context().color());

  context().guideline().setGraphicsItemZValue (Z_VALUE_GUIDELINE_HANDLE);
  context().guideline().setGraphicsItemVisible (true);
  // ItemIsSelectable is overkill, and in special cases adds ugly selected dashes
  context().guideline().setGraphicsItemFlags (QGraphicsItem::ItemIsFocusable |
                                              QGraphicsItem::ItemIsMovable);
  context().guideline().setGraphicsItemAcceptHoverEvents (false);
  context().guideline().setGraphicsItemPen (guidelineFormat.colorHidden (),
                                            guidelineFormat.lineWidthNonHover ());
}

bool GuidelineStateHandleAbstract::doPaint () const
{
  return true;
}

void GuidelineStateHandleAbstract::handleActiveChange (bool /* active */)
{
  // Noop  
}

void GuidelineStateHandleAbstract::handleGuidelineMode (bool /* visible */,
                                                        bool /* locked */)
{
  // Noop
}

void GuidelineStateHandleAbstract::handleHoverEnterEvent ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandleAbstract::handleHoverEnterEvent";

  // Noop
}

void GuidelineStateHandleAbstract::handleHoverLeaveEvent ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandleAbstract::handleHoverEnterEvent";

  // Noop
}

void GuidelineStateHandleAbstract::handleMousePress (const QPointF & /* posScene */)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandleAbstract::handleMousePress";

  // Noop
}

void GuidelineStateHandleAbstract::handleTimeout ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandleAbstract::handleTimeout";

  // Noop
}

void GuidelineStateHandleAbstract::updateWithLatestTransformation ()
{
  // Noop
}
