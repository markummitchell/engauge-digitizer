#ifndef CALLBACK_GATHER_X_THETA_VALUES_FUNCTIONS_H
#define CALLBACK_GATHER_X_THETA_VALUES_FUNCTIONS_H

#include "CallbackSearchReturn.h"
#include "ExportValuesXOrY.h"
#include <QHash>
#include <QMap>
#include "Transformation.h"
#include "ValuesVectorXOrY.h"

class DocumentModelExportFormat;
class Point;

// Save values into container that preserves order by key (QMap). These are common to all included curves
// QMap is for fast random access
typedef QMap<double, bool> ValuesVectorXOrY;

typedef QHash<QString, bool> CurveNamesIncluded;

/// Callback for collecting X/Theta independent variables, for functions, in preparation for exporting.
class CallbackGatherXThetaValuesFunctions
{
public:
  /// Single constructor.
  CallbackGatherXThetaValuesFunctions(const DocumentModelExportFormat &modelExport,
                                      const QStringList &curveNamesIncluded,
                                      const Transformation &transformation);

  /// Callback method.
  CallbackSearchReturn callback (const QString &curveName,
                                 const Point &point);

  /// Resulting x/theta values for all included functions
  ValuesVectorXOrY xThetaValuesRaw () const;

private:
  CallbackGatherXThetaValuesFunctions();

  const Transformation m_transformation;
  CurveNamesIncluded m_curveNamesIncluded;
  ValuesVectorXOrY m_xThetaValues;
};

#endif // CALLBACK_GATHER_X_THETA_VALUES_FUNCTIONS_H
