/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DocumentModelGeneral.h"
#include "FormatCoordsUnitsStrategyAbstractBase.h"
#include "Logger.h"
#include <qmath.h>
#include "Transformation.h"

FormatCoordsUnitsStrategyAbstractBase::FormatCoordsUnitsStrategyAbstractBase ()
{
}

int FormatCoordsUnitsStrategyAbstractBase::precisionDigitsForRawNumber (double valueUnformatted,
                                                                        double valueUnformattedOther,
                                                                        bool isXTheta,
                                                                        const DocumentModelGeneral &modelGeneral,
                                                                        const Transformation &transformation) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "FormatCoordsUnitsStrategyAbstractBase::precisionDigitsForRawNumber";

  const double PIXEL_SHIFT = 1;
  const int DEFAULT_PRECISION = 5; // Precision used before transformation is available. Equal or greater than x/y pixel counts

  if (transformation.transformIsDefined()) {

    // Measure the resolution if the point is moved some number of pixels in screen coordinates
    QPointF posGraph;
    if (isXTheta) {

      posGraph = QPointF (valueUnformatted,
                          valueUnformattedOther);

    } else {

      posGraph = QPointF (valueUnformattedOther,
                          valueUnformatted);

    }

    QPointF posScreen, posScreenShifted, posGraphShifted;

    transformation.transformRawGraphToScreen (posGraph,
                                              posScreen);

    posScreenShifted = posScreen + QPointF (PIXEL_SHIFT, PIXEL_SHIFT);

    transformation.transformScreenToRawGraph (posScreenShifted,
                                              posGraphShifted);

    double xResolutionPerPixel = (posGraphShifted.x() - posGraph.x()) / PIXEL_SHIFT;
    double yResolutionPerPixel = (posGraphShifted.y() - posGraph.y()) / PIXEL_SHIFT;
    double resolutionPerPixel = (isXTheta ? xResolutionPerPixel : yResolutionPerPixel);

    // Compute number of digits ahead of the decimal point (any single decimal place would work but the decimal point is easiest)
    int powerValue = qFloor (qLn (qAbs (valueUnformatted)) / qLn (10.0));
    int powerResolution = qFloor (qLn (qAbs (resolutionPerPixel)) / qLn (10.0));

    int numberDigitsForResolution = powerValue - powerResolution + 1 + modelGeneral.extraPrecision();

    return numberDigitsForResolution + 1; // Add one just to be safe

  } else {

    return DEFAULT_PRECISION;
  }
}
