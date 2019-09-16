/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateVerticalLeftShow.h"
#include "Logger.h"

GuidelineStateTemplateVerticalLeftShow::GuidelineStateTemplateVerticalLeftShow (GuidelineStateContext &context) :
  GuidelineStateTemplateVerticalLeftAbstract (context)
{
}

GuidelineStateTemplateVerticalLeftShow::~GuidelineStateTemplateVerticalLeftShow ()
{
}

void GuidelineStateTemplateVerticalLeftShow::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateVerticalLeftShow::begin";

  context().guideline().setVisible (true); // Undo setVisible(false) from Hide class

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(context().guideline().lineWidthTemplate(),
                                                                sceneRect ()));
}

bool GuidelineStateTemplateVerticalLeftShow::doPaint () const
{
  return true;
}

void GuidelineStateTemplateVerticalLeftShow::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateVerticalLeftShow::end";
}

void GuidelineStateTemplateVerticalLeftShow::handleMousePress (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalLeftShow::handleMousePress";

  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_VERTICAL_SHOW,
                          GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_SHOW);
}

void GuidelineStateTemplateVerticalLeftShow::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_HIDE);
  }
}

QString GuidelineStateTemplateVerticalLeftShow::state () const
{
  return ("GuidelineStateTemplateVerticalLeftShow");
}
