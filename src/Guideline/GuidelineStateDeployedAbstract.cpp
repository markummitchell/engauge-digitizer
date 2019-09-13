/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GraphicsScene.h"
#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedAbstract.h"
#include "Logger.h"

GuidelineStateDeployedAbstract::GuidelineStateDeployedAbstract (GuidelineStateContext &context) :
  GuidelineStateAbstractBase (context)
{
}

GuidelineStateDeployedAbstract::~GuidelineStateDeployedAbstract ()
{
}

bool GuidelineStateDeployedAbstract::alwaysVisible () const
{
  return true;
}

void GuidelineStateDeployedAbstract::handleMousePress ()
{
  // Noop
}

void GuidelineStateDeployedAbstract::handleMouseRelease ()
{
  // Noop
}

bool GuidelineStateDeployedAbstract::initialHoverEventsEnable () const
{
  return true;
}
