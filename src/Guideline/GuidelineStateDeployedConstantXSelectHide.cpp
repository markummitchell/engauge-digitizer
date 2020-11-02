/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantXSelectHide.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantXSelectHide::GuidelineStateDeployedConstantXSelectHide (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantXAbstract (context)
{
}

GuidelineStateDeployedConstantXSelectHide::~GuidelineStateDeployedConstantXSelectHide ()
{
}

void GuidelineStateDeployedConstantXSelectHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXSelectHide::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (false,
               false);

  context().guideline().setGraphicsItemVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantXSelectHide::doPaint () const
{
  return false;
}

void GuidelineStateDeployedConstantXSelectHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXSelectHide::end";
}

void GuidelineStateDeployedConstantXSelectHide::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantXSelectHide::handleGuidelineMode (bool visible,
                                                               bool locked)
{
  if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_LOCK);
  } else if (visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_EDIT);
  }
}

void GuidelineStateDeployedConstantXSelectHide::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantXSelectHide::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantXSelectHide::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantXSelectHide::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_HIDE);
}
