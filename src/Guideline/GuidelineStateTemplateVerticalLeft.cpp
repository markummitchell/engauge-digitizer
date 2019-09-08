/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineStateAbstractBase.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateVerticalLeft.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateTemplateVerticalLeft::GuidelineStateTemplateVerticalLeft (GuidelineStateContext &context) :
  GuidelineStateAbstractBase (context)
{
}

GuidelineStateTemplateVerticalLeft::~GuidelineStateTemplateVerticalLeft ()
{
}

void GuidelineStateTemplateVerticalLeft::begin ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalLeft::begin";

  context().guideline().setLine (templateHomeLine());
}

GuidelineState GuidelineStateTemplateVerticalLeft::cloneState () const
{
  return GUIDELINE_STATE_DEPLOYED_VERTICAL;
}

void GuidelineStateTemplateVerticalLeft::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalLeft::end";
}

bool GuidelineStateTemplateVerticalLeft::isTemplate () const
{
  return true;
}

QLineF GuidelineStateTemplateVerticalLeft::templateHomeLine () const
{
  double lineWidth = context().guideline().lineWidthTemplate();
  
  return QLineF (sceneRect().bottomLeft() + QPointF (0.5 * lineWidth, diagonal ()),
                 sceneRect().topLeft() + QPointF (0.5 * lineWidth, -1.0 * diagonal ()));
}
