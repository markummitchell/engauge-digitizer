/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantTHover.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantTHover::GuidelineStateDeployedConstantTHover (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantTAbstract (context)
{
}

GuidelineStateDeployedConstantTHover::~GuidelineStateDeployedConstantTHover ()
{
}

void GuidelineStateDeployedConstantTHover::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTHover::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_ON,
               false);
}

bool GuidelineStateDeployedConstantTHover::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantTHover::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTHover::end";
}

void GuidelineStateDeployedConstantTHover::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantTHover::handleGuidelineMode (bool visible,
                                                                bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_LOCKED);
  }
}

void GuidelineStateDeployedConstantTHover::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE
}

void GuidelineStateDeployedConstantTHover::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
}

void GuidelineStateDeployedConstantTHover::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_T,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
}

QString GuidelineStateDeployedConstantTHover::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HOVER);
}
