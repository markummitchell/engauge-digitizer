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
#include "GuidelineStateDeployedConstantXHide.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantXHide::GuidelineStateDeployedConstantXHide (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantXAbstract (context)
{
}

GuidelineStateDeployedConstantXHide::~GuidelineStateDeployedConstantXHide ()
{
}

void GuidelineStateDeployedConstantXHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXHide::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               false);

  context().guideline().setGraphicsItemVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantXHide::doPaint () const
{
  return false;
}

void GuidelineStateDeployedConstantXHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXHide::end";
}

void GuidelineStateDeployedConstantXHide::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantXHide::handleGuidelineMode (bool visible,
                                                               bool locked)
{
  if (visible) {
    if (locked) {
      context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_LOCKED);
    } else {
      context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
    }
  }
}

void GuidelineStateDeployedConstantXHide::handleHoverEnterEvent ()
{
  // Noop
}

void GuidelineStateDeployedConstantXHide::handleHoverLeaveEvent ()
{
  // Noop
}

void GuidelineStateDeployedConstantXHide::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantXHide::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HIDE);
}
