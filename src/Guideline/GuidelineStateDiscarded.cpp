/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateAbstractBase.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDiscarded.h"
#include "Logger.h"
#include <QPen>
#include "ZValues.h"

GuidelineStateDiscarded::GuidelineStateDiscarded (GuidelineStateContext &context) :
  GuidelineStateAbstractBase (context)
{
}

GuidelineStateDiscarded::~GuidelineStateDiscarded ()
{
}

void GuidelineStateDiscarded::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDiscarded::begin";

  GuidelineFormat guidelineFormat;
  
  context().guideline().setGraphicsItemZValue (Z_VALUE_GUIDELINE_DISCARDED);
  context().guideline().setGraphicsItemVisible (false); //
  context().guideline().setGraphicsItemAcceptHoverEvents (false);
  context().guideline().setGraphicsItemPen (guidelineFormat.colorHidden (),
                                            guidelineFormat.lineWidthNonHover ());
}

bool GuidelineStateDiscarded::doPaint () const
{
  return false;
}

void GuidelineStateDiscarded::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDiscarded::end";
}

void GuidelineStateDiscarded::handleHoverEnterEvent ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandle::handleHoverEnterEvent";

  // Noop. Never called since hover only works when visible
}

void GuidelineStateDiscarded::handleHoverLeaveEvent ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandle::handleHoverEnterEvent";

  // Noop. Never called since hover only works when visible
}

void GuidelineStateDiscarded::handleMousePress (const QPointF & /* posScene */)
{
  // Noop
}

void GuidelineStateDiscarded::handleMouseRelease ()
{
  // Noop
}

void GuidelineStateDiscarded::handleShowHide (bool /* show */)
{
}

QLineF GuidelineStateDiscarded::lineFromPoint (const QPointF & /* poscreen */) const
{
  return QLineF (QPointF (0, 0),
                 QPointF (0, 0));
}

void GuidelineStateDiscarded::setPointGraph (const QPointF & /* posGraph */)
{
  // Noop
}

QString GuidelineStateDiscarded::state () const
{
  return ("GuidelineStateDiscarded");
}

void GuidelineStateDiscarded::updateWithLatestTransformation ()
{
  // Noop
}
