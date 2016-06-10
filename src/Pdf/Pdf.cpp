/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Pdf.h"
#include "poppler-qt5.h"
#include <QImage>
#include <QString>

using namespace Poppler;

Pdf::Pdf ()
{
}

bool Pdf::load (const QString &fileName,
                QImage &image,
                int resolution) const
{
  bool success = false;
  const int FIRST_PAGE = 0;
  const int X_TOP_LEFT = 0, Y_TOP_LEFT = 0;
  const int WIDTH = -1, HEIGHT = -1; // Negative values give full page

  // Try to read the file
  Document *document = Document::load (fileName);

  if (document != 0) {
    if (!document->isLocked ()) {

      Page *page = document->page (FIRST_PAGE);
      if (page != 0) {

        image = page->renderToImage (resolution,
                                     resolution,
                                     X_TOP_LEFT,
                                     Y_TOP_LEFT,
                                     WIDTH,
                                     HEIGHT);
        if (!image.isNull ()) {

          // Success!
          success = true;
        }

        delete page;
      }
    }

    delete document;
  }

  return success;
}
