#include "ColorFilter.h"
#include "DocumentModelPointMatch.h"
#include "EngaugeAssert.h"
#include <iostream>
#include "Logger.h"
#include "PointMatchAlgorithm.h"
#include <QFile>
#include <QImage>
#include <qmath.h>
#include <QTextStream>

using namespace std;

#define DUMP_TO_GNUPLOT true

#define FOLD2DINDEX(i,j,jmax) ((i)*(jmax)+j)

PointMatchAlgorithm::PointMatchAlgorithm()
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointMatchAlgorithm::PointMatchAlgorithm";
}

void PointMatchAlgorithm::allocateMemory(double** array,
                                         fftw_complex** arrayPrime,
                                         int width,
                                         int height)
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointMatchAlgorithm::allocateMemory";

  *array = new double [width * height];
  ENGAUGE_CHECK_PTR(*array);

  *arrayPrime = new fftw_complex [width * height];
  ENGAUGE_CHECK_PTR(*arrayPrime);
}

void PointMatchAlgorithm::assembleLocalMaxima(double* image,
                                              double* sample, 
                                              double* convolution, 
                                              PointMatchList& listCreated, 
                                              int width,
                                              int height,
                                              int sampleXCenter,
                                              int sampleYCenter,
                                              int sampleXExtent,
                                              int sampleYExtent)
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointMatchAlgorithm::assembleLocalMaxima";

  // Ignore tiny correlation values near zero by applying this threshold
  const double SINGLE_PIXEL_CORRELATION = 1.0;

  int iDeltaMin = xDeltaMin(sampleXCenter);
  int iDeltaMax = xDeltaMax(sampleXCenter, sampleXExtent);
  int jDeltaMin = yDeltaMin(sampleYCenter);
  int jDeltaMax = yDeltaMax(sampleYCenter, sampleYExtent);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {

      double convIJ = convolution[FOLD2DINDEX(i, j, height)];

      // Loop through neighboring points
      bool isLocalMax = true;
      for (int iDelta= iDeltaMin; iDelta < iDeltaMax; iDelta++) {

        int iNeighbor = i + iDelta;
        if ((0 <= iNeighbor) && (iNeighbor < width)) {

          for (int jDelta = jDeltaMin; jDelta < jDeltaMax; jDelta++) {

            int jNeighbor = j + jDelta;
            if ((0 <= jNeighbor) && (jNeighbor < height)) {

              if ((convolution [FOLD2DINDEX(iNeighbor, jNeighbor, height)] >= convIJ) &&
                  (iNeighbor != i || jNeighbor != j)) {

                isLocalMax = false;
                break;
              }
            }
          }
        }
      }
          
      if (isLocalMax && (convIJ > SINGLE_PIXEL_CORRELATION)) {

        // Save new local maximum

        int x = i + sampleXCenter;
        int y = j + sampleYCenter;

        // Correlation stored in convIJ is not used since fast convolution is meant to be performed once (it is global and slow),
        // and later on we may want to redo local correlations when a maximum is removed and it overlaps another maxima. So, the
        // manually-computed correlation value is assigned to this maximum. Computation of manual convolutions is not too slow
        // because there are typically less than 200 of them
        double corr = correlation(image,
                                  sample,
                                  width,
                                  height,
                                  x,
                                  y,
                                  sampleXCenter,
                                  sampleYCenter,
                                  sampleXExtent,
                                  sampleYExtent);

        PointMatchTriplet t (x,
                             y,
                             corr);

        listCreated.append(t);
      }
    }
  }
}

void PointMatchAlgorithm::computeConvolution(fftw_complex* imagePrime,
                                             fftw_complex* samplePrime,
                                             int width, int height,
                                             double** convolution)
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointMatchAlgorithm::computeConvolution";

  fftw_complex* convolutionPrime;

  allocateMemory(convolution,
                 &convolutionPrime,
                 width,
                 height);

  // Perform in-place conjugation of the sample since equation is F-1 {F(f) * F*(g)}
  conjugateMatrix(width,
                  height,
                  samplePrime);

  // Perform the convolution in transform space
  multiplyMatrices(width,
                   height,
                   imagePrime,
                   samplePrime,
                   convolutionPrime);

  // Backward transform the convolution
  fftw_plan pConvolution = fftw_plan_dft_c2r_2d(width,
                                                height,
                                                convolutionPrime,
                                                *convolution,
                                                FFTW_ESTIMATE);

  fftw_execute (pConvolution);

  releasePhaseArray(convolutionPrime);
}

