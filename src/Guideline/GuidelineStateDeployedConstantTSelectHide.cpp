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
#include "GuidelineStateDeployedConstantTSelectHide.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantTSelectHide::GuidelineStateDeployedConstantTSelectHide (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantTAbstract (context)
{
}

GuidelineStateDeployedConstantTSelectHide::~GuidelineStateDeployedConstantTSelectHide ()
{
}

void GuidelineStateDeployedConstantTSelectHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTSelectHide::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               false);

  context().guideline().setGraphicsItemVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantTSelectHide::doPaint () const
{
  return false;
}

void GuidelineStateDeployedConstantTSelectHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTSelectHide::end";
}

void GuidelineStateDeployedConstantTSelectHide::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantTSelectHide::handleGuidelineMode (bool visible,
                                                               bool locked)
{
  if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_LOCK);
  } else if (visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_EDIT);
  }
}

void GuidelineStateDeployedConstantTSelectHide::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantTSelectHide::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantTSelectHide::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantTSelectHide::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_HIDE);
}
