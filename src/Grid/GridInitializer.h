#ifndef GRID_INITIALIZER_H
#define GRID_INITIALIZER_H

#include "DocumentModelGridDisplay.h"
#include <QRectF>

class DocumentModelCoords;
class QSize;

class Transformation;

/// This class initializes the count, start, step and stop parameters for one coordinate (either x/theta or y/range)
class GridInitializer
{
 public:
  /// Single constructor
  GridInitializer();

  /// Compute axis scale count from the other axis parameters
  int computeCount (bool linearAxis,
                    double start,
                    double stop,
                    double step) const;

  /// Compute axis scale start from the other axis parameters
  double computeStart (bool linearAxis,
                       double stop,
                       double step,
                       int count) const;

  /// Compute axis scale step from the other axis parameters
  double computeStep (bool linearAxis,
                      double start,
                      double stop,
                      int count) const;

  /// Compute axis scale stop from the other axis parameters
  double computeStop (bool linearAxis,
                      double start,
                      double step,
                      int count) const;

  /// Initialize given the boundaries of the graph coordinates. The output is useful for the Checker class
  DocumentModelGridDisplay initializeWithNarrowCoverage (const QRectF &boundingRectGraph,
                                                         const DocumentModelCoords &modelCoords) const;

  /// Initialize given the boundaries of the graph coordinates, and then extra processing for polar coordinates:
  /// -# radial range expanded to cover the center (to remove hole at center) to the image corners
  ///    (to guarantee coverage at corners of graph)
  /// -# angular range is expanded to cover the entire circle (so coverage is total for all directions)
  DocumentModelGridDisplay initializeWithWidePolarCoverage (const QRectF &boundingRectGraph,
                                                            const DocumentModelCoords &modelCoords,
                                                            const Transformation &transformation,
                                                            const QSize &imageSize) const;

  /// Compute power of 10 for input value, rounding down to nearest integer solution of value>=10**solution
  int valuePower (double value) const;

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

  void overridePolarCoordinateSettings (const DocumentModelCoords &modelCoords,
                                        const Transformation &transformation,
                                        DocumentModelGridDisplay &modelGridDisplay,
                                        const QSize &imageSize) const; // Adjust grid lines for polar coordinates
  double roundOffToPower (double arg,
                          int roundOffPower) const;

  const QRectF m_boundingRectGraph;
};

#endif // GRID_INITIALIZER_H
