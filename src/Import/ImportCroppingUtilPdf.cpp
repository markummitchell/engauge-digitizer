/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ImportCroppingUtilPdf.h"
#include "poppler-qt5.h"
#include <QApplication>

using namespace Poppler;

ImportCroppingUtilPdf::ImportCroppingUtilPdf()
{
}

bool ImportCroppingUtilPdf::applyImportCropping (bool isErrorReportRegressionTest,
                                                 const QString &fileName,
                                                 ImportCropping importCropping,
                                                 Document *&document) const
{
  document = nullptr;

  bool cropping = false;

  if (!isErrorReportRegressionTest) {

    // Simple check to prevent complaints from poppler code
    if (fileName.right (4).toLower () == ".pdf") {

      // Try to read the file
      QApplication::setOverrideCursor (Qt::BusyCursor); // Since load could take a while
      document = Document::load (fileName);
      QApplication::restoreOverrideCursor();
      if (document != nullptr) {
        if (!document->isLocked ()) {

          cropping = (importCropping == IMPORT_CROPPING_ALWAYS ||
                      (importCropping == IMPORT_CROPPING_MULTIPAGE_PDFS && document->numPages () > 1));
        }
      }
    }
  }

  return cropping;
}
