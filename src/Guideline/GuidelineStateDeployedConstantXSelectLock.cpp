/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantXSelectLock.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantXSelectLock::GuidelineStateDeployedConstantXSelectLock (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantXAbstract (context)
{
}

GuidelineStateDeployedConstantXSelectLock::~GuidelineStateDeployedConstantXSelectLock ()
{
}

void GuidelineStateDeployedConstantXSelectLock::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXSelectLock::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               true);
}

bool GuidelineStateDeployedConstantXSelectLock::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantXSelectLock::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXSelectLock::end";
}

void GuidelineStateDeployedConstantXSelectLock::handleActiveChange (bool active)
{
  if (active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantXSelectLock::handleGuidelineMode (bool visible,
                                                                       bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantXSelectLock::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantXSelectLock::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantXSelectLock::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_X,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_EDIT);
}

QString GuidelineStateDeployedConstantXSelectLock::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_LOCK);
}
