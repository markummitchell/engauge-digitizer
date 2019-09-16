/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateHorizontalTopShow.h"
#include "Logger.h"

GuidelineStateTemplateHorizontalTopShow::GuidelineStateTemplateHorizontalTopShow (GuidelineStateContext &context) :
  GuidelineStateTemplateHorizontalTopAbstract (context)
{
}

GuidelineStateTemplateHorizontalTopShow::~GuidelineStateTemplateHorizontalTopShow ()
{
}

void GuidelineStateTemplateHorizontalTopShow::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateHorizontalTopShow::begin";

  context().guideline().setVisible (true); // Undo setVisible(false) from Hide class

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(context().guideline().lineWidthTemplate(),
                                                                sceneRect ()));
}

bool GuidelineStateTemplateHorizontalTopShow::doPaint () const
{
  return true;
}

void GuidelineStateTemplateHorizontalTopShow::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateHorizontalTopShow::end";
}

void GuidelineStateTemplateHorizontalTopShow::handleMousePress (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalTopShow::handleMousePress";

  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_HORIZONTAL_SHOW,
                          GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_SHOW);
}

void GuidelineStateTemplateHorizontalTopShow::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_HIDE);
  }
}

QString GuidelineStateTemplateHorizontalTopShow::state () const
{
  return ("GuidelineStateTemplateHorizontalTopShow");
}
