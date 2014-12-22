#include "CallbackPositionHighlightsFromAxesPoints.h"
#include "HighlightsPoint.h"
#include "Point.h"
#include "Transformation.h"

CallbackPositionHighlightsFromAxesPoints::CallbackPositionHighlightsFromAxesPoints(HighlightsPoint *highlightsPoints0,
                                                                                   HighlightsPoint *highlightsPoints1,
                                                                                   HighlightsPoint *highlightsPoints2,
                                                                                   const Transformation &transformation) :
  m_transformation (transformation),
  m_nextHighlightPoint (0)
{
  m_highlightsPoints.push_back (highlightsPoints0);
  m_highlightsPoints.push_back (highlightsPoints1);
  m_highlightsPoints.push_back (highlightsPoints2);
}

CallbackSearchReturn CallbackPositionHighlightsFromAxesPoints::callback (const QString & /* curveName */,
                                                                         const Point &point)
{
  Q_ASSERT (m_nextHighlightPoint < 3);

  HighlightsPoint *highlightsPoint = m_highlightsPoints [m_nextHighlightPoint];

  highlightsPoint->setPos (point.posScreen());

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}
