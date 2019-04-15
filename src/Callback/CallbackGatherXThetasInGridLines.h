/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CALLBACK_GATHER_X_THETAS_IN_GRID_LINES_H
#define CALLBACK_GATHER_X_THETAS_IN_GRID_LINES_H

#include "CallbackGatherXThetasAbstractBase.h"
#include "CallbackSearchReturn.h"
#include "ExportValuesXOrY.h"
#include "Transformation.h"
#include <QHash>
#include <QString>
#include "ValuesVectorXOrY.h"

class Document;
class MainWindowModel;
class Point;

/// Callback for collecting X/Theta independent variables, for functions, in preparation for exporting,
/// based on grid lines.
///
/// Although most of the time the X values are extracted from the X values of the document curves, they are sometimes
/// extracted from the X coordinates of the grid lines (depending on ExportPointsSelectionFunctions), or even
/// both the document curves and grid lines
class CallbackGatherXThetasInGridLines : public CallbackGatherXThetasAbstractBase
{
public:
  /// Single constructor.
  CallbackGatherXThetasInGridLines(const MainWindowModel &modelMainWindow,
                                   const DocumentModelExportFormat &modelExport,
                                   const QStringList &curvesIncluded,
                                   const Transformation &transformation,
                                   const Document &document);

  /// Callback method.
  virtual CallbackSearchReturn callback (const QString &curveName,
                                         const Point &point);
  
private:
  CallbackGatherXThetasInGridLines();

  void addGridLines (const MainWindowModel &modelMainWindow,
                     const Transformation &transformation,
                     const Document &document);
};

#endif // CALLBACK_GATHER_X_THETAS_IN_GRID_LINES_H
