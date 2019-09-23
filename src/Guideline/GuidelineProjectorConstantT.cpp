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
                                                     double thetaGraph)
{
  QPointF posGraphBL, posGraphTL, posGraphTR, posGraphBR;
  calculateCorners (transformation,
                    sceneRect,
                    posGraphBL,
                    posGraphTL,
                    posGraphTR,
                    posGraphBR);

  double angleBL = qAtan2 (posGraphBL.y(), posGraphBL.x());
  double angleTL = qAtan2 (posGraphTL.y(), posGraphTL.x());
  double angleTR = qAtan2 (posGraphTR.y(), posGraphTR.x());
  double angleBR = qAtan2 (posGraphBR.y(), posGraphBR.x());

  // These containers would be QVector2D to emphasize we are not working with x and y valuees, but
  // QVector2D would give double/float conversion errors
  QPointF anglesLeft   (qMin (angleBL, angleTL),
                        qMax (angleBL, angleTL));
  QPointF anglesTop    (qMin (angleTL, angleTR),
                        qMax (angleTL, angleTR));
  QPointF anglesRight  (qMin (angleTR, angleBR),
                        qMax (angleTR, angleBR));
  QPointF anglesBottom (qMin (angleBR, angleBL),
                        qMax (angleBR, angleBL));

  // Fix any side that crosses over the discontinuous transition
  if (anglesLeft.y() - anglesRight.x() > M_PI) {
    double temp = anglesLeft.x();
    anglesLeft.setX (anglesLeft.y());
    anglesLeft.setY (temp + 2 * M_PI);
  }
  if (anglesTop.y() - anglesTop.x() > M_PI) {
    double temp = anglesTop.x();
    anglesTop.setX (anglesTop.y());
    anglesTop.setY (temp + 2 * M_PI);
  }
  if (anglesRight.y() - anglesRight.x() > M_PI) {
    double temp = anglesRight.x();
    anglesRight.setX (anglesRight.y());
    anglesRight.setY (temp + 2 * M_PI);
  }
  if (anglesBottom.y() - anglesBottom.x() > M_PI) {
    double temp = anglesBottom.x();
    anglesBottom.setX (anglesBottom.y());
    anglesBottom.setY (temp + 2 * M_PI);
  }

  // Which side matches theta?
  QPointF posGraph;
  double thetaGraphPlus = thetaGraph + 2 * M_PI;
  if ((anglesLeft.x() <= thetaGraph     && thetaGraph     <= anglesLeft.y()) ||
      (anglesLeft.x() <= thetaGraphPlus && thetaGraphPlus <= anglesLeft.y())) {

    // Left side
    posGraph = intersect (thetaGraph, posGraphBL, posGraphTL);

  } else if ((anglesTop.x() <= thetaGraph     && thetaGraph     <= anglesTop.y()) ||
             (anglesTop.x() <= thetaGraphPlus && thetaGraphPlus <= anglesTop.y())) {

    // Top side
    posGraph = intersect (thetaGraph, posGraphTL, posGraphTR);

  } else if ((anglesRight.x() <= thetaGraph     && thetaGraph     <= anglesRight.y()) ||
             (anglesRight.x() <= thetaGraphPlus && thetaGraphPlus <= anglesRight.y())) {

    // Right side
    posGraph = intersect (thetaGraph, posGraphTR, posGraphBR);

  } else {

    // Bottom side
    posGraph = intersect (thetaGraph, posGraphBR, posGraphBL);

  }

  QPointF posSceneCenter, posSceneOther;
  transformation.transformRawGraphToScreen (QPointF (0, 0),
                                            posSceneCenter);
  transformation.transformRawGraphToScreen (posGraph,
                                            posSceneOther);

  return QLineF (posSceneCenter,
                 posSceneOther);
}

QLineF GuidelineProjectorConstantT::fromPosScreen (const Transformation &transformation,
                                                   const QRectF &sceneRect,
                                                   const QPointF &posScreen)
{
  QPointF posGraph;
  transformation.transformScreenToRawGraph (posScreen,  posGraph);

  return fromCoordinateT (transformation,
                          sceneRect,
                          qAtan2 (posGraph.y(),
                                  posGraph.x()));
}

QPointF GuidelineProjectorConstantT::intersect (double theta,
                                                const QPointF &p1,
                                                const QPointF &p2) const
{
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
    double slope = qTan (theta);

    // Use OPTION 1 with x - x0 = fraction * (y - y0)
    //                   x * (1 - fraction * slope) = x0 + fraction * y0
    // since line is mostly vertical (deltaX<deltaY) we know the line y=slope*x
    // that intersects it is mostly horizontal so it cannot have infinite slope
    // so the following code has no way to overflow (by inspection)
    double fraction = deltaX / deltaY;
    x = (p1.x () + fraction * p1.y ()) / (1.0 - fraction * slope);
    y = slope * x;

  } else {

    // Safe to compute since mostly vertical. Derived from tan(theta)=y/x and tan(90-theta)=x/y
    double slopeInverse = qTan (M_PI_2 - theta);

    // Use OPTION 2 with y - y0 = fraction * (x - x0)
    //                   y * (1 - fraction / slope) = y0 - fraction * x0
    // since line is mostly horizontal (deltaY<deltaX) we know the line y=slope*x
    // that intersects it is mostly vertical so it cannot have zero slope
    // so the following code has no way to overflow (by inspection)
    double fraction = deltaY / deltaX;
    y = (p1.y () - fraction * p1.x ()) / (1.0 - fraction * slopeInverse);
    x = slopeInverse * y;
  }

  return QPointF (x,
                  y);
}
