/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantRSelectEditHover.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantRSelectEditHover::GuidelineStateDeployedConstantRSelectEditHover (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantRAbstract (context)
{
}

GuidelineStateDeployedConstantRSelectEditHover::~GuidelineStateDeployedConstantRSelectEditHover ()
{
}

void GuidelineStateDeployedConstantRSelectEditHover::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRSelectEditHover::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_ON,
               false);

  context().guideline().setGraphicsItemVisible (true); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantRSelectEditHover::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantRSelectEditHover::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRSelectEditHover::end";
}

void GuidelineStateDeployedConstantRSelectEditHover::handleActiveChange (bool active)
{
  if (!active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_UNSELECT_EDIT);
  }
}

void GuidelineStateDeployedConstantRSelectEditHover::handleGuidelineMode (bool visible,
                                                                          bool locked)
{
  // Currently visible and not locked
  if (visible && locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_LOCK);
  } else if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_HIDE);
  }
}

void GuidelineStateDeployedConstantRSelectEditHover::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantRSelectEditHover::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_EDIT);
}

void GuidelineStateDeployedConstantRSelectEditHover::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_R,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_EDIT);
}

QString GuidelineStateDeployedConstantRSelectEditHover::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_EDIT_HOVER);
}
