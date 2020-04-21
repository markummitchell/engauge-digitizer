/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineViewState.h"
#include "GuidelineViewStateContext.h"
#include "GuidelineViewStateLock.h"
#include "Logger.h"

GuidelineViewStateLock::GuidelineViewStateLock (GuidelineViewStateContext &context) :
  GuidelineViewStateAbstractBase (context)
{
}

GuidelineViewStateLock::~GuidelineViewStateLock ()
{
}

void GuidelineViewStateLock::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineViewStateLock::begin";
}

void GuidelineViewStateLock::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineViewStateLock::end";
}

void GuidelineViewStateLock::handleStateChange (GuidelineViewState state)
{
  context().requestStateTransition (state);
}

GuidelineViewState GuidelineViewStateLock::state () const
{
  return GUIDELINE_VIEW_STATE_LOCK;
}
