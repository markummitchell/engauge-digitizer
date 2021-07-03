/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef EXPORT_X_THETA_VALUES_MERGED_FUNCTIONS_H
#define EXPORT_X_THETA_VALUES_MERGED_FUNCTIONS_H

#include "DocumentModelExportFormat.h"
#include "ExportValuesXOrY.h"
#include "MainWindowModel.h"
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
                                    const MainWindowModel &modelMainWindow,
                                    const ValuesVectorXOrY &xThetaValuesRaw,
                                    const Transformation &transformation);

  /// Resulting x/theta values for all included functions
  ExportValuesXOrY xThetaValues (bool &isOverrun) const;

private:
  ExportXThetaValuesMergedFunctions();

  bool breakForPointOverrun (unsigned int curveSize,
                             bool &isOverrun) const;
  void firstSimplestNumberLinear (double &xThetaFirstSimplestNumber,
                                  double &xThetaMin,
                                  double &xThetaMax) const;
  void firstSimplestNumberLog (double &xThetaFirstSimplestNumber,
                               double &xThetaMin,
                               double &xThetaMax) const;
  ExportValuesXOrY periodicLinear(bool &isOverrun) const;
  ExportValuesXOrY periodicLinearGraph (double xThetaFirstSimplestNumber,
                                        double xThetaMin,
                                        double xThetaMax,
                                        bool &isOverrun) const;
  ExportValuesXOrY periodicLinearScreen (double xThetaMin,
                                         double xThetaMax,
                                         bool &isOverrun) const;
  ExportValuesXOrY periodicLog(bool &isOverrun) const;
  ExportValuesXOrY periodicLogGraph (double xThetaFirstSimplestNumber,
                                     double xThetaMin,
                                     double xThetaMax,
                                     bool &isOverrun) const;
  ExportValuesXOrY periodicLogScreen (double xThetaMin,
                                      double xThetaMax,
                                      bool &isOverrun) const;

  const DocumentModelExportFormat m_modelExport;
  const MainWindowModel m_modelMainWindow;
  const ValuesVectorXOrY m_xThetaValuesRaw;
  const Transformation m_transformation;
};

#endif // EXPORT_X_THETA_VALUES_MERGED_FUNCTIONS_H
