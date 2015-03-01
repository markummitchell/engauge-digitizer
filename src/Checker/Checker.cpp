#include "CallbackUpdateTransform.h"
#include "Checker.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GraphicsArcItem.h"
#include "Logger.h"
#include "mmsubs.h"
#include <QDebug>
#include <QGraphicsScene>
#include <qmath.h>
#include <QPen>
#include <QTextStream>
#include "QtToString.h"
#include "Transformation.h"

const QString DUMMY_CURVENAME ("dummy");
const int Z_VALUE_IN_FRONT = 100;
const int NO_SIDE = -1;

// To emphasize that the axis lines are still there, we make these checker somewhat transparent
const double CHECKER_OPACITY = 0.6;

// One-pixel wide line (produced by setting width=0) is too small. 5 is big enough to be always noticeable,
// but such a thick line obscures the axes points. To keep the axes points visible, we remove portions of 
// the line nearer to an axes point than the point radius.
const int CHECKER_POINTS_WIDTH = 5;

const double PI = 3.1415926535;
const double TWO_PI = 2.0 * PI;
const double RADIANS_TO_TICS = 5760 / TWO_PI;
const double RADIANS_TO_DEGREES = 180.0 / PI;

Checker::Checker(QGraphicsScene &scene) :
  m_scene (scene)
{
  for (int i = 0; i < MAX_LINES_PER_SIDE; i++) {
    m_sideLeft [i] = 0;
    m_sideTop [i] = 0;
    m_sideRight [i] = 0;
    m_sideBottom [i] = 0;
  }
}

void Checker::adjustPolarAngleRanges (const DocumentModelCoords &modelCoords,
                                      const Transformation &transformation,
                                      const QList<Point> &points,
                                      double &xMin,
                                      double &xMax,
                                      double &yMin) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Checker::adjustPolarAngleRanges";

  const double UNIT_LENGTH = 1.0;

  if (modelCoords.coordsType() == COORDS_TYPE_POLAR) {

    // Range minimum is origin
    yMin = 0.0;

    // Perform special processing to account for periodicity of polar coordinates. Start with unit vectors
    // in the directions of the three axis points
    double angle0 = points.at(0).posGraph().x();
    double angle1 = points.at(1).posGraph().x();
    double angle2 = points.at(2).posGraph().x();
    QPointF pos0 = transformation.cartesianFromCartesianOrPolar(modelCoords,
                                                                QPointF (angle0, UNIT_LENGTH));
    QPointF pos1 = transformation.cartesianFromCartesianOrPolar(modelCoords,
                                                                QPointF (angle1, UNIT_LENGTH));
    QPointF pos2 = transformation.cartesianFromCartesianOrPolar(modelCoords,
                                                                QPointF (angle2, UNIT_LENGTH));

    // Angles in radians. Unlike the units-specific values in angle0, angle1 and angle2, we know these range from
    // 0 to TWO_PI
    double angle0Radians = qAtan2 (pos0.y(), pos0.x());
    double angle1Radians = qAtan2 (pos1.y(), pos1.x());
    double angle2Radians = qAtan2 (pos2.y(), pos2.y());

    // Identify the axis point that is more in the center of the other two axis points. The arc is then drawn
    // from one of the other two points to the other. Center point has smaller angles with the other points
    double sumAngle0 = angleBetweenVectors(pos0, pos1) + angleBetweenVectors(pos0, pos2);
    double sumAngle1 = angleBetweenVectors(pos1, pos0) + angleBetweenVectors(pos1, pos2);
    double sumAngle2 = angleBetweenVectors(pos2, pos0) + angleBetweenVectors(pos2, pos1);
    if ((sumAngle0 <= sumAngle1) && (sumAngle0 <= sumAngle2)) {

      // Point 0 is in the middle
      xMin = (angle1Radians < angle2Radians) ? angle1 : angle2;
      xMax = (angle1Radians < angle2Radians) ? angle2 : angle1;

    } else if ((sumAngle1 <= sumAngle0) && (sumAngle2 <= sumAngle2)) {

      // Point 1 is in the middle
      xMin = (angle0Radians < angle2Radians) ? angle0 : angle2;
      xMax = (angle0Radians < angle2Radians) ? angle2 : angle0;

    } else {

      // Point 2 is in the middle
      xMin = (angle0Radians < angle1Radians) ? angle0 : angle1;
      xMax = (angle0Radians < angle1Radians) ? angle1 : angle0;

    }
  }
}

