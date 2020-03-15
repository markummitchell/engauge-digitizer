/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantRUnselectLock.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantRUnselectLock::GuidelineStateDeployedConstantRUnselectLock (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantRAbstract (context)
{
}

GuidelineStateDeployedConstantRUnselectLock::~GuidelineStateDeployedConstantRUnselectLock ()
{
}

void GuidelineStateDeployedConstantRUnselectLock::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRUnselectLock::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               true);
}

bool GuidelineStateDeployedConstantRUnselectLock::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantRUnselectLock::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRUnselectLock::end";
}

void GuidelineStateDeployedConstantRUnselectLock::handleActiveChange (bool active)
{
  if (active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantRUnselectLock::handleGuidelineMode (bool visible,
                                                                       bool locked)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_UNSELECT_HIDE);
  } else if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_UNSELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantRUnselectLock::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantRUnselectLock::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantRUnselectLock::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantRUnselectLock::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_UNSELECT_LOCK);
}
