/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeSegmentConstantYRLine.h"
#include "EnumsToQt.h"
#include "mmsubs.h"
#include <qmath.h>
#include <QGraphicsLineItem>
#include <QPen>

CentipedeSegmentConstantYRLine::CentipedeSegmentConstantYRLine(const DocumentModelGuideline &modelGuideline,
                                                               const Transformation &transformation,
                                                               const QPointF &posCenterScreen) :
  CentipedeSegmentAbstract (modelGuideline,
                            transformation,
                            posCenterScreen)
{
  QPointF posLow = posScreenConstantYRLowXT (modelGuideline.creationCircleRadius ());
  QPointF posHigh = posScreenConstantYRHighXT (modelGuideline.creationCircleRadius ());

  m_graphicsItem = new QGraphicsLineItem (QLineF (posLow,
                                                  posHigh));

  QColor color (ColorPaletteToQColor (modelGuideline.lineColor()));

  m_graphicsItem->setPen (QPen (color,
                                modelGuideline.lineWidth()));
}

CentipedeSegmentConstantYRLine::~CentipedeSegmentConstantYRLine ()
{
  delete m_graphicsItem;
}

double CentipedeSegmentConstantYRLine::distanceToClosestEndpoint (const QPointF &posScreen) const
{
  QPointF posLow = posScreenConstantYRLowXT (modelGuideline().creationCircleRadius ());
  QPointF posHigh = posScreenConstantYRHighXT (modelGuideline().creationCircleRadius ());

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
