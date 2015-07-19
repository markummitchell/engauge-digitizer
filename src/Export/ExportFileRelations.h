#ifndef EXPORT_FILE_RELATIONS_H
#define EXPORT_FILE_RELATIONS_H

#include "ExportFileAbstractBase.h"
#include "ExportValues.h"
#include <QStringList>
#include <QVector>

class Document;
class DocumentModelExport;
class QTextStream;
class Transformation;

/// Strategy class for exporting to a file. This strategy is external to the Document class so that class is simpler.
class ExportFileRelations : public ExportFileAbstractBase
{
public:
  /// Single constructor.
  ExportFileRelations();

  /// Export Document points according to the settings. The DocumentModelExport inside the Document is ignored so
  /// DlgSettingsExport can supply its own DocumentModelExport when previewing what would be exported.
  void exportToFile (const DocumentModelExport &modelExport,
                     const Document &document,
                     const Transformation &transformation,
                     QTextStream &str) const;

private:
  void exportAllPerLineXThetaValuesMerged (const DocumentModelExport &modelExport,
                                           const Document &document,
                                           const QStringList &curvesIncluded,
                                           const ExportValues &xThetaValuesMerged,
                                           const QString &delimiter,
                                           const Transformation &transformation,
                                           QTextStream &str) const;
  void exportOnePerLineXThetaValuesMerged (const DocumentModelExport &modelExport,
                                           const Document &document,
                                           const QStringList &curvesIncluded,
                                           const ExportValues &xThetaValuesMerged,
                                           const QString &delimiter,
                                           const Transformation &transformation,
                                           QTextStream &str) const;
};

#endif // EXPORT_FILE_RELATIONS_H
