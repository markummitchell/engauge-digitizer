/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantYSelectHide.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantYSelectHide::GuidelineStateDeployedConstantYSelectHide (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantYAbstract (context)
{
}

GuidelineStateDeployedConstantYSelectHide::~GuidelineStateDeployedConstantYSelectHide ()
{
}

void GuidelineStateDeployedConstantYSelectHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYSelectHide::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (false,
               false);

  context().guideline().setGraphicsItemVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantYSelectHide::doPaint () const
{
  return false;
}

void GuidelineStateDeployedConstantYSelectHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYSelectHide::end";
}

void GuidelineStateDeployedConstantYSelectHide::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantYSelectHide::handleGuidelineMode (bool visible,
                                                               bool locked)
{
  if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_LOCK);
  } else if (visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_EDIT);
  }
}

void GuidelineStateDeployedConstantYSelectHide::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantYSelectHide::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantYSelectHide::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantYSelectHide::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_HIDE);
}
