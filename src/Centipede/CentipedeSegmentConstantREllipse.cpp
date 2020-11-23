/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeDebugPolar.h"
#include "CentipedeEndpointsPolar.h"
#include "CentipedeSegmentConstantREllipse.h"
#include "DocumentModelCoords.h"
#include "EnumsToQt.h"
#include "GraphicsArcItem.h"
#include "GraphicsArcItemRelay.h"
#include "GraphicsScene.h"
#include "mmsubs.h"
#include <qdebug.h>
#include <qmath.h>
#include <QPen>
#include "QtToString.h"

const int TICS_PER_CYCLE = 360 * 16;
const double RADIANS_TO_TICS = TICS_PER_CYCLE / (2.0 * M_PI);

CentipedeSegmentConstantREllipse::CentipedeSegmentConstantREllipse(GraphicsScene &scene,
                                                                   const DocumentModelCoords &modelCoords,
                                                                   const DocumentModelGuideline &modelGuideline,
                                                                   const Transformation &transformation,
                                                                   const QPointF &posClickScreen) :
  CentipedeSegmentAbstract (modelGuideline,
                            transformation,
                            posClickScreen),
  m_angleScreenToEllipseAxes (0)
{
  QPointF posClickGraph;
  transformation.transformScreenToRawGraph (posClickScreen,
                                            posClickGraph);
  double rGraph = posClickGraph.y();

  CentipedeEndpointsPolar endpointsPolar (modelCoords,
                                          modelGuideline,
                                          transformation,
                                          posClickScreen);
  
  m_posLow = endpointsPolar.posScreenConstantRForLowT (modelGuideline.creationCircleRadius());
  m_posHigh = endpointsPolar.posScreenConstantRForHighT (modelGuideline.creationCircleRadius());
  m_angleCenter = endpointsPolar.angleScreenConstantRCenterAngle (modelGuideline.creationCircleRadius ());
  endpointsPolar.angleScreenConstantRHighLowAngles (modelGuideline.creationCircleRadius (),
                                                    m_angleCenter,
                                                    m_angleLow,
                                                    m_angleHigh);

  QRectF rectBounding;
  CentipedeDebugPolar debugPolar;
  endpointsPolar.ellipseScreenConstantRForTHighLowAngles (transformation,
                                                          posClickScreen,
                                                          m_angleRotation,
                                                          rectBounding,
                                                          debugPolar);;

  debugPolar.display (scene,
                      modelCoords,
                      transformation);

  QPointF posCenterGraph (0, 0), posCenterScreen;
  if (modelCoords.coordScaleYRadius() == COORD_SCALE_LOG) {
    posCenterGraph = QPointF (0, modelCoords.originRadius());
  }

  QPointF posScreen0;
  transformation.transformRawGraphToScreen (posCenterGraph,
                                            posCenterScreen);
  transformation.transformRawGraphToScreen (QPointF (0, rGraph),
                                            posScreen0);

  // Create graphics item and its relay. As explained in GuidelineEllipse::updateGeometry, the correct sequence
  // of graphical operations is very tricky, and less successful if setTransformOriginPoint is used (e.g. works for
  // non-shear cases but not shear cases)
  m_graphicsItem = new GraphicsArcItem (rectBounding);
  m_graphicsItem->setSpanAngle (0); // Prevent flicker by display before span angle is changed from all-inclusive default
  m_graphicsItem->setRotation (qRadiansToDegrees (m_angleRotation));
  m_graphicsItem->setPos (posCenterScreen);
  m_graphicsItemRelay = new GraphicsArcItemRelay (this,
                                                  m_graphicsItem);
  QColor color (ColorPaletteToQColor (modelGuideline.lineColor()));
  m_graphicsItem->setPen (QPen (color,
                                modelGuideline.lineWidthActive ()));
  updateRadius (modelGuideline.creationCircleRadius());

  scene.addItem (m_graphicsItem);
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

void CentipedeSegmentConstantREllipse::updateRadius (double radius)
{
  // Scale up/down the angles, with them converging to center angle as radius goes to zero
  double scaling = radius / modelGuideline().creationCircleRadius ();

  double angleLowRad = m_angleCenter + scaling * (m_angleLow - m_angleCenter) + m_angleRotation;
  double angleHighRad = m_angleCenter + scaling * (m_angleHigh - m_angleCenter) + m_angleRotation;
  int angleLowTics = (int) (angleLowRad * RADIANS_TO_TICS);
  int angleHighTics = (int) (angleHighRad * RADIANS_TO_TICS);

  // Update geometry but only after the event handler currently on the stack has disappeared.
  // This means sending a signal instead of calling QGraphicsEllipseItem::setStartAngle and
  // QGraphicsEllipseItem::setSpanAngle directly
  int angleDeltaTics = angleHighTics - angleLowTics;

  emit signalUpdateAngles (angleLowTics,
                           angleDeltaTics);

  CentipedeDebugPolar debugPolar;
  debugPolar.dumpEllipseGraphicsItem ("CentipedeSegmentConstantREllipse::updateRadius",
                                      m_graphicsItem);
}
