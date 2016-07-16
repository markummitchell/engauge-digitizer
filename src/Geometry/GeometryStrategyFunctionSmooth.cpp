/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GeometryStrategyFunctionSmooth.h"
#include <qdebug.h>
#include <qmath.h>
#include "Spline.h"
#include "SplinePair.h"
#include "Transformation.h"
#include <vector>

using namespace std;

GeometryStrategyFunctionSmooth::GeometryStrategyFunctionSmooth()
{
}

GeometryStrategyFunctionSmooth::~GeometryStrategyFunctionSmooth()
{
}

void GeometryStrategyFunctionSmooth::calculateGeometry (const Points &points,
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
  const int NUM_SUB_INTERVALS = 10; // One input point becomes NUM_SUB_INTERVALS points to account for smoothing
  int i;

  QVector<QPointF> positionsGraph;
  calculatePositionsGraph (points,
                           transformation,
                           positionsGraph);

  // Fit splines to the points
  vector<double> t;
  vector<SplinePair> xy;
  for (i = 0; i < positionsGraph.size (); i++) {
    t.push_back ((double) i);
    xy.push_back (SplinePair (positionsGraph [i].x(),
                              positionsGraph [i].y()));
  }
  Spline spline (t,
                 xy);

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

    x.push_back (QString::number (xI));
    y.push_back (QString::number (yI));

    for (int subinterval = 0; subinterval < NUM_SUB_INTERVALS; subinterval++) {

      double t = (double) i + (double) (subinterval + 1) / (double) (NUM_SUB_INTERVALS);

      SplinePair splinePair = spline.interpolateCoeff (t);

      xI = splinePair.x ();
      yI = splinePair.y ();

      qDebug() << t << ", " << xI << ", " << yI;

      if (i > 0) {

        double area = 0.5 * (yILast + yI) * (xI - xILast);
        double distGraph = qSqrt ((xI - xILast) * (xI - xILast) + (yI - yILast) * (yI - yILast));

        fArea += area;
        distance += distGraph;

      }

      xILast = xI;
      yILast = yI;
    }

    distanceGraphDouble.push_back (distance);

  }

  // Compute distance columns
  double dTotal = qMax (1.0, distanceGraphDouble [distanceGraphDouble.size() - 1]); // qMax prevents divide by zero
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
