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
#include "GuidelineStateDeployedConstantYHide.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantYHide::GuidelineStateDeployedConstantYHide (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantYAbstract (context)
{
}

GuidelineStateDeployedConstantYHide::~GuidelineStateDeployedConstantYHide ()
{
}

void GuidelineStateDeployedConstantYHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYHide::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               false);

  context().guideline().setGraphicsItemVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantYHide::doPaint () const
{
  return false;
}

void GuidelineStateDeployedConstantYHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYHide::end";
}

void GuidelineStateDeployedConstantYHide::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantYHide::handleGuidelineMode (bool visible,
                                                               bool locked)
{
  if (visible) {
    if (locked) {
      context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_LOCKED);
    } else {
      context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
    }
  }
}

void GuidelineStateDeployedConstantYHide::handleHoverEnterEvent ()
{
  // Noop
}

void GuidelineStateDeployedConstantYHide::handleHoverLeaveEvent ()
{
  // Noop
}

void GuidelineStateDeployedConstantYHide::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantYHide::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HIDE);
}
