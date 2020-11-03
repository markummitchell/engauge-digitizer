/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeSegmentConstantYREllipse.h"
#include "EnumsToQt.h"
#include "GraphicsArcItem.h"
#include "mmsubs.h"
#include <qmath.h>
#include <QPen>

const double TWO_PI = 2.0 * 3.1415926535;
const int TICS_PER_CYCLE = 360 * 16;
const double RADIANS_TO_TICS = TICS_PER_CYCLE / TWO_PI;

CentipedeSegmentConstantYREllipse::CentipedeSegmentConstantYREllipse(const DocumentModelGuideline &modelGuideline,
                                                                     const Transformation &transformation,
                                                                     const QPointF &posClickScreen) :
  CentipedeSegmentAbstract (modelGuideline,
                            transformation,
                            posClickScreen)
{
  m_posLow = posScreenConstantYRForLowXT (modelGuideline.creationCircleRadius ());
  m_posHigh = posScreenConstantYRForHighXT (modelGuideline.creationCircleRadius ());
  m_angleLow = angleScreenConstantYRLowAngle (modelGuideline.creationCircleRadius ());
  m_angleCenter = angleScreenConstantYRCenterAngle (modelGuideline.creationCircleRadius ());
  m_angleHigh = angleScreenConstantYRHighAngle (modelGuideline.creationCircleRadius ());

  QPointF posClickGraph;
  transformation.transformScreenToLinearCartesianGraph (posClickScreen,
                                                        posClickGraph);
  double rGraph = qSqrt (posClickGraph.x() * posClickGraph.x() + posClickGraph.y() * posClickGraph.y());

  // Points at 45, 135, 225 and 315 degrees at range rGraph
  QPointF posScreenCenter, posScreenTL, posScreenTR, posScreenBR; // No need for BL point
  transformation.transformLinearCartesianGraphToScreen (QPointF (0, 0),
                                                        posScreenCenter);
  transformation.transformLinearCartesianGraphToScreen (QPointF (-rGraph, rGraph),
                                                        posScreenTL);
  transformation.transformLinearCartesianGraphToScreen (QPointF (rGraph, rGraph),
                                                        posScreenTR);
  transformation.transformLinearCartesianGraphToScreen (QPointF (rGraph, -rGraph),
                                                        posScreenBR);

  double angleRadians = 0, aAligned = 0, bAligned = 0;
  ellipseFromParallelogram (posScreenTL.x() - posScreenCenter.x(),
                            posScreenTL.y() - posScreenCenter.y(),
                            posScreenTR.x() - posScreenCenter.x(),
                            posScreenTR.y() - posScreenCenter.y(),
                            posScreenBR.x() - posScreenCenter.x(),
                            posScreenBR.y() - posScreenCenter.y(),
                            angleRadians,
                            aAligned,
                            bAligned);

  // Origin
  QPointF posOriginScreen;
  transformation.transformLinearCartesianGraphToScreen (QPointF (0, 0),
                                                        posOriginScreen);

  // Bounding rectangle before rotation
  QRectF rectBounding (posOriginScreen + QPointF (-1.0 * aAligned,
                                                  bAligned),
                       posOriginScreen + QPointF (aAligned,
                                                  -1.0 * bAligned));

  m_graphicsItem = new GraphicsArcItem (rectBounding);

  QColor color (ColorPaletteToQColor (modelGuideline.lineColor()));

  m_graphicsItem->setPen (QPen (color,
                                modelGuideline.lineWidthActive ()));
  updateRadius (modelGuideline.creationCircleRadius());
}

CentipedeSegmentConstantYREllipse::~CentipedeSegmentConstantYREllipse ()
{
  delete m_graphicsItem;
}

double CentipedeSegmentConstantYREllipse::distanceToClosestEndpoint (const QPointF &posScreen) const
{
  double distanceLow = magnitude (posScreen - m_posLow);
  double distanceHigh = magnitude (posScreen - m_posHigh);

  return qMin (distanceLow, distanceHigh);
}

QGraphicsItem *CentipedeSegmentConstantYREllipse::graphicsItem ()
{
  return dynamic_cast<QGraphicsItem*> (m_graphicsItem);
}

void CentipedeSegmentConstantYREllipse::updateRadius (double radius)
{
  // Scale up/down the angles, with them converging to center angle as radius goes to zero
  double scaling = radius / modelGuideline().creationCircleRadius ();
  int angleLow = (int) ((m_angleCenter + scaling * (m_angleLow - m_angleCenter)) * RADIANS_TO_TICS);
  int angleHigh = (int) ((m_angleCenter + scaling * (m_angleHigh - m_angleCenter)) * RADIANS_TO_TICS);
  while (angleLow < 0) {
    angleLow += TICS_PER_CYCLE;
  }
  while (angleHigh < angleLow) {
    angleHigh += TICS_PER_CYCLE;
  }
  m_graphicsItem->setStartAngle (angleLow);
  m_graphicsItem->setSpanAngle (angleHigh - angleLow);
}

