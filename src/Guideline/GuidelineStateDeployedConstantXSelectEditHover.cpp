/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantXSelectEditHover.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantXSelectEditHover::GuidelineStateDeployedConstantXSelectEditHover (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantXAbstract (context)
{
}

GuidelineStateDeployedConstantXSelectEditHover::~GuidelineStateDeployedConstantXSelectEditHover ()
{
}

void GuidelineStateDeployedConstantXSelectEditHover::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXSelectEditHover::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (true,
               false);

  context().guideline().setGraphicsItemVisible (true); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantXSelectEditHover::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantXSelectEditHover::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXSelectEditHover::end";
}

void GuidelineStateDeployedConstantXSelectEditHover::handleActiveChange (bool active)
{
  if (!active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_UNSELECT_EDIT);
  }
}

void GuidelineStateDeployedConstantXSelectEditHover::handleGuidelineMode (bool visible,
                                                                          bool locked)
{
  // Currently visible and not locked
  if (visible && locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_LOCK);
  } else if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_HIDE);
  }
}

void GuidelineStateDeployedConstantXSelectEditHover::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantXSelectEditHover::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_EDIT);
}

void GuidelineStateDeployedConstantXSelectEditHover::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_X,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_EDIT);
}

QString GuidelineStateDeployedConstantXSelectEditHover::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_EDIT_HOVER);
}
