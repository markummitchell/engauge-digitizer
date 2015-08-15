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
                                                                        const Transformation &transformation) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "FormatCoordsUnitsStrategyAbstractBase::precisionDigitsForRawNumber";

  const double PIXEL_SHIFT = 1;

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

  int numberDigitsForResolution = powerValue - powerResolution + 1;

  return numberDigitsForResolution + 1; // Add one just to be safe
}
