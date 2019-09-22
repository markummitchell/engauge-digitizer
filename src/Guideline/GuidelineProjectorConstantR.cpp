/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include <algorithm>
#include "EllipseParameters.h"
#include "GuidelineProjectorConstantR.h"
#include "mmsubs.h"
#include <QList>
#include <qmath.h>
#include <QRectF>
#include "Transformation.h"

GuidelineProjectorConstantR::GuidelineProjectorConstantR()
{
}

GuidelineProjectorConstantR::~GuidelineProjectorConstantR()
{
}

EllipseParameters GuidelineProjectorConstantR::fromCoordinateR (const Transformation &transformation,
                                                                const QRectF &sceneRect,
                                                                double rGraph)
{
  QRectF rect (0, 0, 0, 0);
  QPointF posGraphBL, posGraphTL, posGraphTR, posGraphBR;
  calculateCorners (transformation,
                    sceneRect,
                    posGraphBL,
                    posGraphTL,
                    posGraphTR,
                    posGraphBR);

  // X or y component of points at 45, 135, 225 and 315 degrees at range rGraph
  double rComponent = rGraph / qSqrt (2.0);

  QPointF posScreenCenter, posScreenTL, posScreenTR, posScreenBR; // No need for BL point
  transformation.transformRawGraphToScreen (QPointF (0, 0),
                                            posScreenCenter);
  transformation.transformRawGraphToScreen (QPointF (-rComponent, rComponent),
                                            posScreenTL);
  transformation.transformRawGraphToScreen (QPointF (rComponent, rComponent),
                                            posScreenTR);
  transformation.transformRawGraphToScreen (QPointF (rComponent, -rComponent),
                                            posScreenBR);

  QPointF posGraphCenter = (posGraphTL + posGraphBR) / 2.0;
  double angleRadians = 0, aAligned = 0, bAligned = 0;
  ellipseFromParallelogram ((posGraphTL - posGraphCenter).x(),
                            (posGraphTL - posGraphCenter).y(),
                            (posGraphTR - posGraphCenter).x(),
                            (posGraphTR - posGraphCenter).y(),
                            angleRadians,
                            aAligned,
                            bAligned);

  return EllipseParameters (posScreenCenter,
                            angleRadians,
                            aAligned,
                            bAligned);
}

EllipseParameters GuidelineProjectorConstantR::fromPosScreen (const Transformation &transformation,
                                                              const QRectF &sceneRect,
                                                              const QPointF &posScreen)
{
  QPointF posGraph;
  transformation.transformScreenToRawGraph (posScreen,  posGraph);

  double range = qSqrt (posGraph.x() * posGraph.x() +
                        posGraph.y() * posGraph.y());

  return fromCoordinateR (transformation,
                          sceneRect,
                          range);
}
