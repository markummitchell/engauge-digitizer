/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeSegmentConstantXTRadial.h"
#include "EnumsToQt.h"
#include "GraphicsLineItemRelay.h"
#include "mmsubs.h"
#include <qmath.h>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QPen>

const int NUM_LINE_POINTS = 400; // Use many points so complicated (linear, log, high dynamic range) interpolation is not needed

CentipedeSegmentConstantXTRadial::CentipedeSegmentConstantXTRadial(const DocumentModelGuideline &modelGuideline,
                                                                   const Transformation &transformation,
                                                                   const QPointF &posClickScreen) :
  CentipedeSegmentAbstract (modelGuideline,
                            transformation,
                            posClickScreen)
{
  posScreenConstantYRForXTHighLowAngles (transformation,
                                         posClickScreen,
                                         modelGuideline.creationCircleRadius(),
                                         m_posLow,
                                         m_posHigh);

  m_graphicsItem = new QGraphicsLineItem (QLineF (m_posLow,
                                                  m_posHigh));
  m_graphicsItemRelay = new GraphicsLineItemRelay (this,
                                                   m_graphicsItem);

  QColor color (ColorPaletteToQColor (modelGuideline.lineColor()));

  m_graphicsItem->setPen (QPen (color,
                                modelGuideline.lineWidthActive ()));
}

CentipedeSegmentConstantXTRadial::~CentipedeSegmentConstantXTRadial ()
{
  delete m_graphicsItem;
  delete m_graphicsItemRelay;
}

double CentipedeSegmentConstantXTRadial::distanceToClosestEndpoint (const QPointF &posScreen) const
{
  double distanceLow = magnitude (posScreen - m_posLow);
  double distanceHigh = magnitude (posScreen - m_posHigh);

  return qMin (distanceLow, distanceHigh);
}

QGraphicsItem *CentipedeSegmentConstantXTRadial::graphicsItem ()
{
  return dynamic_cast<QGraphicsItem*> (m_graphicsItem);
}

void CentipedeSegmentConstantXTRadial::posScreenConstantYRForXTHighLowAngles (const Transformation &transformation,
                                                                              const QPointF &posClickScreen,
                                                                              double radius,
                                                                              QPointF &posLow,
                                                                              QPointF &posHigh) const
{
  // This replaces CentipedeSegmentAbstract::posScreenConstantXTCommon since the polar coordinate radial vector
  // can be on the other side of the origin if the ellipse center is within radius of the origin. This routine
  // uses an unusual strategy of iterating on a line rather than a circle (since circle has tough issues with quadrants
  // and 360 rollover)

  // Origin and screen vector to center
  QPointF posOriginScreen;
  transformation.transformRawGraphToScreen (QPointF (0, 0),
                                            posOriginScreen);
  QPointF vecCenter = posClickScreen - posOriginScreen;

  // Number of solutions found
  int numberFound = 0;

  // Iterate points along the line from -2*vecCenterMagnitude to +2*vecCenterMagnitude
  const double DOUBLE_PLUS_EXTRA = 2.1;
  double maxRadius = DOUBLE_PLUS_EXTRA * (magnitude (vecCenter) + radius);
  QPointF posStart = posOriginScreen - 2 * maxRadius * normalize (vecCenter);
  QPointF posStop = posOriginScreen + 2 * maxRadius * normalize (vecCenter);
  for (int i = 0; i < NUM_LINE_POINTS; i++) {
    double sPrevious = (double) i / (double) NUM_LINE_POINTS;
    double sNext = (double) (i + 1) / (double) NUM_LINE_POINTS;

    QPointF posPrevious = (1.0 - sPrevious) * posStart + sPrevious * posStop;
    QPointF posNext = (1.0 - sNext) * posStart + sNext * posStop;

    double distancePrevious = magnitude (posPrevious - posClickScreen);
    double distanceNext = magnitude (posNext - posClickScreen);

    if ((distancePrevious < radius && radius <= distanceNext) ||
        (distancePrevious > radius && radius >= distanceNext)) {

      if (numberFound == 0) {
        posLow = (posPrevious + posNext) / 2.0; // Average for accuracy
      } else if (numberFound == 1) {
        posHigh = (posPrevious + posNext) / 2.0; // Average for accuracy
        break; // Done
      }

      ++numberFound;
    }
  }
}

void CentipedeSegmentConstantXTRadial::updateRadius (double radius)
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
