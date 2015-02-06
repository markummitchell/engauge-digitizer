#ifndef FILTER_HISTOGRAM_H
#define FILTER_HISTOGRAM_H

#include "DocumentModelFilter.h"
#include <QRgb>

const int HISTOGRAM_BINS = 100;

class QColor;
class QImage;

/// Class that generates a histogram according to the current filter.
class FilterHistogram
{
public:
  /// Single constructor
  FilterHistogram();

  /// Compute histogram bin number from pixel according to filter
  int binFromPixel (Filter &filter,
                    FilterMode filterMode,
                    const QColor &pixel,
                    const QRgb &rgbBackground) const;

  /// Generate the histogram. The resolution is coarse since
  /// -# finer resolution is not needed
  /// -# this smooths out the curve
  void generate (Filter &filter,
                 double histogramBins [],
                 FilterMode filterMode,
                 const QImage &image,
                 int &maxBinCount) const;

  /// Inverse of binFromPixel
  int valueFromBin (Filter &filter,
                    FilterMode filterMode,
                    int bin);
};

#endif // FILTER_HISTOGRAM_H
