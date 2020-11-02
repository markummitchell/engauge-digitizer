/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantXUnselectLock.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantXUnselectLock::GuidelineStateDeployedConstantXUnselectLock (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantXAbstract (context)
{
}

GuidelineStateDeployedConstantXUnselectLock::~GuidelineStateDeployedConstantXUnselectLock ()
{
}

void GuidelineStateDeployedConstantXUnselectLock::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXUnselectLock::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (false,
               true);

  context().guideline().setGraphicsItemVisible (true); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantXUnselectLock::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantXUnselectLock::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXUnselectLock::end";
}

void GuidelineStateDeployedConstantXUnselectLock::handleActiveChange (bool active)
{
  if (active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantXUnselectLock::handleGuidelineMode (bool visible,
                                                                       bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_UNSELECT_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_UNSELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantXUnselectLock::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantXUnselectLock::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantXUnselectLock::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantXUnselectLock::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_UNSELECT_LOCK);
}
