/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantRUnselectHide.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantRUnselectHide::GuidelineStateDeployedConstantRUnselectHide (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantRAbstract (context)
{
}

GuidelineStateDeployedConstantRUnselectHide::~GuidelineStateDeployedConstantRUnselectHide ()
{
}

void GuidelineStateDeployedConstantRUnselectHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRUnselectHide::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (false,
               false);

  context().guideline().setGraphicsItemVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantRUnselectHide::doPaint () const
{
  return false;
}

void GuidelineStateDeployedConstantRUnselectHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRUnselectHide::end";
}

void GuidelineStateDeployedConstantRUnselectHide::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantRUnselectHide::handleGuidelineMode (bool visible,
                                                               bool locked)
{
  if (visible || locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_UNSELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantRUnselectHide::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantRUnselectHide::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantRUnselectHide::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantRUnselectHide::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_UNSELECT_HIDE);
}