void PointMatchAlgorithm::conjugateMatrix(int width,
                                          int height,
                                          fftw_complex* matrix)
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointMatchAlgorithm::conjugateMatrix";

  ENGAUGE_CHECK_PTR(matrix);

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {

      int index = FOLD2DINDEX(x, y, height);
      matrix [index] [1] = -1.0 * matrix [index] [1];
    }
  }
}

double PointMatchAlgorithm::correlation(double* image,
                                        double* sample,
                                        int width,
                                        int height,
                                        int x,
                                        int y,
                                        int sampleXCenter,
                                        int sampleYCenter,
                                        int sampleXExtent,
                                        int sampleYExtent)
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointMatchAlgorithm::correlation";

  ENGAUGE_CHECK_PTR(image);
  ENGAUGE_CHECK_PTR(sample);

  int iDeltaMin = xDeltaMin(sampleXCenter);
  int iDeltaMax = xDeltaMax(sampleXCenter, sampleXExtent);
  int jDeltaMin = yDeltaMin(sampleYCenter);
  int jDeltaMax = yDeltaMax(sampleYCenter, sampleYExtent);

  // Highest correlation value corresponds to image pixels centered around (x,y) matching the sample pixels centered
  // around (sampleXCenter,sampleYCenter)
  double sum = 0.0;
  for (int iDelta = iDeltaMin; iDelta < iDeltaMax; iDelta++) {

    int iImage = x + iDelta;
    int iSample = sampleXCenter + iDelta; // assumes sample starts at lowest row
    if ((0 <= iImage) && (iImage < width)) {

      for (int jDelta = jDeltaMin; jDelta < jDeltaMax; jDelta++) {

        int jImage = y + jDelta;
        int jSample = sampleYCenter + jDelta; // assumes sample starts at lowest column
        if ((0 <= jImage) && (jImage < height)) {

          // Good correlation occurs when both pixels have the same PixelOnUnscanned value. Once an image pixel has
          // been scanned then it should be ignored
          if ((image [FOLD2DINDEX(iImage, jImage, height)] == PixelOnUnscanned) &&
              (sample [FOLD2DINDEX(iSample, jSample, height)] == PixelOnUnscanned)) {

            sum += PixelOnUnscanned;
          }
	}
      }
    }
  }

  return sum;
}

