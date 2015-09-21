#include "ColorFilter.h"
#include "DocumentModelColorFilter.h"
#include "DocumentModelGridRemoval.h"
#include "FilterImage.h"
#include "GridRemoval.h"
#include "Logger.h"
#include <QImage>
#include <QPixmap>
#include "Transformation.h"

FilterImage::FilterImage ()
{
}

QPixmap FilterImage::filter (const QImage &imageUnfiltered,
                             const Transformation &transformation,
                             const QString &curveSelected,
                             const DocumentModelColorFilter &modelColorFilter,
                             const DocumentModelGridRemoval &modelGridRemoval) const
{
  // Filtered image
  ColorFilter filter;
  QImage imageFiltered (imageUnfiltered.width (),
                        imageUnfiltered.height (),
                        QImage::Format_RGB32);
  QRgb rgbBackground = filter.marginColor (&imageUnfiltered);
  filter.filterImage (imageUnfiltered,
                      imageFiltered,
                      modelColorFilter.colorFilterMode(curveSelected),
                      modelColorFilter.low(curveSelected),
                      modelColorFilter.high(curveSelected),
                      rgbBackground);
  
  GridRemoval gridRemoval;
  QPixmap pixmapFiltered = gridRemoval.remove (transformation,
                                               modelGridRemoval,
                                               imageFiltered);

  return pixmapFiltered;
}


