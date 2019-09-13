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

bool GuidelineStateTemplateAbstract::alwaysVisible () const
{
  return false;
}

void GuidelineStateTemplateAbstract::handleMousePressCommon (const QLineF &line,
                                                             GuidelineState stateDeployed)
{
  // Visible Guideline will follow this one
  Guideline *guidelineVisible = new Guideline (*context().guideline().scene(),
                                               stateDeployed);

  guidelineVisible->setLine (line);

  QObject::connect (&context().guideline(), SIGNAL (signalHandleMoved (QPointF)),
                    guidelineVisible, SLOT (slotHandleMoved (QPointF)));

  context().guideline().bindGuidelineVisible (guidelineVisible);

  context().requestStateTransition (GUIDELINE_STATE_HANDLE);
}

void GuidelineStateTemplateAbstract::handleMouseReleaseCommon (GuidelineState stateReplacement)
{
  // See comments in GuidelineStateTemplateHorizontalTop::handleMouseRelease
  Guideline *guidelineReplacement = new Guideline (*context().guideline().scene(),
                                                   stateReplacement);

  guidelineReplacement->setAcceptHoverEvents (true);

  // This is a small memory leak, since we are not actually deleting this no-longer-needed handle,
  // but a very reliable way to get this handle out of the way
  context().requestStateTransition (GUIDELINE_STATE_NULL);
}

bool GuidelineStateTemplateAbstract::initialHoverEventsEnable () const
{
  return false;
}
