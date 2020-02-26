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
#include "GuidelineStateDeployedConstantRActive.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantRActive::GuidelineStateDeployedConstantRActive (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantRAbstract (context)
{
}

GuidelineStateDeployedConstantRActive::~GuidelineStateDeployedConstantRActive ()
{
}

void GuidelineStateDeployedConstantRActive::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRActive::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               false);
}

bool GuidelineStateDeployedConstantRActive::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantRActive::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRActive::end";
}

void GuidelineStateDeployedConstantRActive::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantRActive::handleGuidelineMode (bool visible,
                                                                 bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_LOCKED);
  }
}

void GuidelineStateDeployedConstantRActive::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HOVER);
}

void GuidelineStateDeployedConstantRActive::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HOVER
}

void GuidelineStateDeployedConstantRActive::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_R,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
}

QString GuidelineStateDeployedConstantRActive::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
}
