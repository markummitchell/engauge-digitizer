/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GeometryStrategyRelationSmooth.h"
#include <qmath.h>
#include "Transformation.h"

GeometryStrategyRelationSmooth::GeometryStrategyRelationSmooth()
{
}

GeometryStrategyRelationSmooth::~GeometryStrategyRelationSmooth()
{
}

void GeometryStrategyRelationSmooth::calculateGeometry (const Points &points,
                                                        const Transformation &transformation,
                                                        QString &funcArea,
                                                        QString &polyArea,                                                        QVector<QString> &x,
                                                        QVector<QString> &y,
                                                        QVector<QString> &distanceGraphForward,
                                                        QVector<QString> &distancePercentForward,
                                                        QVector<QString> &distanceGraphBackward,
                                                        QVector<QString> &distancePercentBackward) const
{
  int i;

  QVector<QPointF> positionsGraph;
  calculatePositionsGraph (points,
                           transformation,
                           positionsGraph);

  // Area is computed using trapezoidal integration using using four points (x(I),0) (x(I),y(I)) (x(I+1),0) (y(I+1))
  double fArea = 0;

  // Distance is computed using linear segments between (x(I),y(I)) and (x(I+1),y(I+1))
  double distance = 0;

  // Compute x and y coordinates and cumulative distance vector
  double xILast = 0, yILast = 0;
  QVector<double> distanceGraphDouble;
  for (i = 0; i < positionsGraph.size(); i++) {

    double xI = positionsGraph [i].x();
    double yI = positionsGraph [i].y();
    double area = 0.5 * (yILast + yI) * (xI - xILast);
    double distGraph = qSqrt ((xI - xILast) * (xI - xILast) + (yI - yILast) * (yI - yILast));

    x.push_back (QString::number (xI));
    y.push_back (QString::number (yI));
    distanceGraphDouble.push_back (distance);

    if (i > 0) {
      fArea += area;
      distance += distGraph;
    }

    xILast = xI;
    yILast = yI;
  }

  // Compute distance columns
  double dTotal = qMax (1.0, distanceGraphDouble [distanceGraphDouble.size() - 1]);
  for (i = 0; i < distanceGraphDouble.size (); i++) {
    double d = distanceGraphDouble [i];
    distanceGraphForward.push_back (QString::number (d));
    distancePercentForward.push_back (QString::number (100.0 * d / dTotal));
    distanceGraphBackward.push_back (QString::number (dTotal - d));
    distancePercentBackward.push_back (QString::number (100.0 * (dTotal - d) / dTotal));
  }

  // Set header values
  funcArea = QString::number (fArea);
  polyArea = "";
}
