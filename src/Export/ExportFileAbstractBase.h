#ifndef EXPORT_FILE_ABSTRACT_BASE_H
#define EXPORT_FILE_ABSTRACT_BASE_H

#include "CurveConnectAs.h"
#include "ExportFileAbstractBase.h"
#include "ExportValues.h"
#include <QStringList>
#include <QVector>

class Document;
class DocumentModelExport;
class QTextStream;
class Transformation;

/// Strategy base class for exporting to a file. This class provides common methods
class ExportFileAbstractBase
{
public:
  /// Single constructor.
  ExportFileAbstractBase();

 protected:
  /// Identify curves to include in export
  QStringList curvesToInclude (const DocumentModelExport &modelExport,
                               const Document &document,
                               const QStringList &curvesGraphsNames,
                               CurveConnectAs curveConnectAs1,
                               CurveConnectAs curveConnectAs2) const;
  
  /// Deallocate the 2D y/radius array allocated by initializeYRadiusValues
  void destroyYRadiusValues (QVector<QVector<QString*> > &yRadiusValues) const;

  /// Allocate a 2D y/radius array indexed by (included) curve and x/theta.
  /// Array rows and columns are set up so yRadiusValues[N] gives vector for Nth curve. Values are strings
  /// so non-applicable entries can be blank
  void initializeYRadiusValues (const QStringList &curvesIncluded,
                                const ExportValues &xThetaValuesMerged,
                                QVector<QVector<QString*> > &yRadiusValues) const;

  /// Output 2D y/radius array along with x/theta vector in first column
  void outputXThetaYRadiusValues (const ExportValues &xThetaValuesMerged,
                                  QVector<QVector<QString*> > &yRadiusValues,
                                  const QString &delimiter,
                                  QTextStream &str) const;
};

#endif // EXPORT_FILE_ABSTRACT_BASE_H
