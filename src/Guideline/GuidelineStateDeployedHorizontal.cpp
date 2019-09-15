/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedHorizontal.h"
#include "Logger.h"

GuidelineStateDeployedHorizontal::GuidelineStateDeployedHorizontal (GuidelineStateContext &context) :
  GuidelineStateDeployedAbstract (context)
{
}

GuidelineStateDeployedHorizontal::~GuidelineStateDeployedHorizontal ()
{
}

QString GuidelineStateDeployedHorizontal::state () const
{
  return ("GuidelineStateDeployedHorizontal");
}
