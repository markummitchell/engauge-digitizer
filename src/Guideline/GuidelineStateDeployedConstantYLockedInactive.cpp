/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantYLockedInactive.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantYLockedInactive::GuidelineStateDeployedConstantYLockedInactive (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantYAbstract (context)
{
}

GuidelineStateDeployedConstantYLockedInactive::~GuidelineStateDeployedConstantYLockedInactive ()
{
}

void GuidelineStateDeployedConstantYLockedInactive::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYLockedInactive::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               true);
}

bool GuidelineStateDeployedConstantYLockedInactive::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantYLockedInactive::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYLockedInactive::end";
}

void GuidelineStateDeployedConstantYLockedInactive::handleActiveChange (bool active)
{
  if (active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
  }
}

void GuidelineStateDeployedConstantYLockedInactive::handleGuidelineMode (bool visible,
                                                                 bool /* locked */)
{
  // Never transition from locked state to active state on mode change
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HIDE);
  }
}

void GuidelineStateDeployedConstantYLockedInactive::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE
}

void GuidelineStateDeployedConstantYLockedInactive::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE
}

void GuidelineStateDeployedConstantYLockedInactive::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_Y,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
}

QString GuidelineStateDeployedConstantYLockedInactive::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_LOCKED_INACTIVE);
}
