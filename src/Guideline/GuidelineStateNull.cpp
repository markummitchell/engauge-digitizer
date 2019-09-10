/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
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

bool GuidelineStateNull::alwaysVisible () const
{
  return true;
}

void GuidelineStateNull::begin ()
{
  LOG4CPP_ERROR_S ((*mainCat)) << "GuidelineStateNull::begin";
}

GuidelineState GuidelineStateNull::cloneState () const
{
  // This should not be called
  return GUIDELINE_STATE_NULL;
}

void GuidelineStateNull::end ()
{
  LOG4CPP_ERROR_S ((*mainCat)) << "GuidelineStateNull::end";
}

bool GuidelineStateNull::initialHoverEventsEnable () const
{
  return false;
}

QLineF GuidelineStateNull::templateHomeLine() const
{
  LOG4CPP_ERROR_S ((*mainCat)) << "GuidelineStateNull::templateHomeLine";
  
  return QLineF (0, 0, 0, 0);
}
