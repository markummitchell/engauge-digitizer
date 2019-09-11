/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateHorizontalBottom.h"
#include "Logger.h"

GuidelineStateTemplateHorizontalBottom::GuidelineStateTemplateHorizontalBottom (GuidelineStateContext &context) :
  GuidelineStateTemplateAbstract (context)
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

void GuidelineStateTemplateHorizontalBottom::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottom::end";
}

void GuidelineStateTemplateHorizontalBottom::handleMousePress ()
{
}

void GuidelineStateTemplateHorizontalBottom::handleMouseRelease ()
{
  // Clone this Guideline and put the clone back at the border. We cannot move the
  // currently dragged line back to the border since the current event is handled
  // asynchronously and the final move is not until after this method has completed
  // (which would override any setLine() call to move this Guideline back to the border).
  // The returned pointer is not saved since the object is already registered with
  // the QGraphicsScene
  Guideline *guidelineReplacement = new Guideline (*context().guideline().scene(),
                                                   GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM);

  // We are currently in DigitizeStateSelect and the other 3 template guidelines
  // have hover enabled. The Guideline constructor above assumed we are not in
  // DigitizeStateSelect (since right here is the only exception) so we enable
  // hover events here
  guidelineReplacement->setAcceptHoverEvents (true);

  // Transition state for the current Guideline
  context().requestStateTransition (GUIDELINE_STATE_DEPLOYED_HORIZONTAL);
}

QLineF GuidelineStateTemplateHorizontalBottom::templateHomeLine () const
{
  double lineWidth = context().guideline().lineWidthTemplate();
  
  return QLineF (sceneRect().bottomLeft() + QPointF (-1.0 * diagonal(), -0.5 * lineWidth),
                 sceneRect().bottomRight() + QPointF (diagonal(), -0.5 * lineWidth));
}
