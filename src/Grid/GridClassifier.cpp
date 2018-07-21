/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ColorFilter.h"
#include "Correlation.h"
#include "DocumentModelCoords.h"
#include "EngaugeAssert.h"
#include "GridClassifier.h"
#include <iostream>
#include "Logger.h"
#include <QDebug>
#include <QFile>
#include <QImage>
#include "QtToString.h"
#include "Transformation.h"

int GridClassifier::NUM_PIXELS_PER_HISTOGRAM_BINS = 1;
double GridClassifier::PEAK_HALF_WIDTH = 4;
int GridClassifier::MIN_STEP_PIXELS = 4 * GridClassifier::PEAK_HALF_WIDTH; // Step includes down ramp, flat part, up ramp
const QString GNUPLOT_DELIMITER ("\t");

// We set up the picket fence with binStart arbitrarily set close to zero. Peak is
// not exactly at zero since we want to include the left side of the first peak.
int GridClassifier::BIN_START_UNSHIFTED = GridClassifier::PEAK_HALF_WIDTH;

using namespace std;

GridClassifier::GridClassifier()
{
}

int GridClassifier::binFromCoordinate (double coord,
                                       double coordMin,
                                       double coordMax) const
{
  ENGAUGE_ASSERT (coordMin < coordMax);
  ENGAUGE_ASSERT (coordMin <= coord);
  ENGAUGE_ASSERT (coord <= coordMax);

  int bin = 0.5 + (m_numHistogramBins - 1.0) * (coord - coordMin) / (coordMax - coordMin);

  return bin;
}

void GridClassifier::classify (bool isGnuplot,
                               const QPixmap &originalPixmap,
                               const Transformation &transformation,
                               int &countX,
                               double &startX,
                               double &stepX,
                               int &countY,
                               double &startY,
                               double &stepY)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridClassifier::classify";

  QImage image = originalPixmap.toImage ();

  m_numHistogramBins = image.width() / NUM_PIXELS_PER_HISTOGRAM_BINS;
  ENGAUGE_ASSERT (m_numHistogramBins > 1);

  double xMin, xMax, yMin, yMax;
  double binStartX, binStepX, binStartY, binStepY;

  m_binsX = new double [m_numHistogramBins];
  m_binsY = new double [m_numHistogramBins];

  computeGraphCoordinateLimits (image,
                                transformation,
                                xMin,
                                xMax,
                                yMin,
                                yMax);
  initializeHistogramBins ();
  populateHistogramBins (image,
                         transformation,
                         xMin,
                         xMax,
                         yMin,
                         yMax);
  searchStartStepSpace (isGnuplot,
                        m_binsX,
                        "x",
                        xMin,
                        xMax,
                        startX,
                        stepX,
                        binStartX,
                        binStepX);
  searchStartStepSpace (isGnuplot,
                        m_binsY,
                        "y",
                        yMin,
                        yMax,
                        startY,
                        stepY,
                        binStartY,
                        binStepY);
  searchCountSpace (m_binsX,
                    binStartX,
                    binStepX,
                    countX);
  searchCountSpace (m_binsY,
                    binStartY,
                    binStepY,
                    countY);

  delete [] m_binsX;
  delete [] m_binsY;
}

void GridClassifier::computeGraphCoordinateLimits (const QImage &image,
                                                   const Transformation &transformation,
                                                   double &xMin,
                                                   double &xMax,
                                                   double &yMin,
                                                   double &yMax)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridClassifier::computeGraphCoordinateLimits";

  // Project every pixel onto the x axis, and onto the y axis. One set of histogram bins will be
  // set up along each of the axes. The range of bins will encompass every pixel in the image, and no more.

  QPointF posGraphTL, posGraphTR, posGraphBL, posGraphBR;
  transformation.transformScreenToRawGraph (QPointF (0, 0)                         , posGraphTL);
  transformation.transformScreenToRawGraph (QPointF (image.width(), 0)             , posGraphTR);
  transformation.transformScreenToRawGraph (QPointF (0, image.height())            , posGraphBL);
  transformation.transformScreenToRawGraph (QPointF (image.width(), image.height()), posGraphBR);

  // Compute x and y ranges for setting up the histogram bins
  if (transformation.modelCoords().coordsType() == COORDS_TYPE_CARTESIAN) {

    // For affine cartesian coordinates, we only need to look at the screen corners
    xMin = qMin (qMin (qMin (posGraphTL.x(), posGraphTR.x()), posGraphBL.x()), posGraphBR.x());
    xMax = qMax (qMax (qMax (posGraphTL.x(), posGraphTR.x()), posGraphBL.x()), posGraphBR.x());
    yMin = qMin (qMin (qMin (posGraphTL.y(), posGraphTR.y()), posGraphBL.y()), posGraphBR.y());
    yMax = qMax (qMax (qMax (posGraphTL.y(), posGraphTR.y()), posGraphBL.y()), posGraphBR.y());

  } else {

    // For affine polar coordinates, easiest approach is to assume the full circle
    xMin = 0.0;
    xMax = transformation.modelCoords().thetaPeriod();
    yMin = transformation.modelCoords().originRadius();
    yMax = qMax (qMax (qMax (posGraphTL.y(), posGraphTR.y()), posGraphBL.y()), posGraphBR.y());

  }

  ENGAUGE_ASSERT (xMin < xMax);
  ENGAUGE_ASSERT (yMin < yMax);
}

