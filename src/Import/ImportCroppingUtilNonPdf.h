/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef IMPORT_CROPPING_UTIL_NON_PDF_H
#define IMPORT_CROPPING_UTIL_NON_PDF_H

#include "ImportCropping.h"
#include "ImportCroppingUtilBase.h"

/// Import of non-pdf files
class ImportCroppingUtilNonPdf : public ImportCroppingUtilBase
{
public:
  /// Single constructor
  ImportCroppingUtilNonPdf();

  /// Skip cropping dialog during regression testing, otherwise crop if it is always turned on
  bool applyImportCropping (bool isRegression,
                            ImportCropping importCropping) const;

};

#endif // IMPORT_CROPPING_UTIL_NON_PDF_H
