/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GraphicsScene.h"
#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateHandle.h"
#include "Logger.h"

GuidelineStateHandle::GuidelineStateHandle (GuidelineStateContext &context) :
  GuidelineStateAbstractBase (context)
{
}

GuidelineStateHandle::~GuidelineStateHandle ()
{
}

bool GuidelineStateHandle::alwaysVisible () const
{
  return true;
}

void GuidelineStateHandle::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateHandle::begin";
}

void GuidelineStateHandle::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateHandle::end";
}

void GuidelineStateHandle::handleMousePress ()
{
  // Noop
}

void GuidelineStateHandle::handleMouseRelease ()
{
  // Noop
}

bool GuidelineStateHandle::initialHoverEventsEnable () const
{
  return true;
}

QLineF GuidelineStateHandle::templateHomeLine() const
{
  // Only applies to template guidelines
  ENGAUGE_ASSERT (false);
  
  return QLineF (0, 0, 0, 0);
}
