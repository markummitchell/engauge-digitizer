/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeSegmentConstantYREllipse.h"
#include "mmsubs.h"
#include <qmath.h>
#include <QGraphicsEllipseItem>

CentipedeSegmentConstantYREllipse::CentipedeSegmentConstantYREllipse(const Transformation &transformation,
                                                                     const QPointF &posCenterScreen,
                                                                     double initialRadius) :
  CentipedeSegmentAbstract (transformation,
                            posCenterScreen,
                            initialRadius)
{
  QPointF posLow = posScreenConstantYRLowXT (initialRadius);
  QPointF posHigh = posScreenConstantYRHighXT (initialRadius);

  m_graphicsItem = new QGraphicsEllipseItem ();
}

CentipedeSegmentConstantYREllipse::~CentipedeSegmentConstantYREllipse ()
{
  delete m_graphicsItem;
}

double CentipedeSegmentConstantYREllipse::distanceToClosestEndpoint (const QPointF &posScreen) const
{
  QPointF posLow = posScreenConstantYRLowXT (initialRadius ());
  QPointF posHigh = posScreenConstantYRHighXT (initialRadius ());

  double distanceLow = magnitude (posScreen - posLow);
  double distanceHigh = magnitude (posScreen - posHigh);

  return qMin (distanceLow, distanceHigh);
}

QGraphicsItem *CentipedeSegmentConstantYREllipse::graphicsItem ()
{
  return dynamic_cast<QGraphicsItem*> (m_graphicsItem);
}

void CentipedeSegmentConstantYREllipse::updateRadius (double radius)
{
  QPointF posLow = posScreenConstantYRLowXT (radius);
  QPointF posHigh = posScreenConstantYRHighXT (radius);
}

