/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GraphicsArcItem.h"
#include "GraphicsArcItemRelay.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QObject>
#include <QPainter>
#include "QtToString.h"

const double RADIANS_TO_DEGREES = 180.0 / 3.1415926535;

GraphicsArcItemRelay::GraphicsArcItemRelay (QObject *caller,
                                            GraphicsArcItem *graphicsItem) :
  m_graphicsItem (graphicsItem)
{
  // Queue for later by including Qt::QueuedConnection
  connect (caller, SIGNAL (signalUpdateAngles (int, int, double)),
           this, SLOT (slotUpdateAngles (int, int, double)),
           Qt::QueuedConnection);
}

GraphicsArcItemRelay::~GraphicsArcItemRelay ()
{
  // Calling code is responsible for deallocating graphics item
}
                                 
void GraphicsArcItemRelay::slotUpdateAngles (int startAngle,
                                             int spanAngle,
                                             double rotationAngle)
{
  m_graphicsItem->setStartAngle (startAngle);
  m_graphicsItem->setSpanAngle (spanAngle);
  m_graphicsItem->setRotation (4*rotationAngle * RADIANS_TO_DEGREES);
}
