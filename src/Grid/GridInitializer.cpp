#include "DocumentModelCoords.h"
#include "EngaugeAssert.h"
#include "GridInitializer.h"
#include "Logger.h"
#include <math.h>
#include <qmath.h>
#include "Transformation.h"

GridInitializer::GridInitializer ()
{
}

void GridInitializer::axisScale (double xMin,
                                 double xMax,
                                 bool linearAxis,
                                 double &xStart,
                                 double &xStop,
                                 double &xDelta,
                                 int &xCount) const
{
  const double range_epsilon = 0.00000000001;
  double xAverage, xAverageRoundedUp, xRange;
  int nDigitRange;

  // Define number of digits of precision. although value of 10 seems
  // desirable, the sprintf statements elsewhere in this file, which
  // operate on values with the specified precision, just lose it
  // for more than 8 digits. example '%.7lg' on 40.000005 gives 40.00001
  const int nDigitsPrecision = 8;

  // sort the input values
  if (xMin > xMax) {
    double xTemp = xMin;
    xMin = xMax;
    xMax = xTemp;
  }

  // Scale the coordinates logarithmically if log flag is set
  if (!linearAxis) {
    ENGAUGE_ASSERT(xMin > 0);
    ENGAUGE_ASSERT(xMax > 0);
    xMin = log10(xMin);
    xMax = log10(xMax);
  }

  // Round off average to first significant digit of range
  xAverage = (xMin + xMax) / 2.0;
  xRange = xMax - xMin;
  if (xRange == 0) {
    xRange = fabs (xAverage / 10.0); // for null range use arbitrary range
  }
  nDigitRange = valuePower (xRange);
  xDelta = pow ((double) 10.0, (double) nDigitRange);
  xAverageRoundedUp = xDelta * floor ((xAverage + xDelta / 2.0) / xDelta);

  if (xRange > range_epsilon) {
    // Adjust stepsize if more points are needed, accounting for roundoff
    while (fabs (xRange / xDelta) <= 2.000001) {
      xDelta /= 2.0;
    }
  }

  // Go down until min point is included
  xStart = xAverageRoundedUp;
  while (xStart > xMin) {
    xStart -= xDelta;
  }

  // Go up until max point is included
  xStop = xAverageRoundedUp;
  while (xStop < xMax) {
    xStop += xDelta;
  }

  xCount = 1 + (int) floor ((xStop - xStart) / xDelta + 0.5);

  if (!linearAxis) {

    // Convert from log scale back to linear scale. We make sure to keep numbers like 10^-8 unmolested
    xStart = pow((double) 10.0, xStart);
    xStop = pow((double) 10.0, xStop);
    xDelta = pow((double) 10.0, xDelta);

  } else {

    // Roundoff to eliminate epsilons of 10^-10
    int power = valuePower (xDelta) - nDigitsPrecision;
    xStart = roundOffToPower(xStart, power);
    xStop = roundOffToPower(xStop, power);
    xDelta = roundOffToPower(xDelta, power);

  }
}

int GridInitializer::computeCount (bool linearAxis,
                                   double start,
                                   double stop,
                                   double step) const
{
  int count;

  if (linearAxis) {
    if (step == 0) {
      count = 1;
    } else {
      count = (int) (1.0 + (stop - start) / step);
    }
  } else {
    if ((start <= 0) || (step <= 0.0)) {
      count = 1;
    } else {
      count = (int) (1.0 + log10 (stop / start) / log10 (step));
    }
  }

  return count;
}

double GridInitializer::computeStart (bool linearAxis,
                                      double stop,
                                      double step,
                                      int count) const
{
  double start;

  if (linearAxis) {
    start = stop - step * (count - 1);
  } else {
    start = stop / pow (step, (double) (count - 1));
  }

  return start;
}

double GridInitializer::computeStep (bool linearAxis,
                                     double start,
                                     double stop,
                                     int count) const
{
  double step;

  if (linearAxis) {
    if (count > 1) {
      step = (stop - start) / (count - 1);
    } else {
      step = stop - start;
    }
  } else {
    if (start <= 0.0) {
      step = 1.0;
    } else {
      if (count > 1) {
        step = pow (stop / start, (double) 1.0 / (count - 1));
      } else {
        step = stop / start;
      }
    }
  }

  return step;
}

double GridInitializer::computeStop (bool linearAxis,
                                     double start,
                                     double step,
                                     int count) const
{
  double stop;

  if (linearAxis) {
    stop = start + step * (count - 1);
  } else {
    stop = start * pow (step, (double) (count - 1));
  }

  return stop;
}

