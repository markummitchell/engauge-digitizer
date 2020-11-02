/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantTUnselectLock.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantTUnselectLock::GuidelineStateDeployedConstantTUnselectLock (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantTAbstract (context)
{
}

GuidelineStateDeployedConstantTUnselectLock::~GuidelineStateDeployedConstantTUnselectLock ()
{
}

void GuidelineStateDeployedConstantTUnselectLock::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTUnselectLock::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (false,
               true);

  context().guideline().setGraphicsItemVisible (true); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantTUnselectLock::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantTUnselectLock::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTUnselectLock::end";
}

void GuidelineStateDeployedConstantTUnselectLock::handleActiveChange (bool active)
{
  if (active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantTUnselectLock::handleGuidelineMode (bool visible,
                                                                       bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_UNSELECT_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_UNSELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantTUnselectLock::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantTUnselectLock::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantTUnselectLock::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantTUnselectLock::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_UNSELECT_LOCK);
}
