/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantTLockedInactive.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantTLockedInactive::GuidelineStateDeployedConstantTLockedInactive (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantTAbstract (context)
{
}

GuidelineStateDeployedConstantTLockedInactive::~GuidelineStateDeployedConstantTLockedInactive ()
{
}

void GuidelineStateDeployedConstantTLockedInactive::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTLockedInactive::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               true);
}

bool GuidelineStateDeployedConstantTLockedInactive::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantTLockedInactive::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTLockedInactive::end";
}

void GuidelineStateDeployedConstantTLockedInactive::handleActiveChange (bool active)
{
  if (active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
  }
}

void GuidelineStateDeployedConstantTLockedInactive::handleGuidelineMode (bool visible,
                                                                         bool /* locked */)
{
  // Never transition from locked state to active state on mode change
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HIDE);
  }
}

void GuidelineStateDeployedConstantTLockedInactive::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE
}

void GuidelineStateDeployedConstantTLockedInactive::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE
}

void GuidelineStateDeployedConstantTLockedInactive::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_T,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
}

QString GuidelineStateDeployedConstantTLockedInactive::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_LOCKED_INACTIVE);
}
