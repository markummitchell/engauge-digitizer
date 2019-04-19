/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "LineStyle.h"
#include <qmath.h>
#include "Spline.h"
#include "SplineDrawer.h"

SplineDrawer::SplineDrawer(const Transformation &transformation) :
  m_transformation (transformation)
{
}

void SplineDrawer::bindToSpline (const LineStyle &lineStyle,
                                 int numSegments,
                                 const Spline &spline)
{
  m_segmentOperations.resize (numSegments);

  // Loop through segments to get move/draw choice. We do not need to worry about
  // applying a move (versus a draw) for the first segment since that first point
  // is handled by external code
  for (int segment = 0; segment < numSegments; segment++) {

    bool itsAKeeper = true;
    if (m_transformation.transformIsDefined()) {

      // We have the graph<->screen transformation so let's use it. Could there be an ambiguity issue?
      if ((lineStyle.curveConnectAs() == CONNECT_AS_FUNCTION_SMOOTH) &&
          segmentIsMultiValued (spline,
                                numSegments,
                                segment)) {
        itsAKeeper = false;
      }

      // Invisible or visible?
      m_segmentOperations [segment] = (itsAKeeper ?
                                       SPLINE_DRAWER_ENUM_VISIBLE_DRAW :
                                       SPLINE_DRAWER_ENUM_INVISIBLE_MOVE);
    }
  }
}

bool SplineDrawer::segmentIsMultiValued (const Spline &spline,
                                         int numSegments,
                                         int segment) const
{
  ENGAUGE_ASSERT (m_transformation.transformIsDefined());

  if (segment < numSegments - 1) {

    // Not at very end
    double tI = double (segment);
    double tIp1 = double (segment + 1);

    // Compute number of pixels between endpoints
    SplinePair posScreenStart  = spline.interpolateCoeff (tI);
    SplinePair posScreenEnd = spline.interpolateCoeff (tIp1);

    int deltaX = qFloor (posScreenEnd.x() - posScreenStart.x());
    int deltaY = qFloor (posScreenEnd.y() - posScreenStart.y());
    double pixelDistance = qSqrt (deltaX * deltaX + deltaY * deltaY);
    double numSteps = pixelDistance;

    // Search through a sufficiently large number of points to verify single-valuedness
    double tIDelta = 1.0 / numSteps;
    for (int itI = 1; itI < numSteps - 1; itI++) {

      double tIm1 = segment + (itI - 1) * tIDelta;
      double tI   = segment + (itI    ) * tIDelta;
      double tIp1 = segment + (itI + 1) * tIDelta;

      SplinePair spBefore = spline.interpolateCoeff (tIm1);
      SplinePair spCurrent = spline.interpolateCoeff (tI);
      SplinePair spAfter = spline.interpolateCoeff (tIp1);

      QPointF posScreenBefore (spBefore.x(), spBefore.y());
      QPointF posScreenCurrent (spCurrent.x(), spCurrent.y());
      QPointF posScreenAfter (spAfter.x(), spAfter.y());

      QPointF posGraphBefore, posGraphCurrent, posGraphAfter;
      m_transformation.transformScreenToRawGraph (posScreenBefore,
                                                  posGraphBefore);
      m_transformation.transformScreenToRawGraph (posScreenCurrent,
                                                  posGraphCurrent);
      m_transformation.transformScreenToRawGraph (posScreenAfter,
                                                  posGraphAfter);

      // In between the start and end points we look for deltaXBefore>0 and deltaXAfter<0,
      // or deltaXBefore<0 and deltaXAfter>0, either of those two cases indicates multi-valued
      double deltaXBefore = posGraphCurrent.x() - posGraphBefore.x();
      double deltaXAfter = posGraphAfter.x() - posGraphCurrent.x();

      if ((deltaXBefore > 0 && deltaXAfter < 0) ||
          (deltaXBefore < 0 && deltaXAfter > 0)) {

        // Multi-valued
        return true;
      }
    }
  }

  return false;
}

SplineDrawerOperation SplineDrawer::segmentOperation (int segment) const
{
  if (segment < m_segmentOperations.count()) {
    return m_segmentOperations.at (segment);
  } else {
    return SPLINE_DRAWER_ENUM_INVISIBLE_MOVE;
  }
}
