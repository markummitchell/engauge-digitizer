#include "DocumentModelCoords.h"
#include "EngaugeAssert.h"
#include "GridInitializer.h"
#include "Logger.h"
#include <math.h>

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
  if (xMin > xMax)
  {
    double xTemp = xMin;
    xMin = xMax;
    xMax = xTemp;
  }

  // Scale the coordinates logarithmically if log flag is set
  if (!linearAxis)
  {
    ENGAUGE_ASSERT(xMin > 0);
    ENGAUGE_ASSERT(xMax > 0);
    xMin = log10(xMin);
    xMax = log10(xMax);
  }

  // Round off average to first significant digit of range
  xAverage = (xMin + xMax) / 2.0;
  xRange = xMax - xMin;
  if (xRange == 0)
  xRange = fabs (xAverage / 10.0); // for null range use arbitrary range
  nDigitRange = valuePower (xRange);
  xDelta = pow ((double) 10.0, (double) nDigitRange);
  xAverageRoundedUp = xDelta * floor ((xAverage + xDelta / 2.0) / xDelta);


  if (xRange > range_epsilon)
  {
    // Adjust stepsize if more points are needed, accounting for roundoff
    while (fabs (xRange / xDelta) <= 2.000001)
      xDelta /= 2.0;
  }

  // Go down until min point is included
  xStart = xAverageRoundedUp;
  while (xStart > xMin)
    xStart -= xDelta;

  // Go up until max point is included
  xStop = xAverageRoundedUp;
  while (xStop < xMax)
    xStop += xDelta;

  xCount = 1 + (int) floor ((xStop - xStart) / xDelta + 0.5);

  if (!linearAxis)
  {
    // Convert from log scale back to linear scale
    xStart = pow((double) 10.0, xStart);
    xStop = pow((double) 10.0, xStop);
    xDelta = pow((double) 10.0, xDelta);
  }

  // Roundoff to eliminate epsilons of 10^-10
  int power = valuePower (xDelta) - nDigitsPrecision;
  xStart = roundOffToPower(xStart, power);
  xStop = roundOffToPower(xStop, power);
  xDelta = roundOffToPower(xDelta, power);
}

DocumentModelGridDisplay GridInitializer::initialize (const QRectF &boundingRectGraph,
                                                      const DocumentModelCoords &modelCoords) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridInitializer::initalize";

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
  if (avalue < pow(10.0, minPower))
    return minPower;
  else
    return (int) floor (log10 (avalue));
}
