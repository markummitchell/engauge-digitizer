/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef COLOR_FILTER_HISTOGRAM_H
#define COLOR_FILTER_HISTOGRAM_H

#include <QRgb>

class ColorFilter;
class QColor;
class QImage;

/// Class that generates a histogram according to the current filter.
class ColorFilterHistogram
{
public:
  /// Single constructor
  ColorFilterHistogram();

  /// Compute histogram bin number from pixel according to filter
  int binFromPixel (const ColorFilter &filter,
                    ColorFilterMode colorFilterMode,
                    const QColor &pixel,
                    const QRgb &rgbBackground) const;

  /// Generate the histogram. The resolution is coarse since
  /// -# finer resolution is not needed
  /// -# this smooths out the curve
  void generate (const ColorFilter &filter,
                 double histogramBins [],
                 ColorFilterMode colorFilterMode,
                 const QImage &image,
                 int &maxBinCount) const;

  /// Number of histogram bins
  static int HISTOGRAM_BINS () { return 100; }

  /// Inverse of binFromPixel
  int valueFromBin (const ColorFilter &filter,
                    ColorFilterMode colorFilterMode,
                    int bin);

private:

  static int FIRST_NON_EMPTY_BIN_AT_START () { return 1; }
  static int LAST_NON_EMPTY_BIN_AT_END () { return ColorFilterHistogram::HISTOGRAM_BINS () - 2; }
};

#endif // COLOR_FILTER_HISTOGRAM_H
