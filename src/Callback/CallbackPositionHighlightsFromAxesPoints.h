#ifndef CALLBACK_POSITION_HIGHLIGHTS_FROM_AXES_POINTS_H
#define CALLBACK_POSITION_HIGHLIGHTS_FROM_AXES_POINTS_H

#include "CallbackSearchReturn.h"
#include <QString>
#include <QVector>

class HighlightsPoint;
class Point;
class Transformation;

typedef QVector<HighlightsPoint *> HighlightsPoints;

/// Callback for positioning the HighlightsPoint objects according to the axes points buried in Document.
class CallbackPositionHighlightsFromAxesPoints
{
public:
  /// Single constructor.
  CallbackPositionHighlightsFromAxesPoints(HighlightsPoint *highlightsPoints0,
                                           HighlightsPoint *highlightsPoints1,
                                           HighlightsPoint *highlightsPoints2,
                                           const Transformation &transformation);

  /// Callback method.
  CallbackSearchReturn callback (const QString &curveName,
                                 const Point &point);

private:
  CallbackPositionHighlightsFromAxesPoints();

  HighlightsPoints m_highlightsPoints;
  const Transformation &m_transformation;

  // Use counter to match incoming points with the highlights points
  int m_nextHighlightPoint;
};

#endif // CALLBACK_POSITION_HIGHLIGHTS_FROM_AXES_POINTS_H
