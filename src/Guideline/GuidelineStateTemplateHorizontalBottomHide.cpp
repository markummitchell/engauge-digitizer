/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateHorizontalBottomHide.h"
#include "Logger.h"
#include <QObject>

GuidelineStateTemplateHorizontalBottomHide::GuidelineStateTemplateHorizontalBottomHide (GuidelineStateContext &context) :
  GuidelineStateTemplateHorizontalBottomAbstract (context)
{
}

GuidelineStateTemplateHorizontalBottomHide::~GuidelineStateTemplateHorizontalBottomHide ()
{
}

void GuidelineStateTemplateHorizontalBottomHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottomHide::begin";

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(context().guideline().lineWidthTemplate(),
                                                                sceneRect ()));

  context().guideline().setVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateTemplateHorizontalBottomHide::doPaint () const
{
  return false;
}

void GuidelineStateTemplateHorizontalBottomHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottomHide::end";
}

void GuidelineStateTemplateHorizontalBottomHide::handleMousePress (const QPointF & /* posScene */)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottomHide::handleMousePress";
}

void GuidelineStateTemplateHorizontalBottomHide::handleShowHide (bool show)
{
  if (show) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_SHOW);
  }
}

QString GuidelineStateTemplateHorizontalBottomHide::state () const
{
  return ("GuidelineStateTemplateHorizontalBottomHide");
}

