/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateVerticalRight.h"
#include "Logger.h"

GuidelineStateTemplateVerticalRight::GuidelineStateTemplateVerticalRight (GuidelineStateContext &context) :
  GuidelineStateTemplateAbstract (context)
{
}

GuidelineStateTemplateVerticalRight::~GuidelineStateTemplateVerticalRight ()
{
}

void GuidelineStateTemplateVerticalRight::begin ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalRight::begin";

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(context().guideline().lineWidthTemplate(),
                                                                diagonal (sceneRect ()),
                                                                sceneRect ()));
}

void GuidelineStateTemplateVerticalRight::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalRight::end";
}

void GuidelineStateTemplateVerticalRight::handleMousePress ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalRight::handleMousePress";

  QLineF line = templateHomeLine(context().guideline().lineWidthTemplate(),
                                 diagonal (sceneRect ()),
                                 sceneRect ());

  handleMousePressCommon (line,
                          GUIDELINE_STATE_DEPLOYED_VERTICAL,
                          GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT);
}

void GuidelineStateTemplateVerticalRight::handleMouseRelease ()
{
  // Not called
}

QString GuidelineStateTemplateVerticalRight::state () const
{
  return ("GuidelineStateTemplateVerticalRight");
}

QLineF GuidelineStateTemplateVerticalRight::templateHomeLine (double lineWidth,
                                                              double diagonal,
                                                              const QRectF &sceneRect)
{
  return QLineF (sceneRect.bottomRight() + QPointF (-0.5 * lineWidth, diagonal),
                 sceneRect.topRight() + QPointF (-0.5 * lineWidth, -1.0 * diagonal));
}
