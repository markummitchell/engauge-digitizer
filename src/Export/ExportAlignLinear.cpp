#include "EngaugeAssert.h"
#include "ExportAlignLinear.h"
#include <qmath.h>

const double EPSILON = 0.000001;

ExportAlignLinear::ExportAlignLinear(double xMin,
                                     double xMax)
{
  ENGAUGE_ASSERT (xMin <= xMax);

  // Start with digit N=1, then keep adding to that digit until:
  // 1) number is between xMin and xMax in which case that value is the result
  // 2) number exceeds xMax in which case digit N+1 is added and this repeats
  double powerOf10 = qPow (10.0, (int) (log10 (qAbs (xMin)) + EPSILON));
  int firstDigit = (int) (xMin / powerOf10);
  double digitsCurrent = firstDigit * powerOf10; // May or may not be less than xMax
  while (digitsCurrent > xMin) {
    digitsCurrent -= powerOf10; // Go backwards until less than xMin. Required only if xMin < 0
  }
  double digitsHighestUnderXMin = digitsCurrent;
  do {
    digitsCurrent = digitsHighestUnderXMin; // Go back to highest value so far less than xMin
    while (digitsCurrent < xMin) {
      digitsCurrent += powerOf10;

      if (digitsCurrent < xMin) {
        digitsHighestUnderXMin = digitsCurrent;
      }
    }
    powerOf10 /= 10.0;
  } while (digitsCurrent > xMax);

  m_firstSimplestNumber = digitsCurrent;
}

double ExportAlignLinear::firstSimplestNumber () const
{
  return m_firstSimplestNumber;
}

double ExportAlignLinear::log10 (double in) const
{
  return qLn (in) / qLn (10.0);
}
