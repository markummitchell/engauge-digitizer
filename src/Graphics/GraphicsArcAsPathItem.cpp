/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GraphicsArcAsPathItem.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>
#include <QRectF>

//const double TWO_PI = 2.0 * 3.1415926535;
const int TICS_PER_CYCLE = 360 * 16;
//const double RADIANS_TO_TICS = TICS_PER_CYCLE / TWO_PI;

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
  m_spanAngle (TICS_PER_CYCLE)
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
  m_spanAngle (TICS_PER_CYCLE)
{
  updateGeometry ();
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

void GraphicsArcAsPathItem::updateGeometry ()
{
  // TO DO
}
