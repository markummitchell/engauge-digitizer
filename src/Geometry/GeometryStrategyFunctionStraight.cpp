/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GeometryStrategyFunctionStraight.h"
#include "Transformation.h"

GeometryStrategyFunctionStraight::GeometryStrategyFunctionStraight()
{
}

GeometryStrategyFunctionStraight::~GeometryStrategyFunctionStraight()
{
}

void GeometryStrategyFunctionStraight::calculateGeometry (const Points &points,
                                                          const DocumentModelCoords &modelCoords,
                                                          const DocumentModelGeneral &modelGeneral,
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
  const int NUM_SUB_INTERVALS_STRAIGHT = 1; // Value of one with trapezoidal integration results in calculations using straight lines between points

  QVector<QPointF> positionsGraph, positionsGraphWithSubintervals;
  calculatePositionsGraph (points,
                           transformation,
                           positionsGraph);

  insertSubintervalsAndLoadDistances (NUM_SUB_INTERVALS_STRAIGHT,
                                      positionsGraph,
                                      positionsGraphWithSubintervals,
                                      distanceGraphForward,
                                      distancePercentForward,
                                      distanceGraphBackward,
                                      distancePercentBackward);
  double fArea = functionArea (positionsGraphWithSubintervals);

  loadXY (positionsGraph,
          modelCoords,
          modelGeneral,
          modelMainWindow,
          transformation,
          x,
          y);

  // Set header values
  funcArea = QString::number (fArea);
  polyArea = "";
}
