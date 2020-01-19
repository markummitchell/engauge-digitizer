/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef EXPORT_BY_FILENAME_H
#define EXPORT_BY_FILENAME_H

class DocumentModelExportFormat;
class ExportToFile;
class QString;

/// Utility class for adjusting export settings given filename extension
class ExportByFilename
{
public:
  /// Single constructor.
  ExportByFilename();
  virtual ~ExportByFilename ();

  /// Adjust export settings given filename extension
  DocumentModelExportFormat modelExportOverride (const DocumentModelExportFormat &modelExportFormatBefore,
                                                 const ExportToFile &exportStrategy,
                                                 const QString &selectedNameFilter) const; 
};

#endif // EXPORT_BY_FILENAME_H
