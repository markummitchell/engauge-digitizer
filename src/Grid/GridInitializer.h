#ifndef GRID_INITIALIZER_H
#define GRID_INITIALIZER_H

#include "DocumentModelGridDisplay.h"
#include <QRectF>

class DocumentModelCoords;

/// This class initializes the count, start, step and stop parameters for one coordinate (either x/theta or y/range)
class GridInitializer
{
 public:
  /// Single constructor
  GridInitializer();

  /// Initialize given the boundaries of the graph coordinates 
  DocumentModelGridDisplay initialize (const QRectF &boundingRectGraph,
                                       const DocumentModelCoords &modelCoords) const;

 private:

  // Given the min and max values on an axis, this method picks start, delta and stop
  // values that nicely bound the low and high values. Key in algorithm is to minimize
  // number of significant digits in start, delta and stop
  void axisScale (double xMin,
                  double xMax,
                  bool linearAxis,
                  double &xStart,
                  double &xStop,
                  double &xDelta,
                  int &count) const;

  double roundOffToPower (double arg,
                          int roundOffPower) const;

  // Compute power of 10 for input value, rounding down to nearest integer solution of value>=10**solution
  int valuePower (double value) const;

  const QRectF m_boundingRectGraph;
};

#endif // GRID_INITIALIZER_H
