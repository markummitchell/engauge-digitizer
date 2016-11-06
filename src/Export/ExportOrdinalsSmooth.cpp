/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ExportOrdinalsSmooth.h"
#include "LinearToLog.h"
#include "Logger.h"
#include <qdebug.h>
#include <qmath.h>
#include <QPointF>
#include "Spline.h"
#include "Transformation.h"

using namespace std;

ExportOrdinalsSmooth::ExportOrdinalsSmooth ()
{
}

void ExportOrdinalsSmooth::loadSplinePairsWithoutTransformation (const Points &points,
                                                                 vector<double> &t,
                                                                 vector<SplinePair> &xy) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportOrdinalsSmooth::loadSplinePairsWithoutTransformation";

  Points::const_iterator itrP;
  for (itrP = points.begin(); itrP != points.end(); itrP++) {
    const Point &point = *itrP;
    QPointF posScreen = point.posScreen();

    t.push_back (point.ordinal ());
    xy.push_back (SplinePair (posScreen.x(),
                              posScreen.y()));
  }
}

void ExportOrdinalsSmooth::loadSplinePairsWithTransformation (const Points &points,
                                                              const Transformation &transformation,
                                                              bool isLogXTheta,
                                                              bool isLogYRadius,
                                                              vector<double> &t,
                                                              vector<SplinePair> &xy) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportOrdinalsSmooth::loadSplinePairsWithTransformation";

  LinearToLog linearToLog;

  Points::const_iterator itrP;
  for (itrP = points.begin(); itrP != points.end(); itrP++) {
    const Point &point = *itrP;
    QPointF posScreen = point.posScreen();
    QPointF posGraph;
    transformation.transformScreenToRawGraph (posScreen,
                                              posGraph);

    t.push_back (point.ordinal ());
    xy.push_back (SplinePair (linearToLog.linearize (posGraph.x(), isLogXTheta),
                              linearToLog.linearize (posGraph.y(), isLogYRadius)));
  }
}

ExportValuesOrdinal ExportOrdinalsSmooth::ordinalsAtIntervalsGraph (const vector<double> &t,
                                                                    const vector<SplinePair> &xy,
                                                                    double pointsInterval) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportOrdinalsSmooth::ordinalsAtIntervalsGraph";

  const double NUM_SMALLER_INTERVALS = 1000;

  // Results. Initially empty, but at the end it will have tMin, ..., tMax
  ExportValuesOrdinal ordinals;

  // Spline class requires at least one point
  if (xy.size() > 0) {

    // Fit a spline
    Spline spline (t,
                   xy);

    // Integrate the distances for the subintervals
    double integratedSeparation = 0;
    QPointF posLast (xy [0].x(),
                     xy [0].y());

    // Simplest method to find the intervals is to break up the curve into many smaller intervals, and then aggregate them
    // into intervals that, as much as possible, have the desired length. Simplicity wins out over accuracy in this
    // approach - accuracy is sacrificed to achieve simplicity
    double tMin = t.front();
    double tMax = t.back();

    double tLast = 0.0;
    int iTLastInterval = 0;
    for (int iT = 0; iT < NUM_SMALLER_INTERVALS; iT++) {

      double t = tMin + ((tMax - tMin) * iT) / (NUM_SMALLER_INTERVALS - 1.0);

      SplinePair pairNew = spline.interpolateCoeff(t);

      QPointF posNew = QPointF (pairNew.x(),
                                pairNew.y());

      QPointF posDelta = posNew - posLast;
      double integratedSeparationDelta = qSqrt (posDelta.x() * posDelta.x() + posDelta.y() * posDelta.y());
      integratedSeparation += integratedSeparationDelta;

      while (integratedSeparation >= pointsInterval) {

        // End of current interval, and start of next interval. For better accuracy without having to crank up
        // the number of points by orders of magnitude, we use linear interpolation
        double sInterp;
        if (iT == 0) {
          sInterp = 0.0;
        } else {
          sInterp = (double) pointsInterval / (double) integratedSeparation;
        }
        double tInterp = (1.0 - sInterp) * tLast + sInterp * t;

        integratedSeparation -= pointsInterval; // Part of delta that was not used gets applied to next interval

        tLast = tInterp;
        ordinals.push_back (tInterp);
        iTLastInterval = iT;
      }

      tLast = t;
      posLast = posNew;
    }

    if (iTLastInterval < NUM_SMALLER_INTERVALS - 1) {

      // Add last point so we end up at tMax
      ordinals.push_back (tMax);

    }
  }

  return ordinals;
}
