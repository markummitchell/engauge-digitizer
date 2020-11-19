/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeEndpointsCartesian.h"
#include "CentipedeEndpointsPolar.h"
#include "CentipedeSegmentConstantREllipse.h"
#include "EnumsToQt.h"
#include "GraphicsArcItem.h"
#include "GraphicsArcItemRelay.h"
#include "mmsubs.h"
#include <qdebug.h>
#include <qmath.h>
#include <QPen>

const int TICS_PER_CYCLE = 360 * 16;
const double RADIANS_TO_TICS = TICS_PER_CYCLE / (2.0 * M_PI);

CentipedeSegmentConstantREllipse::CentipedeSegmentConstantREllipse(const DocumentModelGuideline &modelGuideline,
                                                                   const Transformation &transformation,
                                                                   const QPointF &posClickScreen) :
  CentipedeSegmentAbstract (modelGuideline,
                            transformation,
                            posClickScreen),
  m_angleScreenToEllipseAxes (0)
{
  CentipedeEndpointsCartesian endpointsCartesian (modelGuideline,
                                                  transformation,
                                                  posClickScreen);
  CentipedeEndpointsPolar endpointsPolar (modelGuideline,
                                          transformation,
                                          posClickScreen);
  
  m_posLow = endpointsCartesian.posScreenConstantYRForLowXT (modelGuideline.creationCircleRadius());
  m_posHigh = endpointsCartesian.posScreenConstantYRForHighXT (modelGuideline.creationCircleRadius());
  m_angleCenter = endpointsPolar.angleScreenConstantYRCenterAngle (modelGuideline.creationCircleRadius ());
  endpointsPolar.angleScreenConstantYRHighLowAngles (modelGuideline.creationCircleRadius (),
                                                     m_angleCenter,
                                                     m_angleLow,
                                                     m_angleHigh);

  QPointF posClickGraph;
  transformation.transformScreenToRawGraph (posClickScreen,
                                            posClickGraph);
  double rGraph = posClickGraph.y();

  // Points at origin, then 0  degrees at range rGraph
  QPointF posScreenCenter, posScreen0, posScreen90, posScreen180;
  transformation.transformRawGraphToScreen (QPointF (0, 0),
                                            posScreenCenter);
  transformation.transformRawGraphToScreen (QPointF (0, rGraph),
                                            posScreen0);
  transformation.transformRawGraphToScreen (QPointF (90.0, rGraph),
                                            posScreen90);
  transformation.transformRawGraphToScreen (QPointF (180.0, rGraph),
                                            posScreen180);

  QPointF centerTo90 = posScreen90 - posScreenCenter;

  // Corners of parallelogram circumscribing the ellipse
  QPointF posScreenTL = posScreen180 + centerTo90;
  QPointF posScreenTR = posScreen0 + centerTo90;
  QPointF posScreenBR = posScreen0 - centerTo90;

  double angleEllipseFromMajorAxis= 0, aAligned = 0, bAligned = 0;
  ellipseFromParallelogram (posScreenTL.x() - posScreenCenter.x(),
                            posScreenTL.y() - posScreenCenter.y(),
                            posScreenTR.x() - posScreenCenter.x(),
                            posScreenTR.y() - posScreenCenter.y(),
                            posScreenBR.x() - posScreenCenter.x(),
                            posScreenBR.y() - posScreenCenter.y(),
                            angleEllipseFromMajorAxis,
                            aAligned,
                            bAligned);

  // Angle between +x axis in screen and semimajor axis is computed in all four quadrants
  // by projecting onto +x and +y screen axesangleEllipseFromScreenAxis
  m_angleRotation = angleFromBasisVectors (1,
                                           0,
                                           0,
                                           -1,
                                           posScreen0.x() - posScreenCenter.x(),
                                           posScreen0.y() - posScreenCenter.y());

  // Origin
  QPointF posOriginScreen;
  transformation.transformLinearCartesianGraphToScreen (QPointF (0, 0),
                                                        posOriginScreen);

  // Bounding rectangle before rotation
  QRectF rectBounding (posOriginScreen + QPointF (-1.0 * aAligned,
                                                  bAligned),
                       posOriginScreen + QPointF (aAligned,
                                                  -1.0 * bAligned));
  rectBounding = rectBounding.normalized(); // This seems to prevent some drawing artifacts

  // Create graphics item and its relay
  m_graphicsItem = new GraphicsArcItem (rectBounding);
  m_graphicsItem->setSpanAngle (0); // Prevent flicker by display before span angle is changed from all-inclusive default
  m_graphicsItemRelay = new GraphicsArcItemRelay (this,
                                                  m_graphicsItem);

  QColor color (ColorPaletteToQColor (modelGuideline.lineColor()));

  m_graphicsItem->setPen (QPen (color,
                                modelGuideline.lineWidthActive ()));
  updateRadius (modelGuideline.creationCircleRadius());
}

CentipedeSegmentConstantREllipse::~CentipedeSegmentConstantREllipse ()
{
  delete m_graphicsItem;
  delete m_graphicsItemRelay;
}

double CentipedeSegmentConstantREllipse::distanceToClosestEndpoint (const QPointF &posScreen) const
{
  double distanceLow = magnitude (posScreen - m_posLow);
  double distanceHigh = magnitude (posScreen - m_posHigh);

  return qMin (distanceLow, distanceHigh);
}

QGraphicsItem *CentipedeSegmentConstantREllipse::graphicsItem ()
{
  return dynamic_cast<QGraphicsItem*> (m_graphicsItem);
}

void CentipedeSegmentConstantREllipse::updateRadius (double radius)
{
  // Scale up/down the angles, with them converging to center angle as radius goes to zero
  double scaling = radius / modelGuideline().creationCircleRadius ();

  double angleLowRad = m_angleCenter + scaling * (m_angleLow - m_angleCenter) - m_angleScreenToEllipseAxes;
  double angleHighRad = m_angleCenter + scaling * (m_angleHigh - m_angleCenter) - m_angleScreenToEllipseAxes;
  int angleLowTics = (int) (angleLowRad * RADIANS_TO_TICS);
  int angleHighTics = (int) (angleHighRad * RADIANS_TO_TICS);

  // Update geometry but only after the event handler currently on the stack has disappeared.
  // This means sending a signal instead of calling QGraphicsEllipseItem::setStartAngle and
  // QGraphicsEllipseItem::setSpanAngle directly
  int angleDeltaTics = angleHighTics - angleLowTics;

  emit signalUpdateAngles (angleLowTics,
                           angleDeltaTics,
                           m_angleRotation);
}
