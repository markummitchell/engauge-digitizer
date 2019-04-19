/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "ExportAlignLinear.h"
#include <qmath.h>

const double EPSILON = 0.000001;

ExportAlignLinear::ExportAlignLinear(double xMin,
                                     double xMax) :
  m_firstSimplestNumber (0)
{
  ENGAUGE_ASSERT (xMin <= xMax);

  const int MAX_S = 7; // This algorithm is probably constrained to the 7 digits of precision of real numbers

  // Start by identifying the first digit D for the larger magnitude (=unsigned) of xMin and xMax. Examples
  // are D=0 for 0.1 to 0.99..., D=1 for 1 to 9.99..., D=2 for 10 to 99.999...
  double absMin = qAbs (xMin);
  double absMax = qAbs (xMax);
  int D = qFloor (log10 (qMax (absMin, absMax)) + EPSILON);

  // Number of significant digits S will start at 1 and then get increased until
  //    rounded(xMin) + 10^R <= xMax
  // where rounded(xMin) is xMin rounded off to the the Rth digit, where R=D-S
  int S = 1;
  double roundedMin = 0.0;
  while (S < MAX_S) {
    int R = D - S + 1;
    roundedMin = roundToDigit (xMin, R);
    double nominalStep = qPow (10.0, R);

    if (xMin < 0 && xMin < roundedMin) {
      // For negative xMin we often or always have to jump over by nominalStep to keep
      // xMin in the range
      roundedMin -= nominalStep;
    }

    // Need at least one step between roundedMin and xMax, otherwise ranges
    if (roundedMin + 2 * nominalStep <= xMax) {
      break;
    }

    S = S + 1;
  }

  m_firstSimplestNumber = roundedMin;
}

double ExportAlignLinear::firstSimplestNumber () const
{
  return m_firstSimplestNumber;
}

double ExportAlignLinear::log10 (double in) const
{
  return qLn (in) / qLn (10.0);
}

double ExportAlignLinear::roundToDigit (double value,
                                        int digit) const
{
  double scale = qPow (10.0, digit);
  int valueRoundedWithWrongScale = qFloor (value / scale + EPSILON);
  double valueRounded = valueRoundedWithWrongScale * scale;

  return valueRounded;
}
