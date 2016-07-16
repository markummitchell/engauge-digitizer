/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GeometryStrategyRelationSmooth.h"
#include "Transformation.h"

GeometryStrategyRelationSmooth::GeometryStrategyRelationSmooth()
{
}

GeometryStrategyRelationSmooth::~GeometryStrategyRelationSmooth()
{
}

void GeometryStrategyRelationSmooth::calculateGeometry (const Points &points,
                                                        const DocumentModelCoords &modelCoords,
                                                        const MainWindowModel &modelMainWindow,
                                                        const Transformation &transformation,
                                                        QString &funcArea,
                                                        QString &polyArea,
                                                        QVector<QString> &x,
                                                        QVector<QString> &y,
                                                        QVector<QString> &distanceGraphForward,
                                                        QVector<QString> &distancePercentForward,
                                                        QVector<QString> &distanceGraphBackward,
                                                        QVector<QString> &distancePercentBackward) const
{
  const int NUM_SUB_INTERVALS_SMOOTH = 10; // One input point becomes NUM_SUB_INTERVALS points to account for smoothing

  QVector<QPointF> positionsGraph, positionsGraphWithSubintervals;
  calculatePositionsGraph (points,
                           transformation,
                           positionsGraph);

  insertSubintervalsAndLoadDistances (NUM_SUB_INTERVALS_SMOOTH,
                                      positionsGraph,
                                      positionsGraphWithSubintervals,
                                      distanceGraphForward,
                                      distancePercentForward,
                                      distanceGraphBackward,
                                      distancePercentBackward);
  double pArea = polygonAreaForSimplyConnected (positionsGraphWithSubintervals);

  loadXY (positionsGraph,
          modelCoords,
          modelMainWindow,
          transformation,
          x,
          y);

  // Set header values
  funcArea = "";
  polyArea = QString::number (pArea);
}
