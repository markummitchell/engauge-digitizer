/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateHorizontalBottomShow.h"
#include "Logger.h"
#include <QObject>

GuidelineStateTemplateHorizontalBottomShow::GuidelineStateTemplateHorizontalBottomShow (GuidelineStateContext &context) :
  GuidelineStateTemplateHorizontalBottomAbstract (context)
{
}

GuidelineStateTemplateHorizontalBottomShow::~GuidelineStateTemplateHorizontalBottomShow ()
{
}

void GuidelineStateTemplateHorizontalBottomShow::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottomShow::begin";

  context().guideline().setVisible (true); // Undo setVisible(false) from Hide class

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(context().guideline().lineWidthTemplate(),
                                                                sceneRect ()));
}

bool GuidelineStateTemplateHorizontalBottomShow::doPaint () const
{
  return true;
}

void GuidelineStateTemplateHorizontalBottomShow::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottomShow::end";
}

void GuidelineStateTemplateHorizontalBottomShow::handleMousePress (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottomShow::handleMousePress";

  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_HORIZONTAL_SHOW,
                          GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_SHOW);
}

void GuidelineStateTemplateHorizontalBottomShow::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_HIDE);
  }
}

QString GuidelineStateTemplateHorizontalBottomShow::state () const
{
  return ("GuidelineStateTemplateHorizontalBottomShow");
}

