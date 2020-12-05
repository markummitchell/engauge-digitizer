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
  connect (caller, SIGNAL (signalUpdateAngles (QPointF, QPointF, QPointF, double, double)),
           this, SLOT (slotUpdateAngles (QPointF, QPointF, QPointF, double, double)),
           Qt::QueuedConnection);
}

GraphicsArcItemRelay::~GraphicsArcItemRelay ()
{
  // Calling code is responsible for deallocating graphics item
}
                                 
void GraphicsArcItemRelay::slotUpdateAngles (QPointF posTangentialLow,
                                             QPointF posTangentialCenter,
                                             QPointF posTangentialHigh,
                                             double widthToHeight,
                                             double scaling)
{
  // Rotate into ellipse reference frame (where x and y axis are aligned with
  // semimajor/semiminor axes. The QTransform supplied by m_graphicsItem is
  // just the identity transform and therefore not useful
  double angleRotation = -1.0 * m_graphicsItem->rotation();
  QTransform rotateTransform;
  rotateTransform.rotate (angleRotation);
  QPointF posLowInEllipseFrame = rotateTransform.map (posTangentialLow);
  QPointF posCenterInEllipseFrame = rotateTransform.map (posTangentialCenter);
  QPointF posHighInEllipseFrame = rotateTransform.map (posTangentialHigh);

  // Compensate for y scale being different than x scale using widthToHeight
  double angleLow = -1.0 * qAtan2 (posLowInEllipseFrame.y() * widthToHeight,
                                   posLowInEllipseFrame.x());
  double angleCenter = -1.0 * qAtan2 (posCenterInEllipseFrame.y() * widthToHeight,
                                      posCenterInEllipseFrame.x());
  double angleHigh = -1.0 * qAtan2 (posHighInEllipseFrame.y() * widthToHeight,
                                    posHighInEllipseFrame.x());

  int lowTics = (int) (RADIANS_TO_TICS * (angleCenter + scaling * (angleLow - angleCenter)));
  int highTics = (int) (RADIANS_TO_TICS * (angleCenter + scaling * (angleHigh - angleCenter)));

  m_graphicsItem->setStartAngle (lowTics);
  m_graphicsItem->setSpanAngle (highTics - lowTics);
}
