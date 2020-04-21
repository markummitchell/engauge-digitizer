/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineViewStateAbstractBase.h"
#include "GuidelineViewStateContext.h"
#include "Logger.h"

GuidelineViewStateAbstractBase::GuidelineViewStateAbstractBase(GuidelineViewStateContext &context) :
  m_context (context)
{
}

GuidelineViewStateAbstractBase::~GuidelineViewStateAbstractBase ()
{
}

GuidelineViewStateContext &GuidelineViewStateAbstractBase::context () const
{
  return m_context;
}
