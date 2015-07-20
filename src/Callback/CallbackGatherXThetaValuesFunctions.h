#ifndef CALLBACK_GATHER_X_THETA_VALUES_FUNCTIONS_H
#define CALLBACK_GATHER_X_THETA_VALUES_FUNCTIONS_H

#include "CallbackSearchReturn.h"
#include "DocumentModelExport.h"
#include "ExportValues.h"
#include <QHash>
#include <QMap>
#include "Transformation.h"

class Point;

// Save values into container that preserves order by key (QMap)
typedef QMap<double, bool> ValuesContainer;

typedef QHash<QString, bool> CurveNamesIncluded;

/// Callback for collecting X/Theta independent variables, for functions, in preparation for exporting.
class CallbackGatherXThetaValuesFunctions
{
public:
  /// Single constructor.
  CallbackGatherXThetaValuesFunctions(const DocumentModelExport &modelExport,
                                      const QStringList &curveNamesIncluded,
                                      const Transformation &transformation);

  /// Callback method.
  CallbackSearchReturn callback (const QString &curveName,
                                 const Point &point);

  /// Resulting values for functions.
  /// Not applicable for relations
  ExportValues xThetaValues () const;

private:
  CallbackGatherXThetaValuesFunctions();

  const DocumentModelExport m_modelExport;
  const Transformation m_transformation;

  CurveNamesIncluded m_curveNamesIncluded;

  ValuesContainer m_values;
};

#endif // CALLBACK_GATHER_X_THETA_VALUES_FUNCTIONS_H
