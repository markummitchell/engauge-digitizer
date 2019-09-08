/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineStateAbstractBase.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateHorizontalTop.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateTemplateHorizontalTop::GuidelineStateTemplateHorizontalTop (GuidelineStateContext &context) :
  GuidelineStateAbstractBase (context)
{
}

GuidelineStateTemplateHorizontalTop::~GuidelineStateTemplateHorizontalTop ()
{
}

bool GuidelineStateTemplateHorizontalTop::alwaysVisible () const
{
  return false;
}

void GuidelineStateTemplateHorizontalTop::begin ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalTop::begin";

  context().guideline().setLine (templateHomeLine());
}

GuidelineState GuidelineStateTemplateHorizontalTop::cloneState () const
{
  return GUIDELINE_STATE_DEPLOYED_HORIZONTAL;
}

void GuidelineStateTemplateHorizontalTop::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalTop::end";
}

bool GuidelineStateTemplateHorizontalTop::initialHoverEventsEnable () const
{
  return false;
}

bool GuidelineStateTemplateHorizontalTop::isTemplate () const
{
  return true;
}

QLineF GuidelineStateTemplateHorizontalTop::templateHomeLine () const
{
  double lineWidth = context().guideline().lineWidthTemplate();
  
  return QLineF (sceneRect().topLeft() + QPointF (-1.0 * diagonal(), 0.5 * lineWidth),
                 sceneRect().topRight() + QPointF (diagonal(), 0.5 * lineWidth));
}
