#include "HighlightsPoint.h"
#include "Logger.h"
#include <qmath.h>
#include <QPen>
#include "Transformation.h"

// To emphasize that the axis lines are still there, we make these highlights somewhat transparent
const double HIGHLIGHTS_OPACITY = 0.6;

// Rather than complicate the user interface and make the point size adjustable, we just make
// it a constant. The size should be very big to guarantee visibility
const int HIGHLIGHTS_POINT_RADIUS = 50;

// One-pixel wide line (produced by setting width=0) is too small
const int HIGHLIGHTS_POINTS_WIDTH = 5;

HighlightsPoint::HighlightsPoint() :
  QGraphicsPolygonItem (0)
{
  setOpacity (HIGHLIGHTS_OPACITY);

  // Draw as a pair of vertical and horizontal lines, about (0,0)
  QVector<QPointF> points; // Screen (pixels) coordinates
  points.push_back (QPointF (0, -HIGHLIGHTS_POINT_RADIUS));
  points.push_back (QPointF (0, HIGHLIGHTS_POINT_RADIUS));
  points.push_back (QPointF (0, 0));
  points.push_back (QPointF (-HIGHLIGHTS_POINT_RADIUS, 0));
  points.push_back (QPointF (HIGHLIGHTS_POINT_RADIUS, 0));
  points.push_back (QPointF (0, 0));

  QPolygonF polygon (points);

  setPolygon (polygon);
}

HighlightsPoint::HighlightsPoint(const Transformation &transformation) :
  QGraphicsPolygonItem (0)
{
  setOpacity (HIGHLIGHTS_OPACITY);

  Q_ASSERT (transformation.transformIsDefined());

  // The directions computed below would be the same for any point, since the transformation is affine. We pick the origin
  QPointF posScreen (0, 0);

  QPointF posGraph;
  transformation.transform (posScreen,
                            posGraph);

  QPointF posGraphPlusX = posGraph + QPointF (1, 0);
  QPointF posGraphPlusY = posGraph + QPointF (0, 1);

  QPointF posScreenPlusX, posScreenPlusY;
  transformation.transformInverse (posGraphPlusX,
                                   posScreenPlusX);
  transformation.transformInverse (posGraphPlusY,
                                   posScreenPlusY);

  // Vectors in the up (y) and right (x) directions, in screen coordiantes, as computed from the transformation
  QPointF vecRight (posScreenPlusX.x() - posScreen.x(),
                    posScreenPlusX.y() - posScreen.y());
  QPointF vecUp (posScreenPlusY.x () - posScreen.x(),
                 posScreenPlusY.y () - posScreen.y());

  // Scale the up and right vectors so they can be directly added to posScreen
  double vecRightMag = qSqrt (vecRight.x() * vecRight.x() + vecRight.y() * vecRight.y());
  double vecUpMag = qSqrt (vecUp.x() * vecUp.x() + vecUp.y() * vecUp.y());

  Q_ASSERT (vecRightMag != 0);
  Q_ASSERT (vecUpMag != 0);

  vecRight *= HIGHLIGHTS_POINT_RADIUS / vecRightMag;
  vecUp *= HIGHLIGHTS_POINT_RADIUS / vecUpMag;

  // Other two directions
  QPointF vecLeft (vecRight);
  QPointF vecDown (vecUp);
  vecLeft *= -1;
  vecDown *= -1;

  // Draw as a pair of vertical and horizontal lines, about (0,0). The vertice positions are
  // determined by the transformation. Note that this polygon is closed automatically, so first
  // and last points will be connected automaticaly
  QVector<QPointF> points; // Screen (pixels) coordinates
  points.push_back (vecDown);
  points.push_back (vecUp);
  points.push_back (QPointF (0, 0));
  points.push_back (vecLeft);
  points.push_back (vecRight);
  points.push_back (QPointF (0, 0));

  QPolygonF polygon (points);

  setPolygon (polygon);
}

void HighlightsPoint::setLineColor (const QColor &lineColor)
{
  LOG4CPP_INFO_S ((*mainCat)) << "HighlightsPoint::setLineColor";

  setPen (QPen (QBrush (lineColor), HIGHLIGHTS_POINTS_WIDTH));
}
