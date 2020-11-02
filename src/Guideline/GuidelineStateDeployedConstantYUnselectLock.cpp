/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantYUnselectLock.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantYUnselectLock::GuidelineStateDeployedConstantYUnselectLock (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantYAbstract (context)
{
}

GuidelineStateDeployedConstantYUnselectLock::~GuidelineStateDeployedConstantYUnselectLock ()
{
}

void GuidelineStateDeployedConstantYUnselectLock::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYUnselectLock::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (false,
               true);

  context().guideline().setGraphicsItemVisible (true); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantYUnselectLock::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantYUnselectLock::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYUnselectLock::end";
}

void GuidelineStateDeployedConstantYUnselectLock::handleActiveChange (bool active)
{
  if (active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantYUnselectLock::handleGuidelineMode (bool visible,
                                                                       bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_UNSELECT_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_UNSELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantYUnselectLock::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantYUnselectLock::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantYUnselectLock::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantYUnselectLock::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_UNSELECT_LOCK);
}
