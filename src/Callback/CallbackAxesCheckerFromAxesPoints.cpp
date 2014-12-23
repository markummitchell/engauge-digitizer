#include "CallbackAxesCheckerFromAxesPoints.h"

CallbackAxesCheckerFromAxesPoints::CallbackAxesCheckerFromAxesPoints()
{
}

CallbackSearchReturn CallbackAxesCheckerFromAxesPoints::callback (const QString & /* curveName */,
                                                                  const Point &point)
{
  Q_ASSERT (m_points.count () < 3);

  m_points.push_back (point);

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}

QPolygonF CallbackAxesCheckerFromAxesPoints::polygon() const
{
  QPolygonF pf;

  return pf;
}
