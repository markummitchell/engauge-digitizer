#include "CallbackAngleX.h"
#include "CallbackAngleY.h"
#include "Logger.h"
#include "PlotClassifier.h"
#include <QBitmap>
#include <QDebug>
#include <QFile>
#include <QImage>
#include <QLabel>
#include <qmath.h>
#include <QPixmap>
#include <QTextStream>
#include <QTransform>
#include <QVBoxLayout>

const int GRAY_LEVEL_COUNT = 256;
const int GRAY_LEVEL_COUNT2 = GRAY_LEVEL_COUNT * GRAY_LEVEL_COUNT;

const QRgb BITMAP_OFF = 0xFFFFFFFF;
const QRgb BITMAP_ON = 0xFF000000;

const QRgb VALUE_BACKGROUND = 0x0000FF;
const QRgb VALUE_FOREGROUND = 0x00FF00;
const QRgb VALUE_PROCESSED = 0xFF0000;

const QRgb VALUE_OFF_UNASSIGNED = qRgb (255, 255, 255);
const QRgb VALUE_OFF_INTERIOR = qRgb (0, 255, 0);
const QRgb VALUE_OFF_PERIMETER = qRgb (0, 0, 255);

const double PI = 3.1415926535;
const double DEG_2_RAD = PI / 180.0;

PlotClassifier::PlotClassifier(const QPixmap &pixmap,
                               QWidget *parent) :
  QDialog (parent)
{
  QVBoxLayout *layout = new QVBoxLayout;
  setLayout (layout);

  m_lbl = new QLabel;
  m_lbl->setPixmap (pixmap);
  layout->addWidget (m_lbl);
}

void PlotClassifier::classify ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "PlotClassifier::classify";

  QImage img; // Remove this

  for (int x = 0; x < img.width(); x++) {
    for (int y = 0; y < img.height(); y++) {

      if (img.pixel (x, y) == VALUE_OFF_UNASSIGNED) {

        // Grab all neighboring VALUE_OFF_UNASSIGNED pixels. We do this by walking around the perimeter in an (arbitrarily)
        // clockwise direction, making sure not to cross into the VALUE_ON pixels, or go out of the image's bounds. First
        // we must go until we hit a boundary. Let's go (arbitrarily) up.
        int xPerim = x, yPerim = y;
        while (yPerim > 0 && (img.pixel (xPerim, yPerim - 1) == VALUE_OFF_UNASSIGNED)) {
          --yPerim;
        }

        PerimeterPixels perimeterPixels;

        pushPerimeterPointAndRecurse (perimeterPixels,
                                      xPerim,
                                      yPerim,
                                      xPerim,
                                      yPerim - 1);

        // Mark all interior points recursively. For a simply connected set (like a circle) we could start
        // from any single perimeter point, but for cases like figure eights we try from every perimeter point
        PerimeterPixels::const_iterator itr;
        for (itr = perimeterPixels.begin (); itr != perimeterPixels.end (); itr++) {
          QPoint point = *itr;
          markNeighborhoodPixelsAsProcessed (point.x (),
                                             point.y ());
        }
      }
    }
  }
}

void PlotClassifier::markNeighborhoodPixelsAsProcessed (int x,
                                                        int y)
{
  LOG4CPP_INFO_S ((*mainCat)) << "PlotClassifier::markNeighborhoodPixelsAsProcessed";

  QImage img = m_lbl->pixmap()->toImage ();

  // At the highest level, (x,y) is either VALUE_OFF_PERIMETER or VALUE_OFF_UNASSIGNED. At lower level it
  // is just VALUE_OFF_UNASSIGNED
  QRgb pixel = img.pixel (x, y);
  if (pixel == VALUE_OFF_UNASSIGNED) {
    img.setPixel (x, y, VALUE_OFF_INTERIOR);
  }

  for (int xDelta = -1; xDelta < 2; xDelta++) {

    int xNext = x + xDelta;
    if ((0 <= xNext) && (xNext < img.width ())) {

      for (int yDelta = -1; yDelta < 2; yDelta++) {

        int yNext = y + yDelta;
        if ((0 <= yNext) && (yNext < img.height ())) {

          if ((xDelta != 0) || (yDelta != 0)) {

            QRgb pixelNext = img.pixel (xNext, yNext);
            if (pixelNext == VALUE_OFF_UNASSIGNED) {

              markNeighborhoodPixelsAsProcessed (xNext,
                                                 yNext);
            }
          }
        }
      }
    }
  }
}

void PlotClassifier::outputHistogram (long histogram [],
                                      int grayPeakLow,
                                      int grayPeakHigh,
                                      int countPeak)
{
  QFile fHistogram ("histogram.tsv");
  fHistogram.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream strHistogram (&fHistogram);

  for (int gray = 0; gray < GRAY_LEVEL_COUNT; gray++) {
    int maxProfile = 0;
    if (grayPeakLow <= gray && gray <= grayPeakHigh) {
      maxProfile = countPeak;
    }
    strHistogram << gray << "\t" << histogram [gray] << "\t" << maxProfile << endl;
  }

  fHistogram.close();
}

