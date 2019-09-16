/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedVerticalShow.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedVerticalShow::GuidelineStateDeployedVerticalShow (GuidelineStateContext &context) :
  GuidelineStateDeployedVerticalAbstract (context)
{
}

GuidelineStateDeployedVerticalShow::~GuidelineStateDeployedVerticalShow ()
{
}

void GuidelineStateDeployedVerticalShow::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedVerticalShow::begin";

  context().guideline().setVisible (true); // Undo setVisible from GuidelineStateDeployedVerticalHide

  beginCommon ();
}

bool GuidelineStateDeployedVerticalShow::doPaint () const
{
  return true;
}

void GuidelineStateDeployedVerticalShow::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedVerticalShow::end";
}

void GuidelineStateDeployedVerticalShow::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_VERTICAL_SHOW,
                          GUIDELINE_STATE_NULL);
}

void GuidelineStateDeployedVerticalShow::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_VERTICAL_HIDE);
  }
}

QString GuidelineStateDeployedVerticalShow::state () const
{
  return ("GuidelineStateDeployedVerticalShow");
}
