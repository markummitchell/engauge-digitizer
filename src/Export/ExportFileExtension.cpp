/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ExportFileExtension.h"
#include "ExportFileExtensionOverride.h"
#include "ExportToFile.h"
#include <QObject>

QString exportFileExtensionToFilename (ExportFileExtension exportFileExtension)
{
  QString rtn; // Empty value (only occurring if corrupted input) will be handled as EXPORT_FILE_EXTENSION_NOT_CSV_TSV:
  ExportToFile exportStrategy;
  ExportFileExtensionOverride extensionOverride;
  
  switch (exportFileExtension)
  {
  case EXPORT_FILE_EXTENSION_CSV:
    rtn = extensionOverride.extensionWithPeriodCsv (exportStrategy);
    break;

  case EXPORT_FILE_EXTENSION_NOT_CSV_TSV:
    // Empty value will not be considered as csv or tsv file name
    break;

  case EXPORT_FILE_EXTENSION_TSV:
    rtn = extensionOverride.extensionWithPeriodTsv (exportStrategy);
    break;
  }

  return rtn;
}

QString exportFileExtensionToPreviewString (ExportFileExtension exportFileExtension)
{
  QString rtn (QObject::tr ("Preview"));
  
  switch (exportFileExtension)
  {
  case EXPORT_FILE_EXTENSION_CSV:
    rtn = QString (QObject::tr ("Preview for CSV files:"));
    break;

  case EXPORT_FILE_EXTENSION_NOT_CSV_TSV:
    rtn = QString (QObject::tr ("Preview for files without CSV or TSV:"));
    break;    

  case EXPORT_FILE_EXTENSION_TSV:
    rtn = QString (QObject::tr ("Preview for TSV files:"));
    break;
  }

  return rtn;
}
