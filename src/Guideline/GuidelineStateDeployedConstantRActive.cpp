/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantRActive.h"
#include "Logger.h"
#include <QGraphicsScene>
#include "Transformation.h"

GuidelineStateDeployedConstantRActive::GuidelineStateDeployedConstantRActive (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantRAbstract (context)
{
}

GuidelineStateDeployedConstantRActive::~GuidelineStateDeployedConstantRActive ()
{
}

void GuidelineStateDeployedConstantRActive::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRActive::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateDeployedConstantRHide

  beginCommon (GuidelineFormat::HOVER_OFF);
}

bool GuidelineStateDeployedConstantRActive::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantRActive::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRActive::end";
}

void GuidelineStateDeployedConstantRActive::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantRActive::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HOVER);
}

void GuidelineStateDeployedConstantRActive::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HOVER
}

void GuidelineStateDeployedConstantRActive::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE,
                          GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateDeployedConstantRActive::handleVisibleChange (bool visible)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HIDE);
  }
}

QString GuidelineStateDeployedConstantRActive::state () const
{
  return ("GuidelineStateDeployedConstantRActive");
}
