/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include <algorithm>
#include "GuidelineProjectorConstantY.h"
#include <QList>
#include <QRectF>
#include "Transformation.h"

GuidelineProjectorConstantY::GuidelineProjectorConstantY(const Transformation &transformation,
                                                         const QPointF &posScreen,
                                                         const QRectF &sceneRect)
{
  double width = sceneRect.width();
  double height = sceneRect.height();

  // Convert sceneRect to graph coordinates
  QPointF posScreenBL (0, 0), posScreenTL (0, height), posScreenTR (width, height), posScreenBR (width, 0);

  if (isOutside (posScreen, posScreenBL, posScreenTL, posScreenTR, posScreenBR)) {

    // Point is outside so make into an impossible to see point
    m_pos1 = QPointF (0, 0);
    m_pos2 = QPointF (0, 0);

  } else {
    
    QPointF posGraph, posGraphBL, posGraphTL, posGraphTR, posGraphBR;
    transformation.transformScreenToRawGraph (posScreen,   posGraph);
    transformation.transformScreenToRawGraph (posScreenBL, posGraphBL);
    transformation.transformScreenToRawGraph (posScreenTL, posGraphTL);
    transformation.transformScreenToRawGraph (posScreenTR, posGraphTR);
    transformation.transformScreenToRawGraph (posScreenBR, posGraphBR);

    // Solutions below, and above, posGraph in terms of x values
    QList<double> xValuesBelow;
    QList<double> xValuesAbove;

    // We start with the vector equation
    //                            R = (1-s)*P1 + s*P2
    // For each corner, intersect just the y components of the vector equation
    //                            y = (1-s)*y1 + s*y2
    //                            y = y0
    // to get an s value. To prevent overflow due to division by zero, we use the
    // trick that only values of s between 0 and 1 (=between the 2 endpoints) are
    // desired. Allowing for roundoff, and then adding some, we limit s to between
    // -1 and 2. Since s=numerator/denominator then -1<numerator/denominator<2
    // must be true or else we skip the division, which prevents overflow errors
    double numLeft   = posGraph.y() - posGraphBL.y();
    double numTop    = posGraph.y() - posGraphTL.y();
    double numRight  = posGraph.y() - posGraphTR.y();
    double numBottom = posGraph.y() - posGraphBR.y();
    double denLeft   = posGraphTL.y() - posGraphBL.y();
    double denTop    = posGraphTR.y() - posGraphTL.y();
    double denRight  = posGraphBR.y() - posGraphTR.y();
    double denBottom = posGraphBL.y() - posGraphBR.y();

    addSide (numLeft  , denLeft  , posGraph.x(), posGraphBL.x(), posGraphTL.x(), xValuesBelow, xValuesAbove);
    addSide (numTop   , denTop   , posGraph.x(), posGraphTL.x(), posGraphTR.x(), xValuesBelow, xValuesAbove);
    addSide (numRight , denRight , posGraph.x(), posGraphTR.x(), posGraphBR.x(), xValuesBelow, xValuesAbove);
    addSide (numBottom, denBottom, posGraph.x(), posGraphBR.x(), posGraphBL.x(), xValuesBelow, xValuesAbove);

    // Sort
    std::sort (xValuesBelow.begin(), xValuesBelow.end());
    std::sort (xValuesAbove.begin(), xValuesAbove.end());
  
    if (xValuesBelow.size() == 0) {
      // Pathological case with roundoff error. Lowest value in xValuesAbove is assumed to be on below side
      double moved = xValuesAbove.front();
      xValuesAbove.removeFirst();
      xValuesBelow.push_back (moved);
    } else if (xValuesAbove.size() == 0) {
      // Pathological case with roundoff error. Highest value in xValuesBelow is assumed to be on above side
      double moved = xValuesBelow.back();
      xValuesBelow.removeLast();
      xValuesAbove.push_front (moved);
    }

    // Line goes between highest x in xValuesBelow and lowest x in xValuesAbove
    double x1 = xValuesBelow.back ();
    double x2 = xValuesAbove.front ();

    // Convert from graph coordinates back to screen coordinates
    transformation.transformRawGraphToScreen (QPointF (x1, posGraph.y()),
                                              m_pos1);
    transformation.transformRawGraphToScreen (QPointF (x2, posGraph.y()),
                                              m_pos2);
  }
}

GuidelineProjectorConstantY::~GuidelineProjectorConstantY()
{
}

void GuidelineProjectorConstantY::addSide (double num,
                                           double den,
                                           double x,
                                           double x1,
                                           double x2,
                                           QList<double> &xValuesBelow,
                                           QList<double> &xValuesAbove)
{
  // Inequalities have to be flipped if multiplying by a negative number
  bool okForDenPositive = (den >= 0) && (-1.0 * den < num) && (num < 2.0 * den);
  bool okForDenNegative = (den < 0) && (-1.0 * den > num) && (num > 2.0 * den);

  if (okForDenPositive || okForDenNegative) {
    double sIntercept = num / den;
    double xIntercept = (1.0 - sIntercept) * x1 + sIntercept * x2;
    if (xIntercept < x) {
      xValuesBelow.push_back (xIntercept);
    } else {
      xValuesAbove.push_back (xIntercept);
    }
  }
}

bool GuidelineProjectorConstantY::isOutside (const QPointF &posScreen,
                                             const QPointF &posScreenBL,
                                             const QPointF &posScreenTL,
                                             const QPointF &posScreenTR,
                                             const QPointF &posScreenBR) const
{
  QPolygonF polygon;
  polygon << posScreenBL << posScreenTL << posScreenTR << posScreenBR;

  // Qt::OddEvenFill is faster and less accurate and Qt::WindingFill is slower and more accurate
  return !polygon.containsPoint (posScreen,
                                 Qt::WindingFill);
}

QPointF GuidelineProjectorConstantY::pos1() const
{
  return m_pos1;
}

QPointF GuidelineProjectorConstantY::pos2() const
{
  return m_pos2;
}
