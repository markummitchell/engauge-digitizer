/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeSegmentConstantXTEllipse.h"
#include "EnumsToQt.h"
#include "mmsubs.h"
#include <qmath.h>
#include <QGraphicsEllipseItem>
#include <QPen>

CentipedeSegmentConstantXTEllipse::CentipedeSegmentConstantXTEllipse(const DocumentModelGuideline &modelGuideline,
                                                                     const Transformation &transformation,
                                                                     const QPointF &posCenterScreen) :
  CentipedeSegmentAbstract (modelGuideline,
                            transformation,
                            posCenterScreen)
{
  QPointF posLow = posScreenConstantXTLowYR (modelGuideline.creationCircleRadius ());
  QPointF posHigh = posScreenConstantXTHighYR (modelGuideline.creationCircleRadius ());

  m_graphicsItem = new QGraphicsEllipseItem ();

  QColor color (ColorPaletteToQColor (modelGuideline.lineColor()));

  m_graphicsItem->setPen (QPen (color,
                                modelGuideline.lineWidth()));
}

CentipedeSegmentConstantXTEllipse::~CentipedeSegmentConstantXTEllipse ()
{
  delete m_graphicsItem;
}

double CentipedeSegmentConstantXTEllipse::distanceToClosestEndpoint (const QPointF &posScreen) const
{
  QPointF posLow = posScreenConstantXTLowYR (modelGuideline().creationCircleRadius ());
  QPointF posHigh = posScreenConstantXTHighYR (modelGuideline().creationCircleRadius ());

  double distanceLow = magnitude (posScreen - posLow);
  double distanceHigh = magnitude (posScreen - posHigh);

  return qMin (distanceLow, distanceHigh);
}

QGraphicsItem *CentipedeSegmentConstantXTEllipse::graphicsItem ()
{
  return dynamic_cast<QGraphicsItem*> (m_graphicsItem);
}

void CentipedeSegmentConstantXTEllipse::updateRadius (double radius)
{
  QPointF posLow = posScreenConstantXTLowYR (radius);
  QPointF posHigh = posScreenConstantXTHighYR (radius);
}


