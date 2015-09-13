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
