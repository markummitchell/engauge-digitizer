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
#include "GuidelineStateDeployedConstantTSelectEdit.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantTSelectEdit::GuidelineStateDeployedConstantTSelectEdit (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantTAbstract (context)
{
}

GuidelineStateDeployedConstantTSelectEdit::~GuidelineStateDeployedConstantTSelectEdit ()
{
}

void GuidelineStateDeployedConstantTSelectEdit::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTSelectEdit::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               false);
}

bool GuidelineStateDeployedConstantTSelectEdit::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantTSelectEdit::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTSelectEdit::end";
}

void GuidelineStateDeployedConstantTSelectEdit::handleActiveChange (bool active)
{
  if (!active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_UNSELECT_EDIT);
  }
}

void GuidelineStateDeployedConstantTSelectEdit::handleGuidelineMode (bool visible,
                                                                     bool locked)
{
  // Currently visible and not locked
  if (visible && locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_LOCK);
  } else if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_HIDE);
  }
}

void GuidelineStateDeployedConstantTSelectEdit::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_EDIT_HOVER);
}

void GuidelineStateDeployedConstantTSelectEdit::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantTSelectEdit::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_T,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_EDIT);
}

QString GuidelineStateDeployedConstantTSelectEdit::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_EDIT);
}
