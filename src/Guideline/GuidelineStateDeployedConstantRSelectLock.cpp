/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantRSelectLock.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantRSelectLock::GuidelineStateDeployedConstantRSelectLock (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantRAbstract (context)
{
}

GuidelineStateDeployedConstantRSelectLock::~GuidelineStateDeployedConstantRSelectLock ()
{
}

void GuidelineStateDeployedConstantRSelectLock::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRSelectLock::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               true);
}

bool GuidelineStateDeployedConstantRSelectLock::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantRSelectLock::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRSelectLock::end";
}

void GuidelineStateDeployedConstantRSelectLock::handleActiveChange (bool active)
{
  if (active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_UNSELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantRSelectLock::handleGuidelineMode (bool visible,
                                                                     bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantRSelectLock::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantRSelectLock::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantRSelectLock::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_R,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_EDIT);
}

QString GuidelineStateDeployedConstantRSelectLock::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_LOCK);
}
