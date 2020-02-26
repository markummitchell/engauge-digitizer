/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantXLocked.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantXLocked::GuidelineStateDeployedConstantXLocked (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantXAbstract (context)
{
}

GuidelineStateDeployedConstantXLocked::~GuidelineStateDeployedConstantXLocked ()
{
}

void GuidelineStateDeployedConstantXLocked::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXLocked::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_ON,
               true);
}

bool GuidelineStateDeployedConstantXLocked::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantXLocked::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXLocked::end";
}

void GuidelineStateDeployedConstantXLocked::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantXLocked::handleGuidelineMode (bool visible,
                                                                 bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HIDE);
  } else if (!locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
  }
}

void GuidelineStateDeployedConstantXLocked::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE
}

void GuidelineStateDeployedConstantXLocked::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
}

void GuidelineStateDeployedConstantXLocked::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_X,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
}

QString GuidelineStateDeployedConstantXLocked::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_LOCKED);
}
