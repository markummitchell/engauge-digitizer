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
  QPixmap filter (const QImage &imageUnfiltered,
                  const Transformation &transformation,
                  const QString &curveSelected,
                  const DocumentModelColorFilter &modelColorFilter,
                  const DocumentModelGridRemoval &modelGridRemoval) const;
};

#endif // FILTER_IMAGE_H
