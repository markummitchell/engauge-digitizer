/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantRLocked.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantRLocked::GuidelineStateDeployedConstantRLocked (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantRAbstract (context)
{
}

GuidelineStateDeployedConstantRLocked::~GuidelineStateDeployedConstantRLocked ()
{
}

void GuidelineStateDeployedConstantRLocked::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRLocked::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_ON,
               true);
}

bool GuidelineStateDeployedConstantRLocked::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantRLocked::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRLocked::end";
}

void GuidelineStateDeployedConstantRLocked::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantRLocked::handleGuidelineMode (bool visible,
                                                                 bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HIDE);
  } else if (!locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
  }
}

void GuidelineStateDeployedConstantRLocked::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE
}

void GuidelineStateDeployedConstantRLocked::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
}

void GuidelineStateDeployedConstantRLocked::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_R,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
}

QString GuidelineStateDeployedConstantRLocked::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_LOCKED);
}
