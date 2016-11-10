/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "FittingCurve.h"
#include "FittingWindow.h"
#include "Logger.h"
#include <QMimeData>
#include <QTextStream>

const int COLUMN_COEFFICIENTS = 0;
const int COLUMN_POLYNOMIAL_TERMS = 1;

const QString CURVE_FIT_CURVE_NAME ("CurveFit"); // Not seen by user

FittingCurve::FittingCurve () :
  GraphicsLinesForCurve (CURVE_FIT_CURVE_NAME)
{
}

FittingCurve::~FittingCurve()
{
}
