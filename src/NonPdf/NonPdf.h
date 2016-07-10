/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef NON_PDF_H
#define NON_PDF_H

#include "ImportCropping.h"

namespace Poppler {
  class Document;
}
class QImage;
class QString;

/// Return values from load operation
enum NonPdfReturn {
  NON_PDF_RETURN_CANCELED,
  NON_PDF_RETURN_FAILED,
  NON_PDF_RETURN_SUCCESS
};

/// Wrapper around the QImage class for read and importing non-PDF files.
class NonPdf
{
public:
  /// Single constructor
  NonPdf();

  /// Try to load the specified file. Success is indicated in the function return value
  NonPdfReturn load (const QString &fileName,
                     QImage &image,
                     ImportCropping importCropping,
                     bool isErrorReportRegressionTest) const;

private:

  NonPdfReturn loadWithCropping (const QString &fileName,
                                 QImage &image) const; // Dialog is used when not testing
  NonPdfReturn loadWithoutCropping (const QString &fileName,
                                    QImage &image) const; // No dialog is used during testing. Entire image will be loadedd

};

#endif // NON_PDF_H
