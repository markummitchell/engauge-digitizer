/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef EXPORT_FILE_EXTENSION_H
#define EXPORT_FILE_EXTENSION_H

#include <QString>

enum ExportFileExtension {
  EXPORT_FILE_EXTENSION_CSV,
  EXPORT_FILE_EXTENSION_TSV,
  EXPORT_FILE_EXTENSION_NOT_CSV_TSV  
};

/// Internally-used sample file name for each ExportFileExtension value
extern QString exportFileExtensionToFilename (ExportFileExtension exportFileExtension);

/// Displayed text for each ExportFileExtension value
extern QString exportFileExtensionToPreviewString (ExportFileExtension exportFileExtension);

#endif // EXPORT_FILE_EXTENSION_H
