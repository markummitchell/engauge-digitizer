/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedVerticalHide.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedVerticalHide::GuidelineStateDeployedVerticalHide (GuidelineStateContext &context) :
  GuidelineStateDeployedVerticalAbstract (context)
{
}

GuidelineStateDeployedVerticalHide::~GuidelineStateDeployedVerticalHide ()
{
}

void GuidelineStateDeployedVerticalHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedVerticalHide::begin";

  beginCommon ();

  context().guideline().setVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedVerticalHide::doPaint () const
{
  return false;
}

void GuidelineStateDeployedVerticalHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedVerticalHide::end";
}

void GuidelineStateDeployedVerticalHide::handleMousePress (const QPointF & /* posScene */)
{
}

void GuidelineStateDeployedVerticalHide::handleShowHide (bool show)
{
  if (show) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_VERTICAL_SHOW);
  }
}

QString GuidelineStateDeployedVerticalHide::state () const
{
  return ("GuidelineStateDeployedVerticalHide");
}
