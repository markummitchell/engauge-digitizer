#include "ExportAlignLinear.h"
#include "ExportAlignLog.h"
#include <qmath.h>

ExportAlignLog::ExportAlignLog(double xMin,
                               double xMax)
{
  // Convert log numbers to linear numbers
  double xMinLog = log10 (xMin);
  double xMaxLog = log10 (xMax);

  ExportAlignLinear alignLinear (xMinLog,
                                 xMaxLog);

  // Convert result back to log numbers
  m_firstSimplestNumber = qPow (10.0, alignLinear.firstSimplestNumber());
}

double ExportAlignLog::firstSimplestNumber () const
{
  return m_firstSimplestNumber;
}

double ExportAlignLog::log10 (double in) const
{
  return qLn (in) / qLn (10.0);
}
