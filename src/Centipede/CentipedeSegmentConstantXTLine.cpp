/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeSegmentConstantXTLine.h"
#include "mmsubs.h"
#include <qmath.h>
#include <QGraphicsLineItem>

CentipedeSegmentConstantXTLine::CentipedeSegmentConstantXTLine(const Transformation &transformation,
                                                               const QPointF &posCenterScreen,
                                                               double initialRadius) :
  CentipedeSegmentAbstract (transformation,
                            posCenterScreen,
                            initialRadius)
{
  QPointF posLow = posScreenConstantXTLowYR (initialRadius);
  QPointF posHigh = posScreenConstantXTHighYR (initialRadius);

  m_graphicsItem = new QGraphicsLineItem (QLineF (posLow,
                                                  posHigh));
}

CentipedeSegmentConstantXTLine::~CentipedeSegmentConstantXTLine ()
{
  delete m_graphicsItem;
}

double CentipedeSegmentConstantXTLine::distanceToClosestEndpoint (const QPointF &posScreen) const
{
  QPointF posLow = posScreenConstantXTLowYR (initialRadius ());
  QPointF posHigh = posScreenConstantXTHighYR (initialRadius ());

  double distanceLow = magnitude (posScreen - posLow);
  double distanceHigh = magnitude (posScreen - posHigh);

  return qMin (distanceLow, distanceHigh);
}

QGraphicsItem *CentipedeSegmentConstantXTLine::graphicsItem ()
{
  return dynamic_cast<QGraphicsItem*> (m_graphicsItem);
}

void CentipedeSegmentConstantXTLine::updateRadius (double radius)
{
  QPointF posLow = posScreenConstantXTLowYR (radius);
  QPointF posHigh = posScreenConstantXTHighYR (radius);

  m_graphicsItem->setLine (QLineF (posLow,
                                   posHigh));
}
