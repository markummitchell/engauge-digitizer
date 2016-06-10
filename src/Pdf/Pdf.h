/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef PDF_H
#define PDF_H

class QImage;
class QString;

/// Wrapper around the Poppler library. Engauge uses that library to read and import PDF files.
///
/// This class is only compiled and linked in when ENGAUGE_PDF is defined, since it links to the optional poppler library.
class Pdf
{
public:
  /// Single constructor
  Pdf();

  /// Try to load the specified file. Success is indicated in the function return value
  bool load (const QString &fileName,
             QImage &image,
             int resolution) const;

private:

};

#endif // PDF_H
