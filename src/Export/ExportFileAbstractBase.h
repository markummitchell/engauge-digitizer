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
  QStringList curvesToInclude (const DocumentModelExport &modelExport,
                               const Document &document,
                               const QStringList &curvesGraphsNames,
                               CurveConnectAs curveConnectAs1,
                               CurveConnectAs curveConnectAs2) const;
  void destroyYPhiValues (QVector<QVector<QString*> > &yPhiValues) const;
  void initializeYPhiValues (const QStringList &curvesIncluded,
                             const ExportValues &xThetaValuesMerged,
                             QVector<QVector<QString*> > &yPhiValues) const;
  void outputXThetaYPhiValues (const ExportValues &xThetaValuesMerged,
                               QVector<QVector<QString*> > &yPhiValues,
                               const QString &delimiter,
                               QTextStream &str) const;
};

#endif // EXPORT_FILE_ABSTRACT_BASE_H
