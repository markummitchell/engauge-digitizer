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
#include "GuidelineStateDeployedConstantYUnselectHide.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantYUnselectHide::GuidelineStateDeployedConstantYUnselectHide (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantYAbstract (context)
{
}

GuidelineStateDeployedConstantYUnselectHide::~GuidelineStateDeployedConstantYUnselectHide ()
{
}

void GuidelineStateDeployedConstantYUnselectHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYUnselectHide::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               false);

  context().guideline().setGraphicsItemVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantYUnselectHide::doPaint () const
{
  return false;
}

void GuidelineStateDeployedConstantYUnselectHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYUnselectHide::end";
}

void GuidelineStateDeployedConstantYUnselectHide::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantYUnselectHide::handleGuidelineMode (bool visible,
                                                                       bool locked)
{
  if (visible || locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_UNSELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantYUnselectHide::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantYUnselectHide::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantYUnselectHide::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantYUnselectHide::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_UNSELECT_HIDE);
}
