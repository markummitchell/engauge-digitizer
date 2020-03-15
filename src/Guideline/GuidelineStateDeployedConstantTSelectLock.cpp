/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantTSelectLock.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantTSelectLock::GuidelineStateDeployedConstantTSelectLock (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantTAbstract (context)
{
}

GuidelineStateDeployedConstantTSelectLock::~GuidelineStateDeployedConstantTSelectLock ()
{
}

void GuidelineStateDeployedConstantTSelectLock::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTSelectLock::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               true);
}

bool GuidelineStateDeployedConstantTSelectLock::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantTSelectLock::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTSelectLock::end";
}

void GuidelineStateDeployedConstantTSelectLock::handleActiveChange (bool active)
{
  if (active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_UNSELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantTSelectLock::handleGuidelineMode (bool visible,
                                                                     bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantTSelectLock::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantTSelectLock::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantTSelectLock::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_T,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_EDIT);
}

QString GuidelineStateDeployedConstantTSelectLock::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_LOCK);
}
