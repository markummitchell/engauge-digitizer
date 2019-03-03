/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef SPLINE_DRAWER_H
#define SPLINE_DRAWER_H

#include "SplinePair.h"
#include "Transformation.h"
#include <QVector>

class LineStyle;
class Spline;

enum SplineDrawerOperation {
  SPLINE_DRAWER_ENUM_INVISIBLE_MOVE, // Move to final point in segment
  SPLINE_DRAWER_ENUM_VISIBLE_DRAW // Draw to final point in segment
};

typedef QVector<SplineDrawerOperation> SegmentOperations;

/// This class takes the output from Spline and uses that to draw the curve in the graphics window, as
/// a sequence of moves and draws. The moves and draws by themselves would be trivial (move,draw,draw,draw...)
/// but this actually draws, when needed, differently styled curve segments to indicate each curve segment
/// should be CONNECT_AS_FUNCTION_SMOOTH but actually is not single-valued (=not a function)
///
/// This class is aware of the Transformation, unlike the Spline class which is decoupled from that for simplicity.
/// Specifically, this class converts the screen coordinates to graph coordinates to check for single-valuedness.
///
/// The algorithm used here has to work in cartesian, polar, linear and/or log coordinates. This requirement,
/// along with the goal of keeping the Spline class simple, pretty much requires using the Transformation
/// and working in graph coordinates.
class SplineDrawer
{
  // For unit testing
  friend class TestSplineDrawer;
  
 public:
  /// Single constructor
  SplineDrawer(const Transformation &transformation);

  /// Analyze each segment in the Spline
  void bindToSpline (const LineStyle &lineStyle,
                     int numSegments,
                     const Spline &spline);

  /// Return true if specified segment is multi-valued, else false
  bool segmentIsMultiValued (const Spline &spline,
                             int numSegments,
                             int segment) const;

  /// Indicate if, and how, segment is to be drawn
  SplineDrawerOperation segmentOperation (int segment) const;

private:
  SplineDrawer();

  const Transformation m_transformation;

  SegmentOperations m_segmentOperations;
};

#endif // SPLINE_DRAWER_H
