/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateHorizontalTop.h"
#include "Logger.h"

GuidelineStateTemplateHorizontalTop::GuidelineStateTemplateHorizontalTop (GuidelineStateContext &context) :
  GuidelineStateTemplateAbstract (context)
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

void GuidelineStateTemplateHorizontalTop::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalTop::end";
}

void GuidelineStateTemplateHorizontalTop::handleMousePress ()
{
}

void GuidelineStateTemplateHorizontalTop::handleMouseRelease ()
{
  // See comments in GuidelineStateTemplateHorizontalTop::handleMouseRelease
  Guideline *guidelineReplacement = new Guideline (*context().guideline().scene(),
                                                   GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP);

  guidelineReplacement->setAcceptHoverEvents (true);

  context().requestStateTransition (GUIDELINE_STATE_DEPLOYED_HORIZONTAL);
}

QLineF GuidelineStateTemplateHorizontalTop::templateHomeLine () const
{
  double lineWidth = context().guideline().lineWidthTemplate();
  
  return QLineF (sceneRect().topLeft() + QPointF (-1.0 * diagonal(), 0.5 * lineWidth),
                 sceneRect().topRight() + QPointF (diagonal(), 0.5 * lineWidth));
}
