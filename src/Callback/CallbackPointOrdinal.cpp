/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackPointOrdinal.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "mmsubs.h"
#include "Point.h"
#include <qmath.h>
#include "Transformation.h"

CallbackPointOrdinal::CallbackPointOrdinal(const LineStyle &lineStyle,
                                           const Transformation &transformation,
                                           const QPointF &posScreen) :
  m_lineStyle (lineStyle),
  m_transformation (transformation),
  m_posScreen (posScreen),
  m_haveMinimumDistanceToLine (false),
  m_minimumDistanceToLine (0.0),
  m_minimumProjectedDistanceOutsideLine (0.0),
  m_ordinal (0)
{
}

CallbackSearchReturn CallbackPointOrdinal::callback (const Point &pointStart,
                                                     const Point &pointStop)
{
  double xProjection, yProjection, projectedDistanceOutsideLine, distanceToLine;

  projectPointOntoLine(m_posScreen.x(),
                       m_posScreen.y(),
                       pointStart.posScreen().x(),
                       pointStart.posScreen().y(),
                       pointStop.posScreen().x(),
                       pointStop.posScreen().y(),
                       &xProjection,
                       &yProjection,
                       &projectedDistanceOutsideLine,
                       &distanceToLine);

  // Compare to best so far
  if (!m_haveMinimumDistanceToLine ||
      (distanceToLine < m_minimumDistanceToLine) ||
      (distanceToLine == m_minimumDistanceToLine && projectedDistanceOutsideLine < m_minimumProjectedDistanceOutsideLine)) {

    // Compute ordinal
    if (projectedDistanceOutsideLine == 0) {

      // Put new point inside the line segment
      m_ordinal = (pointStart.ordinal() + pointStop.ordinal()) / 2.0;

    } else {

      // Put new point just outside the line segment
      double distanceProjectionToStart = qSqrt ((xProjection - pointStart.posScreen().x()) * (xProjection - pointStart.posScreen().x()) +
                                                (yProjection - pointStart.posScreen().y()) * (yProjection - pointStart.posScreen().y()));
      double distanceProjectionToStop = qSqrt ((xProjection - pointStop.posScreen().x()) * (xProjection - pointStop.posScreen().x()) +
                                               (yProjection - pointStop.posScreen().y()) * (yProjection - pointStop.posScreen().y()));
      if (distanceProjectionToStart < distanceProjectionToStop) {

        // Before start point
        m_ordinal = pointStart.ordinal() - 0.5;

      } else {

        // After stop point
        m_ordinal = pointStop.ordinal() + 0.5;
      }
    }

    // Save as new 'best'
    m_haveMinimumDistanceToLine = true;
    m_minimumDistanceToLine = distanceToLine;
    m_minimumProjectedDistanceOutsideLine = projectedDistanceOutsideLine;
  }

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}

double CallbackPointOrdinal::ordinal () const
{
  return m_ordinal;
}
