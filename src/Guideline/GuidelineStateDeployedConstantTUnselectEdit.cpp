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
#include "GuidelineStateDeployedConstantTUnselectEdit.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantTUnselectEdit::GuidelineStateDeployedConstantTUnselectEdit (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantTAbstract (context)
{
}

GuidelineStateDeployedConstantTUnselectEdit::~GuidelineStateDeployedConstantTUnselectEdit ()
{
}

void GuidelineStateDeployedConstantTUnselectEdit::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTUnselectEdit::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               true);

  context().guideline().setGraphicsItemVisible (true); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantTUnselectEdit::doPaint () const
{
  return false;
}

void GuidelineStateDeployedConstantTUnselectEdit::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTUnselectEdit::end";
}

void GuidelineStateDeployedConstantTUnselectEdit::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantTUnselectEdit::handleGuidelineMode (bool visible,
                                                               bool locked)
{
  if (visible || locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_UNSELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantTUnselectEdit::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantTUnselectEdit::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantTUnselectEdit::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantTUnselectEdit::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_UNSELECT_EDIT);
}
