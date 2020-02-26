/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantRHover.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantRHover::GuidelineStateDeployedConstantRHover (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantRAbstract (context)
{
}

GuidelineStateDeployedConstantRHover::~GuidelineStateDeployedConstantRHover ()
{
}

void GuidelineStateDeployedConstantRHover::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRHover::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_ON,
               false);
}

bool GuidelineStateDeployedConstantRHover::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantRHover::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRHover::end";
}

void GuidelineStateDeployedConstantRHover::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantRHover::handleGuidelineMode (bool visible,
                                                                bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_LOCKED);
  }
}

void GuidelineStateDeployedConstantRHover::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE
}

void GuidelineStateDeployedConstantRHover::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
}

void GuidelineStateDeployedConstantRHover::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_R,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
}

QString GuidelineStateDeployedConstantRHover::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HOVER);
}
