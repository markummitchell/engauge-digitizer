/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineStateAbstractBase.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedHorizontal.h"
#include "Logger.h"

GuidelineStateDeployedHorizontal::GuidelineStateDeployedHorizontal (GuidelineStateContext &context) :
  GuidelineStateAbstractBase (context)
{
}

GuidelineStateDeployedHorizontal::~GuidelineStateDeployedHorizontal ()
{
}

bool GuidelineStateDeployedHorizontal::alwaysVisible () const
{
  return true;
}

void GuidelineStateDeployedHorizontal::begin ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedHorizontal::begin";
}

GuidelineState GuidelineStateDeployedHorizontal::cloneState () const
{
  LOG4CPP_ERROR_S ((*mainCat)) << "GuidelineStateDeployedHorizontal::cloneState cannot clone a deployed guideline";

  return GUIDELINE_STATE_DEPLOYED_HORIZONTAL;
}

void GuidelineStateDeployedHorizontal::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedHorizontal::end";
}

bool GuidelineStateDeployedHorizontal::initialHoverEventsEnable () const
{
  return true;
}

bool GuidelineStateDeployedHorizontal::isTemplate () const
{
  return false;
}

QLineF GuidelineStateDeployedHorizontal::templateHomeLine() const
{
  // Should have called isTemplate() first
  ENGAUGE_ASSERT (false);
  
  return QLineF (0, 0, 0, 0);
}
