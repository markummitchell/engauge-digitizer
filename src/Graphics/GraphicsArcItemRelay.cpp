/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GraphicsArcItem.h"
#include "GraphicsArcItemRelay.h"
#include <QDebug>
#include <QGraphicsScene>
#include <qmath.h>
#include <QObject>
#include <QPainter>
#include "QtToString.h"

const int TICS_PER_CYCLE = 360 * 16;
const double RADIANS_TO_TICS = TICS_PER_CYCLE / (2.0 * M_PI);

GraphicsArcItemRelay::GraphicsArcItemRelay (QObject *caller,
                                            GraphicsArcItem *graphicsItem) :
  m_graphicsItem (graphicsItem)
{
  // Queue for later by including Qt::QueuedConnection
  connect (caller, SIGNAL (signalUpdateAngles (QPointF, QPointF, QPointF, double)),
           this, SLOT (slotUpdateAngles (QPointF, QPointF, QPointF, double)),
           Qt::QueuedConnection);
}

GraphicsArcItemRelay::~GraphicsArcItemRelay ()
{
  // Calling code is responsible for deallocating graphics item
}
                                 
void GraphicsArcItemRelay::slotUpdateAngles (QPointF posTangentialLow,
                                             QPointF posTangentialCenter,
                                             QPointF posTangentialHigh,
                                             double scaling)
{
  // Convert to ellipse reference frame. This transform step replaces
  // a huge amount of complicated math, which is especially complicated
  // with nonzero shear since angles are no longer evenly spaced and
  // basis vectors are nonorthogonal

  QPointF posProjectedLow = m_graphicsItem->transform().map (posTangentialLow);
  QPointF posProjectedCenter = m_graphicsItem->transform().map (posTangentialCenter);
  QPointF posProjectedHigh = m_graphicsItem->transform().map (posTangentialHigh);

  double angleLow = qAtan2 (posProjectedLow.y(),
                            posProjectedLow.x());
  double angleCenter = qAtan2 (posProjectedCenter.y(),
                               posProjectedCenter.x());
  double angleHigh = qAtan2 (posProjectedHigh.y(),
                             posProjectedHigh.x());  

  int lowTics = (int) (RADIANS_TO_TICS * (angleCenter + scaling * (angleLow - angleCenter)));
  int highTics = (int) (RADIANS_TO_TICS * (angleCenter + scaling * (angleHigh - angleCenter)));
  
  m_graphicsItem->setStartAngle (lowTics);
  m_graphicsItem->setSpanAngle (highTics - lowTics);
}
