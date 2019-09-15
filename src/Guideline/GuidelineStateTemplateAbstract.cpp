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

void GuidelineStateTemplateAbstract::beginCommon (const QLineF &line)
{
  context().guideline().setLine (line);

  context().guideline().setAcceptHoverEvents (false);
}

void GuidelineStateTemplateAbstract::handleHoverEnterEvent ()
{
  // Noop
}

void GuidelineStateTemplateAbstract::handleHoverLeaveEvent ()
{
  // Noop
}

void GuidelineStateTemplateAbstract::handleMousePressCommon (const QLineF &line,
                                                             GuidelineState stateDeployed,
                                                             GuidelineState stateReplacement)
{
  context().setStateReplacement (stateReplacement);

  // Visible Guideline will follow this one
  Guideline *guidelineVisible = new Guideline (*context().guideline().scene(),
                                               stateDeployed);

  guidelineVisible->setLine (line);

  context().guideline().bindGuidelineVisible (guidelineVisible);

  context().requestStateTransition (GUIDELINE_STATE_HANDLE);
}
