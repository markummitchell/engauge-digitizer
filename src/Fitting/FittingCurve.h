/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef FITTING_CURVE_H
#define FITTING_CURVE_H

#include "FittingCurveCoefficients.h"
#include <QGraphicsPathItem>

class Transformation;

/// Curve that overlays the current scene so the regression-fitted curve is visible
class FittingCurve : public QGraphicsPathItem
{
public:
  /// Single constructor
  FittingCurve (const FittingCurveCoefficients &fittingCoef,
                double xMin,
                double xMax,
                bool isLogXTheta,
                bool isLogYRadius,
                const Transformation &transformation);
  virtual ~FittingCurve ();

private:

  double yFromCoefficientsAndX (const FittingCurveCoefficients &fittingCoef,
                                                                double x) const;
};

#endif // FITTING_CURVE_H
