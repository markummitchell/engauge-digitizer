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

void GuidelineStateDeployedAbstract::begin ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedAbstract::begin";

  context().guideline().setAcceptHoverEvents (false);
}

void GuidelineStateDeployedAbstract::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedAbstract::end";
}

void GuidelineStateDeployedAbstract::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedAbstract::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedAbstract::handleMousePress ()
{
  // Noop
}

void GuidelineStateDeployedAbstract::handleMouseRelease ()
{
  // Noop
}
