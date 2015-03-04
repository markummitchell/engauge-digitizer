#ifndef COLOR_FILTER_HISTOGRAM_H
#define COLOR_FILTER_HISTOGRAM_H

#include <QRgb>

const int HISTOGRAM_BINS = 100;

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

  /// Inverse of binFromPixel
  int valueFromBin (const ColorFilter &filter,
                    ColorFilterMode colorFilterMode,
                    int bin);
};

#endif // COLOR_FILTER_HISTOGRAM_H
