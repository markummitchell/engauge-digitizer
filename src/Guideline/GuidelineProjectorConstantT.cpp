/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include <algorithm>
#include "GuidelineProjectorConstantT.h"
#include <QList>
#include <qmath.h>
#include <QRectF>
#include "Transformation.h"

GuidelineProjectorConstantT::GuidelineProjectorConstantT()
{
}

GuidelineProjectorConstantT::~GuidelineProjectorConstantT()
{
}

QLineF GuidelineProjectorConstantT::fromCoordinateT (const Transformation &transformation,
                                                     const QRectF &sceneRect,
                                                     double thetaGraphDegrees)
{
  QPointF posGraphBL, posGraphTL, posGraphTR, posGraphBR;
  calculateCorners (transformation,
                    sceneRect,
                    posGraphBL,
                    posGraphTL,
                    posGraphTR,
                    posGraphBR);

  // These containers would be QVector2D to emphasize we are not working with x and y valuees, but
  // QVector2D would give double/float conversion errors
  QPointF anglesLeft   (qMin (posGraphBL.x(), posGraphTL.x()),
                        qMax (posGraphBL.x(), posGraphTL.x()));
  QPointF anglesTop    (qMin (posGraphTL.x(), posGraphTR.x()),
                        qMax (posGraphTL.x(), posGraphTR.x()));
  QPointF anglesRight  (qMin (posGraphTR.x(), posGraphBR.x()),
                        qMax (posGraphTR.x(), posGraphBR.x()));
  QPointF anglesBottom (qMin (posGraphBR.x(), posGraphBL.x()),
                        qMax (posGraphBR.x(), posGraphBL.x()));

  // Fix any side that crosses over the discontinuous transition
  if (qAbs (anglesLeft.y() - anglesLeft.x()) > 180.0) {
    double temp = anglesLeft.x();
    anglesLeft.setX (anglesLeft.y());
    anglesLeft.setY (temp + 360.0);
  }
  if (qAbs (anglesTop.y() - anglesTop.x()) > 180.0) {
    double temp = anglesTop.x();
    anglesTop.setX (anglesTop.y());
    anglesTop.setY (temp + 360.0);
  }
  if (qAbs (anglesRight.y() - anglesRight.x()) > 180.0) {
    double temp = anglesRight.x();
    anglesRight.setX (anglesRight.y());
    anglesRight.setY (temp + 360.0);
  }
  if (qAbs (anglesBottom.y() - anglesBottom.x()) > 180.0) {
    double temp = anglesBottom.x();
    anglesBottom.setX (anglesBottom.y());
    anglesBottom.setY (temp + 360.0);
  }

  // Which side matches theta?
  QLineF line;
  double thetaGraphPlus = thetaGraphDegrees + 360.0;
  if ((anglesLeft.x() <= thetaGraphDegrees && thetaGraphDegrees <= anglesLeft.y()) ||
      (anglesLeft.x() <= thetaGraphPlus    && thetaGraphPlus    <= anglesLeft.y())) {

    // Left side
    line = intersect (transformation,
                      thetaGraphDegrees,
                      posGraphBL,
                      posGraphTL);

  } else if ((anglesTop.x() <= thetaGraphDegrees && thetaGraphDegrees <= anglesTop.y()) ||
             (anglesTop.x() <= thetaGraphPlus    && thetaGraphPlus    <= anglesTop.y())) {

    // Top side
    line = intersect (transformation,
                      thetaGraphDegrees,
                      posGraphTL,
                      posGraphTR);

  } else if ((anglesRight.x() <= thetaGraphDegrees && thetaGraphDegrees <= anglesRight.y()) ||
             (anglesRight.x() <= thetaGraphPlus    && thetaGraphPlus    <= anglesRight.y())) {

    // Right side
    line = intersect (transformation,
                      thetaGraphDegrees,
                      posGraphTR,
                      posGraphBR);

  } else {

    // Bottom side
    line = intersect (transformation,
                      thetaGraphDegrees,
                      posGraphBR,
                      posGraphBL);

  }

  return line;
}

QLineF GuidelineProjectorConstantT::fromPosScreen (const Transformation &transformation,
                                                   const QRectF &sceneRect,
                                                   const QPointF &posScreen)
{
  QPointF posGraph;
  transformation.transformScreenToRawGraph (posScreen,  posGraph);

  return fromCoordinateT (transformation,
                          sceneRect,
                          posGraph.x());
}

QLineF GuidelineProjectorConstantT::intersect (const Transformation &transformation,
                                               double thetaGraphDegrees,
                                               const QPointF &posPolar1,
                                               const QPointF &posPolar2) const
{
  QPointF p1, p2; // Cartesian coordinates
  transformation.transformRawGraphToLinearCartesianGraph (posPolar1,
                                                          p1);
  transformation.transformRawGraphToLinearCartesianGraph (posPolar2,
                                                          p2);

  // Intersect y = x tan (theta) = slope * x
  //           (x - x0) / (x1 - x0) = (y - y0) / (y1 - y0)
  // with divide by zero errors prevented by treating the second equation as either
  //  OPTION 1  (x - x0) = [(x1 - x0) / (y1 - y0)] * (y - y0)
  // or
  //  OPTION 2  (y - y0) = [(y1 - y0) / (x1 - x0)] * (x - x0)

  double deltaX = p2.x() - p1.x();
  double deltaY = p2.y() - p1.y();

  double x, y;
  if (qAbs (deltaX) < qAbs (deltaY)) {

    // Safe to compute since mostly horizontal
    double slope = qTan (qDegreesToRadians (thetaGraphDegrees));

    // Use OPTION 1 with x - x0 = fraction * (y - y0)
    // substituting      y = slope * x
    // we get            x * (1 - fraction * slope) = x0 - fraction * y0
    // since line is mostly vertical (deltaX<deltaY) we know the line y=slope*x
    // that intersects it is mostly horizontal so it cannot have infinite slope
    // so the following code has no way to overflow (by inspection)
    double fraction = deltaX / deltaY;
    x = (p1.x () - fraction * p1.y ()) / (1.0 - fraction * slope);
    y = slope * x;

  } else {

    // Safe to compute since mostly vertical. Derived from tan(theta)=y/x and tan(90-theta)=x/y
    double slopeInverse = qTan (qDegreesToRadians (90.0 - thetaGraphDegrees));

    // Use OPTION 2 with y - y0 = fraction * (x - x0)
    // substituting      x = y / slope
    // we get            y * (1 - fraction / slope) = y0 - fraction * x0
    // since line is mostly horizontal (deltaY<deltaX) we know the line y=slope*x
    // that intersects it is mostly vertical so it cannot have zero slope
    // so the following code has no way to overflow (by inspection)
    double fraction = deltaY / deltaX;
    y = (p1.y () - fraction * p1.x ()) / (1.0 - fraction * slopeInverse);
    x = slopeInverse * y;
  }

  QPointF posGraphCenter (0, 0);
  if (transformation.modelCoords().coordScaleYRadius() == COORD_SCALE_LOG) {
    posGraphCenter = QPointF (0,
                              transformation.modelCoords().originRadius());
  }

  // Convert graph coordinate points into screen coordinate line
  QPointF posSceneCenter, posSceneOther;
  transformation.transformRawGraphToScreen (posGraphCenter,
                                            posSceneCenter);
  transformation.transformLinearCartesianGraphToScreen (QPointF (x, y),
                                                        posSceneOther);

  return QLineF (posSceneCenter,
                 posSceneOther);
}
