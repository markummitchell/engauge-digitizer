/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Guideline.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedHorizontalHide.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedHorizontalHide::GuidelineStateDeployedHorizontalHide (GuidelineStateContext &context) :
  GuidelineStateDeployedHorizontalAbstract (context)
{
}

GuidelineStateDeployedHorizontalHide::~GuidelineStateDeployedHorizontalHide ()
{
}

void GuidelineStateDeployedHorizontalHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedHorizontalHide::begin";

  beginCommon (GuidelineFormat::HOVER_OFF);

  context().guideline().setVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedHorizontalHide::doPaint () const
{
  return false;
}

void GuidelineStateDeployedHorizontalHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedHorizontalHide::end";
}

void GuidelineStateDeployedHorizontalHide::handleHoverEnterEvent ()
{
  // Noop
}

void GuidelineStateDeployedHorizontalHide::handleHoverLeaveEvent ()
{
  // Noop
}

void GuidelineStateDeployedHorizontalHide::handleMousePress (const QPointF & /* posScene */)
{
}

void GuidelineStateDeployedHorizontalHide::handleShowHide (bool show)
{
  if (show) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_HORIZONTAL_NORMAL);
  }
}

QString GuidelineStateDeployedHorizontalHide::state () const
{
  return ("GuidelineStateDeployedHorizontalHide");
}
