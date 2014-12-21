#include "HighlightsPoint.h"
#include "Logger.h"
#include <QPen>

// Rather than complicate the user interface and make the point size adjustable, we just make
// it a constant. The size should be very big to guarantee visibility
const int HIGHLIGHTS_POINT_RADIUS = 20;

// One-pixel wide line (produced by setting width=0) is too small
const int HIGHLIGHTS_POINTS_WIDTH = 1;

HighlightsPoint::HighlightsPoint() :
  QGraphicsPolygonItem (0)
{
  // Draw as a pair of vertical and horizontal lines, about (0,0)
  QVector<QPointF> points;
  points.push_back (QPointF (0, -HIGHLIGHTS_POINT_RADIUS));
  points.push_back (QPointF (0, HIGHLIGHTS_POINT_RADIUS));
  points.push_back (QPointF (0, 0));
  points.push_back (QPointF (-HIGHLIGHTS_POINT_RADIUS, 0));
  points.push_back (QPointF (HIGHLIGHTS_POINT_RADIUS, 0));
  points.push_back (QPointF (0, 0));

  QPolygonF polygon (points);

  setPolygon (polygon);
}

void HighlightsPoint::setLineColor (const QColor &lineColor)
{
  LOG4CPP_INFO_S ((*mainCat)) << "HighlightsPoint::setLineColor";

  setPen (QPen (QBrush (lineColor), HIGHLIGHTS_POINTS_WIDTH));
}
