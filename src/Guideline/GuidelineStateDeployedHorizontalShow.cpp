/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedHorizontalShow.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedHorizontalShow::GuidelineStateDeployedHorizontalShow (GuidelineStateContext &context) :
  GuidelineStateDeployedHorizontalAbstract (context)
{
}

GuidelineStateDeployedHorizontalShow::~GuidelineStateDeployedHorizontalShow ()
{
}

void GuidelineStateDeployedHorizontalShow::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedHorizontalShow::begin";

  context().guideline().setVisible (true); // Undo setVisible from GuidelineStateDeployedHorizontalHide

  beginCommon ();
}

bool GuidelineStateDeployedHorizontalShow::doPaint () const
{
  return true;
}

void GuidelineStateDeployedHorizontalShow::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedHorizontalShow::end";
}

void GuidelineStateDeployedHorizontalShow::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_HORIZONTAL_SHOW,
                          GUIDELINE_STATE_NULL);
}

void GuidelineStateDeployedHorizontalShow::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_HORIZONTAL_HIDE);
  }
}

QString GuidelineStateDeployedHorizontalShow::state () const
{
  return ("GuidelineStateDeployedHorizontalShow");
}
