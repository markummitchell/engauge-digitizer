/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeSegmentConstantYREllipse.h"
#include "EnumsToQt.h"
#include "GraphicsArcItem.h"
#include "mmsubs.h"
#include <qdebug.h>
#include <qmath.h>
#include <QPen>

CentipedeSegmentConstantYREllipse::CentipedeSegmentConstantYREllipse(const DocumentModelGuideline &modelGuideline,
                                                                     const Transformation &transformation,
                                                                     const QPointF &posClickScreen) :
  CentipedeSegmentAbstract (modelGuideline,
                            transformation,
                            posClickScreen)
{
  m_posLow = posScreenConstantYRForLowXT (modelGuideline.creationCircleRadius ());
  m_posHigh = posScreenConstantYRForHighXT (modelGuideline.creationCircleRadius ());

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
  // When this method had code to set QGraphicsEllipseItem::spanAngle and QGraphicsEllipseItem::startAngle, the correct curve segment
  // often did not appear due to QTBUG-80937 as explained in the class documentation for CentipedeSegmentConstantYREllipse. Therefore
  // for consistency the whole ellipse is drawn which always works correctly.
}

