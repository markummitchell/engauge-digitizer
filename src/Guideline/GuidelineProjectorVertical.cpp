/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include <algorithm>
#include "GuidelineProjectorVertical.h"
#include <QList>
#include <QPointF>
#include <QRectF>
#include "Transformation.h"

GuidelineProjectorVertical::GuidelineProjectorVertical(const Transformation &transformation,
                                                       const QPointF &posScreen,
                                                       const QRectF &sceneRect)
{
  double width = sceneRect.width();
  double height = sceneRect.height();

  // Convert sceneRect to graph coordinates
  QPointF posGraph, posGraphBL, posGraphTL, posGraphTR, posGraphBR;
  QPointF posScreenBL (0, 0), posScreenTL (0, height), posScreenTR (width, height), posScreenBR (width, 0);
  transformation.transformScreenToRawGraph (posScreen,   posGraph);
  transformation.transformScreenToRawGraph (posScreenBL, posGraphBL);
  transformation.transformScreenToRawGraph (posScreenTL, posGraphTL);  
  transformation.transformScreenToRawGraph (posScreenTR, posGraphTR);
  transformation.transformScreenToRawGraph (posScreenBR, posGraphBR);

  // Solutions below, and above, posGraph in terms of y values
  QList<double> yValuesBelow;
  QList<double> yValuesAbove;

  // We start with the vector equation
  //                            R = (1-s)*P1 + s*P2
  // For each corner, intersect just the y components of the vector equation
  //                            x = (1-s)*x1 + s*x2
  //                            x = x0
  // to get an s value. To prevent overflow due to division by zero, we use the
  // trick that only values of s between 0 and 1 (=between the 2 endpoints) are
  // desired. Allowing for roundoff, and then adding some, we limit s to between
  // -1 and 2. Since s=numerator/denominator then -1<numerator/denominator<2
  // must be true or else we skip the division, which prevents overflow errors
  double numLeft   = posGraph.x() - posGraphBL.x();
  double numTop    = posGraph.x() - posGraphTL.x();
  double numRight  = posGraph.x() - posGraphTR.x();
  double numBottom = posGraph.x() - posGraphBR.x();
  double denLeft   = posGraphTL.x() - posGraphBL.x();
  double denTop    = posGraphTR.x() - posGraphTL.x();
  double denRight  = posGraphBR.x() - posGraphTR.x();
  double denBottom = posGraphBL.x() - posGraphBR.x();

  addSide (numLeft  , denLeft  , posGraph.y(), posGraphBL.y(), posGraphTL.y(), yValuesBelow, yValuesAbove);
  addSide (numTop   , denTop   , posGraph.y(), posGraphTL.y(), posGraphTR.y(), yValuesBelow, yValuesAbove);
  addSide (numRight , denRight , posGraph.y(), posGraphTR.y(), posGraphBR.y(), yValuesBelow, yValuesAbove);
  addSide (numBottom, denBottom, posGraph.y(), posGraphBR.y(), posGraphBL.y(), yValuesBelow, yValuesAbove);

  // Sort
  std::sort (yValuesBelow.begin(), yValuesBelow.end());
  std::sort (yValuesAbove.begin(), yValuesAbove.end());
  
  if (yValuesBelow.size() == 0) {
    // Pathological case with roundoff error. Lowest value in yValuesAbove is assumed to be on below side
    double moved = yValuesAbove.front();
    yValuesAbove.removeFirst();
    yValuesBelow.push_back (moved);
  } else if (yValuesAbove.size() == 0) {
    // Pathological case with roundoff error. Highest value in yValuesBelow is assumed to be on above side
    double moved = yValuesBelow.back();
    yValuesBelow.removeLast();
    yValuesAbove.push_front (moved);
  }

  // Line goes between highest x in yValuesBelow and lowest x in yValuesAbove
  double y1 = yValuesBelow.back ();
  double y2 = yValuesAbove.front ();

  // Convert from graph coordinates back to screen coordinates
  transformation.transformRawGraphToScreen (QPointF (posGraph.x(), y1),
                                            m_pos1);
  transformation.transformRawGraphToScreen (QPointF (posGraph.x(), y2),
                                            m_pos2);
}

GuidelineProjectorVertical::~GuidelineProjectorVertical()
{
}

void GuidelineProjectorVertical::addSide (double num,
                                          double den,
                                          double y,
                                          double y1,
                                          double y2,
                                          QList<double> &yValuesBelow,
                                          QList<double> &yValuesAbove)
{
  // Inequalities have to be flipped if multiplying by a negative number
  bool okForDenPositive = (den >= 0) && (-1.0 * den < num) && (num < 2.0 * den);
  bool okForDenNegative = (den < 0) && (-1.0 * den > num) && (num > 2.0 * den);

  if (okForDenPositive || okForDenNegative) {
    double sIntercept = num / den;
    double yIntercept = (1.0 - sIntercept) * y1 + sIntercept * y2;
    if (yIntercept < y) {
      yValuesBelow.push_back (yIntercept);
    } else {
      yValuesAbove.push_back (yIntercept);
    }
  }
}

QPointF GuidelineProjectorVertical::pos1() const
{
  return m_pos1;
}

QPointF GuidelineProjectorVertical::pos2() const
{
  return m_pos2;
}
