/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef EXPORT_IMAGE_FOR_REGRESSION_H
#define EXPORT_IMAGE_FOR_REGRESSION_H

class QPixmap;
class QString;

/// Class for exporting during regression, when the Transformation has not yet been defined. This class just
/// exports the image size
class ExportImageForRegression
{
 public:
  /// Single constructor
  ExportImageForRegression(const QPixmap &pixmap);

  /// Export to the specified file. This is called when the Transformation has not been defined
  void fileExport (const QString &filename) const;

 private:
  ExportImageForRegression();

  const int m_width;
  const int m_height;
};

#endif // EXPORT_IMAGE_FOR_REGRESSION_H
