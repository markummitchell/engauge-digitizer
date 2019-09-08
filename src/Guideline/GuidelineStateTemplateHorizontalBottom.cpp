/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineStateAbstractBase.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateHorizontalBottom.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateTemplateHorizontalBottom::GuidelineStateTemplateHorizontalBottom (GuidelineStateContext &context) :
  GuidelineStateAbstractBase (context)
{
}

GuidelineStateTemplateHorizontalBottom::~GuidelineStateTemplateHorizontalBottom ()
{
}

bool GuidelineStateTemplateHorizontalBottom::alwaysVisible () const
{
  return false;
}

void GuidelineStateTemplateHorizontalBottom::begin ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottom::begin";

  context().guideline().setLine (templateHomeLine());
}

GuidelineState GuidelineStateTemplateHorizontalBottom::cloneState () const
{
  return GUIDELINE_STATE_DEPLOYED_HORIZONTAL;
}

void GuidelineStateTemplateHorizontalBottom::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottom::end";
}

bool GuidelineStateTemplateHorizontalBottom::initialHoverEventsEnable () const
{
  return false;
}

bool GuidelineStateTemplateHorizontalBottom::isTemplate () const
{
  return true;
}

QLineF GuidelineStateTemplateHorizontalBottom::templateHomeLine () const
{
  double lineWidth = context().guideline().lineWidthTemplate();
  
  return QLineF (sceneRect().bottomLeft() + QPointF (-1.0 * diagonal(), -0.5 * lineWidth),
                 sceneRect().bottomRight() + QPointF (diagonal(), -0.5 * lineWidth));
}
