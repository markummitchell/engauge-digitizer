/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantXUnselectHide.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantXUnselectHide::GuidelineStateDeployedConstantXUnselectHide (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantXAbstract (context)
{
}

GuidelineStateDeployedConstantXUnselectHide::~GuidelineStateDeployedConstantXUnselectHide ()
{
}

void GuidelineStateDeployedConstantXUnselectHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXUnselectHide::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (false,
               false);

  context().guideline().setGraphicsItemVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantXUnselectHide::doPaint () const
{
  return false;
}

void GuidelineStateDeployedConstantXUnselectHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXUnselectHide::end";
}

void GuidelineStateDeployedConstantXUnselectHide::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantXUnselectHide::handleGuidelineMode (bool visible,
                                                                       bool locked)
{
  if (visible || locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_UNSELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantXUnselectHide::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantXUnselectHide::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantXUnselectHide::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantXUnselectHide::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_UNSELECT_HIDE);
}
