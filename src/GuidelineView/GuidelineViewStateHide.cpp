/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineViewState.h"
#include "GuidelineViewStateContext.h"
#include "GuidelineViewStateHide.h"
#include "Logger.h"

GuidelineViewStateHide::GuidelineViewStateHide (GuidelineViewStateContext &context) :
  GuidelineViewStateAbstractBase (context)
{
}

GuidelineViewStateHide::~GuidelineViewStateHide ()
{
}

void GuidelineViewStateHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineViewStateHide::begin";
}

void GuidelineViewStateHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineViewStateHide::end";
}

void GuidelineViewStateHide::handleStateChange (GuidelineViewState state)
{
  context().requestStateTransition (state);
}

GuidelineViewState GuidelineViewStateHide::state () const
{
  return GUIDELINE_VIEW_STATE_HIDE;
}
