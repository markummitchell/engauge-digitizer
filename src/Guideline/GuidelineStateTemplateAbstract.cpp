/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GraphicsScene.h"
#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateAbstract.h"
#include "Logger.h"

GuidelineStateTemplateAbstract::GuidelineStateTemplateAbstract (GuidelineStateContext &context) :
  GuidelineStateAbstractBase (context)
{
}

GuidelineStateTemplateAbstract::~GuidelineStateTemplateAbstract ()
{
}

void GuidelineStateTemplateAbstract::cloneDraggedGuideline ()
{
  if (context().cloneState () != GUIDELINE_STATE_NULL) {

    // Clone this Guideline and put the clone back at the border. We cannot move the
    // currently dragged line back at the border since the current event is handled
    // asynchronously and the final move is not until after this method has completed
    // (which would override any setLine() call to move this Guideline back to the border).
    // The returned pointer is not saved since the object is already registered with
    // the QGraphicsScene
    Guideline *guidelineReplacement = new Guideline (*context().guideline().scene(),
                                                     context().state ());

    // We are currently in DigitizeStateSelect and the other 3 template guidelines
    // have hover enabled. The Guideline constructor above assumed we are not in
    // DigitizeStateSelect (since right here is the only exception) so we enable
    // hover events here
    guidelineReplacement->setAcceptHoverEvents (true);

    // Transition state for the current Guideline
    context().requestStateTransition (context().cloneState ());
  }
}

bool GuidelineStateTemplateAbstract::initialHoverEventsEnable () const
{
  return false;
}
