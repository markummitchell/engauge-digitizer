/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ColorConstants.h"
#include "ColorFilter.h"
#include "ColorFilterStrategyForeground.h"
#include "ColorFilterStrategyHue.h"
#include "ColorFilterStrategyIntensity.h"
#include "ColorFilterStrategySaturation.h"
#include "ColorFilterStrategyValue.h"
#include "EngaugeAssert.h"
#include "mmsubs.h"
#include <QDebug>
#include <qmath.h>
#include <QImage>

ColorFilter::ColorFilter()
{
  createStrategies ();
}

ColorFilter::~ColorFilter()
{
  qDeleteAll (m_strategies);
}

bool ColorFilter::colorCompare (QRgb rgb1,
                                QRgb rgb2) const
{
  const long MASK = 0xf0f0f0f0;
  return (rgb1 & MASK) == (rgb2 & MASK);
}

void ColorFilter::createStrategies ()
{
  m_strategies [COLOR_FILTER_MODE_FOREGROUND] = new ColorFilterStrategyForeground ();
  m_strategies [COLOR_FILTER_MODE_HUE       ] = new ColorFilterStrategyHue        ();
  m_strategies [COLOR_FILTER_MODE_INTENSITY ] = new ColorFilterStrategyIntensity  ();
  m_strategies [COLOR_FILTER_MODE_SATURATION] = new ColorFilterStrategySaturation ();
  m_strategies [COLOR_FILTER_MODE_VALUE     ] = new ColorFilterStrategyValue      ();
}

void ColorFilter::filterImage (const QImage &imageOriginal,
                               QImage &imageFiltered,
                               ColorFilterMode colorFilterMode,
                               double low,
                               double high,
                               QRgb rgbBackground)
{
  ENGAUGE_ASSERT (imageOriginal.width () == imageFiltered.width());
  ENGAUGE_ASSERT (imageOriginal.height() == imageFiltered.height());
  ENGAUGE_ASSERT (imageFiltered.format () == QImage::Format_RGB32);

  for (int x = 0; x < imageOriginal.width(); x++) {
    for (int y = 0; y < imageOriginal.height (); y++) {

      QColor pixel = imageOriginal.pixel (x, y);
      bool isOn = false;
      if (pixel.rgb() != rgbBackground) {

        isOn = pixelUnfilteredIsOn (colorFilterMode,
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

QRgb ColorFilter::marginColor(const QImage *image) const
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
  ColorFilterEntry entryMax;
  entryMax.count = 0;
  for (ColorList::const_iterator itr = colorCounts.begin (); itr != colorCounts.end (); itr++) {
    if ((*itr).count > entryMax.count) {
      entryMax = *itr;
    }
  }

  return entryMax.color.rgb();
}

void ColorFilter::mergePixelIntoColorCounts (QRgb pixel,
                                             ColorList &colorCounts) const
{
  ColorFilterEntry entry;
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

bool ColorFilter::pixelFilteredIsOn (const QImage &image,
                                     int x,
                                     int y) const
{
  bool rtn = false;

  if ((0 <= x) &&
      (0 <= y) &&
      (x < image.width()) &&
      (y < image.height())) {

    // Pixel is on if it is closer to black than white in gray scale. This test must be performed
    // on little endian and big endian systems, with or without alpha bits (which are typically high bits);
    const int BLACK_WHITE_THRESHOLD = 255 / 2; // Put threshold in middle of range
    int gray = qGray (pixelRGB (image, x, y));
    rtn = (gray < BLACK_WHITE_THRESHOLD);

  }

  return rtn;
}

bool ColorFilter::pixelUnfilteredIsOn (ColorFilterMode colorFilterMode,
                                       const QColor &pixel,
                                       QRgb rgbBackground,
                                       double low0To1,
                                       double high0To1) const
{
  bool rtn = false;

  double s = pixelToZeroToOneOrMinusOne (colorFilterMode,
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

double ColorFilter::pixelToZeroToOneOrMinusOne (ColorFilterMode colorFilterMode,
                                                const QColor &pixel,
                                                QRgb rgbBackground) const
{
  if (m_strategies.contains (colorFilterMode)) {

    // Ignore false positive cmake compiler warning about -Wreturn-stack-address in next line (bug #26396)
    const ColorFilterStrategyAbstractBase *strategy = m_strategies [colorFilterMode];
    return strategy->pixelToZeroToOne (pixel,
                                       rgbBackground);

  } else {

    ENGAUGE_ASSERT (false);
    return 0.0;

  }
}

int ColorFilter::zeroToOneToValue (ColorFilterMode colorFilterMode,
                                   double s) const
{
  if (m_strategies.contains (colorFilterMode)) {

    const ColorFilterStrategyAbstractBase *strategy = m_strategies [colorFilterMode];
    return strategy->zeroToOneToValue (s);

  } else {

    ENGAUGE_ASSERT (false);
    return 0;

  }
}
