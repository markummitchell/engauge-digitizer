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
#include "GuidelineStateDeployedConstantXActive.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantXActive::GuidelineStateDeployedConstantXActive (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantXAbstract (context)
{
}

GuidelineStateDeployedConstantXActive::~GuidelineStateDeployedConstantXActive ()
{
}

void GuidelineStateDeployedConstantXActive::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXActive::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               false);
}

bool GuidelineStateDeployedConstantXActive::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantXActive::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXActive::end";
}

void GuidelineStateDeployedConstantXActive::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantXActive::handleGuidelineMode (bool visible,
                                                                 bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_LOCKED);
  }
}

void GuidelineStateDeployedConstantXActive::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HOVER);
}

void GuidelineStateDeployedConstantXActive::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HOVER
}

void GuidelineStateDeployedConstantXActive::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_X,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
}

QString GuidelineStateDeployedConstantXActive::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
}
