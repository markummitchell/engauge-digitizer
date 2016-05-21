/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GraphicsArcItem.h"
#include "GridLineFactory.h"
#include "Logger.h"
#include <QGraphicsScene>
#include <qmath.h>
#include <QTextStream>
#include "QtToString.h"
#include "Transformation.h"

const int Z_VALUE_IN_FRONT = 100;

// To emphasize that the axis lines are still there, we make these checker somewhat transparent
const double CHECKER_OPACITY = 0.6;

const double PI = 3.1415926535;
const double TWO_PI = 2.0 * PI;
const double DEGREES_TO_RADIANS = PI / 180.0;
const double RADIANS_TO_TICS = 5760 / TWO_PI;

GridLineFactory::GridLineFactory(QGraphicsScene &scene,
                                 int pointRadius,
                                 const QList<Point> &points,
                                 const DocumentModelCoords &m_modelCoords,
                                 const Transformation &transformation) :
  m_scene (scene),
  m_pointRadius (pointRadius),
  m_points (points),
  m_modelCoords (m_modelCoords),
  m_transformation (transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridLineFactory::GridLineFactory"
                              << " pointRadius=" << pointRadius
                              << " transformation=" << transformation;
}

void GridLineFactory::bindItemToScene(QGraphicsItem *item) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GridLineFactory::bindItemToScene";

  item->setOpacity (CHECKER_OPACITY);
  item->setZValue (Z_VALUE_IN_FRONT);
  item->setToolTip (QObject::tr ("Axes checker. If this does not align with the axes, then the axes points should be checked"));

  m_scene.addItem (item);
}

void GridLineFactory::createGridLine (double xFrom,
                                      double yFrom,
                                      double xTo,
                                      double yTo,
                                      GridLine &gridLines)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridLineFactory::createGridLine"
                              << " xFrom=" << xFrom
                              << " yFrom=" << yFrom
                              << " xTo=" << xTo
                              << " yTo=" << yTo;

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
    if (m_modelCoords.coordScaleXTheta() == COORD_SCALE_LOG) {
      xGraph = qExp ((1.0 - s) * qLn (xFrom) + s * qLn (xTo));
    }
    if (m_modelCoords.coordScaleYRadius() == COORD_SCALE_LOG) {
      yGraph = qExp ((1.0 - s) * qLn (yFrom) + s * qLn (yTo));
    }

    QPointF pointScreen;
    m_transformation.transformRawGraphToScreen (QPointF (xGraph, yGraph),
                                                pointScreen);

    double distanceToNearestPoint = minScreenDistanceFromPoints (pointScreen,
                                                                 m_points);
    if ((distanceToNearestPoint < m_pointRadius) ||
        (i == NUM_STEPS)) {

        // Too close to point, so point is not included in side. Or this is the final iteration of the loop
      if (stateSegmentIsActive) {

        // State transition
        finishActiveGridLine (posStartScreen,
                              pointScreen,
                              yFrom,
                              yTo,
                              gridLines);
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

void GridLineFactory::createTransformAlign (const Transformation &transformation,
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

  LOG4CPP_INFO_S ((*mainCat)) << "GridLineFactory::createTransformAlign"
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

void GridLineFactory::deleteSide (GridLine &gridLines)
{
  for (int i = 0; i < gridLines.count(); i++) {
    QGraphicsItem *item = gridLines [i];
    if (item != 0) {
      delete item;
    }
  }

  gridLines.clear();
}

QGraphicsItem *GridLineFactory::ellipseItem (const Transformation &transformation,
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

  LOG4CPP_INFO_S ((*mainCat)) << "GridLineFactory::ellipseItem"
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

void GridLineFactory::finishActiveGridLine (const QPointF &posStartScreen,
                                            const QPointF &posEndScreen,
                                            double yFrom,
                                            double yTo,
                                            GridLine &gridLines) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridLineFactory::finishActiveGridLine"
                              << " posStartScreen=" << QPointFToString (posStartScreen).toLatin1().data()
                              << " posEndScreen=" << QPointFToString (posEndScreen).toLatin1().data()
                              << " yFrom=" << yFrom
                              << " yTo=" << yTo;

  QGraphicsItem *item;
  if ((m_modelCoords.coordsType() == COORDS_TYPE_POLAR) &&
      (yFrom == yTo)) {

    // Linear cartesian radius
    double radiusLinearCartesian = yFrom;
    if (m_modelCoords.coordScaleYRadius() == COORD_SCALE_LOG) {
      radiusLinearCartesian = m_transformation.logToLinearRadius(yFrom,
                                                                 m_modelCoords.originRadius());
    } else {
      radiusLinearCartesian -= m_modelCoords.originRadius();
    }

    // Draw along an arc since this is a side of constant radius, and we have polar coordinates
    item = ellipseItem (m_transformation,
                        radiusLinearCartesian,
                        posStartScreen,
                        posEndScreen);

  } else {

    // Draw straight line
    item = lineItem (posStartScreen,
                     posEndScreen);
  }

  gridLines.push_back (item);
  bindItemToScene (item);
}

QGraphicsItem *GridLineFactory::lineItem (const QPointF &posStartScreen,
                                          const QPointF &posEndScreen) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridLineFactory::lineItem"
                              << " posStartScreen=" << QPointFToString (posStartScreen).toLatin1().data()
                              << " posEndScreen=" << QPointFToString (posEndScreen).toLatin1().data();

  return new QGraphicsLineItem (QLineF (posStartScreen,
                                        posEndScreen));
}

double GridLineFactory::minScreenDistanceFromPoints (const QPointF &posScreen,
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