void PointMatchAlgorithm::dumpToGnuplot (double* convolution,
                                         int width,
                                         int height) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointMatchAlgorithm::dumpToGnuplot";

  QString filename ("convolution.gnuplot");
  QFile file (filename);
  if (file.open (QIODevice::WriteOnly | QIODevice::Text)) {

    QTextStream str (&file);

    str << "# I J Convolution" << endl;
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++) {

        double convIJ = convolution[FOLD2DINDEX(i, j, height)];
        str << i << " " << j << " " << convIJ << endl;
      }
    }
  }

  file.close();

  cout << "Suggested gnuplot commands" << endl;
  cout << "set dgrid3d 50,50" << endl;
  cout << "set hidden3d" << endl;
  cout << "splot """ << filename.toLatin1().data() << """ u 1:2:3 with lines" << endl;
}

QList<QPoint> PointMatchAlgorithm::findPoints (const QList<QPoint> &samplePointPixels,
                                               const QImage &imageProcessed,
                                               const DocumentModelPointMatch &modelPointMatch,
                                               const Points &pointsExisting)
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointMatchAlgorithm::findPoints"
                              << " samplePointPixels=" << samplePointPixels.count();

  // Use larger arrays for computations, if necessary, to improve fft performance
  int originalWidth = imageProcessed.width();
  int originalHeight = imageProcessed.height();
  int width = optimizeLengthForFft(originalWidth);
  int height = optimizeLengthForFft(originalHeight);

  // The untransformed (unprimed) and transformed (primed) storage arrays can be huge for big pictures, so minimize
  // the number of allocated arrays at every point in time
  double *image, *sample, *convolution;
  fftw_complex *imagePrime, *samplePrime;

  // Compute convolution=F(-1){F(image)*F(*)(sample)}
  int sampleXCenter, sampleYCenter, sampleXExtent, sampleYExtent;
  loadImage(imageProcessed,
            modelPointMatch,
            pointsExisting,
            width,
            height,
            &image,
            &imagePrime);
  loadSample(samplePointPixels,
             width,
             height,
             &sample,
             &samplePrime,
             &sampleXCenter,
             &sampleYCenter,
             &sampleXExtent,
             &sampleYExtent);
  computeConvolution(imagePrime,
                     samplePrime,
                     width,
                     height,
                     &convolution);

#ifdef DUMP_TO_GNUPLOT
  dumpToGnuplot(convolution,
                width,
                height);
#endif

  // Assemble local maxima, where each is the maxima centered in a region
  // having a width of sampleWidth and a height of sampleHeight
  PointMatchList listCreated;
  assembleLocalMaxima(image,
                      sample,
                      convolution,
                      listCreated,
                      width,
                      height,
                      sampleXCenter,
                      sampleYCenter,
                      sampleXExtent,
                      sampleYExtent);
  qSort (listCreated);

  // Copy sorted match points to output
  QList<QPoint> pointsCreated;
  PointMatchList::iterator itr;
  for (itr = listCreated.begin(); itr != listCreated.end(); itr++) {

    PointMatchTriplet triplet = *itr;
    pointsCreated.push_back (triplet.point ());

    // Current order of maxima would be fine if they never overlapped. However, they often overlap so as each
    // point is pulled off the list, and its pixels are removed from the image, we might consider updating all
    // succeeding maxima here if those maximax overlap the just-removed maxima. The maxima list is kept
    // in descending order according to correlation value
  }

  releaseImageArray(image);
  releasePhaseArray(imagePrime);
  releaseImageArray(sample);
  releasePhaseArray(samplePrime);
  releaseImageArray(convolution);

  return pointsCreated;
}

void PointMatchAlgorithm::loadImage(const QImage &imageProcessed,
                                    const DocumentModelPointMatch &modelPointMatch,
                                    const Points &pointsExisting,
                                    int width,
                                    int height,
                                    double** image,
                                    fftw_complex** imagePrime)
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointMatchAlgorithm::loadImage";

  allocateMemory(image,
                 imagePrime,
                 width,
                 height);
  
  populateImageArray(imageProcessed, 
                     width,
                     height,
                     image);

  removePixelsNearExistingPoints(*image,
                                 width,
                                 height,
                                 pointsExisting,
                                 modelPointMatch.maxPointSize());

  // Forward transform the image
  fftw_plan pImage = fftw_plan_dft_r2c_2d(width,
                                          height,
                                          *image,
                                          *imagePrime,
                                          FFTW_ESTIMATE);
  fftw_execute(pImage);
}

void PointMatchAlgorithm::loadSample(const QList<QPoint> &samplePointPixels,
                                     int width,
                                     int height,
                                     double** sample,
                                     fftw_complex** samplePrime,
                                     int* sampleXCenter,
                                     int* sampleYCenter,
                                     int* sampleXExtent,
                                     int* sampleYExtent)
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointMatchAlgorithm::loadImage";

  // Populate 2d sample array with same size (width x height) as image so fft transforms will have same
  // dimensions, which means their transforms can be multiplied element-to-element
  allocateMemory(sample, samplePrime, width, height);

  populateSampleArray(samplePointPixels,
                      width, height,
                      sample,
                      sampleXCenter,
                      sampleYCenter,
                      sampleXExtent,
                      sampleYExtent);

  // Forward transform the sample
  fftw_plan pSample = fftw_plan_dft_r2c_2d(width,
                                           height,
                                           *sample,
                                           *samplePrime,
                                           FFTW_ESTIMATE);
  fftw_execute(pSample);
}

void PointMatchAlgorithm::multiplyMatrices(int width,
                                        int height,
                                        fftw_complex* in1, 
                                        fftw_complex* in2,
                                        fftw_complex* out)
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointMatchAlgorithm::multiplyMatrices";

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {

      int index = FOLD2DINDEX(x, y, height);

      out [index] [0] = in1 [index] [0] * in2 [index] [0] - in1 [index] [1] * in2 [index] [1];
      out [index] [1] = in1 [index] [0] * in2 [index] [1] + in1 [index] [1] * in2 [index] [0];
    }
  }
}

int PointMatchAlgorithm::optimizeLengthForFft(int originalLength)
{
  // LOG4CPP_INFO_S is below

  const int INITIAL_CLOSEST_LENGTH = 0;

  // Loop through powers, looking for the lowest multiple of 2^a * 3^b * 5^c * 7^d that is at or above the original 
  // length. Since the original length is expected to usually be less than 2000, we use only the smaller primes 
  // (2, 3, 5 and 7) and ignore 11 and 13 even though fftw can benefit from those as well
  int closestLength = INITIAL_CLOSEST_LENGTH;
  for (int power2 = 1; power2 < originalLength; power2 *= 2) {
    for (int power3 = 1; power3 < originalLength; power3 *= 3) {
      for (int power5 = 1; power5 < originalLength; power5 *= 5) {
        for (int power7 = 1; power7 < originalLength; power7 *= 7) {

          int newLength = power2 * power3 * power5 * power7;
          if (originalLength <= newLength) {

            if ((closestLength == INITIAL_CLOSEST_LENGTH) ||
                (newLength < closestLength)) {

              // This is the best so far, so save it. No special weighting is given to powers of 2, although those 
              // can be more efficient than other 
              closestLength = newLength;
            }
          }
        }
      }
    }
  }

  if (closestLength == INITIAL_CLOSEST_LENGTH) {

    // No closest length was found, so just return the original length and expect slow fft performance
    closestLength = originalLength;
  }

  LOG4CPP_INFO_S ((*mainCat)) << "PointMatchAlgorithm::optimizeLengthForFft"
                              << " originalLength=" << originalLength
                              << " newLength=" << closestLength;

  return closestLength;
}

void PointMatchAlgorithm::populateImageArray(const QImage &imageProcessed,
                                             int width,
                                             int height,
                                             double** image)
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointMatchAlgorithm::populateImageArray";

  // Initialize memory with original image in real component, and imaginary component set to zero
  ColorFilter colorFilter;
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      bool pixelIsOn = colorFilter.pixelFilteredIsOn (imageProcessed,
                                                      x,
                                                      y);
      PixelStates pixelState = (pixelIsOn ?
                                  PixelOnUnscanned :
                                  PixelOff);

      (*image) [FOLD2DINDEX(x, y, height)]  = pixelState;
    }
  }
}

void PointMatchAlgorithm::populateSampleArray(const QList<QPoint> &samplePointPixels,
                                              int width,
                                              int height,
                                              double** sample,
                                              int* sampleXCenter,
                                              int* sampleYCenter,
                                              int* sampleXExtent,
                                              int* sampleYExtent)
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointMatchAlgorithm::populateSampleArray";

  // Compute bounds
  bool first = true;
  unsigned int i;
  int xMin = width, yMin = height, xMax = 0, yMax = 0;
  for (i = 0; i < (unsigned int) samplePointPixels.size(); i++) {

    int x = (samplePointPixels.at(i)).x();
    int y = (samplePointPixels.at(i)).y();
    if (first || (x < xMin))
      xMin = x;
    if (first || (x > xMax))
      xMax = x;
    if (first || (y < yMin))
      yMin = y;
    if (first || (y > yMax))
      yMax = y;

    first = false;
  }

  const int border = 1; // #pixels in border on each side

  xMin -= border;
  yMin -= border;
  xMax += border;
  yMax += border;

  // Initialize memory with original image in real component, and imaginary component set to zero
  int x, y;
  for (x = 0; x < width; x++) {
    for (y = 0; y < height; y++) {
      (*sample) [FOLD2DINDEX(x, y, height)] = PixelOff;
    }
  }

  int xSum = 0, ySum = 0;
  for (i = 0; i < (unsigned int) samplePointPixels.size(); i++) {

    // Place, quite arbitrarily, the sample image up against the top left corner
    x = (samplePointPixels.at(i)).x() - xMin;
    y = (samplePointPixels.at(i)).y() - yMin;
    ENGAUGE_ASSERT((0 < x) && (x < width));
    ENGAUGE_ASSERT((0 < y) && (y < height));
    (*sample) [FOLD2DINDEX(x, y, height)] = PixelOnUnscanned;

    xSum += x;
    ySum += y;
  }

  // Compute location of center of mass, which will represent the center of the point
  *sampleXCenter = (int) ((double) xSum / (double) samplePointPixels.size() + 0.5);
  *sampleYCenter = (int) ((double) ySum / (double) samplePointPixels.size() + 0.5);

  // Dimensions of portion of array actually used by sample (rest is empty)
  *sampleXExtent = xMax - xMin + 1;
  *sampleYExtent = yMax - yMin + 1;
}

void PointMatchAlgorithm::releaseImageArray(double* array)
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointMatchAlgorithm::releaseImageArray";

  ENGAUGE_CHECK_PTR(array);
  delete[] array;
}

void PointMatchAlgorithm::releasePhaseArray(fftw_complex* arrayPrime)
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointMatchAlgorithm::releasePhaseArray";

  ENGAUGE_CHECK_PTR(arrayPrime);
  delete[] arrayPrime;
}

void PointMatchAlgorithm::removePixelsNearExistingPoints(double* image,
                                                         int imageWidth,
                                                         int imageHeight,
                                                         const Points &pointsExisting,
                                                         int pointSeparation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "PointMatchAlgorithm::removePixelsNearExistingPoints";

  for (int i = 0; i < pointsExisting.size(); i++) {

    int xPoint = pointsExisting.at(i).posScreen().x();
    int yPoint = pointsExisting.at(i).posScreen().y();

    // Loop through rows of pixels
    int yMin = yPoint - pointSeparation;
    if (yMin < 0)
      yMin = 0;
    int yMax = yPoint + pointSeparation;
    if (imageHeight < yMax)
      yMax = imageHeight;

    for (int y = yMin; y < yMax; y++) {

      // Pythagorean theorem gives range of x values
      int radical = pointSeparation * pointSeparation - (y - yPoint) * (y - yPoint);
      if (0 < radical) {

        int xMin = (int) (xPoint - qSqrt((double) radical));
        if (xMin < 0)
          xMin = 0;
        int xMax = xPoint + (xPoint - xMin);
        if (imageWidth < xMax)
          xMax = imageWidth;

        // Turn off pixels in this row of pixels
        for (int x = xMin; x < xMax; x++) {

          if (image [FOLD2DINDEX(x, y, imageHeight)] != PixelOff) {

            image [FOLD2DINDEX(x, y, imageHeight)] = PixelOff;
          }
        }
      }
    }
  }
}

int PointMatchAlgorithm::xDeltaMax(int sampleXCenter, int sampleXExtent)
{
  return (int) sampleXExtent - (int) sampleXCenter;
}

int PointMatchAlgorithm::xDeltaMin(int sampleXCenter)
{
  return -1 * (int) sampleXCenter;
}

int PointMatchAlgorithm::yDeltaMax(int sampleYCenter, int sampleYExtent)
{
  return (int) sampleYExtent - (int) sampleYCenter;
}

int PointMatchAlgorithm::yDeltaMin(int sampleYCenter)
{
  return -1 * (int) sampleYCenter;
}
