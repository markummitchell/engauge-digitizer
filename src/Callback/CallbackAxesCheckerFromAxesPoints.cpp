#include "CallbackAxesCheckerFromAxesPoints.h"
#include "EngaugeAssert.h"

CallbackAxesCheckerFromAxesPoints::CallbackAxesCheckerFromAxesPoints()
{
}

CallbackSearchReturn CallbackAxesCheckerFromAxesPoints::callback (const QString & /* curveName */,
                                                                  const Point &point)
{
  ENGAUGE_ASSERT (m_points.count () < 3);

  m_points.push_back (point);

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}

Points CallbackAxesCheckerFromAxesPoints::points() const
{
  return m_points;
}
