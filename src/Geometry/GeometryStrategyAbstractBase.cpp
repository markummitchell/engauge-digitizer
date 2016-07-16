/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GeometryStrategyAbstractBase.h"
#include "Transformation.h"

GeometryStrategyAbstractBase::GeometryStrategyAbstractBase()
{
}

GeometryStrategyAbstractBase::~GeometryStrategyAbstractBase()
{
}

void GeometryStrategyAbstractBase::calculatePositionsGraph (const Points &points,
                                                            const Transformation &transformation,
                                                            QVector<QPointF> &positionsGraph) const
{
  positionsGraph.clear();

  for (int i = 0; i < points.size(); i++) {
    const Point &pointScreen = points [i];
    QPointF posScreen = pointScreen.posScreen ();
    QPointF posGraph;

    transformation.transformScreenToRawGraph (posScreen,
                                              posGraph);

    positionsGraph.push_back (posGraph);
  }
}
