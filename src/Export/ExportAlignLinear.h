/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef EXPORT_ALIGN_LINEAR_H
#define EXPORT_ALIGN_LINEAR_H

/// Pick first simplest x value between specified min and max, for linear scaling.
/// A simplest value is defined here as one having the smallest number of significant digits, and is used for aligning 
/// periodic values on simple numbers.
/// Examples:
/// -# 0.4 to 3.4, result is 1
/// -# 110 to 1100, result is 200 (not 1000 although both have same number of significant digits)
/// -# 112.123 to 122.456, result is 120
class ExportAlignLinear
{
 public:
  /// Single constructor
  ExportAlignLinear(double xMin,
                    double xMax);

  /// Result
  double firstSimplestNumber () const;

 private:
  ExportAlignLinear();

  double log10 (double in) const;

  double m_firstSimplestNumber;
};

#endif // EXPORT_ALIGN_LINEAR_H
