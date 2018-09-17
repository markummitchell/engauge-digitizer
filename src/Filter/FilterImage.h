/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef FILTER_IMAGE_H
#define FILTER_IMAGE_H

#include <QPixmap>

class DocumentModelColorFilter;
class DocumentModelGridRemoval;
class QImage;
class Transformation;

/// Filters an image using a combination of color filtering and grid removal
class FilterImage
{
 public:
  /// Single constructor
  FilterImage();

  /// Filter original unfiltered image into filtered pixmap
  QPixmap filter (bool isGnuplot,
                  const QImage &imageUnfiltered,
                  const Transformation &transformation,
                  const QString &curveSelected,
                  const DocumentModelColorFilter &modelColorFilter,
                  const DocumentModelGridRemoval &modelGridRemoval) const;
};

#endif // FILTER_IMAGE_H
