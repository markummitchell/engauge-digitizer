#ifndef GRID_CLASSIFIER_H
#define GRID_CLASSIFIER_H

#include "ColorFilterHistogram.h"

class QPixmap;
class Transformation;

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
  void classify (bool isGnuplot,
                 const QPixmap &originalPixmap,
                 const Transformation &transformation,
                 int &countX,
                 double &startX,
                 double &stepX,
                 int &countY,
                 double &startY,
                 double &stepY);

private:

  // Number of histogram bins could be so large that each bin corresponds to one pixel, but computation time may then be
  // too slow when doing the correleations later on
  static int NUM_PIXELS_PER_HISTOGRAM_BINS;

  static int MIN_STEP_PIXELS;
  static double PEAK_HALF_WIDTH;
  static int BIN_START_UNSHIFTED;

  int binFromCoordinate (double coord,
                         double coordMin,
                         double coordMax) const; // Inverse of coordinateFromBin
  void classify();
  void computeGraphCoordinateLimits (const QImage &image,
                                     const Transformation &transformation,
                                     double &xMin,
                                     double &xMax,
                                     double &yMin,
                                     double &yMax);
  double coordinateFromBin (int bin,
                            double coordMin,
                            double coordMax) const; // Inverse of binFromCoordinate
  void copyVectorToVector (const double from [],
                           double to []) const;
  void dumpGnuplotCoordinate (const QString &coordinateLabel,
                              double corr,
                              const double *bins,
                              double coordinateMin,
                              double coordinateMax,
                              int binStart,
                              int binStep) const;
  void dumpGnuplotCorrelations (const QString &coordinateLabel,
                                double valueMin,
                                double valueMax,
                                const double signalA [],
                                const double signalB [],
                                const double correlationsMax []);
  void initializeHistogramBins ();
  void loadPicketFence (double picketFence [],
                        int binStart,
                        int binStep,
                        int count,
                        bool isCount) const;
  void populateHistogramBins (const QImage &image,
                              const Transformation &transformation,
                              double xMin,
                              double xMax,
                              double yMin,
                              double yMax);
  void searchCountSpace (double bins [],
                         double binStart,
                         double binStep,
                         int &countMax);
  void searchStartStepSpace (bool isGnuplot,
                             double bins [],
                             const QString &coordinateLabel,
                             double valueMin,
                             double valueMax,
                             double &start,
                             double &step,
                             double &binStart,
                             double &binStep);

  double *m_binsX;
  double *m_binsY;

  int m_numHistogramBins; // More bins improve accuracy but slow computation. Controlled by NUM_PIXELS_PER_HISTOGRAM_BINS
};

#endif // GRID_CLASSIFIER_H
