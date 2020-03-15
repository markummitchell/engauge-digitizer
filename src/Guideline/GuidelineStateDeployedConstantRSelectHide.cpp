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
#include "GuidelineStateDeployedConstantRSelectHide.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantRSelectHide::GuidelineStateDeployedConstantRSelectHide (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantRAbstract (context)
{
}

GuidelineStateDeployedConstantRSelectHide::~GuidelineStateDeployedConstantRSelectHide ()
{
}

void GuidelineStateDeployedConstantRSelectHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRSelectHide::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               false);

  context().guideline().setGraphicsItemVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantRSelectHide::doPaint () const
{
  return false;
}

void GuidelineStateDeployedConstantRSelectHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRSelectHide::end";
}

void GuidelineStateDeployedConstantRSelectHide::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantRSelectHide::handleGuidelineMode (bool visible,
                                                                     bool locked)
{
  if (locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_LOCK);
  } else if (visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_EDIT);
  }
}

void GuidelineStateDeployedConstantRSelectHide::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantRSelectHide::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantRSelectHide::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantRSelectHide::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_HIDE);
}
