#ifndef EXPORT_TO_FILE_H
#define EXPORT_TO_FILE_H

class DocumentModelExport;
class QTextStream;

/// Strategy class for exporting to a file. This strategy is external to the Document class so that class is simpler.
class ExportToFile
{
public:
  /// Single constructor.
  ExportToFile();

  /// Export Document points according to the settings.
  void exportToFile (DocumentModelExport &modelExport,
                     QTextStream &str) const;
};

#endif // EXPORT_TO_FILE_H
