/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineStateAbstractBase.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateVerticalRight.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateTemplateVerticalRight::GuidelineStateTemplateVerticalRight (GuidelineStateContext &context) :
  GuidelineStateAbstractBase (context)
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

GuidelineState GuidelineStateTemplateVerticalRight::cloneState () const
{
  return GUIDELINE_STATE_DEPLOYED_VERTICAL;
}

void GuidelineStateTemplateVerticalRight::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalRight::end";
}

bool GuidelineStateTemplateVerticalRight::initialHoverEventsEnable () const
{
  return false;
}

bool GuidelineStateTemplateVerticalRight::isTemplate () const
{
  return true;
}

QLineF GuidelineStateTemplateVerticalRight::templateHomeLine () const
{
  double lineWidth = context().guideline().lineWidthTemplate();
  
  return QLineF (sceneRect().bottomRight() + QPointF (-0.5 * lineWidth, diagonal ()),
                 sceneRect().topRight() + QPointF (-0.5 * lineWidth, -1.0 * diagonal ()));
}
