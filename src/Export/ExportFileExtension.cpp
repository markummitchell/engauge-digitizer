/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ExportFileExtension.h"

QString exportFileExtensionToFilename (ExportFileExtension exportFileExtension)
{
  QString rtn = "?";

  switch (exportFileExtension)
  {
  case EXPORT_FILE_EXTENSION_CSV:
    rtn = ".csv";
    break;

  case EXPORT_FILE_EXTENSION_NOT_CSV_TSV:
    rtn = ".txt";
    break;

  case EXPORT_FILE_EXTENSION_TSV:
    rtn = ".tsv";
    break;
  }

  return rtn;
}

QString exportFileExtensionToPreviewString (ExportFileExtension exportFileExtension)
{
  QString rtn = "?";
  
  switch (exportFileExtension)
  {
  case EXPORT_FILE_EXTENSION_CSV:
    rtn = "Preview for CSV files";
    break;

  case EXPORT_FILE_EXTENSION_NOT_CSV_TSV:
    rtn = "Preview for files without CSV or TSV";
    break;    

  case EXPORT_FILE_EXTENSION_TSV:
    rtn = "Preview for TSV files";
    break;
  }

  return rtn;
}
