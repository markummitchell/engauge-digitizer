/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeSegmentConstantYRLine.h"
#include "mmsubs.h"
#include <qmath.h>
#include <QGraphicsLineItem>

CentipedeSegmentConstantYRLine::CentipedeSegmentConstantYRLine(const Transformation &transformation,
                                                               const QPointF &posCenterScreen,
                                                               double initialRadius) :
  CentipedeSegmentAbstract (transformation,
                            posCenterScreen,
                            initialRadius)
{
  QPointF posLow = posScreenConstantYRLowXT (initialRadius);
  QPointF posHigh = posScreenConstantYRHighXT (initialRadius);

  m_graphicsItem = new QGraphicsLineItem (QLineF (posLow,
                                                  posHigh));
}

CentipedeSegmentConstantYRLine::~CentipedeSegmentConstantYRLine ()
{
  delete m_graphicsItem;
}

double CentipedeSegmentConstantYRLine::distanceToClosestEndpoint (const QPointF &posScreen) const
{
  QPointF posLow = posScreenConstantYRLowXT (initialRadius ());
  QPointF posHigh = posScreenConstantYRHighXT (initialRadius ());

  double distanceLow = magnitude (posScreen - posLow);
  double distanceHigh = magnitude (posScreen - posHigh);

  return qMin (distanceLow, distanceHigh);
}

QGraphicsItem *CentipedeSegmentConstantYRLine::graphicsItem ()
{
  return dynamic_cast<QGraphicsItem*> (m_graphicsItem);
}

void CentipedeSegmentConstantYRLine::updateRadius (double radius)
{
  QPointF posLow = posScreenConstantYRLowXT (radius);
  QPointF posHigh = posScreenConstantYRHighXT (radius);

  m_graphicsItem->setLine (QLineF (posLow,
                                   posHigh));
}
