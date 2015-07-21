#ifndef CALLBACK_GATHER_X_THETA_VALUES_RELATIONS_H
#define CALLBACK_GATHER_X_THETA_VALUES_RELATIONS_H

#include "CallbackSearchReturn.h"
#include "DocumentModelExport.h"
#include "ExportValuesOrdinal.h"
#include <QHash>
#include <QList>
#include <QMap>
#include <QString>
#include "Transformation.h"

class Point;

// Save values into container with columns that probably have different sizes
typedef QMap<QString, ExportValuesOrdinal> ValuesColumns;

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

  /// Size of the largest column of x/theta values, in the specified curves
  int maxColumnSize (const QStringList &curvesIncluded) const;

  /// Resulting x/theta values for the specified curve
  ExportValuesOrdinal ordinals (const QString &curveName) const;

private:
  CallbackGatherXThetaValuesRelations();

  const DocumentModelExport m_modelExport;
  const Transformation m_transformation;

  CurveNamesIncluded m_curveNamesIncluded;

  ValuesColumns m_ordinals;
};

#endif // CALLBACK_GATHER_X_THETA_VALUES_RELATIONS_H
