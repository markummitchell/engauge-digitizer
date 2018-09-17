/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

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

QPixmap FilterImage::filter (bool isGnuplot,
                             const QImage &imageUnfiltered,
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
  
  GridRemoval gridRemoval (isGnuplot);
  QPixmap pixmapFiltered = gridRemoval.remove (transformation,
                                               modelGridRemoval,
                                               imageFiltered);

  return pixmapFiltered;
}


