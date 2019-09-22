/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include <algorithm>
#include "GuidelineProjectorConstantR.h"
#include <QList>
#include <QRectF>
#include "Transformation.h"

GuidelineProjectorConstantR::GuidelineProjectorConstantR()
{
}

GuidelineProjectorConstantR::~GuidelineProjectorConstantR()
{
}

void GuidelineProjectorConstantR::addSide (const Transformation &transformation,
                                           double r,
                                           const QPointF &p1,
                                           const QPointF &p2,
                                           QList<QPointF> &intersections)
{
  // We start with the vector equation
  //                            R = (1-s)*P1 + s*P2
  // For each corner, intersect just the y components of the vector equation
  //                            y = (1-s)*y1 + s*y2
  //                            y = y0
  // to get an s value. To prevent overflow due to division by zero, we use the
  // trick that only values of s between 0 and 1 (=between the 2 endpoints) are
  // desired
  double num = r - p1.y();
  double den = p2.y () - p1.y ();

  // Prevent divide by zero. Working with s=num/den and 0<s<1 we get 0<num/den<1.
  // Inequalities have to be flipped if multiplying by a negative number
  bool okForDenPositive = (den >= 0) && (0.0 * den <= num) && (num < den);
  bool okForDenNegative = (den < 0) && (0.0 * den >= num) && (num > 1.0 * den);

  if (okForDenPositive || okForDenNegative) {
    double sIntercept = num / den;
    QPointF pIntercept ((1.0 - sIntercept) * p1 + sIntercept * p2);

    QPointF posScreen;
    transformation.transformRawGraphToScreen (pIntercept,
                                              posScreen);
    intersections.push_back (posScreen);
  }
}

QRectF GuidelineProjectorConstantR::fromCoordinateR (const Transformation &transformation,
                                                     const QRectF &sceneRect,
                                                     double rGraph)
{
  QRectF rect (0, 0, 0, 0);
  QPointF posGraphBL, posGraphTL, posGraphTR, posGraphBR;
  calculateCorners (transformation,
                    sceneRect,
                    posGraphBL,
                    posGraphTL,
                    posGraphTR,
                    posGraphBR);

  // Intersections found on all the sides
  QList<QPointF> intersections;

  addSide (transformation, rGraph, posGraphBL, posGraphTL, intersections);
  addSide (transformation, rGraph, posGraphTL, posGraphTR, intersections);
  addSide (transformation, rGraph, posGraphTR, posGraphBR, intersections);
  addSide (transformation, rGraph, posGraphBR, posGraphBL, intersections);

  if (intersections.size() == 2) {
    rect = QRectF (intersections.at (0),
                   intersections.at (1));
  }

  return rect;
}

QRectF GuidelineProjectorConstantR::fromPosScreen (const Transformation &transformation,
                                                   const QRectF &sceneRect,
                                                   const QPointF &posScreen)
{
  QPointF posGraph;
  transformation.transformScreenToRawGraph (posScreen,  posGraph);

  return fromCoordinateR (transformation,
                          sceneRect,
                          posGraph.y());
}
