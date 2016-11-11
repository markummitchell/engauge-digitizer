/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "FittingCurveCoefficients.h"
#include "FittingCurve.h"
#include "Logger.h"
#include <qmath.h>
#include <QPainterPath>
#include <QPen>
#include "Transformation.h"

FittingCurve::FittingCurve (const FittingCurveCoefficients &fittingCoef,
                            double xMin,
                            double xMax,
                            bool isLogXTheta,
                            bool isLogYRadius,
                            const Transformation &transformation)
{
  const int NUM_POINTS = 1000; // Use so many points that spline interpolation is not needed for smoothness
  const double Z_LINE = 500; // More than the z value for lines since this line takes priority, and user can hide it

  setZValue (Z_LINE);
  setPen (QPen (QColor (Qt::red)));

  QPainterPath path;

  if (transformation.transformIsDefined()) {

    for (int i = 0; i < NUM_POINTS; i++) {

      // Compute (x,y) point in graph coordinates
      double s = (double) i / (double) (NUM_POINTS - 1);
      double x = xMin + s * (xMax - xMin);
      double y = yFromCoefficientsAndX (fittingCoef,
                                        x);

      // The coefficients were computed assuming the x and y values were transformed if they were log scale base 10, so
      // we must compensate here in the same way
      if (isLogXTheta) {
        x = qPow (10.0, x);
      }
      if (isLogYRadius) {
        y = qPow (10.0, y);
      }

      // Convert to screen coordinates
      QPointF posGraph (x, y);
      QPointF posScreen;
      transformation.transformRawGraphToScreen (posGraph,
                                                posScreen);

      // Add point to line
      if (i == 0) {
        path.moveTo (posScreen);
      } else {
        path.lineTo (posScreen);
      }
    }
  }

  setPath (path);
}

FittingCurve::~FittingCurve()
{
}

double FittingCurve::yFromCoefficientsAndX (const FittingCurveCoefficients &fittingCoef,
                                            double x) const
{
  double sum = 0;

  for (int order = 0; order < fittingCoef.size(); order++) {
    sum += fittingCoef [order] * qPow (x, order);
  }

  return sum;
}
