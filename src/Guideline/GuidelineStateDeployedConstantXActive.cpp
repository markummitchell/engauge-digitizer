/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantXActive.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedConstantXActive::GuidelineStateDeployedConstantXActive (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantXAbstract (context)
{
}

GuidelineStateDeployedConstantXActive::~GuidelineStateDeployedConstantXActive ()
{
}

void GuidelineStateDeployedConstantXActive::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXActive::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateDeployedConstantXHide

  beginCommon (GuidelineFormat::HOVER_OFF);
}

bool GuidelineStateDeployedConstantXActive::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantXActive::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXActive::end";
}

void GuidelineStateDeployedConstantXActive::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HOVER);
}

void GuidelineStateDeployedConstantXActive::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HOVER
}

void GuidelineStateDeployedConstantXActive::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE,
                          GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateDeployedConstantXActive::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HIDE);
  }
}

QString GuidelineStateDeployedConstantXActive::state () const
{
  return ("GuidelineStateDeployedConstantXActive");
}
