/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "FormatCoordsUnits.h"
#include "GeometryStrategyAbstractBase.h"
#include <qmath.h>
#include <QPointF>
#include "Spline.h"
#include "SplinePair.h"
#include "Transformation.h"
#include <vector>

using namespace std;

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

double GeometryStrategyAbstractBase::functionArea (const QVector<QPointF> &positionsGraph) const
{
  // Integrate using trapezoidal approximation to get the area under the function
  double sum = 0, xLast = 0, yLast = 0;
  for (int i = 1; i < positionsGraph.size (); i++) {
    double x = positionsGraph [i].x();
    double y = positionsGraph [i].y();
    double area = 0.5 * (y + yLast) * (x - xLast);
    sum += area;
    xLast = x;
    yLast = y;
  }

  return sum;
}

void GeometryStrategyAbstractBase::insertSubintervalsAndLoadDistances (int subintervalsPerInterval,
                                                                       const QVector<QPointF> &positionsGraph,
                                                                       QVector<QPointF> &positionsGraphWithSubintervals,
                                                                       QVector<QString> &distanceGraphForward,
                                                                       QVector<QString> &distancePercentForward,
                                                                       QVector<QString> &distanceGraphBackward,
                                                                       QVector<QString> &distancePercentBackward) const
{
  if (positionsGraph.size () > 0) {

    int i;

    // Fit splines to the points
    vector<double> t;
    vector<SplinePair> xy;
    for (int i = 0; i < positionsGraph.size (); i++) {
      t.push_back ((double) i);
      xy.push_back (SplinePair (positionsGraph [i].x(),
                                positionsGraph [i].y()));
    }

    Spline spline (t,
                   xy);

    // Loop over the original points, with one original point per original interval
    QVector<double> distanceGraphDouble;
    double xLast = 0, yLast = 0, distance = 0;
    for (i = 0; i < positionsGraph.size(); i++) {

      // In the interval i-1 to i we insert points to create smaller subintervals
      for (int subinterval = 0; subinterval < subintervalsPerInterval; subinterval++) {

        // Go from i-1 (exclusive) to i (inclusive)
        double t = (double) (i - 1.0) + (double) (subinterval + 1) / (double) (subintervalsPerInterval);

        SplinePair splinePair = spline.interpolateCoeff (t);

        double x = splinePair.x ();
        double y = splinePair.y ();

        // All points from intervals where i>0, and last point from interval i=0
        if (i > 0 || subinterval == subintervalsPerInterval - 1) {

          // Insert one of several new points for each original point
          positionsGraphWithSubintervals.push_back (QPointF (x, y));

        }

        if (i > 0) {

          // Add to cumulative distance
          distance += qSqrt ((x - xLast) * (x - xLast) + (y - yLast) * (y - yLast));

        }

        xLast = x;
        yLast = y;
      }

      // Insert one distance entry for each original point
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
  }
}

void GeometryStrategyAbstractBase::loadXY (const QVector<QPointF> &positionsGraph,
                                           const DocumentModelCoords &modelCoords,
                                           const MainWindowModel &modelMainWindow,
                                           const Transformation &transformation,
                                           QVector<QString> &x,
                                           QVector<QString> &y) const
{
  FormatCoordsUnits formatCoordsUnits;

  for (int i = 0; i < positionsGraph.size(); i++) {

    double xI = positionsGraph [i].x();
    double yI = positionsGraph [i].y();

    QString xFormatted, yFormatted;
    formatCoordsUnits.unformattedToFormatted (xI,
                                              yI,
                                              modelCoords,
                                              modelMainWindow,
                                              xFormatted,
                                              yFormatted,
                                              transformation);
    x.push_back (xFormatted);
    y.push_back (yFormatted);

  }
}

double GeometryStrategyAbstractBase::polygonAreaForSimplyConnected (const QVector<QPointF> &points) const
{
  // Shoelace formula
  int N = points.size ();

  double sum = 0.0;
  if (N > 0) {


    for (int i = 0; i < N - 1; i++) {
      sum += points [i].x() * points [i + 1].y() - points [i + 1].x() * points [i].y();
    }

    sum += points [N  - 1].x() * points [0].y() - points [0].x() * points [N - 1].y ();
  }

  return qAbs (sum) / 2.0;
}
