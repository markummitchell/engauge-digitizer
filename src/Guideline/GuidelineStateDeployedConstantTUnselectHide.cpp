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
#include "GuidelineStateDeployedConstantTUnselectHide.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantTUnselectHide::GuidelineStateDeployedConstantTUnselectHide (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantTAbstract (context)
{
}

GuidelineStateDeployedConstantTUnselectHide::~GuidelineStateDeployedConstantTUnselectHide ()
{
}

void GuidelineStateDeployedConstantTUnselectHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTUnselectHide::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               false);

  context().guideline().setGraphicsItemVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantTUnselectHide::doPaint () const
{
  return false;
}

void GuidelineStateDeployedConstantTUnselectHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTUnselectHide::end";
}

void GuidelineStateDeployedConstantTUnselectHide::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantTUnselectHide::handleGuidelineMode (bool visible,
                                                                       bool locked)
{
  if (visible || locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_UNSELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantTUnselectHide::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantTUnselectHide::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantTUnselectHide::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantTUnselectHide::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_UNSELECT_HIDE);
}
