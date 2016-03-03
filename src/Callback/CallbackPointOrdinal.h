/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CALLBACK_POINT_ORDINAL_H
#define CALLBACK_POINT_ORDINAL_H

#include "CallbackSearchReturn.h"
#include "LineStyle.h"
#include <QPointF>
#include <QString>
#include "Transformation.h"

class Point;

/// Callback for computing the ordinal for a specified point, as a function of the LineStyle and curve geometry
class CallbackPointOrdinal
{
public:
  /// Single constructor
  CallbackPointOrdinal(const LineStyle &lineStyle,
                       const Transformation &transformation,
                       const QPointF &posScreen);

  /// Callback method.
  CallbackSearchReturn callback (const Point &pointStart,
                                 const Point &pointStop);

  /// Computed ordinal
  double ordinal () const;

private:
  CallbackPointOrdinal();

  const LineStyle m_lineStyle;
  const Transformation m_transformation;
  const QPointF m_posScreen;

  // Find the line segment using one or two steps:
  // 1) If the closest point to m_posScreen is between the endpoints of a line segment, then finding the minimum point-to-line distance
  //    is sufficient to determine the closest line segment. There is no ambiguity, since only one line segment will have the
  //    minimum point-to-line distance
  // 2) If case 1 does not apply, then there are two cases:
  //    2a) The point is just past one terminating line segment. There is no ambiguity, since only one line segment will have the
  //        minimum point-to-line distance
  //    2b) The point is near a vertex between two line segments. There is ambiguity with the two line segments which is resolved
  //        by comparing the minimum projected-distance-outside-line (minimum value wins)
  bool m_haveMinimumDistanceToLine;
  double m_minimumDistanceToLine;
  double m_minimumProjectedDistanceOutsideLine;
  double m_ordinal; // Valid when m_haveMinimumDistanceToLine is true
};

#endif // CALLBACK_POINT_ORDINAL_H
