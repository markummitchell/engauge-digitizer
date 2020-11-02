/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantYUnselectEdit.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantYUnselectEdit::GuidelineStateDeployedConstantYUnselectEdit (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantYAbstract (context)
{
}

GuidelineStateDeployedConstantYUnselectEdit::~GuidelineStateDeployedConstantYUnselectEdit ()
{
}

void GuidelineStateDeployedConstantYUnselectEdit::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYUnselectEdit::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (false,
               true);

  context().guideline().setGraphicsItemVisible (true); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantYUnselectEdit::doPaint () const
{
  return false;
}

void GuidelineStateDeployedConstantYUnselectEdit::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYUnselectEdit::end";
}

void GuidelineStateDeployedConstantYUnselectEdit::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantYUnselectEdit::handleGuidelineMode (bool visible,
                                                               bool locked)
{
  if (visible || locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_UNSELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantYUnselectEdit::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantYUnselectEdit::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantYUnselectEdit::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantYUnselectEdit::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_UNSELECT_EDIT);
}
