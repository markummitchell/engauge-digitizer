/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineState.h"
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
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDiscarded::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  GuidelineFormat guidelineFormat (context().color());
  
  context().guideline().setGraphicsItemZValue (Z_VALUE_GUIDELINE_DISCARDED);
  context().guideline().setGraphicsItemVisible (false); //
  context().guideline().setGraphicsItemAcceptHoverEvents (false);
  context().guideline().setGraphicsItemPen (guidelineFormat.colorHidden (),
                                            guidelineFormat.lineWidthNonHover ());
}

QPointF GuidelineStateDiscarded::convertGraphCoordinateToScreenPoint (double /* valueGraph */) const
{
  LOG4CPP_ERROR_S ((*mainCat)) << "GuidelineStateDiscarded::convertGraphCoordinateToScreenPoint "
                               << "should not be called";

  ENGAUGE_ASSERT (false);

  return QPointF (0, 0); // No-harm value
}

double GuidelineStateDiscarded::convertScreenPointToGraphCoordinate (const QPointF & /* posScreen */) const
{
  LOG4CPP_ERROR_S ((*mainCat)) << "GuidelineStateDiscarded::convertScreenPointToGraphCoordinate";

  ENGAUGE_ASSERT (false);

  return 0.1; // No-harm value even if using log scale
}

bool GuidelineStateDiscarded::doPaint () const
{
  return false;
}

void GuidelineStateDiscarded::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDiscarded::end";
}

void GuidelineStateDiscarded::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDiscarded::handleGuidelineMode (bool /* visible */,
                                                   bool /* locked */)
{
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

void GuidelineStateDiscarded::handleMouseRelease (const QPointF & /* posScene */)
{
  // Noop
}

void GuidelineStateDiscarded::handleState ()
{
  // Noop
}

void GuidelineStateDiscarded::handleTimeout ()
{
  // Noop
}

EllipseParameters GuidelineStateDiscarded::pointToEllipse (const QPointF & /* poscreen */) const
{
  return EllipseParameters();
}

QLineF GuidelineStateDiscarded::pointToLine (const QPointF & /* posGraph */) const
{
  return QLineF (0, 0, 0, 0);
}

QString GuidelineStateDiscarded::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateDiscarded::updateWithLatestTransformation ()
{
  // Noop
}
