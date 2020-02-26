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
#include "GuidelineStateDeployedConstantTHide.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantTHide::GuidelineStateDeployedConstantTHide (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantTAbstract (context)
{
}

GuidelineStateDeployedConstantTHide::~GuidelineStateDeployedConstantTHide ()
{
}

void GuidelineStateDeployedConstantTHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTHide::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               false);

  context().guideline().setGraphicsItemVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantTHide::doPaint () const
{
  return false;
}

void GuidelineStateDeployedConstantTHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTHide::end";
}

void GuidelineStateDeployedConstantTHide::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantTHide::handleGuidelineMode (bool visible,
                                                               bool locked)
{
  if (visible) {
    if (locked) {
      context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_LOCKED);
    } else {
      context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
    }
  }
}

void GuidelineStateDeployedConstantTHide::handleHoverEnterEvent ()
{
  // Noop
}

void GuidelineStateDeployedConstantTHide::handleHoverLeaveEvent ()
{
  // Noop
}

void GuidelineStateDeployedConstantTHide::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantTHide::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HIDE);
}
