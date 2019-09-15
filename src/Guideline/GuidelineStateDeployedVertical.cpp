/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedVertical.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedVertical::GuidelineStateDeployedVertical (GuidelineStateContext &context) :
  GuidelineStateDeployedAbstract (context)
{
}

GuidelineStateDeployedVertical::~GuidelineStateDeployedVertical ()
{
}

void GuidelineStateDeployedVertical::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_VERTICAL,
                          GUIDELINE_STATE_NULL);
}

QLineF GuidelineStateDeployedVertical::lineFromPoint (const QPointF &point) const
{
  double height = context().guideline().scene()->height();

  return QLineF (QPointF (point.x(), 0),
                 QPointF (point.x(), height - 1));
}

QString GuidelineStateDeployedVertical::state () const
{
  return ("GuidelineStateDeployedVertical");
}
