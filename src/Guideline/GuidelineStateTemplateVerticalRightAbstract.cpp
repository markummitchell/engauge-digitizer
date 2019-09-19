/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateVerticalRightAbstract.h"
#include "Logger.h"

GuidelineStateTemplateVerticalRightAbstract::GuidelineStateTemplateVerticalRightAbstract (GuidelineStateContext &context) :
  GuidelineStateTemplateAbstract (context)
{
}

GuidelineStateTemplateVerticalRightAbstract::~GuidelineStateTemplateVerticalRightAbstract ()
{
}

QLineF GuidelineStateTemplateVerticalRightAbstract::templateHomeLine (const QRectF &sceneRect)
{
  return QLineF (sceneRect.bottomRight(),
                 sceneRect.topRight());
}
