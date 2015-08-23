#ifndef EXPORT_ORDINALS_STRAIGHT_H
#define EXPORT_ORDINALS_STRAIGHT_H

#include "ExportValuesOrdinal.h"
#include "Point.h"
#include "Points.h"
#include <QList>
#include <QPointF>

class Transformation;

/// Utility class to interpolate points spaced evenly along a piecewise defined curve with line segments between points
class ExportOrdinalsStraight 
{
 public:
  /// Single constructor
  ExportOrdinalsStraight ();

  /// Compute ordinals, without any conversion to graph coordinates
  ExportValuesOrdinal ordinalsAtIntervalsGraphWithoutTransformation (const Points &points,
                                                                     double pointsInterval) const;

  /// Compute ordinals, converting screen coordinates to graph coordinates
  ExportValuesOrdinal ordinalsAtIntervalsGraphWithTransformation (const Points &points,
                                                                  const Transformation &transformation,
                                                                  double pointsInterval) const;
  
};

#endif // EXPORT_ORDINALS_STRAIGHT_H
