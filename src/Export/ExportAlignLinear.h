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
///
/// A comprehensive set of examples is given in TestExportAlign
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
  double roundToDigit (double value,
                       int digit) const;

  double m_firstSimplestNumber;
};

#endif // EXPORT_ALIGN_LINEAR_H
