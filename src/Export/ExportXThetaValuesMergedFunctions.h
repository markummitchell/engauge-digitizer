#ifndef EXPORT_X_THETA_VALUES_MERGED_FUNCTIONS_H
#define EXPORT_X_THETA_VALUES_MERGED_FUNCTIONS_H

#include "DocumentModelExportFormat.h"
#include "ExportValuesXOrY.h"
#include "Transformation.h"
#include "ValuesVectorXOrY.h"

class Point;
class Transformation;

/// Creates the set of merged x/theta values for exporting functions, using interpolation
class ExportXThetaValuesMergedFunctions
{
public:
  /// Single constructor.
  ExportXThetaValuesMergedFunctions(const DocumentModelExportFormat &modelExport,
                                    const ValuesVectorXOrY &xThetaValuesRaw,
                                    const Transformation &transformation);

  /// Resulting x/theta values for all included functions
  ExportValuesXOrY xThetaValues () const;

private:
  ExportXThetaValuesMergedFunctions();

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
  ExportValuesXOrY periodicLinearScreen (double xThetaMin,
                                         double xThetaMax) const;
  ExportValuesXOrY periodicLog() const;
  ExportValuesXOrY periodicLogGraph (double xThetaFirstSimplestNumber,
                                     double xThetaMin,
                                     double xThetaMax) const;
  ExportValuesXOrY periodicLogScreen (double xThetaMin,
                                      double xThetaMax) const;

  const DocumentModelExportFormat m_modelExport;
  const ValuesVectorXOrY m_xThetaValuesRaw;
  const Transformation m_transformation;
};

#endif // EXPORT_X_THETA_VALUES_MERGED_FUNCTIONS_H
