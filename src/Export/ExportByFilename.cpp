/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DocumentModelExportFormat.h"
#include "ExportByFilename.h"
#include "ExportToFile.h"

ExportByFilename::ExportByFilename()
{
}

ExportByFilename::~ExportByFilename()
{
}

DocumentModelExportFormat ExportByFilename::modelExportOverride (const DocumentModelExportFormat &modelExportFormatBefore,
                                                                 const ExportToFile &exportStrategy,
                                                                 const QString &fileName) const
{
  DocumentModelExportFormat modelExportFormatAfter = modelExportFormatBefore;

  // See if delimiter setting overrides commas/tabs for files with csv/tsv file extensions respectively
  if (!modelExportFormatAfter.overrideCsvTsv()) {

    // Extract file extensions
    QString csvExtension = QString (".%1")
                           .arg (exportStrategy.fileExtensionCsv());
    QString tsvExtension = QString (".%1")
                           .arg (exportStrategy.fileExtensionTsv());
    QString fileExtensionVersusCsv = fileName.right (csvExtension.size());
    QString fileExtensionVersusTsv = fileName.right (tsvExtension.size());

    // Override if CSV or TSV was selected. We cannot use QFileDialog::selectedNameFilter() since that is
    // broken in Linux, so we use the file extension
    if (csvExtension.compare (fileExtensionVersusCsv, Qt::CaseInsensitive) == 0) {
      modelExportFormatAfter.setDelimiter (EXPORT_DELIMITER_COMMA);
    } else if (tsvExtension.compare (fileExtensionVersusTsv, Qt::CaseInsensitive) == 0) {
      modelExportFormatAfter.setDelimiter (EXPORT_DELIMITER_TAB);
    }
  }

  return modelExportFormatAfter;
}
