/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantYSelectLock.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantYSelectLock::GuidelineStateDeployedConstantYSelectLock (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantYAbstract (context)
{
}

GuidelineStateDeployedConstantYSelectLock::~GuidelineStateDeployedConstantYSelectLock ()
{
}

void GuidelineStateDeployedConstantYSelectLock::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYSelectLock::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (false,
               true);
}

bool GuidelineStateDeployedConstantYSelectLock::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantYSelectLock::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYSelectLock::end";
}

void GuidelineStateDeployedConstantYSelectLock::handleActiveChange (bool active)
{
  if (active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantYSelectLock::handleGuidelineMode (bool visible,
                                                                     bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantYSelectLock::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantYSelectLock::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantYSelectLock::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_Y,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_EDIT);
}

QString GuidelineStateDeployedConstantYSelectLock::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_LOCK);
}
