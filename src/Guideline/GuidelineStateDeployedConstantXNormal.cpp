/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantXNormal.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedConstantXNormal::GuidelineStateDeployedConstantXNormal (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantXAbstract (context)
{
}

GuidelineStateDeployedConstantXNormal::~GuidelineStateDeployedConstantXNormal ()
{
}

void GuidelineStateDeployedConstantXNormal::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXNormal::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateDeployedConstantXHide

  beginCommon (GuidelineFormat::HOVER_OFF);
}

bool GuidelineStateDeployedConstantXNormal::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantXNormal::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXNormal::end";
}

void GuidelineStateDeployedConstantXNormal::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HOVER);
}

void GuidelineStateDeployedConstantXNormal::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HOVER
}

void GuidelineStateDeployedConstantXNormal::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_X_NORMAL,
                          GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateDeployedConstantXNormal::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HIDE);
  }
}

QString GuidelineStateDeployedConstantXNormal::state () const
{
  return ("GuidelineStateDeployedConstantXNormal");
}
