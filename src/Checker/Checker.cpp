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

const int NUM_AXES_POINTS = 3;

extern const QString DUMMY_CURVE_NAME;
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
const double DEGREES_TO_RADIANS = PI / 180.0;
const double RADIANS_TO_TICS = 5760 / TWO_PI;
const double RADIANS_TO_DEGREES = 180.0 / PI;

Checker::Checker(QGraphicsScene &scene) :
  m_scene (scene)
{
}

void Checker::adjustPolarAngleRanges (const DocumentModelCoords &modelCoords,
                                      const Transformation &transformation,
                                      const QList<Point> &points,
                                      double &xMin,
                                      double &xMax,
                                      double &yMin) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Checker::adjustPolarAngleRanges transformation=" << transformation;

  const double UNIT_LENGTH = 1.0;

  QString path; // For logging
  if (modelCoords.coordsType() == COORDS_TYPE_POLAR) {

    // Range minimum is at origin
    yMin = modelCoords.originRadius();

    path = QString ("yMin=%1 ").arg (yMin); // For logging

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

    // Identify the axis point that is more in the center of the other two axis points. The arc is then drawn
    // from one of the other two points to the other. Center point has smaller angles with the other points
    double sumAngle0 = angleBetweenVectors(pos0, pos1) + angleBetweenVectors(pos0, pos2);
    double sumAngle1 = angleBetweenVectors(pos1, pos0) + angleBetweenVectors(pos1, pos2);
    double sumAngle2 = angleBetweenVectors(pos2, pos0) + angleBetweenVectors(pos2, pos1);
    if ((sumAngle0 <= sumAngle1) && (sumAngle0 <= sumAngle2)) {

      // Point 0 is in the middle. Either or neither of points 1 and 2 may be along point 0
      if ((angleFromVectorToVector (pos0, pos1) < 0) ||
          (angleFromVectorToVector (pos0, pos2) > 0)) {
        path += QString ("from 1=%1 through 0 to 2=%2").arg (angle1).arg (angle2);
        xMin = angle1;
        xMax = angle2;
      } else {
        path += QString ("from 2=%1 through 0 to 1=%2").arg (angle2).arg (angle1);
        xMin = angle2;
        xMax = angle1;
      }
    } else if ((sumAngle1 <= sumAngle0) && (sumAngle1 <= sumAngle2)) {

      // Point 1 is in the middle. Either or neither of points 0 and 2 may be along point 1
      if ((angleFromVectorToVector (pos1, pos0) < 0) ||
          (angleFromVectorToVector (pos1, pos2) > 0)) {
        path += QString ("from 0=%1 through 1 to 2=%2").arg (angle0).arg (angle2);
        xMin = angle0;
        xMax = angle2;
      } else {
        path += QString ("from 2=%1 through 1 to 0=%2").arg (angle2).arg (angle0);
        xMin = angle2;
        xMax = angle0;
      }
    } else {

      // Point 2 is in the middle. Either or neither of points 0 and 1 may be along point 2
      if ((angleFromVectorToVector (pos2, pos0) < 0) ||
          (angleFromVectorToVector (pos2, pos1) > 0)) {
        path += QString ("from 0=%1 through 2 to 1=%2").arg (angle0).arg (angle1);
        xMin = angle0;
        xMax = angle1;
      } else {
        path += QString ("from 1=%1 through 2 to 0=%2").arg (angle1).arg (angle0);
        xMin = angle1;
        xMax = angle0;
      }
    }

    // Make sure theta is increasing
    while (xMax < xMin) {

      double thetaPeriod = modelCoords.thetaPeriod();

      path += QString (" xMax+=%1").arg (thetaPeriod);
      xMax += thetaPeriod;

    }
  }

  LOG4CPP_INFO_S ((*mainCat)) << "Checker::adjustPolarAngleRanges path=(" << path.toLatin1().data() << ")";
}

