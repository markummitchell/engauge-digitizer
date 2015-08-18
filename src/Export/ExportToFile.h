#ifndef EXPORT_TO_FILE_H
#define EXPORT_TO_FILE_H

#include <QStringList>

class Document;
class DocumentModelExportFormat;
class QTextStream;
class Transformation;

/// Strategy class for exporting to a file. This strategy is external to the Document class so that class is simpler.
class ExportToFile
{
public:
  /// Single constructor.
  ExportToFile();

  /// Export Document points according to the settings. The DocumentModelExportFormat inside the Document is ignored so
  /// DlgSettingsExport can supply its own DocumentModelExportFormat when previewing what would be exported.
  void exportToFile (const DocumentModelExportFormat &modelExport,
                     const Document &document,
                     const Transformation &transformation,
                     QTextStream &str) const;

};

#endif // EXPORT_TO_FILE_H
