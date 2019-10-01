/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantYActive.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedConstantYActive::GuidelineStateDeployedConstantYActive (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantYAbstract (context)
{
}

GuidelineStateDeployedConstantYActive::~GuidelineStateDeployedConstantYActive ()
{
}

void GuidelineStateDeployedConstantYActive::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYActive::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateDeployedConstantYHide

  beginCommon (GuidelineFormat::HOVER_OFF);
}

bool GuidelineStateDeployedConstantYActive::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantYActive::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYActive::end";
}

void GuidelineStateDeployedConstantYActive::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantYActive::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HOVER);
}

void GuidelineStateDeployedConstantYActive::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HOVER
}

void GuidelineStateDeployedConstantYActive::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE,
                          GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateDeployedConstantYActive::handleVisibleChange (bool visible)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HIDE);
  }
}

QString GuidelineStateDeployedConstantYActive::state () const
{
  return ("GuidelineStateDeployedConstantYActive");
}