void Checker::bindItemToScene(QGraphicsItem *item)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "Checker:bindItemToScene";

  item->setOpacity (CHECKER_OPACITY);
  item->setZValue (Z_VALUE_IN_FRONT);
  item->setToolTip (QObject::tr ("Axes checker. If this does not align with the axes, then the axes points should be checked"));

  m_scene.addItem (item);
}

void Checker::createSide (int pointRadius,
                          const QList<Point> &points,
                          const DocumentModelCoords &modelCoords,
                          double xFrom,
                          double yFrom,
                          double xTo,
                          double yTo,
                          const Transformation &transformation,
                          QGraphicsItem *items [MAX_LINES_PER_SIDE])
{
  QPointF pointFromGraph (xFrom, yFrom), pointToGraph (xTo, yTo);

  QPointF pointFromGraphCart = transformation.cartesianFromCartesianOrPolar (modelCoords,
                                                                             pointFromGraph);
  QPointF pointToGraphCart = transformation.cartesianFromCartesianOrPolar (modelCoords,
                                                                           pointToGraph);

  // Convert graph coordinates to screen coordinates
  QPointF pointFromScreen, pointToScreen;
  transformation.transformInverse (pointFromGraphCart,
                                   pointFromScreen);
  transformation.transformInverse (pointToGraphCart,
                                   pointToScreen);

  // Build a list of points where the circle around each point intercepts the infinite line through
  // pointFromScreen and pointToScreen
  QList<double> sInterceptPoints;
  sInterceptPoints << 0; // Start at limit
  sInterceptPoints << 1; // Stop at limit
  QList<Point>::const_iterator itr;
  for (itr = points.begin (); itr != points.end (); itr++) {
    const Point &point = *itr;
    interceptPointCircleWithLine (pointRadius,
                                  sInterceptPoints,
                                  point,
                                  pointFromScreen,
                                  pointToScreen);
  }

  qSort (sInterceptPoints);

  // Loop through sorted s values, ignoring those outside the range 0 to 1. Draw line for (s(i-1),s(i))
  // if the midpoint is not near any point
  int itemCount = 0;
  double sLast = 0;
  for (int i = 0; i < sInterceptPoints.count(); i++) {
    double s = sInterceptPoints.at (i);
    if (i > 0) {
      if (0 < s && sLast < 1) {

        double sMidpoint = (s + sLast) / 2.0;

        QPointF posStartScreen    = (1.0 - sLast    ) * pointFromScreen + sLast     * pointToScreen;
        QPointF posMidpointScreen = (1.0 - sMidpoint) * pointFromScreen + sMidpoint * pointToScreen;
        QPointF posEndScreen      = (1.0 - s        ) * pointFromScreen + s         * pointToScreen;

        if (minScreenDistanceFromPoints (posMidpointScreen, points) > pointRadius) {
          QGraphicsItem *item;

          if ((modelCoords.coordsType() == COORDS_TYPE_POLAR) &&
              (pointFromGraph.y() == pointToGraph.y())) {

            // Draw along an arc since this is a side of constant radius, and we have polar coordinates
            item = ellipseItem (transformation,
                                pointFromGraph.y(),
                                posStartScreen,
                                posEndScreen);

          } else {

            // Draw straight line
            item = new QGraphicsLineItem (QLineF (posStartScreen,
                                                  posEndScreen));

          }

          items [itemCount++] = item;
          bindItemToScene (item);
        }
      }
    }
    sLast = s;
  }
}

