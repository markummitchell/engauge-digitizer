/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeSegmentConstantYREllipse.h"
#include "EnumsToQt.h"
#include "mmsubs.h"
#include <qmath.h>
#include <QGraphicsEllipseItem>
#include <QPen>

CentipedeSegmentConstantYREllipse::CentipedeSegmentConstantYREllipse(const DocumentModelGuideline &modelGuideline,
                                                                     const Transformation &transformation,
                                                                     const QPointF &posCenterScreen) :
  CentipedeSegmentAbstract (modelGuideline,
                            transformation,
                            posCenterScreen)
{
  QPointF posLow = posScreenConstantYRLowXT (modelGuideline.creationCircleRadius ());
  QPointF posHigh = posScreenConstantYRHighXT (modelGuideline.creationCircleRadius ());

  // Mirror posHigh through origin as posCenterScreen - (posHigh - posCenterScreen)
  QPointF posHighMirror (2.0 * posCenterScreen.x() - posHigh.x(),
                         2.0 * posCenterScreen.y() - posHigh.y());

  double angle, a, b;
  ellipseFromParallelogram (posLow.x(),
                            posLow.y(),
                            posHigh.x(),
                            posHigh.y(),
                            posHighMirror.x(),
                            posHighMirror.y(),
                            angle,
                            a,
                            b);

  // Bounding rectangle before rotation
  QRectF rectBounding (posCenterScreen + QPointF (-1.0 * a / 2.0,
                                                  b / 2.0),
                       posCenterScreen + QPointF (a / 2.0,
                                                  -1.0 * b / 2.0));

  m_graphicsItem = new QGraphicsEllipseItem (rectBounding);

  QColor color (ColorPaletteToQColor (modelGuideline.lineColor()));

  m_graphicsItem->setPen (QPen (color,
                                modelGuideline.lineWidthActive ()));
}

CentipedeSegmentConstantYREllipse::~CentipedeSegmentConstantYREllipse ()
{
  delete m_graphicsItem;
}

double CentipedeSegmentConstantYREllipse::distanceToClosestEndpoint (const QPointF &posScreen) const
{
  QPointF posLow = posScreenConstantYRLowXT (modelGuideline().creationCircleRadius ());
  QPointF posHigh = posScreenConstantYRHighXT (modelGuideline().creationCircleRadius ());

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

