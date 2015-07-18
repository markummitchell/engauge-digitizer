#include "CallbackBoundingRects.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "Point.h"
#include <qmath.h>
#include "QtToString.h"
#include "Transformation.h"

CallbackBoundingRects::CallbackBoundingRects(const Transformation &transformation) :
  m_isEmpty (true),
  m_transformation (transformation)
{
}

QRectF CallbackBoundingRects::boundingRectGraph (bool &isEmpty) const
{
  isEmpty = m_isEmpty;

  return m_boundingRectGraph;
}

QRectF CallbackBoundingRects::boundingRectScreen (bool &isEmpty) const
{
  isEmpty = m_isEmpty;

  return m_boundingRectScreen;
}

CallbackSearchReturn CallbackBoundingRects::callback (const QString &curveName,
                                                      const Point &point)
{
  QPointF posGraph;
  if (curveName == AXIS_CURVE_NAME) {
    posGraph = point.posGraph(); // Axis point has graph coordinates
  } else {
    m_transformation.transformScreenToRawGraph (point.posScreen(),
                                                posGraph); // Curve point has undefined graph coordinates, but they can be calculated
  }
  mergeCoordinates (posGraph,
                    m_boundingRectGraph);
  mergeCoordinates (point.posScreen(),
                    m_boundingRectScreen);

  m_isEmpty = false; // Set this after the calls to mergeCoordinates which uses it

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}

void CallbackBoundingRects::mergeCoordinates (const QPointF &pos,
                                              QRectF &boundingRect)
{
  bool newGraphLeft   = m_isEmpty;
  bool newGraphTop    = m_isEmpty;
  bool newGraphRight  = m_isEmpty;
  bool newGraphBottom = m_isEmpty;

  if (!newGraphLeft) {
    newGraphLeft   = (pos.x() < boundingRect.left());
  }
  if (!newGraphTop) {
    newGraphTop    = (pos.y() < boundingRect.top());
  }
  if (!newGraphRight) {
    newGraphRight  = (boundingRect.right() < pos.x());
  }
  if (!newGraphBottom) {
    newGraphBottom = (boundingRect.bottom() < pos.y());
  }

  if (newGraphLeft) {
    boundingRect.setLeft (pos.x());
  }
  if (newGraphTop) {
    boundingRect.setTop (pos.y());
  }
  if (newGraphRight) {
    boundingRect.setRight (pos.x());
  }
  if (newGraphBottom) {
    boundingRect.setBottom (pos.y());
  }
}
