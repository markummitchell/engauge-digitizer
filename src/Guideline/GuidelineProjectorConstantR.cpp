/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include <algorithm>
#include "EllipseParameters.h"
#include "GuidelineProjectorConstantR.h"
#include "Logger.h"
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
                                                                const QRectF & /* sceneRect */,
                                                                double rGraph)
{
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

  double rGraph = posGraph.y();

  if (transformation.modelCoords().coordScaleYRadius() == COORD_SCALE_LOG) {
    if (rGraph <= 0) {

      // Range enforcement on the range values with log scale should have prevented this branch
      LOG4CPP_ERROR_S ((*mainCat)) << "GuidelineProjectorConstantR::fromPosScreen out of bounds range " << rGraph;

    } else {

      // Adjust radius from log to linear so, after conversion to cartesian, we have linear x and y
      rGraph = qLn (rGraph);

    }
  }

  return fromCoordinateR (transformation,
                          sceneRect,
                          rGraph);
}
