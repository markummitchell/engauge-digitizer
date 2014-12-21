#ifndef GRID_CLASSIFIER_H
#define GRID_CLASSIFIER_H

class QPixmap;
class Transformation;

// Number of histogram bins could be so large that each bin corresponds to one pixel, but computation time may then be
// too slow when doing the correleations later on
const int NUM_HISTOGRAM_BINS = 400;

/// Classify the grid pattern in an original image.
///
/// This class uses the following tricks for faster performance:
/// -# FFT is used for "fast correlations" in frequency space rather than graph space
/// -# FFT initialization/shutdown housekeeping is done once
/// -# Rather than a combinatorial search of grid line start, step and count, we exploit the periodicity
///    of the FFT to search start and step as the first step, and then as a separate second step we
///    search count. In the first step, the periodicity means the repeating grid lines wrap around the
///    end of the end of the image back around to the start of the image - so the grid line count is
///    not even relevant. In other words, the searches are START X STEP + COUNT rather than
///    START X STEP X COUNT
class GridClassifier
{
public:
  /// Single constructor.
  GridClassifier();

  /// Classify the specified image, and return the most probably x and y grid settings.
  void classify (const QPixmap &originalPixmap,
                 const Transformation &transformation,
                 int &countX,
                 double &startX,
                 double &stepX,
                 int &countY,
                 double &startY,
                 double &stepY);

private:

  void classify();
  void computeGraphCoordinateLimits (const QImage &image,
                                     const Transformation &transformation,
                                     double &xMin,
                                     double &xMax,
                                     double &yMin,
                                     double &yMax);
  void initializeHistogramBins ();
  void loadPicketFence (double picketFence [NUM_HISTOGRAM_BINS],
                        int binStart,
                        int binStep,
                        int count,
                        bool isCount);
  void populateHistogramBins (const QImage &image,
                              const Transformation &transformation,
                              double xMin,
                              double xMax,
                              double yMin,
                              double yMax);
  void searchCountSpace (double bins [NUM_HISTOGRAM_BINS],
                         double binStart,
                         double binStep,
                         int &countMax);
  void searchStartStepSpace (double xMin,
                             double xMax,
                             double yMin,
                             double yMax,
                             double &startX,
                             double &stepX,
                             double &startY,
                             double &stepY,
                             double &binStartX,
                             double &binStepX,
                             double &binStartY,
                             double &binStepY);

  double m_binsX [NUM_HISTOGRAM_BINS];
  double m_binsY [NUM_HISTOGRAM_BINS];
};

#endif // GRID_CLASSIFIER_H
