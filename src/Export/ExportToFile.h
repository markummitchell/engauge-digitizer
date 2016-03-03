/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef EXPORT_TO_FILE_H
#define EXPORT_TO_FILE_H

#include <QStringList>

class Document;
class DocumentModelExportFormat;
class MainWindowModel;
class QTextStream;
class Transformation;

enum ExportToFileExtension {
  EXPORT_TO_FILE_EXTENSION_CSV,
  EXPORT_TO_FILE_EXTENSION_TSV,
  EXPORT_TO_FILE_EXTENSION_DEFAULT
};

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
                     const MainWindowModel &modelMainWindow,
                     const Transformation &transformation,
                     QTextStream &str) const;

  /// File extension for csv export files
  QString fileExtensionCsv () const;

  /// File extension for tsv export files
  QString fileExtensionTsv () const;

  /// QFileDialog filter for CSV files
  QString filterCsv () const;

  /// QFileDialog filter for TSV files
  QString filterTsv () const;

};

#endif // EXPORT_TO_FILE_H
