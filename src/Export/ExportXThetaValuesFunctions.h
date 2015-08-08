#ifndef EXPORT_X_THETA_VALUES_FUNCTIONS_H
#define EXPORT_X_THETA_VALUES_FUNCTIONS_H

#include "DocumentModelExport.h"
#include "ExportValuesXOrY.h"
#include "ValuesVectorXOrY.h"

class Point;
class Transformation;

/// Creates the set of x/theta values for exporting functions, using interpolation
class ExportXThetaValuesFunctions
{
public:
  /// Single constructor.
  ExportXThetaValuesFunctions(const DocumentModelExport &modelExport,
                              const ValuesVectorXOrY &xThetaValuesRaw,
                              const Transformation &transformation);

  /// Resulting x/theta values for all included functions
  ExportValuesXOrY xThetaValues () const;

private:
  ExportXThetaValuesFunctions();

  void firstSimplestNumberLinear (double &xThetaFirstSimplestNumber,
                                  double &xThetaMin,
                                  double &xThetaMax) const;
  void firstSimplestNumberLog (double &xThetaFirstSimplestNumber,
                               double &xThetaMin,
                               double &xThetaMax) const;
  ExportValuesXOrY periodicLinear() const;
  ExportValuesXOrY periodicLinearGraph (double xThetaFirstSimplestNumber,
                                        double xThetaMin,
                                        double xThetaMax) const;
  ExportValuesXOrY periodicLinearScreen (double xThetaFirstSimplestNumber,
                                         double xThetaMin,
                                         double xThetaMax) const;
  ExportValuesXOrY periodicLog() const;
  ExportValuesXOrY periodicLogGraph (double xThetaFirstSimplestNumber,
                                     double xThetaMin,
                                     double xThetaMax) const;
  ExportValuesXOrY periodicLogScreen (double xThetaFirstSimplestNumber,
                                      double xThetaMin,
                                      double xThetaMax) const;

  const DocumentModelExport m_modelExport;
  const ValuesVectorXOrY m_xThetaValuesRaw;
  const bool m_isLinear;
};

#endif // EXPORT_X_THETA_VALUES_FUNCTIONS_H
