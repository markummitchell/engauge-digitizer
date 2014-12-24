#include "CallbackUpdateTransform.h"
#include "Checker.h"
#include "Logger.h"
#include <qmath.h>
#include <QPen>
#include "Transformation.h"

const QString DUMMY_CURVENAME ("dummy");

// To emphasize that the axis lines are still there, we make these checker somewhat transparent
const double CHECKER_OPACITY = 0.6;

// One-pixel wide line (produced by setting width=0) is too small
const int CHECKER_POINTS_WIDTH = 5;

Checker::Checker() :
  QGraphicsPolygonItem (0)
{
  setOpacity (CHECKER_OPACITY);
}

void Checker::prepareForDisplay (const QPolygonF &polygon,
                                 const QColor &lineColor)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Checker::prepareForDisplay";

  Q_ASSERT (polygon.count () == 3);

  // Convert pixel coordinates in QPointF to screen and graph coordinates in Point using
  // identity transformation, so this routine can call the general case routine
  QList<Point> points;
  QPolygonF::const_iterator itr;
  for (itr = polygon.begin (); itr != polygon.end (); itr++) {

    QPointF pF = *itr;
    Point p (DUMMY_CURVENAME,
             pF,
             pF);
    points.push_back (p);
  }

  prepareForDisplay (points,
                     lineColor);
}

void Checker::prepareForDisplay (const QList<Point> &points,
                                 const QColor &lineColor)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Checker::prepareForDisplay";

  setPen (QPen (QBrush (lineColor), CHECKER_POINTS_WIDTH));

  Q_ASSERT (points.count () == 3);

  // Figure out which two axes points are closest in either x or y graph coordinates - they are on the same axis
  double x01 = qAbs (points.at(0).posGraph().x() - points.at(1).posGraph().x());
  double x12 = qAbs (points.at(1).posGraph().x() - points.at(2).posGraph().x());
  double x02 = qAbs (points.at(0).posGraph().x() - points.at(2).posGraph().x());
  double x = qMin (qMin (x01, x12), x02);

  double y01 = qAbs (points.at(0).posGraph().y() - points.at(1).posGraph().y());
  double y12 = qAbs (points.at(1).posGraph().y() - points.at(2).posGraph().y());
  double y02 = qAbs (points.at(0).posGraph().y() - points.at(2).posGraph().y());
  double y = qMin (qMin (y01, y12), y02);

  QPolygonF polygonClosed;
  if (x < y) {

    // Two points are on vertical axis. Draw perpendicular line through the third point to represent horizontal axis
    if (x == x01) {
      polygonClosed = threeLinesFromThreePoints (points.at (0), points.at (1), points.at (2));
    } else if (x == x12) {
      polygonClosed = threeLinesFromThreePoints (points.at (1), points.at (2), points.at (0));
    } else {
      polygonClosed = threeLinesFromThreePoints (points.at (0), points.at (2), points.at (1));
    }

  } else {

    // Two points are on horizontal axis. Draw perpendicular line through the third point to represent vertical axis
    if (y == y01) {
      polygonClosed = threeLinesFromThreePoints (points.at (0), points.at (1), points.at (2));
    } else if (y == y12) {
      polygonClosed = threeLinesFromThreePoints (points.at (1), points.at (2), points.at (0));
    } else {
      polygonClosed = threeLinesFromThreePoints (points.at (0), points.at (2), points.at (1));
    }

  }

  setPolygon (polygonClosed);
}

QPolygonF Checker::threeLinesFromThreePoints (const Point &pointAxis0a,
                                            const Point &pointAxis0b,
                                            const Point &pointAxis1)
{
  const double EPSILON = (qMax (qAbs (pointAxis0a.posGraph().x() - pointAxis0b.posGraph().x ()),
                                qAbs (pointAxis0a.posGraph().y() - pointAxis0b.posGraph().y ()))) / 1000000.0;

  QPointF pointBothAxesGraph;
  // Compute slope from the two points on the same axis, then compute the inverse slope
  double deltaX = pointAxis0b.posGraph().x () - pointAxis0a.posGraph().x ();
  double deltaY = pointAxis0b.posGraph().y () - pointAxis0a.posGraph().y ();
  if (qAbs (deltaX) < EPSILON) {

    // Axis 0 is vertical line
    pointBothAxesGraph = QPointF (pointAxis0b.posGraph().x(),
                                  pointAxis1.posGraph().y());

  } else if (qAbs (deltaY) < EPSILON) {

    // Axis 0 is horizontal line
    pointBothAxesGraph = QPointF (pointAxis1.posGraph().x(),
                                  pointAxis0a.posGraph().y());

  } else {

    // Axis 0 is not vertical or horizontal line
    double slope0 = deltaY / deltaX;
    double slope1 = -1.0 * deltaX / deltaY
                          ;
    // Solve for y intercepts
    double yIntercept0 = pointAxis0a.posGraph().y () - slope0 * pointAxis0a.posGraph().x ();
    double yIntercept1 = pointAxis1.posGraph().y () - slope1 * pointAxis1.posGraph().x ();

    // Find intersection point of the two equations y = slope * x + yIntercept, by subtracting them
    double xIntersect = -1.0 * (yIntercept0 - yIntercept1) / (slope0 - slope1);
    double yIntersect = slope0 * xIntersect + yIntercept0;

    pointBothAxesGraph = QPointF (xIntersect,
                                  yIntersect);

  }

  // Transform intersection point to screen coordinates
  QTransform transform = transformationFromThreePoints (pointAxis0a,
                                                        pointAxis0b,
                                                        pointAxis1);
  QPointF pointBothAxesScreen = transform.map (pointBothAxesGraph);

  // Create the three lines in screen coordinates
  QPolygonF polygon;

  polygon.push_back (pointBothAxesScreen);
  polygon.push_back (pointAxis0a.posScreen ());
  polygon.push_back (pointBothAxesScreen);
  polygon.push_back (pointAxis0b.posScreen ());
  polygon.push_back (pointBothAxesScreen);
  polygon.push_back (pointAxis1.posScreen ());
  polygon.push_back (pointBothAxesScreen);

  return polygon;
}

QTransform Checker::transformationFromThreePoints (const Point &pointAxis0a,
                                                   const Point &pointAxis0b,
                                                   const Point &pointAxis1)
{
  const QString DUMMY_CURVENAME;

  CallbackUpdateTransform cb;
  cb.callback (DUMMY_CURVENAME, pointAxis0a);
  cb.callback (DUMMY_CURVENAME, pointAxis0b);
  cb.callback (DUMMY_CURVENAME, pointAxis1);

  return cb.transform();
}
