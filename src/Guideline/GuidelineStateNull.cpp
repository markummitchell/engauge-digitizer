/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Guideline.h"
#include "GuidelineFormat.h"
#include "GuidelineStateAbstractBase.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateNull.h"
#include "Logger.h"
#include <QPen>
#include "ZValues.h"

GuidelineStateNull::GuidelineStateNull (GuidelineStateContext &context) :
  GuidelineStateAbstractBase (context)
{
}

GuidelineStateNull::~GuidelineStateNull ()
{
}

void GuidelineStateNull::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateNull::begin";

  GuidelineFormat guidelineFormat;
  
  context().guideline().setZValue (Z_VALUE_GUIDELINE_NULL);
  context().guideline().setVisible (false); //
  context().guideline().setAcceptHoverEvents (false);
  context().guideline().setPenColor (guidelineFormat.colorHidden (),
                                     guidelineFormat.lineWidthNonHover ());
}

bool GuidelineStateNull::doPaint () const
{
  return false;
}

void GuidelineStateNull::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateNull::end";
}

void GuidelineStateNull::handleHoverEnterEvent ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandle::handleHoverEnterEvent";

  // Noop. Never called since hover only works when visible
}

void GuidelineStateNull::handleHoverLeaveEvent ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandle::handleHoverEnterEvent";

  // Noop. Never called since hover only works when visible
}

void GuidelineStateNull::handleMousePress (const QPointF & /* posScene */)
{
  // Noop
}

void GuidelineStateNull::handleMouseRelease ()
{
  // Noop
}

void GuidelineStateNull::handleShowHide (bool /* show */)
{
}

QLineF GuidelineStateNull::lineFromPoint (const QPointF & /* poscreen */) const
{
  return QLineF (QPointF (0, 0),
                 QPointF (0, 0));
}

QString GuidelineStateNull::state () const
{
  return ("GuidelineStateNull");
}