DocumentModelGridDisplay GridInitializer::initializeWithNarrowCoverage (const QRectF &boundingRectGraph,
                                                                        const DocumentModelCoords &modelCoords) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridInitializer::initializeWithNarrowCoverage";

  DocumentModelGridDisplay modelGridDisplay;

  int count;
  double start, stop, step;

  // X/theta coordinate
  axisScale (boundingRectGraph.x(),
             boundingRectGraph.x() + boundingRectGraph.width(),
             (modelCoords.coordScaleXTheta() == COORD_SCALE_LINEAR),
             start,
             stop,
             step,
             count);

  modelGridDisplay.setDisableX (GRID_COORD_DISABLE_COUNT);
  modelGridDisplay.setCountX (count);
  modelGridDisplay.setStartX (start);
  modelGridDisplay.setStepX (step);
  modelGridDisplay.setStopX (stop);

  // Y/radius coordinate
  axisScale (boundingRectGraph.y(),
             boundingRectGraph.y() + boundingRectGraph.height(),
             (modelCoords.coordScaleYRadius() == COORD_SCALE_LINEAR),
             start,
             stop,
             step,
             count);

  modelGridDisplay.setDisableY (GRID_COORD_DISABLE_COUNT);
  modelGridDisplay.setCountY (count);
  modelGridDisplay.setStartY (start);
  modelGridDisplay.setStepY (step);
  modelGridDisplay.setStopY (stop);

  modelGridDisplay.setStable (true);

  return modelGridDisplay;
}

DocumentModelGridDisplay GridInitializer::initializeWithWidePolarCoverage (const QRectF &boundingRectGraph,
                                                                           const DocumentModelCoords &modelCoords,
                                                                           const Transformation &transformation,
                                                                           const QSize &imageSize) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridInitializer::initializeWithWidePolarCoverage";

  DocumentModelGridDisplay modelGridDisplay = initializeWithNarrowCoverage (boundingRectGraph,
                                                                            modelCoords);

  if (modelCoords.coordsType() == COORDS_TYPE_POLAR) {

    overridePolarCoordinateSettings (modelCoords,
                                     transformation,
                                     modelGridDisplay,
                                     imageSize);
  }

  return modelGridDisplay;
}

void GridInitializer::overridePolarCoordinateSettings (const DocumentModelCoords &modelCoords,
                                                       const Transformation &transformation,
                                                       DocumentModelGridDisplay &modelGridDisplay,
                                                       const QSize &imageSize) const
{
  ENGAUGE_ASSERT (modelCoords.coordsType() == COORDS_TYPE_POLAR);

  // We make sure the angular range is over the entire circle, which is probably useful
  // unless the orgin is very close to a corner of the graph, in which case the large range does not hurt anything
  double startX = 0.0;
  double stopX = 360.0;
  double stepX = 30.0;
  int countX = (int) (0.5 + (stopX - startX) / stepX);
  modelGridDisplay.setStartX (startX);
  modelGridDisplay.setStepX (stepX);
  modelGridDisplay.setStopX (stopX);
  modelGridDisplay.setCountX (countX);

  // We extend the range to cover the four corners of the image, since otherwise
  // areas around at least some graph corners are not covered by the grid lines
  QPointF posTL, posBL, posTR, posBR;
  transformation.transformScreenToRawGraph (QPointF (0                 , imageSize.height ()), posTL);
  transformation.transformScreenToRawGraph (QPointF (0                 , 0                  ), posBL);
  transformation.transformScreenToRawGraph (QPointF (imageSize.width (), imageSize.height ()), posTR);
  transformation.transformScreenToRawGraph (QPointF (imageSize.width (), 0                  ), posBR);

  double radiusTL = qSqrt (posTL.x () * posTL.x () + posTL.y () * posTL.y ());
  double radiusBL = qSqrt (posBL.x () * posBL.x () + posBL.y () * posBL.y ());
  double radiusTR = qSqrt (posTR.x () * posTR.x () + posTR.y () * posTR.y ());
  double radiusBR = qSqrt (posBR.x () * posBR.x () + posBR.y () * posBR.y ());

  double radius = qMax (qMax (qMax (radiusTL, radiusBL), radiusTR), radiusBR);

  double startY = (modelCoords.coordScaleYRadius() == COORD_SCALE_LINEAR ?
                     0.0 :
                     modelCoords.originRadius());
  double stopY = radius;
  double stepY = modelGridDisplay.stepY ();
  double denominator = (modelCoords.coordScaleYRadius() == COORD_SCALE_LINEAR ?
                        stepY :
                        qLn (stepY));
  int countY = 1;
  if (denominator != 0) {
    countY = (modelCoords.coordScaleYRadius() == COORD_SCALE_LINEAR ?
              (int) (0.5 + (stopY - startY) / denominator) :
              (int) (0.5 + (qLn (stopY) - qLn (startY)) / denominator));
  }

  modelGridDisplay.setStartY (startY);
  modelGridDisplay.setStopY (stopY);
  modelGridDisplay.setCountY (countY);
}

double GridInitializer::roundOffToPower(double arg,
                                        int power) const
{
  double powerOf10 = pow ((double) 10, power);
  return powerOf10 * floor (arg / powerOf10 + 0.5);
}

int GridInitializer::valuePower(double value) const
{
  const int minPower = -30; // MAX_DOUBLE is 10^38

  double avalue = fabs(value);
  if (avalue < pow(10.0, minPower)) {
    return minPower;
  } else {
    return (int) floor (log10 (avalue));
  }
}
