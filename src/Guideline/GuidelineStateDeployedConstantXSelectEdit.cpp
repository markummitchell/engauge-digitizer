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
#include "GuidelineStateDeployedConstantXSelectEdit.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantXSelectEdit::GuidelineStateDeployedConstantXSelectEdit (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantXAbstract (context)
{
}

GuidelineStateDeployedConstantXSelectEdit::~GuidelineStateDeployedConstantXSelectEdit ()
{
}

void GuidelineStateDeployedConstantXSelectEdit::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXSelectEdit::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon (GuidelineFormat::HOVER_OFF,
               false);
}

bool GuidelineStateDeployedConstantXSelectEdit::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantXSelectEdit::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXSelectEdit::end";
}

void GuidelineStateDeployedConstantXSelectEdit::handleActiveChange (bool active)
{
  if (!active) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_UNSELECT_EDIT);
  }
}

void GuidelineStateDeployedConstantXSelectEdit::handleGuidelineMode (bool visible,
                                                                     bool locked)
{
  // Currently visible and not locked
  if (visible && locked) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_LOCK);
  } else if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_HIDE);
  }
}

void GuidelineStateDeployedConstantXSelectEdit::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_EDIT_HOVER);
}

void GuidelineStateDeployedConstantXSelectEdit::handleHoverLeaveEvent ()
{
}

void GuidelineStateDeployedConstantXSelectEdit::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_HANDLE_X,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_EDIT);
}

QString GuidelineStateDeployedConstantXSelectEdit::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_EDIT);
}
