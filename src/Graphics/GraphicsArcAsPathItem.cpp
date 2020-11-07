/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GraphicsArcAsPathItem.h"
#include <QDebug>
#include <QGraphicsScene>
#include <qmath.h>
#include <QPainter>
#include <QPainterPath>
#include <QRectF>

const double TWO_PI = 2.0 * 3.1415926535;
const int TICS_PER_CYCLE = 360 * 16;
const double RADIANS_TO_TICS = TICS_PER_CYCLE / TWO_PI;
const double DEGREES_TO_RADIANS = TWO_PI / 360.0;

const int TICS_STEP = 8; // 16 tics per degree

GraphicsArcAsPathItem::GraphicsArcAsPathItem(double x,
                                             double y,
                                             double width,
                                             double height,
                                             QGraphicsItem *parent) :
  QGraphicsPathItem(parent),
  m_x (x),
  m_y (y),
  m_width (width),
  m_height (height),
  m_startAngle (0),
  m_spanAngle (TICS_PER_CYCLE),
  m_rotationAngle (0)
{
  updateGeometry ();
}

GraphicsArcAsPathItem::GraphicsArcAsPathItem(const QRectF &rect,
                                             QGraphicsItem *parent) :
  QGraphicsPathItem (parent),
  m_x (rect.x()),
  m_y (rect.y()),
  m_width (rect.width()),
  m_height (rect.height()),
  m_startAngle (0),
  m_spanAngle (TICS_PER_CYCLE),
  m_rotationAngle (0)
{
  updateGeometry ();
}

QPointF GraphicsArcAsPathItem::pointForAngle (int angleTheta) const
{
  // Points are at
  //
  //             (cosPhi -sinPhi) (cosTheta  0       ) (a)
  // posCenter + (sinPhi cosPhi ) (0         sinTheta) (b)
  //
  // where Phi is the rotation of the entire ellipse, and Theta is the angle between m_startAngle
  // and m_startAngle + m_spanAngle
  QPointF point (m_x + (m_width / 2.0) * qCos (m_rotationAngle) * qCos (angleTheta / RADIANS_TO_TICS),
                 m_y + (m_height / 2.0) * qSin (m_rotationAngle) * qCos (angleTheta / RADIANS_TO_TICS));

  return point;
}

void GraphicsArcAsPathItem::setSpanAngle (int spanAngle)
{
  m_spanAngle = spanAngle;
  updateGeometry ();
}

void GraphicsArcAsPathItem::setStartAngle (int startAngle)
{
  m_startAngle = startAngle;
  updateGeometry ();
}

void GraphicsArcAsPathItem::setRotation (double angleDegrees)
{
  m_rotationAngle = angleDegrees * DEGREES_TO_RADIANS;
  updateGeometry();
}

void GraphicsArcAsPathItem::updateGeometry ()
{
  // Populate points
  QPolygonF polygon;
  int angle = m_startAngle;
  while (angle < m_startAngle + m_spanAngle) {
    QPointF pos = pointForAngle (angle);
    polygon << pos;

    angle += TICS_STEP;
  }

  // Add last point if we did not end on it
  if (angle > m_startAngle + m_spanAngle - 1) {
    QPointF pos = pointForAngle (m_startAngle + m_spanAngle);
    polygon << pos;
  }

  // Convert polygon to path
  QPainterPath path;
  path.addPolygon (polygon);

  // Save
  setBrush (QColor (Qt::blue));
  setPen (QColor (Qt::green));
  setPath (path);
}