void Checker::bindItemToScene(QGraphicsItem *item) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "Checker::bindItemToScene";

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
                          SideSegments &sideSegments)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Checker::createSide"
                              << " pointRadius=" << pointRadius
                              << " xFrom=" << xFrom
                              << " yFrom=" << yFrom
                              << " xTo=" << xTo
                              << " yTo=" << yTo
                              << " transformation=" << transformation;

  // Originally a complicated algorithm tried to intercept a straight line from (xFrom,yFrom) to (xTo,yTo). That did not work well since:
  // 1) Calculations for mostly orthogonal cartesian coordinates worked less well with non-orthogonal polar coordinates
  // 2) Ambiguity in polar coordinates between the shorter and longer paths between (theta0,radius) and (theta1,radius)
  //
  // Current algorithm breaks up the interval between (xMin,yMin) and (xMax,yMax) into many smaller pieces and stitches the
  // desired pieces together. For straight lines in linear graphs this algorithm is very much overkill, but there is no significant
  // penalty and this approach works in every situation

  // Should give single-pixel resolution on most images, and 'good enough' resolution on extremely large images
  const int NUM_STEPS = 1000;

  bool stateSegmentIsActive = false;
  QPointF posStartScreen (0, 0);

  // Loop through steps. Final step i=NUM_STEPS does final processing if a segment is active
  for (int i = 0; i <= NUM_STEPS; i++) {

    double s = (double) i / (double) NUM_STEPS;

    // Interpolate coordinates assuming normal linear scaling
    double xGraph = (1.0 - s) * xFrom + s * xTo;
    double yGraph = (1.0 - s) * yFrom + s * yTo;

    // Replace interpolated coordinates using log scaling if appropriate, preserving the same ranges
    if (modelCoords.coordScaleXTheta() == COORD_SCALE_LOG) {
      xGraph = qExp ((1.0 - s) * qLn (xFrom) + s * qLn (xTo));
    }
    if (modelCoords.coordScaleYRadius() == COORD_SCALE_LOG) {
      yGraph = qExp ((1.0 - s) * qLn (yFrom) + s * qLn (yTo));
    }

    QPointF pointScreen;
    transformation.transformRawGraphToScreen (QPointF (xGraph, yGraph),
                                              pointScreen);

    double distanceToNearestPoint = minScreenDistanceFromPoints (pointScreen,
                                                                 points);
    if ((distanceToNearestPoint < pointRadius) ||
        (i == NUM_STEPS)) {

        // Too close to point, so point is not included in side. Or this is the final iteration of the loop
      if (stateSegmentIsActive) {

        // State transition
        finishActiveSegment (modelCoords,
                             posStartScreen,
                             pointScreen,
                             yFrom,
                             yTo,
                             transformation,
                             sideSegments);
        stateSegmentIsActive = false;

      }
    } else {

      // Outside point, so include point in side
      if (!stateSegmentIsActive) {

        // State transition
        stateSegmentIsActive = true;
        posStartScreen = pointScreen;

      }
    }
  }
}

void Checker::createTransformAlign (const Transformation &transformation,
                                    double radiusLinearCartesian,
                                    const QPointF &posOriginScreen,
                                    QTransform &transformAlign,
                                    double &ellipseXAxis,
                                    double &ellipseYAxis) const
{
  // LOG4CPP_INFO_S is below

  // Compute a minimal transformation that aligns the graph x and y axes with the screen x and y axes. Specifically, shear,
  // translation and rotation are allowed but not scaling. Scaling is bad since it messes up the line thickness of the drawn arc.
  //
  // Assumptions:
  // 1) Keep the graph origin at the same screen coordinates
  // 2) Keep the (+radius,0) the same pixel distance from the origin but moved to the same pixel row as the origin
  // 3) Keep the (0,+radius) the same pixel distance from the origin but moved to the same pixel column as the origin

  // Get (+radius,0) and (0,+radius) points
  QPointF posXRadiusY0Graph (radiusLinearCartesian, 0), posX0YRadiusGraph (0, radiusLinearCartesian);
  QPointF posXRadiusY0Screen, posX0YRadiusScreen;
  transformation.transformLinearCartesianGraphToScreen (posXRadiusY0Graph,
                                                        posXRadiusY0Screen);
  transformation.transformLinearCartesianGraphToScreen (posX0YRadiusGraph,
                                                        posX0YRadiusScreen);

  // Compute arc/ellipse parameters
  QPointF deltaXRadiusY0 = posXRadiusY0Screen - posOriginScreen;
  QPointF deltaX0YRadius = posX0YRadiusScreen - posOriginScreen;
  ellipseXAxis = qSqrt (deltaXRadiusY0.x () * deltaXRadiusY0.x () +
                        deltaXRadiusY0.y () * deltaXRadiusY0.y ());
  ellipseYAxis = qSqrt (deltaX0YRadius.x () * deltaX0YRadius.x () +
                        deltaX0YRadius.y () * deltaX0YRadius.y ());

  // Compute the aligned coordinates, constrained by the rules listed above
  QPointF posXRadiusY0AlignedScreen (posOriginScreen.x() + ellipseXAxis, posOriginScreen.y());
  QPointF posX0YRadiusAlignedScreen (posOriginScreen.x(), posOriginScreen.y() - ellipseYAxis);

  transformAlign = Transformation::calculateTransformFromLinearCartesianPoints (posOriginScreen,
                                                                                posXRadiusY0Screen,
                                                                                posX0YRadiusScreen,
                                                                                posOriginScreen,
                                                                                posXRadiusY0AlignedScreen,
                                                                                posX0YRadiusAlignedScreen);

  LOG4CPP_INFO_S ((*mainCat)) << "Checker::createTransformAlign"
                              << " transformation=" << QTransformToString (transformation.transformMatrix()).toLatin1().data() << endl
                              << " radiusLinearCartesian=" << radiusLinearCartesian
                              << " posXRadiusY0Screen=" << QPointFToString (posXRadiusY0Screen).toLatin1().data()
                              << " posX0YRadiusScreen=" << QPointFToString (posX0YRadiusScreen).toLatin1().data()
                              << " ellipseXAxis=" << ellipseXAxis
                              << " ellipseYAxis=" << ellipseYAxis
                              << " posXRadiusY0AlignedScreen=" << QPointFToString (posXRadiusY0AlignedScreen).toLatin1().data()
                              << " posX0YRadiusAlignedScreen=" << QPointFToString (posX0YRadiusAlignedScreen).toLatin1().data()
                              << " transformAlign=" << QTransformToString (transformAlign).toLatin1().data();
}