double GridClassifier::coordinateFromBin (int bin,
                                          double coordMin,
                                          double coordMax) const
{
  ENGAUGE_ASSERT (1 < m_numHistogramBins);
  ENGAUGE_ASSERT (coordMin < coordMax);

  return coordMin + (coordMax - coordMin) * (double) bin / ((double) m_numHistogramBins - 1.0);
}

void GridClassifier::copyVectorToVector (const double from [],
                                         double to []) const
{
  for (int bin = 0; bin < m_numHistogramBins; bin++) {
    to [bin] = from [bin];
  }
}

void GridClassifier::dumpGnuplotCoordinate (const QString &coordinateLabel,
                                            double corr,
                                            const double *bins,
                                            double coordinateMin,
                                            double coordinateMax,
                                            int binStart,
                                            int binStep) const
{
  QString filename = QString ("gridclassifier_%1_corr%2_startMax%3_stepMax%4.gnuplot")
                            .arg (coordinateLabel)
                            .arg (corr, 8, 'f', 3, '0')
                            .arg (binStart)
                            .arg (binStep);

  cout << "Writing gnuplot file: " << filename.toLatin1().data() << "\n";

  QFile fileDump (filename);
  fileDump.open (QIODevice::WriteOnly | QIODevice::Text);
  QTextStream strDump (&fileDump);

  int bin;

  // For consistent scaling, get the max bin count
  int binCountMax = 0;
  for (bin = 0; bin < m_numHistogramBins; bin++) {
    if (bins [bin] > binCountMax) {
      binCountMax = qMax ((double) binCountMax,
                          bins [bin]);
    }
  }

  // Get picket fence
  double *picketFence = new double [m_numHistogramBins];
  loadPicketFence (picketFence,
                   binStart,
                   binStep,
                   0,
                   false);

  // Header
  strDump << "bin"
          << GNUPLOT_DELIMITER << "coordinate"
          << GNUPLOT_DELIMITER << "binCount"
          << GNUPLOT_DELIMITER << "startStep"
          << GNUPLOT_DELIMITER << "picketFence" << "\n";

  // Data, with one row per coordinate value
  for (bin = 0; bin < m_numHistogramBins; bin++) {

    double coordinate = coordinateFromBin (bin,
                                           coordinateMin,
                                           coordinateMax);
    double startStepValue (((bin - binStart) % binStep == 0) ? 1 : 0);
    strDump << bin
            << GNUPLOT_DELIMITER << coordinate
            << GNUPLOT_DELIMITER << bins [bin]
            << GNUPLOT_DELIMITER << binCountMax * startStepValue
            << GNUPLOT_DELIMITER << binCountMax * picketFence [bin] << "\n";
  }

  delete [] picketFence;
}

void GridClassifier::dumpGnuplotCorrelations (const QString &coordinateLabel,
                                              double valueMin,
                                              double valueMax,
                                              const double signalA [],
                                              const double signalB [],
                                              const double correlations [])
{
  QString filename = QString ("gridclassifier_%1_correlations.gnuplot")
                            .arg (coordinateLabel);

  cout << "Writing gnuplot file: " << filename.toLatin1().data() << "\n";

  QFile fileDump (filename);
  fileDump.open (QIODevice::WriteOnly | QIODevice::Text);
  QTextStream strDump (&fileDump);

  int bin;

  // Compute max values so curves can be normalized to the same heights
  double signalAMax = 1, signalBMax = 1, correlationsMax = 1;
  for (bin = 0; bin < m_numHistogramBins; bin++) {
    if (bin == 0 || signalA [bin] > signalAMax) {
      signalAMax = signalA [bin];
    }
    if (bin == 0 || signalB [bin] > signalBMax) {
      signalBMax = signalB [bin];
    }
    if (bin == 0 || correlations [bin] > correlationsMax) {
      correlationsMax = correlations [bin];
    }
  }

  // Prevent divide by zero error
  if (signalAMax == 0) {
    signalAMax = 1.0;
  }
  if (signalBMax == 0) {
    signalBMax = 1.0;
  }
  
  // Output normalized curves
  for (int bin = 0; bin < m_numHistogramBins; bin++) {

    strDump << coordinateFromBin (bin,
                                  valueMin,
                                  valueMax)
            << GNUPLOT_DELIMITER << signalA [bin] / signalAMax
            << GNUPLOT_DELIMITER << signalB [bin] / signalBMax
            << GNUPLOT_DELIMITER << correlations [bin] / correlationsMax << "\n";
  }
}

