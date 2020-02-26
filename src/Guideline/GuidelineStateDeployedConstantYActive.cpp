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
#include "GuidelineStateDeployedConstantYActive.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantYActive::GuidelineStateDeployedConstantYActive (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantYAbstract (context)
{
}

GuidelineStateDeployedConstantYActive::~GuidelineStateDeployedConstantYActive ()
{
}

void GuidelineStateDeployedConstantYActive::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYActive::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               false);
}

bool GuidelineStateDeployedConstantYActive::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantYActive::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYActive::end";
}

void GuidelineStateDeployedConstantYActive::handleGuidelineMode (bool visible,
                                                                 bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_LOCKED);
  }
}

void GuidelineStateDeployedConstantYActive::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantYActive::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HOVER);
}

void GuidelineStateDeployedConstantYActive::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HOVER
}

void GuidelineStateDeployedConstantYActive::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_Y,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
}

QString GuidelineStateDeployedConstantYActive::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
}