void PlotClassifier::pushPerimeterPointAndRecurse (PerimeterPixels &perimeterPixels,
                                                   int xPerim,
                                                   int yPerim,
                                                   int xObstacle,
                                                   int yObstacle)
{
  LOG4CPP_INFO_S ((*mainCat)) << "PlotClassifier::pushPerimeterPointAndRecurse";

  QImage img; // Remove this

  perimeterPixels.push_back (QPoint (xPerim, yPerim));
  img.setPixel (xPerim, yPerim, VALUE_OFF_PERIMETER);

  // Loop around (xPerim,yPerim) clockwise until we hit (xObstacle,yObstacle). This requires
  // looping through twice (=through 720 degrees) to handle the worst case (obstacle is near 360 degrees)
  bool foundObstacle = false;
  bool done = false;
  for (int iteration = 0; (iteration < 2) && !done; iteration++) {
    for (int xDelta = -1; (xDelta < 2) && !done; xDelta++) {
      for (int yDelta = -1; (yDelta < 2) && !done; yDelta++) {

        // We allow xNeighbor and yNeighbor to go out of the image bounds here since obstacle may also be out of bounds
        int xNeighbor = xPerim + xDelta;
        int yNeighbor = yPerim + yDelta;

        if ((xDelta != 0) || (yDelta != 0)) {

          if ((xNeighbor == xObstacle) &&
              (yNeighbor == yObstacle)) {

            if (foundObstacle) {

              // We looped around so far that we cam back to the obstacle, so it is time to quit
              done = true;

            } else {

              foundObstacle = true;

            }

          } else if (foundObstacle) {

            if ((0 <= xNeighbor) && (xNeighbor < img.width ()) &&
                (0 <= yNeighbor) && (yNeighbor < img.height ())) {

              if (img.pixel (xNeighbor, yNeighbor) == VALUE_OFF_UNASSIGNED) {

                // Found next perimeter pixel
                if ((xNeighbor == perimeterPixels.first().x()) &&
                    (yNeighbor == perimeterPixels.first().y())) {

                  // Done with finding perimeter
                  return;

                } else {

                  // Recurse
                  pushPerimeterPointAndRecurse (perimeterPixels,
                                                xNeighbor,
                                                yNeighbor,
                                                xPerim,
                                                yPerim);
                }
              }
            }
          }
        }
      }
    }
  }
}

