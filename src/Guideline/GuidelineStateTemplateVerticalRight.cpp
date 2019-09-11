/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateVerticalRight.h"
#include "Logger.h"

GuidelineStateTemplateVerticalRight::GuidelineStateTemplateVerticalRight (GuidelineStateContext &context) :
  GuidelineStateTemplateAbstract (context)
{
}

GuidelineStateTemplateVerticalRight::~GuidelineStateTemplateVerticalRight ()
{
}

bool GuidelineStateTemplateVerticalRight::alwaysVisible () const
{
  return false;
}

void GuidelineStateTemplateVerticalRight::begin ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalRight::begin";

  context().guideline().setLine (templateHomeLine());
}

void GuidelineStateTemplateVerticalRight::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalRight::end";
}

void GuidelineStateTemplateVerticalRight::handleMousePress ()
{
}

void GuidelineStateTemplateVerticalRight::handleMouseRelease ()
{
  // See comments in GuidelineStateTemplateHorizontalTop::handleMouseRelease
  Guideline *guidelineReplacement = new Guideline (*context().guideline().scene(),
                                                   GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT);

  guidelineReplacement->setAcceptHoverEvents (true);

  context().requestStateTransition (GUIDELINE_STATE_DEPLOYED_VERTICAL);
}

QLineF GuidelineStateTemplateVerticalRight::templateHomeLine () const
{
  double lineWidth = context().guideline().lineWidthTemplate();
  
  return QLineF (sceneRect().bottomRight() + QPointF (-0.5 * lineWidth, diagonal ()),
                 sceneRect().topRight() + QPointF (-0.5 * lineWidth, -1.0 * diagonal ()));
}
