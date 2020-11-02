/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantRUnselectEdit.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantRUnselectEdit::GuidelineStateDeployedConstantRUnselectEdit (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantRAbstract (context)
{
}

GuidelineStateDeployedConstantRUnselectEdit::~GuidelineStateDeployedConstantRUnselectEdit ()
{
}

void GuidelineStateDeployedConstantRUnselectEdit::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRUnselectEdit::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (false,
               true);

  context().guideline().setGraphicsItemVisible (true); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantRUnselectEdit::doPaint () const
{
  return false;
}

void GuidelineStateDeployedConstantRUnselectEdit::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRUnselectEdit::end";
}

void GuidelineStateDeployedConstantRUnselectEdit::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantRUnselectEdit::handleGuidelineMode (bool visible,
                                                               bool locked)
{
  if (visible || locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_UNSELECT_LOCK);
  }
}

void GuidelineStateDeployedConstantRUnselectEdit::handleHoverEnterEvent ()
{
}

void GuidelineStateDeployedConstantRUnselectEdit::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantRUnselectEdit::handleMousePress (const QPointF & /* posScene */)
{
}

QString GuidelineStateDeployedConstantRUnselectEdit::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_UNSELECT_EDIT);
}
