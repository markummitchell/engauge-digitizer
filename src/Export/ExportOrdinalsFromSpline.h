#ifndef EXPORT_ORDINALS_FROM_SPLINE_H
#define EXPORT_ORDINALS_FROM_SPLINE_H

#include "ExportValuesOrdinal.h"
#include "Point.h"
#include "SplinePair.h"
#include <QList>
#include <vector>

typedef QList<Point> Points;

class Transformation;

/// Utility class to interpolate points spaced evenly along a piecewise defined curve
class ExportOrdinalsFromSpline 
{
 public:
  /// Single constructor
  ExportOrdinalsFromSpline ();

  /// Load t (=ordinal) and xy (=screen position) spline pairs, without any conversion to graph coordinates
  void loadSplinePairsWithoutTransformation (const Points &points,
                                             std::vector<double> &t,
                                             std::vector<SplinePair> &xy) const;

  /// Load t (=ordinal) and xy (=screen position) spline pairs, converting screen coordinates to graph coordinates
  void loadSplinePairsWithTransformation (const Points &points,
                                          const Transformation &transformation,
                                          std::vector<double> &t,
                                          std::vector<SplinePair> &xy) const;

  /// Perform the interpolation on the arrays loaded by the other methods
  ExportValuesOrdinal ordinalsAtIntervalsGraph (const std::vector<double> &t,
                                                const std::vector<SplinePair> &xy,
                                                double pointsInterval) const;
};

#endif // EXPORT_ORDINALS_FROM_SPLINE_H
