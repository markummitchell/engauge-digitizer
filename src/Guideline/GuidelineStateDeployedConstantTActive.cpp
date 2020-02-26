/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantTActive.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantTActive::GuidelineStateDeployedConstantTActive (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantTAbstract (context)
{
}

GuidelineStateDeployedConstantTActive::~GuidelineStateDeployedConstantTActive ()
{
}

void GuidelineStateDeployedConstantTActive::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTActive::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               false);
}

bool GuidelineStateDeployedConstantTActive::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantTActive::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTActive::end";
}

void GuidelineStateDeployedConstantTActive::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantTActive::handleGuidelineMode (bool visible,
                                                                 bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_LOCKED);
  }
}

void GuidelineStateDeployedConstantTActive::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HOVER);
}

void GuidelineStateDeployedConstantTActive::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HOVER
}

void GuidelineStateDeployedConstantTActive::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_T,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
}

QString GuidelineStateDeployedConstantTActive::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
}
