#ifndef GRID_CLASSIFIER_H
#define GRID_CLASSIFIER_H

class QPixmap;
class Transformation;

// Number of histogram bins could be so large that each bin corresponds to one pixel, but computation time may then be
// too slow when doing the correleations later on
const int NUM_HISTOGRAM_BINS = 400;

/// Classify the grid pattern in an original image
class GridClassifier
{
public:
  /// Single constructor.
  GridClassifier(const QPixmap &originalPixmap,
                 const Transformation &transformation);

private:
  GridClassifier();

  void classify();

  double m_binsX [NUM_HISTOGRAM_BINS];
  double m_binsY [NUM_HISTOGRAM_BINS];
};

#endif // GRID_CLASSIFIER_H
