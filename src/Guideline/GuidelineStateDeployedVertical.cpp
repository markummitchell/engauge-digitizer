/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineStateAbstractBase.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedVertical.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedVertical::GuidelineStateDeployedVertical (GuidelineStateContext &context) :
  GuidelineStateAbstractBase (context)
{
}

GuidelineStateDeployedVertical::~GuidelineStateDeployedVertical ()
{
}

void GuidelineStateDeployedVertical::begin ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedVertical::begin";
}

void GuidelineStateDeployedVertical::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedVertical::end";
}

