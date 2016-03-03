/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef POINT_COMPARATOR_H
#define POINT_COMPARATOR_H

#include "Point.h"

/// Comparator for sorting Point class
struct PointComparator
{
  /// Comparison function used by qSort
  bool operator()(const Point &a, const Point &b) const
  {
    return a.ordinal() < b.ordinal();
  }
};

#endif // POINT_COMPARATOR_H
