/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantXHover.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantXHover::GuidelineStateDeployedConstantXHover (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantXAbstract (context)
{
}

GuidelineStateDeployedConstantXHover::~GuidelineStateDeployedConstantXHover ()
{
}

void GuidelineStateDeployedConstantXHover::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXHover::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_ON,
               false);
}

bool GuidelineStateDeployedConstantXHover::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantXHover::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXHover::end";
}

void GuidelineStateDeployedConstantXHover::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantXHover::handleGuidelineMode (bool visible,
                                                                bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_LOCKED);
  }
}

void GuidelineStateDeployedConstantXHover::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE
}

void GuidelineStateDeployedConstantXHover::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
}

void GuidelineStateDeployedConstantXHover::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_X,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
}

QString GuidelineStateDeployedConstantXHover::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HOVER);
}
