#include "EngaugeAssert.h"
#include "Filter.h"
#include "FilterHistogram.h"
#include <QImage>

const int FIRST_NON_EMPTY_BIN_AT_START = 1;
const int LAST_NON_EMPTY_BIN_AT_END = HISTOGRAM_BINS - 2;

FilterHistogram::FilterHistogram()
{
}

int FilterHistogram::binFromPixel (const Filter &filter,
                                   FilterMode filterMode,
                                   const QColor &pixel,
                                   const QRgb &rgbBackground) const
{
  // Instead of mapping from s=0 through 1 to bin=0 through HISTOGRAM_BINS-1, we
  // map it to bin=1 through HISTOGRAM_BINS-2 so first and last bin are zero. The
  // result is a peak at the start or end is complete and easier to read
  double s = filter.pixelToZeroToOneOrMinusOne (filterMode,
                                                pixel,
                                                rgbBackground);
  ENGAUGE_ASSERT (s <= 1.0);

  int bin = -1;

  if (s >= 0) {

    bin = FIRST_NON_EMPTY_BIN_AT_START + s * (LAST_NON_EMPTY_BIN_AT_END - FIRST_NON_EMPTY_BIN_AT_START);

  }

  return bin;
}

void FilterHistogram::generate (const Filter &filter,
                                double histogramBins [],
                                FilterMode filterMode,
                                const QImage &image,
                                int &maxBinCount) const
{
  // Initialize histogram bins
  int bin;
  for (bin = 0; bin < HISTOGRAM_BINS; bin++) {
    histogramBins [bin] = 0;
  }

  QRgb rgbBackground = filter.marginColor(&image);

  // Populate histogram bins
  maxBinCount = 0;
  for (int x = 0; x < image.width(); x++) {
    for (int y = 0; y < image.height(); y++) {

      QColor pixel (image.pixel (x, y));
      int bin = binFromPixel (filter,
                              filterMode,
                              pixel,
                              rgbBackground);
      if (bin >= 0) {

        ENGAUGE_ASSERT ((FIRST_NON_EMPTY_BIN_AT_START <= bin) &&
                  (LAST_NON_EMPTY_BIN_AT_END >= bin));
        ++(histogramBins [bin]);

        if (histogramBins [bin] > maxBinCount) {
          maxBinCount = histogramBins [bin];
        }
      }
    }
  }
}

int FilterHistogram::valueFromBin (const Filter &filter,
                                   FilterMode filterMode,
                                   int bin)
{
  // Just do everything in binFromPixel backwards
  double s = (double) (bin - FIRST_NON_EMPTY_BIN_AT_START) / (double) (LAST_NON_EMPTY_BIN_AT_END - FIRST_NON_EMPTY_BIN_AT_START);
  s = qMin (qMax (s, 0.0), 1.0);

  return filter.zeroToOneToValue (filterMode,
                                  s);
}
