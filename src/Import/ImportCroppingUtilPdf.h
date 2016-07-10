/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef IMPORT_CROPPING_UTIL_PDF_H
#define IMPORT_CROPPING_UTIL_PDF_H

#include "ImportCropping.h"
#include "ImportCroppingUtilBase.h"
#include <QString>

namespace Poppler {
  class Document;
}

/// Import of pdf files
class ImportCroppingUtilPdf : public ImportCroppingUtilBase
{
public:
  /// Single constructor
  ImportCroppingUtilPdf();

  /// For pdf files, skip cropping dialog during regression testing, otherwise crop if it is always turned on or if 
  /// there are multiple pages.
  ///
  /// For speed, the Document is returned if cropping is to be performed so the file needs to be read only once
  bool applyImportCropping (bool isRegression,
                            const QString &fileName,
                            ImportCropping importCropping,
                            Poppler::Document *&document) const;

};

#endif // IMPORT_CROPPING_UTIL_PDF_H
