/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Guideline.h"
#include "GuidelineStateAbstractBase.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateNull.h"
#include "Logger.h"

GuidelineStateNull::GuidelineStateNull (GuidelineStateContext &context) :
  GuidelineStateAbstractBase (context)
{
}

GuidelineStateNull::~GuidelineStateNull ()
{
}

void GuidelineStateNull::begin ()
{
  LOG4CPP_ERROR_S ((*mainCat)) << "GuidelineStateNull::begin";

  // Move out of the way
  context().guideline().setLine (0, 0, 0, 0);
}

void GuidelineStateNull::end ()
{
  LOG4CPP_ERROR_S ((*mainCat)) << "GuidelineStateNull::end";
}

void GuidelineStateNull::handleHoverEnterEvent ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandle::handleHoverEnterEvent";

  // Noop
}

void GuidelineStateNull::handleHoverLeaveEvent ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandle::handleHoverEnterEvent";

  // Noop
}

void GuidelineStateNull::handleMousePress ()
{
  // Noop
}

void GuidelineStateNull::handleMouseRelease ()
{
  // Noop
}

QString GuidelineStateNull::state () const
{
  return ("GuidelineStateNull");
}
