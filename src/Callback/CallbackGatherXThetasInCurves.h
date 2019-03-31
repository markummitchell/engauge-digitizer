/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CALLBACK_GATHER_X_THETAS_IN_CURVES_H
#define CALLBACK_GATHER_X_THETAS_IN_CURVES_H

#include "CallbackSearchReturn.h"
#include "CurveNamesIncluded.h"
#include "ExportValuesXOrY.h"
#include "Transformation.h"
#include "ValuesVectorXOrY.h"

class DocumentModelExportFormat;
class Point;

/// Callback for collecting X/Theta independent variables, for functions, in preparation for exporting,
/// based on curve points.
///
/// Although most of the time the X values are extracted from the X values of the document curves, they are sometimes
/// extracted from the X coordinates of the grid lines (depending on ExportPointsSelectionFunctions), or even
/// both the document curves and grid lines
class CallbackGatherXThetasInCurves
{
public:
  /// Single constructor.
  CallbackGatherXThetasInCurves(const DocumentModelExportFormat &modelExport,
                                const QStringList &curveNamesIncluded,
                                const Transformation &transformation);

  /// Callback method.
  CallbackSearchReturn callback (const QString &curveName,
                                 const Point &point);

  /// Resulting x/theta values for all included functions
  ValuesVectorXOrY xThetaValuesRaw () const;

private:
  CallbackGatherXThetasInCurves();

  const Transformation m_transformation;
  CurveNamesIncluded m_curveNamesIncluded;
  ValuesVectorXOrY m_xThetaValues;
};

#endif // CALLBACK_GATHER_X_THETAS_IN_CURVES_H
