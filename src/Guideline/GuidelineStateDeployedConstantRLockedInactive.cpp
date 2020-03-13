/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantRLockedInactive.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantRLockedInactive::GuidelineStateDeployedConstantRLockedInactive (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantRAbstract (context)
{
}

GuidelineStateDeployedConstantRLockedInactive::~GuidelineStateDeployedConstantRLockedInactive ()
{
}

void GuidelineStateDeployedConstantRLockedInactive::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRLockedInactive::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               true);
}

bool GuidelineStateDeployedConstantRLockedInactive::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantRLockedInactive::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRLockedInactive::end";
}

void GuidelineStateDeployedConstantRLockedInactive::handleActiveChange (bool active)
{
  if (active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
  }
}

void GuidelineStateDeployedConstantRLockedInactive::handleGuidelineMode (bool visible,
                                                                 bool /* locked */)
{
  // Never transition from locked state to active state on mode change
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HIDE);
  }
}

void GuidelineStateDeployedConstantRLockedInactive::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE
}

void GuidelineStateDeployedConstantRLockedInactive::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE
}

void GuidelineStateDeployedConstantRLockedInactive::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_R,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
}

QString GuidelineStateDeployedConstantRLockedInactive::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_LOCKED_INACTIVE);
}
