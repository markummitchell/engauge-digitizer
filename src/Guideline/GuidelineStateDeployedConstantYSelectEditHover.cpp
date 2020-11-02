/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantYSelectEditHover.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantYSelectEditHover::GuidelineStateDeployedConstantYSelectEditHover (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantYAbstract (context)
{
}

GuidelineStateDeployedConstantYSelectEditHover::~GuidelineStateDeployedConstantYSelectEditHover ()
{
}

void GuidelineStateDeployedConstantYSelectEditHover::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYSelectEditHover::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (true,
               false);

  context().guideline().setGraphicsItemVisible (true); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantYSelectEditHover::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantYSelectEditHover::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYSelectEditHover::end";
}

void GuidelineStateDeployedConstantYSelectEditHover::handleActiveChange (bool active)
{
  if (!active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_UNSELECT_EDIT);
  }
}

void GuidelineStateDeployedConstantYSelectEditHover::handleGuidelineMode (bool visible,
                                                                          bool locked)
{
  // Currently visible and not locked
  if (visible && locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_LOCK);
  } else if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_HIDE);
  }
}

void GuidelineStateDeployedConstantYSelectEditHover::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantYSelectEditHover::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_EDIT);
}

void GuidelineStateDeployedConstantYSelectEditHover::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_Y,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_EDIT);
}

QString GuidelineStateDeployedConstantYSelectEditHover::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_EDIT_HOVER);
}
