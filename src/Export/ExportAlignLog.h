#ifndef EXPORT_ALIGN_LOG_H
#define EXPORT_ALIGN_LOG_H

/// Pick first simplest x value between specified min and max, for log scaling.
/// A simplest value is defined here as one having the smallest number of significant digits when log value is taken, and
/// is used for aligning periodic values on simple numbers.
/// Examples:
/// -# 0.9 to 2, result is 1 which is 10^0
/// -# 1.1 to 9, result is sqrt(10) which is midway between 1 and 10 in log scale, and equal to 10^0.5
/// -# 9.81 to 9.93, result is 10^0.992 since 9.81=10^0.99166 and 9.93=10^0.9969
class ExportAlignLog
{
 public:
  /// Single constructor
  ExportAlignLog(double xMin,
                 double xMax);

  /// Result
  double firstSimplestNumber () const;

 private:
  ExportAlignLog();

  double log10 (double in) const;

  double m_firstSimplestNumber;
};

#endif // EXPORT_ALIGN_LOG_H
