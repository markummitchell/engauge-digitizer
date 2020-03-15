/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantTSelectEditHover.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantTSelectEditHover::GuidelineStateDeployedConstantTSelectEditHover (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantTAbstract (context)
{
}

GuidelineStateDeployedConstantTSelectEditHover::~GuidelineStateDeployedConstantTSelectEditHover ()
{
}

void GuidelineStateDeployedConstantTSelectEditHover::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTSelectEditHover::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_ON,
               false);
}

bool GuidelineStateDeployedConstantTSelectEditHover::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantTSelectEditHover::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTSelectEditHover::end";
}

void GuidelineStateDeployedConstantTSelectEditHover::handleActiveChange (bool active)
{
  if (!active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_UNSELECT_EDIT);
  }
}

void GuidelineStateDeployedConstantTSelectEditHover::handleGuidelineMode (bool visible,
                                                                          bool locked)
{
  // Currently visible and not locked
  if (visible && locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_LOCK);
  } else if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_HIDE);
  }
}

void GuidelineStateDeployedConstantTSelectEditHover::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantTSelectEditHover::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_EDIT);
}

void GuidelineStateDeployedConstantTSelectEditHover::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_T,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_EDIT);
}

QString GuidelineStateDeployedConstantTSelectEditHover::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_EDIT_HOVER);
}
