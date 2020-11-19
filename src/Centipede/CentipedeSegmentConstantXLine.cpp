/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeEndpointsCartesian.h"
#include "CentipedeSegmentConstantXLine.h"
#include "EnumsToQt.h"
#include "GraphicsLineItemRelay.h"
#include "mmsubs.h"
#include <qmath.h>
#include <QGraphicsLineItem>
#include <QPen>

CentipedeSegmentConstantXLine::CentipedeSegmentConstantXLine(const DocumentModelGuideline &modelGuideline,
                                                             const Transformation &transformation,
                                                             const QPointF &posClickScreen) :
  CentipedeSegmentAbstract (modelGuideline,
                            transformation,
                            posClickScreen)
{
  CentipedeEndpointsCartesian endpoints (modelGuideline,
                                         transformation,
                                         posClickScreen);
  
  m_posLow = endpoints.posScreenConstantXForLowY (modelGuideline.creationCircleRadius ());

  m_posHigh = endpoints.posScreenConstantXForHighY (modelGuideline.creationCircleRadius ());

  // Create graphics item and its relay
  m_graphicsItem = new QGraphicsLineItem (QLineF (m_posLow,
                                                  m_posHigh));
  m_graphicsItemRelay = new GraphicsLineItemRelay (this,
                                                   m_graphicsItem);

  QColor color (ColorPaletteToQColor (modelGuideline.lineColor()));

  m_graphicsItem->setPen (QPen (color,
                                modelGuideline.lineWidthActive ()));
}

CentipedeSegmentConstantXLine::~CentipedeSegmentConstantXLine ()
{
  delete m_graphicsItem;
  delete m_graphicsItemRelay;
}

double CentipedeSegmentConstantXLine::distanceToClosestEndpoint (const QPointF &posScreen) const
{
  double distanceLow = magnitude (posScreen - m_posLow);
  double distanceHigh = magnitude (posScreen - m_posHigh);

  return qMin (distanceLow, distanceHigh);
}

QGraphicsItem *CentipedeSegmentConstantXLine::graphicsItem ()
{
  return dynamic_cast<QGraphicsItem*> (m_graphicsItem);
}

void CentipedeSegmentConstantXLine::updateRadius (double radius)
{
  // Scale up/down the line segment length, keeping it centered on the same center point
  QPointF posCenter = (m_posHigh + m_posLow) / 2.0;
  QPointF delta = m_posHigh - m_posLow;
  double radiusInitial = magnitude (delta) / 2.0; // Convert from diameter to radius
  double scaling = radius / radiusInitial;
  QPointF posLow = posCenter - scaling / 2.0 * delta;
  QPointF posHigh = posCenter + scaling / 2.0 * delta;

  // Update geometry but only after the event handler currently on the stack has disappeared.
  // This means sending a signal instead of calling QGraphicsLineItem::setLine directly
  emit signalUpdateEndpoints (posLow,
                              posHigh);
}
