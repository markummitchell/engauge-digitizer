/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantYHover.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantYHover::GuidelineStateDeployedConstantYHover (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantYAbstract (context)
{
}

GuidelineStateDeployedConstantYHover::~GuidelineStateDeployedConstantYHover ()
{
}

void GuidelineStateDeployedConstantYHover::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYHover::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_ON,
               false);
}

bool GuidelineStateDeployedConstantYHover::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantYHover::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYHover::end";
}

void GuidelineStateDeployedConstantYHover::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantYHover::handleGuidelineMode (bool visible,
                                                                bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_LOCKED);
  }
}

void GuidelineStateDeployedConstantYHover::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE
}

void GuidelineStateDeployedConstantYHover::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
}

void GuidelineStateDeployedConstantYHover::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_Y,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
}

QString GuidelineStateDeployedConstantYHover::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HOVER);
}
