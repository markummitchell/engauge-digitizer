#include "CallbackAxesCheckerFromAxesPoints.h"
#include "EngaugeAssert.h"

CallbackAxesCheckerFromAxesPoints::CallbackAxesCheckerFromAxesPoints()
{
}

CallbackSearchReturn CallbackAxesCheckerFromAxesPoints::callback (const QString & /* curveName */,
                                                                  const Point &point)
{
  m_points.push_back (point);

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}

Points CallbackAxesCheckerFromAxesPoints::points() const
{
  return m_points;
}
