/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DocumentModelExportFormat.h"
#include "ExportFileExtensionOverride.h"
#include "ExportToFile.h"

ExportFileExtensionOverride::ExportFileExtensionOverride()
{
}

ExportFileExtensionOverride::~ExportFileExtensionOverride()
{
}

QString ExportFileExtensionOverride::extensionWithPeriodCsv (const ExportToFile &exportStrategy) const
{
  return QString (".%1")
    .arg (exportStrategy.fileExtensionCsv());
}

QString ExportFileExtensionOverride::extensionWithPeriodTsv (const ExportToFile &exportStrategy) const
{
  return QString (".%1")
    .arg (exportStrategy.fileExtensionTsv());
}

DocumentModelExportFormat ExportFileExtensionOverride::modelExportOverride (const DocumentModelExportFormat &modelBefore,
                                                                            const ExportToFile &exportStrategy,
                                                                            const QString &fileName) const
{
  DocumentModelExportFormat modelAfter = modelBefore;

  // See if delimiter setting overrides commas/tabs for files with csv/tsv file extensions respectively
  if (!modelAfter.overrideCsvTsv()) {

    // Extract file extensions
    QString csvExtension = extensionWithPeriodCsv (exportStrategy);
    QString tsvExtension = extensionWithPeriodTsv (exportStrategy);
    QString fileExtensionVersusCsv = fileName.right (csvExtension.size());
    QString fileExtensionVersusTsv = fileName.right (tsvExtension.size());

    // Override if CSV or TSV was selected. We cannot use QFileDialog::selectedNameFilter() since that is
    // broken in Linux, so we use the file extension
    if (csvExtension.compare (fileExtensionVersusCsv, Qt::CaseInsensitive) == 0) {
      modelAfter.setDelimiter (EXPORT_DELIMITER_COMMA);
    } else if (tsvExtension.compare (fileExtensionVersusTsv, Qt::CaseInsensitive) == 0) {
      modelAfter.setDelimiter (EXPORT_DELIMITER_TAB);
    }
  }

  return modelAfter;
}