void Checker::createTransformAlign (const Transformation &transformation,
                                    double radius,
                                    const QPointF &posOriginScreen,
                                    QTransform &transformAlign,
                                    double &ellipseXAxis,
                                    double &ellipseYAxis) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Checker::TransformAlign"
                              << " transformation=" << QTransformToString (transformation.transformMatrix()).toLatin1().data();

  // Compute a minimal transformation that aligns the graph x and y axes with the screen x and y axes. Specifically, shear,
  // translation and rotation are allowed but not scaling. Scaling is bad since it messes up the line thickness of the drawn arc.
  //
  // Assumptions:
  // 1) Keep the graph origin at the same screen coordinates
  // 2) Keep the (+radius,0) the same pixel distance from the origin but moved to the same pixel row as the origin
  // 3) Keep the (0,+radius) the same pixel distance from the origin but moved to the same pixel column as the origin

  // Get (+radius,0) and (0,+radius) points
  QPointF posXRadiusY0Graph (radius, 0), posX0YRadiusGraph (0, radius);
  QPointF posXRadiusY0Screen, posX0YRadiusScreen;
  transformation.transformInverse (posXRadiusY0Graph,
                                   posXRadiusY0Screen);
  transformation.transformInverse (posX0YRadiusGraph,
                                   posX0YRadiusScreen);

  // Compute arc/ellipse parameters
  ellipseXAxis = qAbs (posXRadiusY0Screen.x() - posOriginScreen.x());
  ellipseYAxis = qAbs (posX0YRadiusScreen.y() - posOriginScreen.y());

  // Compute the aligned coordinates, constrained by the rules listed above
  QPointF posXRadiusY0AlignedScreen (posOriginScreen.x() + ellipseXAxis, posOriginScreen.y());
  QPointF posX0YRadiusAlignedScreen (posOriginScreen.x(), posOriginScreen.y() - ellipseYAxis);

  // Compute transform. Note that transform is not screen-to/from-graph or vice versa, but from
  // screen-unaligned-to/from-screen-aligned
  DocumentModelCoords modelCoords; // Default coordinates are simple linear and cartesian, which is what we want

  CallbackUpdateTransform cb (modelCoords,
                              posOriginScreen,
                              posXRadiusY0Screen,
                              posX0YRadiusScreen,
                              posOriginScreen,
                              posXRadiusY0AlignedScreen,
                              posX0YRadiusAlignedScreen);

  transformAlign = cb.transform();
}

void Checker::deleteSide (QGraphicsItem *items [MAX_LINES_PER_SIDE])
{
  for (int i = 0; i < MAX_LINES_PER_SIDE; i++) {
    QGraphicsItem *item = items [i];
    if (item != 0) {
      delete item;
    }

    items [i] = 0;
  }
}

QGraphicsItem *Checker::ellipseItem(const Transformation &transformation,
                                    double radius,
                                    const QPointF &posStartScreen,
                                    const QPointF &posEndScreen) const
{
  QPointF posStartGraph, posEndGraph;

  transformation.transform (posStartScreen,
                            posStartGraph);
  transformation.transform (posEndScreen,
                            posEndGraph);

  // Get origin
  QPointF posOriginGraph (0, 0), posOriginScreen;
  transformation.transformInverse (posOriginGraph,
                                   posOriginScreen);

  // Compute rotate/shear transform that aligns graph coordinates with screen coordinates, and ellipse parameters.
  // Transform does not include scaling since that messes up the thickness of the drawn line, and does not include
  // translation since that is not important
  double ellipseXAxis, ellipseYAxis;
  QTransform transformAlign;
  createTransformAlign (transformation,
                        radius,
                        posOriginScreen,
                        transformAlign,
                        ellipseXAxis,
                        ellipseYAxis);

  // Get the angles about the origin of the start and end points
  double angleStart = qAtan2 (posStartGraph.y(),
                              posStartGraph.x()) * RADIANS_TO_TICS;
  double angleEnd = qAtan2 (posEndGraph.y(),
                            posEndGraph.x()) * RADIANS_TO_TICS;
  if (angleEnd < angleStart) {
    angleEnd += TWO_PI * RADIANS_TO_TICS;
  }
  double angleSpan = angleEnd - angleStart;

  // Create a circle in graph space with the specified radius
  QRectF boundingRect (-1.0 * ellipseXAxis + posOriginScreen.x(),
                       -1.0 * ellipseYAxis + posOriginScreen.y(),
                       2 * ellipseXAxis,
                       2 * ellipseYAxis);
  GraphicsArcItem *item = new GraphicsArcItem (boundingRect);
  item->setStartAngle (angleStart);
  item->setSpanAngle (angleSpan);

  item->setTransform (transformAlign.transposed ().inverted ());

  return item;
}

