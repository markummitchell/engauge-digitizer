/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GeometryStrategyFunctionSmooth.h"
#include "Spline.h"
#include "SplineDrawer.h"
#include "SplinePair.h"
#include "Transformation.h"

using namespace std;

GeometryStrategyFunctionSmooth::GeometryStrategyFunctionSmooth()
{
}

GeometryStrategyFunctionSmooth::~GeometryStrategyFunctionSmooth()
{
}

void GeometryStrategyFunctionSmooth::calculateGeometry (const Points &points,
                                                        const DocumentModelCoords &modelCoords,
                                                        const DocumentModelGeneral &modelGeneral,
                                                        const MainWindowModel &modelMainWindow,
                                                        const Transformation &transformation,
                                                        QString &funcArea,
                                                        QString &polyArea,
                                                        QVector<QString> &x,
                                                        QVector<QString> &y,
                                                        QVector<bool> &isPotentialExportAmbiguity,
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
  double fArea = functionArea (positionsGraphWithSubintervals);

  loadXY (positionsGraph,
          modelCoords,
          modelGeneral,
          modelMainWindow,
          transformation,
          x,
          y);

  loadSmoothAmbiguityVector (x,
                             y,
                             transformation,
                             isPotentialExportAmbiguity);

  // Set header values
  funcArea = QString::number (fArea);
  polyArea = "";
}

void GeometryStrategyFunctionSmooth::loadSmoothAmbiguityVector (QVector<QString> &x,
                                                                QVector<QString> &y,
                                                                const Transformation &transformation,
                                                                QVector<bool> &isPotentialExportAmbiguity) const
{
  // There are N-1 segments for N points
  int numSegments = x.size () - 1;

  // Graph/screen transformation must be defined for SplineDrawer, and
  // at least one point must be defined for Spline. Even better, one segment
  // must be defined for Spline
  if (transformation.transformIsDefined() &&
      numSegments > 0) {

    // Create spline
    vector<double> t (unsigned (x.size ()));
    vector<SplinePair> xy (unsigned (x.size ()));
    for (unsigned int i = 0; i < unsigned (x.size ()); i++) {
      t [i] = i;
      xy [i] = SplinePair (x.at (signed (i)).toDouble (),
                           y.at (signed (i)).toDouble ());
    }
    Spline s (t,
              xy);

    SplineDrawer sd (transformation);

    for (int segment = 0; segment < numSegments; segment++) {
      bool isMultiValued = sd.segmentIsMultiValued (s,
                                                    x.size (),
                                                    segment);
      isPotentialExportAmbiguity.push_back (isMultiValued);
    }
  } else {

    for (int segment = 0; segment < numSegments; segment++) {
      isPotentialExportAmbiguity.push_back (false);
    }
  }
}
