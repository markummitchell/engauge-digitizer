/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedVertical.h"
#include "Logger.h"

GuidelineStateDeployedVertical::GuidelineStateDeployedVertical (GuidelineStateContext &context) :
  GuidelineStateDeployedAbstract (context)
{
}

GuidelineStateDeployedVertical::~GuidelineStateDeployedVertical ()
{
}

bool GuidelineStateDeployedVertical::alwaysVisible () const
{
  return true;
}

void GuidelineStateDeployedVertical::begin ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedVertical::begin";
}

GuidelineState GuidelineStateDeployedVertical::cloneState () const
{
  LOG4CPP_ERROR_S ((*mainCat)) << "GuidelineStateDeployedVertical::cloneState cannot clone a deployed guideline";

  // This should not be called
  return GUIDELINE_STATE_NULL;
}

void GuidelineStateDeployedVertical::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedVertical::end";
}