void Checker::interceptPointCircleWithLine (int pointRadius,
                                            QList<double> &sInterceptPoints,
                                            const Point &point,
                                            const QPointF &pointFromScreen,
                                            const QPointF &pointToScreen)
{
  double distanceFromTo = qSqrt ((pointToScreen.x() - pointFromScreen.x()) * (pointToScreen.x() - pointFromScreen.x()) +
                                 (pointToScreen.y() - pointFromScreen.y()) * (pointToScreen.y() - pointFromScreen.y()));

  // Compensate for slop in drawing of lines by making radius a tiny bit bigger
  double radiusTweaked = pointRadius + 1;

  // Intersect:
  // 1) (y-y0)/(y1-y0) = (x-x0)/(x1-x0), but converted from two point form to slope intercept form for convenience
  // 2) (x-xc)^2+(y-yc)^2=r^2

  double dx = pointToScreen.x() - pointFromScreen.x();
  double dy = pointToScreen.y() - pointFromScreen.y();

  // Handle more-horizontal and more-vertical lines separately to prevent divide by zero issues
  double xIntercept, yIntercept;
  if (qAbs (dx) < qAbs (dy)) {

    if (dx == 0) {

      // For a perfectly vertical line the inverse slope will crash below, but intersection is trivial
      xIntercept = pointToScreen.x();
      yIntercept = point.posScreen().y();

    } else {

      // x = slope * y + intercept
      double slope = dx / dy;
      double intercept = pointToScreen.x() - slope * pointToScreen.y();

      // Perpendicular line that goes through specified point
      double slopePerp = -1.0 / slope;
      double interceptPerp = point.posScreen().x() - slopePerp * point.posScreen().y();

      // Intersection point of both lines comes from subtracting both x=slope*y+intercept and x=slopePerp*y+interceptPerp
      yIntercept = (interceptPerp - intercept) / (slope - slopePerp);
      xIntercept = slope * yIntercept + intercept;

    }
  } else {

    if (dy == 0) {

      // For a perfectly horizontal line the inverse slope will crash below, but intersection is trivial
      xIntercept = point.posScreen().x();
      yIntercept = pointToScreen.y();

    } else {

      // y = slope * y + intercept
      double slope = dy / dx;
      double intercept = pointToScreen.y() - slope * pointToScreen.x();

      // Perpendicular line that goes through specified point
      double slopePerp = -1.0 / slope;
      double interceptPerp = point.posScreen().y() - slopePerp * point.posScreen().x();

      // Intersection point of both lines comes from subtracting both y=slope*x+intercept and y=slopePerp*x+interceptPerp
      xIntercept = (interceptPerp - intercept) / (slope - slopePerp);
      yIntercept = slope * xIntercept + intercept;

    }
  }

  // Distance from point to line
  double separation = qSqrt ((xIntercept - point.posScreen().x()) * (xIntercept - point.posScreen().x()) +
                             (yIntercept - point.posScreen().y()) * (yIntercept - point.posScreen().y()));
  if (separation < radiusTweaked) {

    // s at intercept (=distanceFromIntercept/distanceFromTo) is not needed, but distance is needed
    double distanceFromIntercept = qSqrt ((xIntercept - pointFromScreen.x()) * (xIntercept - pointFromScreen.x()) +
                                          (yIntercept - pointFromScreen.y()) * (yIntercept - pointFromScreen.y()));

    // Find both intersection points at +/-offsetFromIntercept
    double offsetFromIntercept = qSqrt (radiusTweaked * radiusTweaked - separation * separation);
    double sMinus = (distanceFromIntercept - offsetFromIntercept) / distanceFromTo;
    double sPlus  = (distanceFromIntercept + offsetFromIntercept) / distanceFromTo;

    sInterceptPoints.push_back (sMinus);
    sInterceptPoints.push_back (sPlus);
  }
}

double Checker::minScreenDistanceFromPoints (const QPointF &posScreen,
                                             const QList<Point> &points)
{
  double minDistance = 0;
  for (int i = 0; i < points.count (); i++) {
    const Point &pointCenter = points.at (i);

    double dx = posScreen.x() - pointCenter.posScreen().x();
    double dy = posScreen.y() - pointCenter.posScreen().y();

    double distance = qSqrt (dx * dx + dy * dy);
    if (i == 0 || distance < minDistance) {
      minDistance = distance;
    }
  }

  return minDistance;
}

