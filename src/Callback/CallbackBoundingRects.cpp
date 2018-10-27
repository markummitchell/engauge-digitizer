/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackBoundingRects.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "Point.h"
#include <qmath.h>
#include "QtToString.h"
#include "Transformation.h"

CallbackBoundingRects::CallbackBoundingRects(DocumentAxesPointsRequired documentAxesPointsRequired,
                                             const Transformation &transformation) :
  m_documentAxesPointsRequired (documentAxesPointsRequired),
  m_isEmptyGraphX (true),
  m_isEmptyGraphY (true),
  m_isEmptyScreenX (true),
  m_isEmptyScreenY (true),
  m_transformation (transformation)
{
}

QPointF CallbackBoundingRects::boundingRectGraphMax (bool &isEmpty) const
{
  // Need both X and Y before results are useful
  isEmpty = m_isEmptyGraphX || m_isEmptyGraphY;

  return m_boundingRectGraphMax;
}

QPointF CallbackBoundingRects::boundingRectGraphMin (bool &isEmpty) const
{
  // Need both X and Y before results are useful
  isEmpty = m_isEmptyGraphX || m_isEmptyGraphY;

  return m_boundingRectGraphMin;
}

QRectF CallbackBoundingRects::boundingRectScreen (bool &isEmpty) const
{
  // Need both X and Y before results are useful
  isEmpty = m_isEmptyScreenX || m_isEmptyScreenY;

  return QRectF (m_boundingRectScreenMin,
                 m_boundingRectScreenMax).normalized();
}

CallbackSearchReturn CallbackBoundingRects::callback (const QString &curveName,
                                                      const Point &point)
{
  QPointF posGraph;
  bool haveGraphX = true,  haveGraphY = true;
  if (curveName == AXIS_CURVE_NAME) {
    posGraph = point.posGraph(); // Axis point has graph coordinates

    haveGraphX = (m_documentAxesPointsRequired != DOCUMENT_AXES_POINTS_REQUIRED_4) || point.isXOnly();
    haveGraphY = (m_documentAxesPointsRequired != DOCUMENT_AXES_POINTS_REQUIRED_4) || !point.isXOnly();

  } else {
    m_transformation.transformScreenToRawGraph (point.posScreen(),
                                                posGraph); // Curve point has undefined graph coordinates, but they can be calculated
  }

  if (haveGraphX) {
    mergeCoordinateX (posGraph,
                      m_boundingRectGraphMin,
                      m_boundingRectGraphMax,
                      m_isEmptyGraphX);
  }
  if (haveGraphY) {
    mergeCoordinateY (posGraph,
                      m_boundingRectGraphMin,
                      m_boundingRectGraphMax,
                      m_isEmptyGraphY);
  }
  mergeCoordinateX (point.posScreen(),
                    m_boundingRectScreenMin,
                    m_boundingRectScreenMax,
                    m_isEmptyScreenX);
  mergeCoordinateY (point.posScreen(),
                    m_boundingRectScreenMin,
                    m_boundingRectScreenMax,
                    m_isEmptyScreenY);

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}

void CallbackBoundingRects::mergeCoordinateX (const QPointF &pos,
                                              QPointF &boundingRectMin,
                                              QPointF &boundingRectMax,
                                              bool &isEmpty)
{
  bool newGraphMin = isEmpty;
  bool newGraphMax = isEmpty;

  if (!newGraphMin) {
    newGraphMin = (pos.x() < boundingRectMin.x());
  }
  if (!newGraphMax) {
    newGraphMax = (boundingRectMax.x() < pos.x());
  }

  if (newGraphMin) {
    boundingRectMin.setX (pos.x());
  }
  if (newGraphMax) {
    boundingRectMax.setX (pos.x());
  }

  isEmpty = false;
}

void CallbackBoundingRects::mergeCoordinateY (const QPointF &pos,
                                              QPointF &boundingRectMin,
                                              QPointF &boundingRectMax,
                                              bool &isEmpty)
{
  bool newGraphMin = isEmpty;
  bool newGraphMax = isEmpty;

  if (!newGraphMin) {
    newGraphMin = (pos.y() < boundingRectMin.y());
  }
  if (!newGraphMax) {
    newGraphMax = (boundingRectMax.y() < pos.y());
  }

  if (newGraphMin) {
    boundingRectMin.setY (pos.y());
  }
  if (newGraphMax) {
    boundingRectMax.setY (pos.y());
  }

  isEmpty = false;
}
