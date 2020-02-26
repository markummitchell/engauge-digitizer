/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantTLocked.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantTLocked::GuidelineStateDeployedConstantTLocked (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantTAbstract (context)
{
}

GuidelineStateDeployedConstantTLocked::~GuidelineStateDeployedConstantTLocked ()
{
}

void GuidelineStateDeployedConstantTLocked::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTLocked::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_ON,
               true);
}

bool GuidelineStateDeployedConstantTLocked::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantTLocked::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTLocked::end";
}

void GuidelineStateDeployedConstantTLocked::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantTLocked::handleGuidelineMode (bool visible,
                                                                 bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HIDE);
  } else if (!locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
  }
}

void GuidelineStateDeployedConstantTLocked::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE
}

void GuidelineStateDeployedConstantTLocked::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
}

void GuidelineStateDeployedConstantTLocked::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_T,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
}

QString GuidelineStateDeployedConstantTLocked::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_LOCKED);
}
