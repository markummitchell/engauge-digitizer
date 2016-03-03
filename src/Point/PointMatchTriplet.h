/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef POINT_MATCH_TRIPLET_H
#define POINT_MATCH_TRIPLET_H

#include <QPoint>

/// Representation of one matched point as produced from the point match algorithm
class PointMatchTriplet
{
public:
  /// Single constructor
  PointMatchTriplet(int x,
                    int y,
                    double correlation);

  /// Comparison operator for sorting lists of this class using qSort
  bool operator<(const PointMatchTriplet &other) const;

  /// Get method for correlation
  double correlation() const;

  /// Return (x,y) coordinates as a point
  QPoint point() const;

  /// Get method for x coordinate
  int x() const;

  /// Get method for y coordinate
  int y() const;

private:
  PointMatchTriplet();

  int m_x;
  int m_y;
  double m_correlation;
};

#endif // POINT_MATCH_TRIPLET_H
