/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ImportImageExtensions.h"
#ifdef ENGAUGE_JPEG2000
#include "Jpeg2000.h"
#endif // ENGAUGE_JPEG2000
#include <QByteArray>
#include <QImageReader>
#include <QList>

ImportImageExtensions::ImportImageExtensions ()
{
}

QStringList ImportImageExtensions::fileExtensionsWithAsterisks () const
{
    // Compile a list of supported formats into a filter
    QList<QByteArray>::const_iterator itr;
    QList<QByteArray> supportedImageFormats = QImageReader::supportedImageFormats();
    QStringList supportedImageFormatStrings;
    for (itr = supportedImageFormats.begin (); itr != supportedImageFormats.end (); itr++) {
      QByteArray arr = *itr;
      QString extensionAsWildcard = QString ("*.%1").arg (QString (arr));
      supportedImageFormatStrings << extensionAsWildcard;
    }
#ifdef ENGAUGE_JPEG2000
    Jpeg2000 jpeg2000;
    supportedImageFormatStrings << jpeg2000.supportedImageWildcards();
#endif // ENGAUGE_JPEG2000

#ifdef ENGAUGE_PDF
    supportedImageFormatStrings << "*.pdf";
#endif // ENGAUGE_PDF

    supportedImageFormatStrings.sort();

    return supportedImageFormatStrings;
}

bool ImportImageExtensions::offers (const QString &fileExtension) const
{
  QString valueToTest = QString ("*.%1").arg (fileExtension.toLower());

  return fileExtensionsWithAsterisks().contains (valueToTest);
}