void Checker::deleteSide (SideSegments &sideSegments)
{
  for (int i = 0; i < sideSegments.count(); i++) {
    QGraphicsItem *item = sideSegments [i];
    if (item != 0) {
      delete item;
    }
  }

  sideSegments.clear();
}

QGraphicsItem *Checker::ellipseItem(const Transformation &transformation,
                                    double radiusLinearCartesian,
                                    const QPointF &posStartScreen,
                                    const QPointF &posEndScreen) const
{
  // LOG4CPP_INFO_S is below

  QPointF posStartGraph, posEndGraph;

  transformation.transformScreenToRawGraph (posStartScreen,
                                            posStartGraph);
  transformation.transformScreenToRawGraph (posEndScreen,
                                            posEndGraph);

  // Get the angles about the origin of the start and end points
  double angleStart = posStartGraph.x() * DEGREES_TO_RADIANS;
  double angleEnd = posEndGraph.x() * DEGREES_TO_RADIANS;
  if (angleEnd < angleStart) {
    angleEnd += TWO_PI;
  }
  double angleSpan = angleEnd - angleStart;

  // Get origin
  QPointF posOriginGraph (0, 0), posOriginScreen;
  transformation.transformLinearCartesianGraphToScreen (posOriginGraph,
                                                        posOriginScreen);

  LOG4CPP_INFO_S ((*mainCat)) << "Checker::ellipseItem"
                              << " radiusLinearCartesian=" << radiusLinearCartesian
                              << " posStartScreen=" << QPointFToString (posStartScreen).toLatin1().data()
                              << " posEndScreen=" << QPointFToString (posEndScreen).toLatin1().data()
                              << " posOriginScreen=" << QPointFToString (posOriginScreen).toLatin1().data()
                              << " angleStart=" << angleStart / DEGREES_TO_RADIANS
                              << " angleEnd=" << angleEnd / DEGREES_TO_RADIANS
                              << " transformation=" << transformation;

  // Compute rotate/shear transform that aligns linear cartesian graph coordinates with screen coordinates, and ellipse parameters.
  // Transform does not include scaling since that messes up the thickness of the drawn line, and does not include
  // translation since that is not important
  double ellipseXAxis, ellipseYAxis;
  QTransform transformAlign;
  createTransformAlign (transformation,
                        radiusLinearCartesian,
                        posOriginScreen,
                        transformAlign,
                        ellipseXAxis,
                        ellipseYAxis);

  // Create a circle in graph space with the specified radius
  QRectF boundingRect (-1.0 * ellipseXAxis + posOriginScreen.x(),
                       -1.0 * ellipseYAxis + posOriginScreen.y(),
                       2 * ellipseXAxis,
                       2 * ellipseYAxis);
  GraphicsArcItem *item = new GraphicsArcItem (boundingRect);
  item->setStartAngle (angleStart * RADIANS_TO_TICS);
  item->setSpanAngle (angleSpan * RADIANS_TO_TICS);

  item->setTransform (transformAlign.transposed ().inverted ());

  return item;
}