void GridClassifier::initializeHistogramBins ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridClassifier::initializeHistogramBins";

  for (int bin = 0; bin < m_numHistogramBins; bin++) {
    m_binsX [bin] = 0;
    m_binsY [bin] = 0;
  }
}

void GridClassifier::loadPicketFence (double picketFence [],
                                      int binStart,
                                      int binStep,
                                      int count,
                                      bool isCount) const
{
  const double PEAK_HEIGHT = 1.0; // Arbitrary height, since normalization will counteract any change to this value

  // Count argument is optional. Note that binStart already excludes PEAK_HALF_WIDTH bins at start,
  // and we also exclude PEAK_HALF_WIDTH bins at the end
  ENGAUGE_ASSERT (binStart >= PEAK_HALF_WIDTH);
  ENGAUGE_ASSERT (binStep != 0);
  if (!isCount) {
    count = 1 + (m_numHistogramBins - binStart - PEAK_HALF_WIDTH) / binStep;
  }

  // Bins that we need to worry about
  int binStartMinusHalfWidth = binStart - PEAK_HALF_WIDTH;
  int binStopPlusHalfWidth = (binStart + (count - 1) * binStep) + PEAK_HALF_WIDTH;

  // To normalize, we compute the area under the picket fence. Constraint is
  // areaUnnormalized + NUM_HISTOGRAM_BINS * normalizationOffset = 0
  double areaUnnormalized = count * PEAK_HEIGHT * PEAK_HALF_WIDTH;
  double normalizationOffset = -1.0 * areaUnnormalized / m_numHistogramBins;

  for (int bin = 0; bin < m_numHistogramBins; bin++) {

    // Outside of the peaks, bin is small negative so correlation with unit function is zero. In other
    // words, the function is normalized
    picketFence [bin] = normalizationOffset;

    if ((binStartMinusHalfWidth <= bin) &&
        (bin <= binStopPlusHalfWidth)) {

      // Closest peak
      int ordinalClosestPeak = (int) ((bin - binStart + binStep / 2) / binStep);
      int binClosestPeak = binStart + ordinalClosestPeak * binStep;

      // Distance from closest peak is used to define an isosceles triangle
      int distanceToClosestPeak = qAbs (bin - binClosestPeak);

      if (distanceToClosestPeak < PEAK_HALF_WIDTH) {

        // Map 0 to PEAK_HALF_WIDTH to 1 to 0
        picketFence [bin] = 1.0 - (double) distanceToClosestPeak / PEAK_HALF_WIDTH + normalizationOffset;

      }
    }
  }
}

void GridClassifier::populateHistogramBins (const QImage &image,
                                            const Transformation &transformation,
                                            double xMin,
                                            double xMax,
                                            double yMin,
                                            double yMax)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridClassifier::populateHistogramBins";

  ColorFilter filter;
  QRgb rgbBackground = filter.marginColor (&image);

  for (int x = 0; x < image.width(); x++) {
    for (int y = 0; y < image.height(); y++) {

      QColor pixel = image.pixel (x, y);

      // Skip pixels with background color
      if (!filter.colorCompare (rgbBackground,
                                pixel.rgb ())) {

        // Add this pixel to histograms
        QPointF posGraph;
        transformation.transformScreenToRawGraph (QPointF (x, y), posGraph);

        if (transformation.modelCoords().coordsType() == COORDS_TYPE_POLAR) {

          // If out of the 0 to period range, the theta value must shifted by the period to get into that range
          while (posGraph.x() < xMin) {
            posGraph.setX (posGraph.x() + transformation.modelCoords().thetaPeriod());
          }
          while (posGraph.x() > xMax) {
            posGraph.setX (posGraph.x() - transformation.modelCoords().thetaPeriod());
          }
        }

        int binX = binFromCoordinate (posGraph.x(), xMin, xMax);
        int binY = binFromCoordinate (posGraph.y(), yMin, yMax);

        ENGAUGE_ASSERT (0 <= binX);
        ENGAUGE_ASSERT (0 <= binY);
        ENGAUGE_ASSERT (binX < m_numHistogramBins);
        ENGAUGE_ASSERT (binY < m_numHistogramBins);

        // Roundoff error in log scaling may let bin go just outside legal range
        binX = qMin (binX, m_numHistogramBins - 1);
        binY = qMin (binY, m_numHistogramBins - 1);

        ++m_binsX [binX];
        ++m_binsY [binY];
      }
    }
  }
}

