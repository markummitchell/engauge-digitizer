/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateVerticalLeft.h"
#include "Logger.h"

GuidelineStateTemplateVerticalLeft::GuidelineStateTemplateVerticalLeft (GuidelineStateContext &context) :
  GuidelineStateTemplateAbstract (context)
{
}

GuidelineStateTemplateVerticalLeft::~GuidelineStateTemplateVerticalLeft ()
{
}

void GuidelineStateTemplateVerticalLeft::begin ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalLeft::begin";

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(context().guideline().lineWidthTemplate(),
                                                                sceneRect ()));
}

void GuidelineStateTemplateVerticalLeft::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalLeft::end";
}

void GuidelineStateTemplateVerticalLeft::handleMousePress (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalLeft::handleMousePress";

  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_VERTICAL,
                          GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT);
}

void GuidelineStateTemplateVerticalLeft::handleMouseRelease ()
{
  // Not called
}

QString GuidelineStateTemplateVerticalLeft::state () const
{
  return ("GuidelineStateTemplateVerticalLeft");
}

QLineF GuidelineStateTemplateVerticalLeft::templateHomeLine (double lineWidth,
                                                             const QRectF &sceneRect)
{
  return QLineF (sceneRect.bottomLeft() + QPointF (lineWidth, 0),
                 sceneRect.topLeft() + QPointF (lineWidth, 0));
}
