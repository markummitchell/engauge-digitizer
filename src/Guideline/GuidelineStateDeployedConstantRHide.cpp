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
#include "GuidelineStateDeployedConstantRHide.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantRHide::GuidelineStateDeployedConstantRHide (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantRAbstract (context)
{
}

GuidelineStateDeployedConstantRHide::~GuidelineStateDeployedConstantRHide ()
{
}

void GuidelineStateDeployedConstantRHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRHide::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               false);

  context().guideline().setGraphicsItemVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantRHide::doPaint () const
{
  return false;
}

void GuidelineStateDeployedConstantRHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRHide::end";
}

void GuidelineStateDeployedConstantRHide::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantRHide::handleGuidelineMode (bool visible,
                                                               bool locked)
{
  if (visible) {
    if (locked) {
      context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_LOCKED);
    } else {
      context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
    }
  }
}

void GuidelineStateDeployedConstantRHide::handleHoverEnterEvent ()
{
  // Noop
}

void GuidelineStateDeployedConstantRHide::handleHoverLeaveEvent ()
{
  // Noop
}

void GuidelineStateDeployedConstantRHide::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantRHide::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HIDE);
}
