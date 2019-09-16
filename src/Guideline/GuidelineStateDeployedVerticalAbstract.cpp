/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedVerticalAbstract.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedVerticalAbstract::GuidelineStateDeployedVerticalAbstract (GuidelineStateContext &context) :
  GuidelineStateDeployedAbstract (context)
{
}

GuidelineStateDeployedVerticalAbstract::~GuidelineStateDeployedVerticalAbstract ()
{
}

QLineF GuidelineStateDeployedVerticalAbstract::lineFromPoint (const QPointF &point) const
{
  double height = context().guideline().scene()->height();

  return QLineF (QPointF (point.x(), 0),
                 QPointF (point.x(), height - 1));
}
