/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantYSelectEdit.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantYSelectEdit::GuidelineStateDeployedConstantYSelectEdit (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantYAbstract (context)
{
}

GuidelineStateDeployedConstantYSelectEdit::~GuidelineStateDeployedConstantYSelectEdit ()
{
}

void GuidelineStateDeployedConstantYSelectEdit::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYSelectEdit::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (false,
               false);

  context().guideline().setGraphicsItemVisible (true); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantYSelectEdit::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantYSelectEdit::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYSelectEdit::end";
}

void GuidelineStateDeployedConstantYSelectEdit::handleActiveChange (bool active)
{
  if (!active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_UNSELECT_EDIT);
  }
}

void GuidelineStateDeployedConstantYSelectEdit::handleGuidelineMode (bool visible,
                                                                     bool locked)
{
  // Currently visible and not locked
  if (visible && locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_LOCK);
  } else if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_HIDE);
  }
}

void GuidelineStateDeployedConstantYSelectEdit::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_EDIT_HOVER);
}

void GuidelineStateDeployedConstantYSelectEdit::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantYSelectEdit::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_Y,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_EDIT);
}

QString GuidelineStateDeployedConstantYSelectEdit::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_EDIT);
}
