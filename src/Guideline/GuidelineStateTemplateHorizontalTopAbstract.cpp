/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateHorizontalTopAbstract.h"
#include "Logger.h"

GuidelineStateTemplateHorizontalTopAbstract::GuidelineStateTemplateHorizontalTopAbstract (GuidelineStateContext &context) :
  GuidelineStateTemplateAbstract (context)
{
}

GuidelineStateTemplateHorizontalTopAbstract::~GuidelineStateTemplateHorizontalTopAbstract ()
{
}

QLineF GuidelineStateTemplateHorizontalTopAbstract::templateHomeLine (const QRectF &sceneRect)
{
  return QLineF (sceneRect.topLeft(),
                 sceneRect.topRight());
}