void PlotClassifier::showEvent(QShowEvent *)
{
  // This approach:
  // 1) Removes the border, and after than determines the background color of the graph image that is left. This works
  //    well with graphs on a white page that have a non-white background color
  const QImage img = m_lbl->pixmap()->toImage ();
  QImage imgBorder = img.createHeuristicMask();

  long histogram2 [GRAY_LEVEL_COUNT2]; // Faster to do histogram on gray^2 rather than gray
  for (int gray2 = 0; gray2 < GRAY_LEVEL_COUNT2; gray2++) {
    histogram2 [gray2] = 0;
  }

  for (int x = 0; x < img.width (); x++) {
    for (int y = 0; y < img.height (); y++) {
      QRgb rgbBorder = imgBorder.pixel (x,  y);
      if (rgbBorder == BITMAP_ON) {
        QRgb rgb = img.pixel (x, y);
        int r = qRed (rgb);
        int g = qGreen (rgb);
        int b = qBlue (rgb);
        int gray2 = (r * r + g * g + b * b) / 3.0;
        Q_ASSERT (gray2 < GRAY_LEVEL_COUNT2);
        ++histogram2 [gray2];
      }
    }
  }

  // Collapse the gray^2 histogram into the gray histogram
  long histogram [GRAY_LEVEL_COUNT];
  for (int gray = 0; gray < GRAY_LEVEL_COUNT; gray++) {
    histogram [gray] = 0;
  }
  for (int gray2 = 0; gray2 < GRAY_LEVEL_COUNT2; gray2++) {
    int gray = qSqrt (gray2);
    histogram [gray] += histogram2 [gray2];
  }

  // Find highest histogram peak
  int grayPeak = -1;
  int countPeak = 0;
  for (int gray = 0; gray < GRAY_LEVEL_COUNT; gray++) {
    if ((grayPeak == -1) || (histogram [gray] > countPeak)) {
      grayPeak = gray;
      countPeak = histogram [gray];
    }
  }

  // Find the lowest and highest gray values belonging to this peak. We go at least halfway down the peak (in case the peak goes up-down-up)
  int grayPeakLow = grayPeak, grayPeakHigh = grayPeak;
  bool canGoDown = (grayPeakLow > 0);
  bool shouldGoDown = canGoDown && (
                        (histogram [grayPeakLow - 1] < histogram [grayPeakLow]) ||
                        (histogram [grayPeakLow] > histogram [grayPeak] / 2));
  while (shouldGoDown) {
    --grayPeakLow;
    Q_ASSERT (grayPeakLow >= 0);

    canGoDown = (grayPeakLow > 0);
    shouldGoDown = canGoDown && (
                     (histogram [grayPeakLow - 1] < histogram [grayPeakLow]) ||
                     (histogram [grayPeakLow] > histogram [grayPeak] / 2));
  }
  bool canGoUp = (grayPeakHigh < GRAY_LEVEL_COUNT - 1);
  bool shouldGoUp = canGoUp &  (
                      (histogram [grayPeakHigh + 1] < histogram [grayPeakHigh]) ||
                      (histogram [grayPeakHigh] > histogram [grayPeak] / 2));
  while (shouldGoUp) {
    ++grayPeakHigh;
    Q_ASSERT (grayPeakHigh < GRAY_LEVEL_COUNT - 1);

    canGoUp = (grayPeakHigh < GRAY_LEVEL_COUNT - 1);
    shouldGoUp = canGoUp &  (
                   (histogram [grayPeakHigh + 1] < histogram [grayPeakHigh]) ||
                   (histogram [grayPeakHigh] > histogram [grayPeak] / 2));
  }

  int grayPeakLow2 = grayPeakLow * grayPeakLow;
  int grayPeakHigh2 = grayPeakHigh * grayPeakHigh;

  ForegroundPoints foregroundPoints;

  QImage imgDiscretized (img.width(),
                         img.height(),
                         QImage::Format_RGB32);
  for (int x = 0; x < img.width(); x++) {
    for (int y = 0; y < img.height(); y++) {
      QRgb rgbBorder = imgBorder.pixel (x, y);
      if (rgbBorder == BITMAP_OFF) {
        imgDiscretized.setPixel (x, y, VALUE_PROCESSED);
      } else {
        QRgb rgb = img.pixel (x, y);
        int r = qRed (rgb);
        int g = qGreen (rgb);
        int b = qBlue (rgb);
        int gray2 = (r * r + g * g + b * b) / 3.0;
        if (grayPeakLow2 <= gray2 && gray2 <= grayPeakHigh2) {
          imgDiscretized.setPixel (x, y, VALUE_BACKGROUND);
        } else {
          imgDiscretized.setPixel (x, y, VALUE_FOREGROUND);
          QPoint pointForeground (x, y);
          foregroundPoints.push_back (pointForeground);
        }
      }
    }
  }

  QPixmap pixmap;
  pixmap.convertFromImage (imgDiscretized);
  m_lbl->setPixmap (pixmap);

  QFile fResultsX ("resultsX.tsv");
  fResultsX.open (QIODevice::WriteOnly | QIODevice::Text);
  QTextStream strX (&fResultsX);

  int periodMinX = 15;
  int periodMaxX = pixmap.width () / 4;
  int periodStepX = 2;
  double angleX = 10.0 * DEG_2_RAD;

  CallbackAngleX callbackX (foregroundPoints,
                            angleX,
                            "X",
                            imgDiscretized.width (),
                            imgDiscretized.height ());

  for (double periodX = periodMinX; periodX < periodMaxX; periodX += periodStepX) {
    for (int gridlineCountX = 3; gridlineCountX <= 7; gridlineCountX++) {
      bool moreThanHalfImage = ((gridlineCountX - 1) * periodX > imgDiscretized.width () / 2);
      bool fitsInImage = ((gridlineCountX - 1) * periodX < imgDiscretized.width ());
      if (moreThanHalfImage && fitsInImage) {
        strX << periodX << "\t" << gridlineCountX << "\t" << angleX << "\t" << callbackX.callback (periodX,
                                                                                                   gridlineCountX) << endl;
      }
    }
  }

  fResultsX.close ();

  QFile fResultsY ("resultsY.tsv");
  fResultsY.open (QIODevice::WriteOnly | QIODevice::Text);
  QTextStream strY (&fResultsY);

  int periodMinY = 15;
  int periodMaxY = pixmap.height () / 4;
  int periodStepY = 2;
  double angleY = 0.0 * DEG_2_RAD;

  CallbackAngleY callbackY (foregroundPoints,
                            angleY,
                            "Y",
                            imgDiscretized.width (),
                            imgDiscretized.height ());

  for (double periodY = periodMinY; periodY < periodMaxY; periodY += periodStepY) {
    for (int gridlineCountY = 5; gridlineCountY <= 9; gridlineCountY++) {
      bool moreThanHalfImage = ((gridlineCountY - 1) * periodY > imgDiscretized.height () / 2);
      bool fitsInImage = ((gridlineCountY - 1) * periodY < imgDiscretized.height  ());
      if (moreThanHalfImage && fitsInImage) {
        strY << periodY << "\t" << gridlineCountY << "\t" << angleY << "\t" << callbackY.callback (periodY,
                                                                                                   gridlineCountY) << endl;
      }
    }
  }

  fResultsY.close ();
}
