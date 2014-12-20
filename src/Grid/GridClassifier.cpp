#include "Correlation.h"
#include "Filter.h"
#include "GridClassifier.h"
#include <QDebug>
#include <QPixmap>
#include "QtToString.h"
#include "Transformation.h"

const int MIN_STEP_PIXELS = 5;

GridClassifier::GridClassifier(const QPixmap &originalPixmap,
                               const Transformation &transformation)
{
  QImage image = originalPixmap.toImage ();

  int bin;
  for (bin = 0; bin < NUM_HISTOGRAM_BINS; bin++) {
    m_binsX [bin] = 0;
    m_binsY [bin] = 0;
  }

  // Project every pixel onto the x axis, and onto the y axis. One set of histogram bins will be
  // set up along each of the axes. The range of bins will encompass every pixel in the image, and no more.

  QPointF posGraphTL, posGraphTR, posGraphBL, posGraphBR;
  transformation.transform (QPointF (0, 0)                         , posGraphTL);
  transformation.transform (QPointF (image.width(), 0)             , posGraphTR);
  transformation.transform (QPointF (0, image.height())            , posGraphBL);
  transformation.transform (QPointF (image.width(), image.height()), posGraphBR);

  // Since transformation is affine (linear rather than quadratic), we only need to look at the screen corners to
  // get the domains of x and y
  double xMin = qMin (qMin (qMin (posGraphTL.x(), posGraphTR.x()), posGraphBL.x()), posGraphBR.x());
  double xMax = qMax (qMax (qMax (posGraphTL.x(), posGraphTR.x()), posGraphBL.x()), posGraphBR.x());
  double yMin = qMin (qMin (qMin (posGraphTL.y(), posGraphTR.y()), posGraphBL.y()), posGraphBR.y());
  double yMax = qMax (qMax (qMax (posGraphTL.y(), posGraphTR.y()), posGraphBL.y()), posGraphBR.y());

  Q_ASSERT (xMin < xMax);
  Q_ASSERT (yMin < yMax);

  Filter filter;
  QRgb rgbBackground = filter.marginColor (&image);

  for (int x = 0; x < image.width(); x++) {
    for (int y = 0; y < image.height(); y++) {

      QColor pixel = image.pixel (x, y);

      // Skip pixels with background color
      if (!filter.colorCompare (rgbBackground,
                               pixel.rgb ())) {

        // Add this pixel to histograms
        QPointF posGraph;
        transformation.transform (QPointF (x, y), posGraph);
        int binX = (NUM_HISTOGRAM_BINS - 1.0) * (posGraph.x() - xMin) / (xMax - xMin);
        int binY = (NUM_HISTOGRAM_BINS - 1.0) * (posGraph.y() - yMin) / (yMax - yMin);

        Q_ASSERT (binX < NUM_HISTOGRAM_BINS);
        Q_ASSERT (binY < NUM_HISTOGRAM_BINS);

        ++m_binsX [binX];
        ++m_binsY [binY];
      }
    }
  }

  // Loop though the space of possible gridlines using the independent variables (start,step,count).
  // An FFT is used to compute the best matching step size, and then the start and count are optimized.
  Correlation correlation (NUM_HISTOGRAM_BINS);
  double picketFence [NUM_HISTOGRAM_BINS];
  int binStartX, binStartY;
  int binStartXMax, binStartYMax;
  int binStepXMax, binStepYMax;
  double corrX, corrY, corrXMax, corrYMax;
  bool isFirst = true;
  for (int binStep = MIN_STEP_PIXELS; binStep < NUM_HISTOGRAM_BINS; binStep++) {
    for (int bin = 0; bin < NUM_HISTOGRAM_BINS; bin++) {

      if (bin % binStep) {
        picketFence [bin] = 1.0;
      } else {
        picketFence [bin] = 0.0;
      }
    }

    correlation.correlate (NUM_HISTOGRAM_BINS,
                           m_binsX,
                           picketFence,
                           binStartX,
                           corrX);
    correlation.correlate (NUM_HISTOGRAM_BINS,
                           m_binsY,
                           picketFence,
                           binStartY,
                           corrY);
    if (isFirst || (corrX > corrXMax)) {
      binStartXMax = binStartX;
      binStepXMax = binStep;
      corrXMax = corrX;
    }
    if (isFirst || (corrY > corrYMax)) {
      binStartYMax = binStartY;
      binStepYMax = binStep;
      corrYMax = corrY;
    }
    isFirst = false;
  }

  qDebug() << binStartXMax << " " << binStepXMax << " "
           << binStartYMax << " " << binStepYMax;
}
