/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineViewState.h"
#include "GuidelineViewStateContext.h"
#include "GuidelineViewStateEdit.h"
#include "Logger.h"

GuidelineViewStateEdit::GuidelineViewStateEdit (GuidelineViewStateContext &context) :
  GuidelineViewStateAbstractBase (context)
{
}

GuidelineViewStateEdit::~GuidelineViewStateEdit ()
{
}

void GuidelineViewStateEdit::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineViewStateEdit::begin";
}

void GuidelineViewStateEdit::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineViewStateEdit::end";
}

void GuidelineViewStateEdit::handleStateChange (GuidelineViewState state)
{
  context().requestStateTransition (state);
}

GuidelineViewState GuidelineViewStateEdit::state () const
{
  return GUIDELINE_VIEW_STATE_EDIT;
}
