/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef FITTING_CURVE_COEFFICIENTS_H
#define FITTING_CURVE_COEFFICIENTS_H

#include <QList>

/// Coefficients x0, x1, ... in y = a0 + a1 * x + a2 * x^2 + ...
typedef QList<double> FittingCurveCoefficients;

#endif // FITTING_CURVE_COEFFICIENTS_H
