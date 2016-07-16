/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GeometryStrategyRelationStraight.h"
#include "Transformation.h"

GeometryStrategyRelationStraight::GeometryStrategyRelationStraight()
{
}

GeometryStrategyRelationStraight::~GeometryStrategyRelationStraight()
{
}

void GeometryStrategyRelationStraight::calculateGeometry (const Points &points,
                                                          const Transformation &transformation,
                                                          QVector<QString> &x,
                                                          QVector<QString> &y,
                                                          QVector<QString> &distanceGraph,
                                                          QVector<QString> &distancePercent) const
{
  for (int i = 0; i < points.size(); i++) {
    const Point &point = points [i];
    QPointF posScreen = point.posScreen ();
    QPointF posGraph;

    transformation.transformScreenToRawGraph (posScreen,
                                              posGraph);

    x.push_back (QString::number (posGraph.x()));
    y.push_back (QString::number (posGraph.y()));
    distanceGraph.push_back (QString::number (1.0));
    distancePercent.push_back (QString::number (2.0));
  }
}
