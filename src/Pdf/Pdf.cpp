/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DlgPdfFrame.h"
#include "ImportCroppingUtilPdf.h"
#include "Pdf.h"
#include "poppler-qt5.h"
#include <QImage>
#include <QString>

using namespace Poppler;

const int X_TOP_LEFT = 0, Y_TOP_LEFT = 0;
const int WIDTH = -1, HEIGHT = -1; // Negative values give full page
const int FIRST_PAGE_1_BASED = 1;

Pdf::Pdf ()
{
}

PdfReturn Pdf::load (const QString &fileName,
                     QImage &image,
                     int resolution,
                     bool isErrorReportRegressionTest) const
{
  Document *document = 0;

  ImportCroppingUtilPdf importCroppingUtil;
  bool cropping = importCroppingUtil.applyImportCropping (isErrorReportRegressionTest,
                                                          fileName,
                                                          document);

  PdfReturn rtn;
  if (cropping) {

    rtn = loadWithCropping (document,
                            image,
                            resolution);

  } else {

    rtn = loadWithoutCropping (fileName,
                               image,
                               resolution);

  }

  if (document != 0) {
    delete document;
  }

  return rtn;
}

PdfReturn Pdf::loadWithCropping (Document *document,
                                 QImage &image,
                                 int resolution) const
{
  PdfReturn pdfReturn = PDF_RETURN_FAILED;

  // Get page and extent
  DlgPdfFrame dlg (*document,
                   resolution);
  if (dlg.exec() == QDialog::Accepted) {

    // Returned image is null if it could not be read
    image = dlg.image ();

    if (!image.isNull()) {
      pdfReturn = PDF_RETURN_SUCCESS;
    }

  } else {
    pdfReturn = PDF_RETURN_CANCELED;
  }

  return pdfReturn;
}

PdfReturn Pdf::loadWithoutCropping (const QString &fileName,
                                    QImage &image,
                                    int resolution) const
{
  PdfReturn pdfReturn = PDF_RETURN_FAILED;

  // Simple check to prevent complaints from poppler code
  if (fileName.right (4).toLower () == ".pdf") {

    // Try to read the file
    Document *document = Document::load (fileName);

    if (document != 0) {
      if (!document->isLocked ()) {

        Page *page = document->page (FIRST_PAGE_1_BASED - 1);
        if (page != 0) {

          image = page->renderToImage (resolution,
                                       resolution,
                                       X_TOP_LEFT,
                                       Y_TOP_LEFT,
                                       WIDTH,
                                       HEIGHT);

          if (!image.isNull()) {
            pdfReturn = PDF_RETURN_SUCCESS;
          }

          delete page;
        }
      }

      delete document;
    }
  }

  return pdfReturn;
}
