#ifndef CALLBACK_GATHER_X_THETA_VALUES_RELATIONS_H
#define CALLBACK_GATHER_X_THETA_VALUES_RELATIONS_H

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

/// Callback for collecting X/Theta independent variables in preparation for exporting.
class CallbackGatherXThetaValuesRelations
{
public:
  /// Single constructor.
  CallbackGatherXThetaValuesRelations(const DocumentModelExport &modelExport,
                                      const QStringList &curveNamesIncluded,
                                      const Transformation &transformation);

  /// Callback method.
  CallbackSearchReturn callback (const QString &curveName,
                                 const Point &point);

  /// Number of entries to be reserved. Actual entries will be directly raw data from curves or from xThetaValueStepsForRelations method.
  /// Not applicable for functions
  int xThetaValueCount () const;

  /// Parameters specifying x/theta values when using even increments
  void xThetaValueSteps (double &xThetaMin,
                         double &xThetaStep);

private:
  CallbackGatherXThetaValuesRelations();

  const DocumentModelExport m_modelExport;
  const Transformation m_transformation;

  CurveNamesIncluded m_curveNamesIncluded;

  ValuesContainer m_values;
};

#endif // CALLBACK_GATHER_X_THETA_VALUES_RELATIONS_H