void Checker::prepareForDisplay (const QPolygonF &polygon,
                                 int pointRadius,
                                 const DocumentModelAxesChecker &modelAxesChecker,
                                 const DocumentModelCoords &modelCoords)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Checker::prepareForDisplay";

  ENGAUGE_ASSERT (polygon.count () == NUM_AXES_POINTS);

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

  // Screen and graph coordinates are treated as the same, so identity transform is used
  Transformation transformIdentity;
  transformIdentity.identity();
  prepareForDisplay (points,
                     pointRadius,
                     modelAxesChecker,
                     modelCoords,
                     transformIdentity);
}

void Checker::prepareForDisplay (const QList<Point> &points,
                                 int pointRadius,
                                 const DocumentModelAxesChecker &modelAxesChecker,
                                 const DocumentModelCoords &modelCoords,
                                 const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Checker::prepareForDisplay";

  ENGAUGE_ASSERT (points.count () == NUM_AXES_POINTS);

  // Remove previous lines
  deleteSide (m_sideLeft);
  deleteSide (m_sideTop);
  deleteSide (m_sideRight);
  deleteSide (m_sideBottom);

  // Get the min and max of x and y
  double xMin, xMax, yMin, yMax;
  int i;
  for (i = 0; i < 3; i++) {
    if (i == 0) {
      xMin = points.at(i).posGraph().x();
      xMax = points.at(i).posGraph().x();
      yMin = points.at(i).posGraph().y();
      yMax = points.at(i).posGraph().y();
    }
    xMin = qMin (xMin, points.at(i).posGraph().x());
    xMax = qMax (xMax, points.at(i).posGraph().x());
    yMin = qMin (yMin, points.at(i).posGraph().y());
    yMax = qMax (yMax, points.at(i).posGraph().y());
  }

  // Min and max of angles needs special processing since periodicity introduces some ambiguity. This is a noop for rectangular coordinates
  // and for polar coordinates when periodicity is not an issue
  adjustPolarAngleRanges (modelCoords,
                          transformation,
                          points,
                          xMin,
                          xMax,
                          yMin);

  // Draw the bounding box as four sides
  createSide (pointRadius, points, modelCoords, xMin, yMin, xMin, yMax, transformation, m_sideLeft);
  createSide (pointRadius, points, modelCoords, xMin, yMax, xMax, yMax, transformation, m_sideTop);
  createSide (pointRadius, points, modelCoords, xMax, yMax, xMax, yMin, transformation, m_sideRight);
  createSide (pointRadius, points, modelCoords, xMax, yMin, xMin, yMin, transformation, m_sideBottom);

  updateModelAxesChecker (modelAxesChecker);
}

void Checker::setLineColor (QGraphicsItem *items [MAX_LINES_PER_SIDE], const QPen &pen)
{
  for (int i = 0; i < MAX_LINES_PER_SIDE; i++) {
    QGraphicsItem *item = items [i];
    if (item != 0) {

      // Downcast since QGraphicsItem does not have a pen
      QGraphicsLineItem *itemLine = dynamic_cast<QGraphicsLineItem*> (item);
      QGraphicsEllipseItem *itemArc = dynamic_cast<QGraphicsEllipseItem*> (item);
      if (itemLine != 0) {
        itemLine->setPen (pen);
      } else if (itemArc != 0) {
        itemArc->setPen (pen);
      }
    }
  }
}

void Checker::setVisible (bool visible)
{
  setVisibleSide (m_sideLeft, visible);
  setVisibleSide (m_sideTop, visible);
  setVisibleSide (m_sideRight, visible);
  setVisibleSide (m_sideBottom, visible);
}

void Checker::setVisibleSide (QGraphicsItem *items [MAX_LINES_PER_SIDE],
                              bool visible)
{
  for (int i = 0; i < MAX_LINES_PER_SIDE; i++) {
    QGraphicsItem *item = items [i];
    if (item != 0) {
      item->setVisible (visible);
    }
  }
}

void Checker::updateModelAxesChecker (const DocumentModelAxesChecker &modelAxesChecker)
{
  QColor color = ColorPaletteToQColor (modelAxesChecker.lineColor());
  QPen pen (QBrush (color), CHECKER_POINTS_WIDTH);

  setLineColor (m_sideLeft, pen);
  setLineColor (m_sideTop, pen);
  setLineColor (m_sideRight, pen);
  setLineColor (m_sideBottom, pen);
}
