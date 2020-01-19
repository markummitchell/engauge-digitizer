/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef EXPORT_FILE_EXTENSION_OVERRIDE_H
#define EXPORT_FILE_EXTENSION_OVERRIDE_H

#include <QString>

class DocumentModelExportFormat;
class ExportToFile;

/// Utility class for adjusting export settings given filename extension
class ExportFileExtensionOverride
{
public:
  /// Single constructor.
  ExportFileExtensionOverride();
  virtual ~ExportFileExtensionOverride ();

  /// Extension for csv file with period
  QString extensionWithPeriodCsv (const ExportToFile &exportStrategy) const;

  /// Extension for tsv file with period
  QString extensionWithPeriodTsv (const ExportToFile &exportStrategy) const; 
  
  /// Adjust export settings given filename extension
  DocumentModelExportFormat modelExportOverride (const DocumentModelExportFormat &modelExportFormatBefore,
                                                 const ExportToFile &exportStrategy,
                                                 const QString &selectedNameFilter) const; 
};

#endif // EXPORT_FILE_EXTENSION_OVERRIDE_H
