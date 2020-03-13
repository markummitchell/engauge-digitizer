/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantXLockedInactive.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantXLockedInactive::GuidelineStateDeployedConstantXLockedInactive (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantXAbstract (context)
{
}

GuidelineStateDeployedConstantXLockedInactive::~GuidelineStateDeployedConstantXLockedInactive ()
{
}

void GuidelineStateDeployedConstantXLockedInactive::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXLockedInactive::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               true);
}

bool GuidelineStateDeployedConstantXLockedInactive::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantXLockedInactive::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXLockedInactive::end";
}

void GuidelineStateDeployedConstantXLockedInactive::handleActiveChange (bool active)
{
  if (active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
  }
}

void GuidelineStateDeployedConstantXLockedInactive::handleGuidelineMode (bool visible,
                                                                       bool /* locked */)
{
  // Never transition from locked state to active state on mode change
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HIDE);
  }
}

void GuidelineStateDeployedConstantXLockedInactive::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE
}

void GuidelineStateDeployedConstantXLockedInactive::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE
}

void GuidelineStateDeployedConstantXLockedInactive::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_X,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
}

QString GuidelineStateDeployedConstantXLockedInactive::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_LOCKED_INACTIVE);
}
