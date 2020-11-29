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
  QPointF posGraphCenter (0, 0);
  if (transformation.modelCoords().coordScaleYRadius() == COORD_SCALE_LOG) {
    posGraphCenter = QPointF (0,
                              transformation.modelCoords().originRadius());
  }

  // Points at 45, 135, 225 and 315 degrees at range rGraph
  QPointF posScreenOrigin, posScreen0, posScreen90, posScreen180;
  transformation.transformRawGraphToScreen (posGraphCenter,
                                            posScreenOrigin);
  transformation.transformRawGraphToScreen (QPointF (0, rGraph),
                                            posScreen0);
  transformation.transformRawGraphToScreen (QPointF (90, rGraph),
                                            posScreen90);
  transformation.transformRawGraphToScreen (QPointF (180, rGraph),
                                            posScreen180);

  QPointF centerTo90 = posScreen90 - posScreenOrigin;

  // Corners of parallelogram circumscribing the ellipse
  QPointF posScreenTL = posScreen180 + centerTo90;
  QPointF posScreenTR = posScreen0 + centerTo90;
  QPointF posScreenBR = posScreen0 - centerTo90;

  double angleRadians = 0, aAligned = 0, bAligned = 0;
  ellipseFromParallelogram (posScreenTL.x() - posScreenOrigin.x(),
                            posScreenTL.y() - posScreenOrigin.y(),
                            posScreenTR.x() - posScreenOrigin.x(),
                            posScreenTR.y() - posScreenOrigin.y(),
                            posScreenBR.x() - posScreenOrigin.x(),
                            posScreenBR.y() - posScreenOrigin.y(),
                            angleRadians,
                            aAligned,
                            bAligned);

  return EllipseParameters (posScreenOrigin,
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

  if ((transformation.modelCoords().coordScaleYRadius() == COORD_SCALE_LOG) &&
      (rGraph <= 0)) {

      // Range enforcement on the range values with log scale should have prevented this branch
      LOG4CPP_ERROR_S ((*mainCat)) << "GuidelineProjectorConstantR::fromPosScreen out of bounds range " << rGraph;

  }

  return fromCoordinateR (transformation,
                          sceneRect,
                          rGraph);
}
