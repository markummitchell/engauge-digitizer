/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateVerticalRightShow.h"
#include "Logger.h"

GuidelineStateTemplateVerticalRightShow::GuidelineStateTemplateVerticalRightShow (GuidelineStateContext &context) :
  GuidelineStateTemplateVerticalRightAbstract (context)
{
}

GuidelineStateTemplateVerticalRightShow::~GuidelineStateTemplateVerticalRightShow ()
{
}

void GuidelineStateTemplateVerticalRightShow::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateVerticalRightShow::begin";

  context().guideline().setVisible (true); // Undo setVisible(false) from Hide class

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(context().guideline().lineWidthTemplate(),
                                                                sceneRect ()));
}

bool GuidelineStateTemplateVerticalRightShow::doPaint () const
{
  return true;
}

void GuidelineStateTemplateVerticalRightShow::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateVerticalRightShow::end";
}

void GuidelineStateTemplateVerticalRightShow::handleMousePress (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalRightShow::handleMousePress";

  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_VERTICAL_SHOW,
                          GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_SHOW);
}

void GuidelineStateTemplateVerticalRightShow::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_HIDE);
  }
}

QString GuidelineStateTemplateVerticalRightShow::state () const
{
  return ("GuidelineStateTemplateVerticalRightShow");
}
