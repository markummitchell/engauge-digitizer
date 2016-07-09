/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ImportCroppingUtilPdf.h"
#include "poppler-qt5.h"
#include <QSettings>
#include "Settings.h"

using namespace Poppler;

ImportCroppingUtilPdf::ImportCroppingUtilPdf()
{
}

bool ImportCroppingUtilPdf::applyImportCropping (bool isErrorReportRegressionTest,
                                                 const QString &fileName,
                                                 Document *&document) const
{
  document = 0;

  bool cropping = false;

  if (!isErrorReportRegressionTest) {

    // Simple check to prevent complaints from poppler code
    if (fileName.right (4).toLower () == ".pdf") {

      // Try to read the file
      document = Document::load (fileName);
      if (document != 0) {
        if (!document->isLocked ()) {

          QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
          settings.beginGroup (SETTINGS_GROUP_MAIN_WINDOW);

          ImportCropping importCroppingInput = (ImportCropping) settings.value (SETTINGS_IMPORT_CROPPING,
                                                                                QVariant (DEFAULT_IMPORT_CROPPING)).toInt();

          cropping = (importCroppingInput == IMPORT_CROPPING_ALWAYS ||
                      (importCroppingInput == IMPORT_CROPPING_MULTIPAGE_PDFS && document->numPages () > 1));
        }
      }
    }
  }

  return cropping;
}
