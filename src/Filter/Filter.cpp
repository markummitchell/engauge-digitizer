#include "Filter.h"
#include <QDebug>
#include <qmath.h>
#include <QImage>

Filter::Filter()
{
}

bool Filter::colorCompare (QRgb rgb1,
                           QRgb rgb2) const
{
  const long MASK = 0xf0f0f0f0;
  return (rgb1 & MASK) == (rgb2 & MASK);
}

void Filter::filterImage (const QImage &imageOriginal,
                          QImage &imageFiltered,
                          FilterParameter filterParameter,
                          double low,
                          double high,
                          QRgb rgbBackground)
{
  Q_ASSERT (imageOriginal.width () == imageFiltered.width());
  Q_ASSERT (imageOriginal.height() == imageFiltered.height());
  Q_ASSERT (imageFiltered.format () == QImage::Format_RGB32);

  for (int x = 0; x < imageOriginal.width(); x++) {
    for (int y = 0; y < imageOriginal.height (); y++) {

      QColor pixel = imageOriginal.pixel (x, y);
      bool isOn = false;
      if (pixel.rgb() != rgbBackground) {

        isOn = pixelIsOn (filterParameter,
                          pixel,
                          rgbBackground,
                          low,
                          high);
      }

      imageFiltered.setPixel (x, y, (isOn ?
                                     QColor (Qt::black).rgb () :
                                     QColor (Qt::white).rgb ()));
    }
  }
}

QRgb Filter::marginColor(const QImage *image)
{
  // Add unique colors to colors list
  ColorList colorCounts;
  for (int x = 0; x < image->width (); x++) {
    mergePixelIntoColorCounts (image->pixel (x, 0), colorCounts);
    mergePixelIntoColorCounts (image->pixel (x, image->height () - 1), colorCounts);
  }
  for (int y = 0; y < image->height (); y++) {
    mergePixelIntoColorCounts (image->pixel (0, y), colorCounts);
    mergePixelIntoColorCounts (image->pixel (image->width () - 1, y), colorCounts);
  }

  // Margin color is the most frequent color
  FilterColorEntry entryMax;
  entryMax.count = 0;
  for (ColorList::const_iterator itr = colorCounts.begin (); itr != colorCounts.end (); itr++) {
    if ((*itr).count > entryMax.count) {
      entryMax = *itr;
    }
  }

  return entryMax.color.rgb();
}

void Filter::mergePixelIntoColorCounts (QRgb pixel,
                                        ColorList &colorCounts)
{
  FilterColorEntry entry;
  entry.color = pixel;
  entry.count = 0;

  // Look for previous entry
  bool found = false;
  for (ColorList::iterator itr = colorCounts.begin (); itr != colorCounts.end (); itr++) {
    if (colorCompare (entry.color.rgb(),
                      (*itr).color.rgb())) {
      found = true;
      ++(*itr).count;
      break;
    }
  }

  if (!found) {
    colorCounts.append (entry);
  }
}

bool Filter::pixelIsOn (FilterParameter filterParameter,
                        const QColor &pixel,
                        QRgb rgbBackground,
                        double low0To1,
                        double high0To1)
{
  bool rtn = false;

  double s = pixelToZeroToOneOrMinusOne (filterParameter,
                                         pixel,
                                         rgbBackground);
  if (s >= 0.0) {
    if (low0To1 <= high0To1) {

      // Single valid range
      rtn = (low0To1 <= s) && (s <= high0To1);

    } else {

      // Two ranges
      rtn = (s <= high0To1) || (low0To1 <= s);

    }
  }

  return rtn;
}

double Filter::pixelToZeroToOneOrMinusOne (FilterParameter filterParameter,
                                           const QColor &pixel,
                                           QRgb rgbBackground)
{
  double s = 0.0;

  switch (filterParameter) {
    case FILTER_PARAMETER_FOREGROUND:
      {
        double distance = qSqrt (pow (pixel.red()   - qRed   (rgbBackground), 2) +
                                 pow (pixel.green() - qGreen (rgbBackground), 2) +
                                 pow (pixel.blue()  - qBlue  (rgbBackground), 2));
        s = distance / qSqrt (255.0 * 255.0 + 255.0 * 255.0 + 255.0 * 255.0);
      }
      break;

    case FILTER_PARAMETER_HUE:
      {
        s = pixel.hueF();
        if (s < 0) {
          // Color is achromatic (r=g=b) so it has no hue
        }
      }
      break;

    case FILTER_PARAMETER_INTENSITY:
      {
        double distance = qSqrt (pow (pixel.red(), 2) +
                                 pow (pixel.green(), 2) +
                                 pow (pixel.blue(), 2));
        s = distance / qSqrt (255 * 255 + 255 * 255 + 255 * 255);
      }
      break;

    case FILTER_PARAMETER_SATURATION:
      s = pixel.saturationF();
      break;

    case FILTER_PARAMETER_VALUE:
      s = pixel.valueF();
      break;

    default:
      Q_ASSERT (false);
  }

  return s;
}
