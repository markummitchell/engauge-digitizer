/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "EnumsToQt.h"
#include "GuidelineStateAbstractBase.h"
#include "GuidelineStateContext.h"
#include "Logger.h"

GuidelineStateAbstractBase::GuidelineStateAbstractBase(GuidelineStateContext &context) :
  m_context (context)
{
}

GuidelineStateAbstractBase::~GuidelineStateAbstractBase ()
{
}
