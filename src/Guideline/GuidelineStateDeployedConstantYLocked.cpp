/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantYLocked.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantYLocked::GuidelineStateDeployedConstantYLocked (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantYAbstract (context)
{
}

GuidelineStateDeployedConstantYLocked::~GuidelineStateDeployedConstantYLocked ()
{
}

void GuidelineStateDeployedConstantYLocked::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYLocked::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_ON,
               true);
}

bool GuidelineStateDeployedConstantYLocked::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantYLocked::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYLocked::end";
}

void GuidelineStateDeployedConstantYLocked::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantYLocked::handleGuidelineMode (bool visible,
                                                                 bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HIDE);
  } else if (!locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
  }
}

void GuidelineStateDeployedConstantYLocked::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE
}

void GuidelineStateDeployedConstantYLocked::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
}

void GuidelineStateDeployedConstantYLocked::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_Y,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
}

QString GuidelineStateDeployedConstantYLocked::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_LOCKED);
}
