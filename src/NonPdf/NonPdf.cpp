/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DlgImportCroppingNonPdf.h"
#include "ImportCroppingUtilNonPdf.h"
#include "NonPdf.h"
#include <QApplication>
#include <QImage>
#include <QString>

NonPdf::NonPdf ()
{
}

NonPdfReturn NonPdf::load (const QString &fileName,
                           QImage &image,
                           ImportCropping importCropping,
                           bool isErrorReportRegressionTest) const
{
  ImportCroppingUtilNonPdf importCroppingUtil;
  bool cropping = importCroppingUtil.applyImportCropping (isErrorReportRegressionTest,
                                                          importCropping);

  NonPdfReturn rtn;
  QApplication::setOverrideCursor(Qt::BusyCursor); // Since loading can be slow
  if (cropping) {

    rtn = loadWithCropping (fileName,
                            image);

  } else {

    rtn = loadWithoutCropping (fileName,
                               image);

  }
  QApplication::restoreOverrideCursor();

  return rtn;
}

NonPdfReturn NonPdf::loadWithCropping (const QString &fileName,
                                       QImage &image) const
{
  NonPdfReturn nonPdfReturn = NON_PDF_RETURN_FAILED;

  // Get page and extent. At this point it is always true that the image can be read
  DlgImportCroppingNonPdf dlg (fileName);
  if (dlg.exec() == QDialog::Accepted) {

    // Returned image is null if it could not be read
    image = dlg.image ();

    if (!image.isNull()) {
      nonPdfReturn = NON_PDF_RETURN_SUCCESS;
    }

  } else {
    nonPdfReturn = NON_PDF_RETURN_CANCELED;
  }

  return nonPdfReturn;
}

NonPdfReturn NonPdf::loadWithoutCropping (const QString &fileName,
                                          QImage &image) const
{
  NonPdfReturn nonPdfReturn = NON_PDF_RETURN_FAILED;

  if (image.load (fileName)) {
    nonPdfReturn = NON_PDF_RETURN_SUCCESS;
  }

  return nonPdfReturn;
}
