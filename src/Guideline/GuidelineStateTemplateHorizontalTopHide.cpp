/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateHorizontalTopHide.h"
#include "Logger.h"

GuidelineStateTemplateHorizontalTopHide::GuidelineStateTemplateHorizontalTopHide (GuidelineStateContext &context) :
  GuidelineStateTemplateHorizontalTopAbstract (context)
{
}

GuidelineStateTemplateHorizontalTopHide::~GuidelineStateTemplateHorizontalTopHide ()
{
}

void GuidelineStateTemplateHorizontalTopHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateHorizontalTopHide::begin";

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(context().guideline().lineWidthTemplate(),
                                                                sceneRect ()));

  context().guideline().setVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateTemplateHorizontalTopHide::doPaint () const
{
  return false;
}

void GuidelineStateTemplateHorizontalTopHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateHorizontalTopHide::end";
}

void GuidelineStateTemplateHorizontalTopHide::handleMousePress (const QPointF & /* posScene */)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalTopHide::handleMousePress";
}

void GuidelineStateTemplateHorizontalTopHide::handleShowHide (bool show)
{
  if (show) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_SHOW);
  }
}

QString GuidelineStateTemplateHorizontalTopHide::state () const
{
  return ("GuidelineStateTemplateHorizontalTopHide");
}