void GridClassifier::searchCountSpace (double bins [],
                                       double binStart,
                                       double binStep,
                                       int &countMax)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridClassifier::searchCountSpace"
                              << " start=" << binStart
                              << " step=" << binStep;

  // Loop though the space of possible counts
  Correlation correlation (m_numHistogramBins);
  double *picketFence = new double [m_numHistogramBins];
  double corr, corrMax;
  bool isFirst = true;
  int countStop = 1 + (m_numHistogramBins - binStart) / binStep;
  for (int count = 2; count <= countStop; count++) {

    loadPicketFence (picketFence,
                     binStart,
                     binStep,
                     count,
                     true);

    correlation.correlateWithoutShift (m_numHistogramBins,
                                       bins,
                                       picketFence,
                                       corr);
    if (isFirst || (corr > corrMax)) {
      countMax = count;
      corrMax = corr;
    }

    isFirst = false;
  }

  delete [] picketFence;
}

void GridClassifier::searchStartStepSpace (bool isGnuplot,
                                           double bins [],
                                           const QString &coordinateLabel,
                                           double valueMin,
                                           double valueMax,
                                           double &start,
                                           double &step,
                                           double &binStartMax,
                                           double &binStepMax)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridClassifier::searchStartStepSpace";

  // Correlations are tracked for logging
  double *signalA = new double [m_numHistogramBins];
  double *signalB = new double [m_numHistogramBins];
  double *correlations = new double [m_numHistogramBins];
  double *correlationsMax = new double [m_numHistogramBins];

  // Loop though the space of possible gridlines using the independent variables (start,step).
  Correlation correlation (m_numHistogramBins);
  double *picketFence = new double [m_numHistogramBins];
  int binStart;
  double corr = 0, corrMax = 0;
  bool isFirst = true;

  // We do not explicitly search(=loop) through binStart here, since Correlation::correlateWithShift will take
  // care of that for us

  // Step search starts out small, and stops at value that gives count substantially greater than 2. Freakishly small
  // images need to have MIN_STEP_PIXELS overridden so the loop iterates at least once
  binStartMax = BIN_START_UNSHIFTED + 1; // In case search below ever fails
  binStepMax = qMin (MIN_STEP_PIXELS, m_numHistogramBins / 8); // In case search below ever fails
  for (int binStep = qMin (MIN_STEP_PIXELS, m_numHistogramBins / 8); binStep < m_numHistogramBins / 4; binStep++) {

    loadPicketFence (picketFence,
                     BIN_START_UNSHIFTED,
                     binStep,
                     PEAK_HALF_WIDTH,
                     false);

    correlation.correlateWithShift (m_numHistogramBins,
                                    bins,
                                    picketFence,
                                    binStart,
                                    corr,
                                    correlations);
    if (isFirst || (corr > corrMax)) {

      int binStartMaxNext = binStart + BIN_START_UNSHIFTED + 1; // Compensate for the shift performed inside loadPicketFence

      // Make sure binStartMax never goes out of bounds
      if (binStartMaxNext < m_numHistogramBins) {

        binStartMax = binStartMaxNext;
        binStepMax = binStep;
        corrMax = corr;
        copyVectorToVector (bins, signalA);
        copyVectorToVector (picketFence, signalB);
        copyVectorToVector (correlations, correlationsMax);

        // Output a gnuplot file. We should see the correlation values consistently increasing
        if (isGnuplot) {

           dumpGnuplotCoordinate(coordinateLabel,
                                 corr,
                                 bins,
                                 valueMin,
                                 valueMax,
                                 binStart,
                                 binStep);
        }
      }
    }

    isFirst = false;
  }

  // Convert from bins back to graph coordinates
  start = coordinateFromBin (binStartMax,
                             valueMin,
                             valueMax);
  if (binStartMax + binStepMax < m_numHistogramBins) {

    // Normal case where a reasonable step value is being calculated
    double next = coordinateFromBin (binStartMax + binStepMax,
                                     valueMin,
                                     valueMax);
    step = next - start;
  } else {

    // Pathological case where step jumps to outside the legal range. We bring the step back into range
    double next = coordinateFromBin (m_numHistogramBins - 1,
                                     valueMin,
                                     valueMax);
    step = next - start;
  }

  if (isGnuplot) {
    dumpGnuplotCorrelations (coordinateLabel,
                             valueMin,
                             valueMax,
                             signalA,
                             signalB,
                             correlationsMax);
  }

  delete [] signalA;
  delete [] signalB;
  delete [] correlations;
  delete [] correlationsMax;
  delete [] picketFence;
}