void Checker::finishActiveSegment (const DocumentModelCoords &modelCoords,
                                   const QPointF &posStartScreen,
                                   const QPointF &posEndScreen,
                                   double yFrom,
                                   double yTo,
                                   const Transformation &transformation,
                                   SideSegments &sideSegments) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Checker::finishActiveSegment"
                              << " posStartScreen=" << QPointFToString (posStartScreen).toLatin1().data()
                              << " posEndScreen=" << QPointFToString (posEndScreen).toLatin1().data()
                              << " yFrom=" << yFrom
                              << " yTo=" << yTo;

  QGraphicsItem *item;
  if ((modelCoords.coordsType() == COORDS_TYPE_POLAR) &&
      (yFrom == yTo)) {

    // Linear cartesian radius
    double radiusLinearCartesian = yFrom;
    if (modelCoords.coordScaleYRadius() == COORD_SCALE_LOG) {
      radiusLinearCartesian = transformation.logToLinearRadius(yFrom,
                                                               modelCoords.originRadius());
    } else {
      radiusLinearCartesian -= modelCoords.originRadius();
    }

    // Draw along an arc since this is a side of constant radius, and we have polar coordinates
    item = ellipseItem (transformation,
                        radiusLinearCartesian,
                        posStartScreen,
                        posEndScreen);

  } else {

    // Draw straight line
    item = lineItem (posStartScreen,
                     posEndScreen);
  }

  sideSegments.push_back (item);
  bindItemToScene (item);
}

QGraphicsItem *Checker::lineItem (const QPointF &posStartScreen,
                                  const QPointF &posEndScreen) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Checker::lineItem"
                              << " posStartScreen=" << QPointFToString (posStartScreen).toLatin1().data()
                              << " posEndScreen=" << QPointFToString (posEndScreen).toLatin1().data();

  return new QGraphicsLineItem (QLineF (posStartScreen,
                                        posEndScreen));
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
  // identity transformation, so this routine can reuse computations provided by Transformation
  QList<Point> points;
  QPolygonF::const_iterator itr;
  for (itr = polygon.begin (); itr != polygon.end (); itr++) {

    const QPointF &pF = *itr;

    Point p (DUMMY_CURVE_NAME,
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
  LOG4CPP_INFO_S ((*mainCat)) << "Checker::prepareForDisplay "
                              << " transformation=" << transformation;

  ENGAUGE_ASSERT (points.count () == NUM_AXES_POINTS);

  // Remove previous lines
  deleteSide (m_sideLeft);
  deleteSide (m_sideTop);
  deleteSide (m_sideRight);
  deleteSide (m_sideBottom);

  // Get the min and max of x and y. We initialize yTo to prevent compiler warning
  double xFrom, xTo, yFrom, yTo = 0;
  int i;
  for (i = 0; i < NUM_AXES_POINTS; i++) {
    if (i == 0) {
      xFrom = points.at(i).posGraph().x();
      xTo   = points.at(i).posGraph().x();
      yFrom = points.at(i).posGraph().y();
      yTo   = points.at(i).posGraph().y();
    }
    xFrom = qMin (xFrom, points.at(i).posGraph().x());
    xTo   = qMax (xTo  , points.at(i).posGraph().x());
    yFrom = qMin (yFrom, points.at(i).posGraph().y());
    yTo   = qMax (yTo  , points.at(i).posGraph().y());
  }

  // Min and max of angles needs special processing since periodicity introduces some ambiguity. This is a noop for rectangular coordinates
  // and for polar coordinates when periodicity is not an issue
  adjustPolarAngleRanges (modelCoords,
                          transformation,
                          points,
                          xFrom,
                          xTo,
                          yFrom);

  // Draw the bounding box as four sides. In polar plots the bottom side is zero-length, with pie shape resulting
  createSide (pointRadius, points, modelCoords, xFrom, yFrom, xFrom, yTo  , transformation, m_sideLeft);
  createSide (pointRadius, points, modelCoords, xFrom, yTo  , xTo  , yTo  , transformation, m_sideTop);
  createSide (pointRadius, points, modelCoords, xTo  , yTo  , xTo  , yFrom, transformation, m_sideRight);
  createSide (pointRadius, points, modelCoords, xTo  , yFrom, xFrom, yFrom, transformation, m_sideBottom);

  updateModelAxesChecker (modelAxesChecker);
}

void Checker::setLineColor (SideSegments &sideSegments,
                            const QPen &pen)
{
  for (int i = 0; i < sideSegments.count(); i++) {
    QGraphicsItem *item = sideSegments [i];
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

void Checker::setVisibleSide (SideSegments &sideSegments,
                              bool visible)
{
  for (int i = 0; i < sideSegments.count(); i++) {
    QGraphicsItem *item = sideSegments [i];
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
