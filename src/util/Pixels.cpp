/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Pixels.h"
#include <QImage>
#include <qmath.h>
#include <QRgb>

Pixels::Pixels ()
{
}

int Pixels::countBlackPixelsAroundPoint (const QImage &image,
                                         int x,
                                         int y,
                                         int stopCountAt)
{
  int count = 0;
  QueuedPoints queuedPoints;
  HashLookup hashLookup; // Prevents reprocessing of already-processed pixels

  // First point
  if (pixelIsBlack (image, x, y)) {
    queuedPoints.push_back (QPoint (x, y));
  }

  while (queuedPoints.count () > 0) {
    
    // Pop off queue
    QPoint p = queuedPoints.front ();
    queuedPoints.pop_front ();

    QString hash = hashForCoordinates (p.x(),
                                       p.y());

    // Skip if out of bounds, processed already or not black
    bool inBounds = (0 <= p.x() &&
                     0 <= p.y() &&
                     p.x() < image.width () &&
                     p.y() < image.height ());
    if (inBounds &&
        !hashLookup.contains (hash) &&
        pixelIsBlack (image, p.x(), p.y())) {

      // Black pixel. Add to count, and remember to not reprocess later
      ++count;
      if (count == stopCountAt) {
        return count; // Reached limit. Stop immediately (probably for speed)
      }
      hashLookup [hash] = true;

      // Queue neighbors for processing
      for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
          if (dx != 0 || dy != 0) {
            queuedPoints.push_back (QPoint (p.x() + dx,
                                            p.y() + dy));
          }
        }
      }
    }
  }

  return count; // Did not reach limit
}

void Pixels::fillHole (QImage &image,
                       int row,
                       int col,
                       int thresholdCount) const
{
  // Square of 1 pixel is surrounded by 3x3 box with indexes -1 to +2
  //           2-4 pixels               4x4                  -2 to +2
  //           5-9                      5x5                  -2 to +3
  //           10-16                    6x6                  -3 to +3
  int rowStart = row - (1 + qSqrt (thresholdCount - 1)); // Inclusive
  int colStart = col - (1 + qSqrt (thresholdCount - 1)); // Inclusive
  int rowStop = row + (1 + qSqrt (thresholdCount)); // Exclusive
  int colStop = col + (1 + qSqrt (thresholdCount)); // Exclusive

  // First pass is for counting
  int countWhite = 0;
  for (int row = rowStart; row < rowStop; row++) {
    for (int col = colStart; col < colStop; col++) {
      if (!pixelIsBlack (image,
                         col,
                         row)) {
        ++countWhite;
      }
    }
  }

  // Second pass fills in the hole
  if (countWhite < thresholdCount) {
    for (int row = rowStart; row < rowStop; row++) {
      for (int col = colStart; col < colStop; col++) {
        image.setPixel (col,
                        row,
                        Qt::black);
      }
    }
  }
}

void Pixels::fillHoles (QImage &image,
                        int thresholdCount)
{
  int height = image.height();
  int width = image.width();

  // 2d matrix, indexed as 1d vector, of pixel states
  QVector<PixelFillState> states (image.width() * image.height());
  states.fill (PIXEL_FILL_STATE_UNPROCESSED);

  // Search for unprocessed pixels
  for (int col = 0; col < width; col++) {
    for (int row = 0; row < height; row++) {
      if (states [indexCollapse (row, col, width)] == PIXEL_FILL_STATE_UNPROCESSED) {

        // Found an unprocessed pixel so process it
        if (pixelIsBlack (image, col, row)) {

          // Black pixel needs no processing
          states [indexCollapse (row, col, width)] = PIXEL_FILL_STATE_PROCESSED;

        } else {

          // Get this pixel and all of its white neighbors
          int pixelsInRegion = fillPass (image,
                                         states,
                                         row,
                                         col,
                                         PIXEL_FILL_STATE_UNPROCESSED,
                                         PIXEL_FILL_STATE_IN_PROCESS,
                                         NO_FILL);

          FillIt fillIt = (pixelsInRegion < thresholdCount) ? YES_FILL : NO_FILL;

          fillPass (image,
                    states,
                    row,
                    col,
                    PIXEL_FILL_STATE_IN_PROCESS,
                    PIXEL_FILL_STATE_PROCESSED,
                    fillIt);
        }
      }
    }
  }
}

void Pixels::fillIsolatedWhitePixels (QImage &image)
{
  const int BORDER = 1;
  const int HALF_NUMBER_NEIGHBORS = 4; // 8 neighbors in each direction from (col,row)

  int height = image.height();
  int width = image.width();

  // 2d matrix, indexed as 1d vector, of neighbor counts
  QVector<bool> pixelsAreBlack (image.width() * image.height());

  // Replace slow QImage addressing by faster QVector addressing
  for (int col = 0; col < width; col++) {
    for (int row = 0; row < height; row++) {
      pixelsAreBlack [indexCollapse (row, col, width)] = pixelIsBlack (image, col, row);
    }
  }

  // Search for white pixels. Black pixels will be ignored, and also pixels along the four
  // borders are ignored so we do not need to worry about going out of bounds
  for (int col = BORDER; col < width - BORDER; col++) {
    for (int row = BORDER; row < height - BORDER; row++) {
      int count = 0;
      count += pixelsAreBlack [indexCollapse (row - 1, col - 1, width)] ? 1 : 0;
      count += pixelsAreBlack [indexCollapse (row - 1, col    , width)] ? 1 : 0;
      count += pixelsAreBlack [indexCollapse (row - 1, col + 1, width)] ? 1 : 0;
      count += pixelsAreBlack [indexCollapse (row    , col - 1, width)] ? 1 : 0;
      count += pixelsAreBlack [indexCollapse (row    , col + 1, width)] ? 1 : 0;
      count += pixelsAreBlack [indexCollapse (row + 1, col - 1, width)] ? 1 : 0;
      count += pixelsAreBlack [indexCollapse (row + 1, col    , width)] ? 1 : 0;
      count += pixelsAreBlack [indexCollapse (row + 1, col + 1, width)] ? 1 : 0;
      if (count > HALF_NUMBER_NEIGHBORS) {
        image.setPixel (col,
                          row,
                          Qt::black);
      }
    }
  }
}

int Pixels::fillPass (QImage &image,
                      QVector<PixelFillState> &states,
                      int rowIn,
                      int colIn,
                      PixelFillState stateFrom,
                      PixelFillState stateTo,
                      FillIt fillit)
{
  int height = image.height();
  int width = image.width ();
  int count = 0;
  QList<QPoint> applicablePoints;

  // Add only applicable points to the running list
  applicablePoints.append (QPoint (colIn, rowIn));

  while (applicablePoints.count() > 0) {

    QPoint p = applicablePoints.front();
    applicablePoints.pop_front();

    int col = p.x();
    int row = p.y();

    // Double check point is still applicable and that has not changed since added to list
    PixelFillState stateGot = states [indexCollapse (row, col, width)];
    if (stateGot == stateFrom &&
        !pixelIsBlack (image,
                       col,
                       row)) {

      // Still applicable. Do state-specific stuff here
      if (stateTo == PIXEL_FILL_STATE_IN_PROCESS) {
        ++count;
      } else {
        if (fillit == YES_FILL) {
          image.setPixel (col, row, Qt::black);
        }
      }

      // Change state to prevent reprocessing
      states [indexCollapse (row, col, width)] = stateTo;

      // "Recurse" using list instead of actual recursion (to prevent stack overflow)
      for (int dx = -1; dx <= 1; dx++) {
        int colD = col + dx;
        if (0 <= colD && colD < width) {

          for (int dy = -1; dy <= 1; dy++) {
            int rowD = row + dy;
            if (0 <= rowD && rowD < height) {

              if (dx != 0 || dy != 0) {

                PixelFillState stateGot = states [indexCollapse (rowD, colD, width)];
                if (stateGot == stateFrom &&
                    !pixelIsBlack (image,
                                   colD,
                                   rowD)) {

                  // This point is applicable
                  applicablePoints.append (QPoint (colD, rowD));
                }
              }
            }
          }
        }
      }
    }
  }

  return count;
}

QString Pixels::hashForCoordinates (int x,
                                    int y) const
{
  const int FIELD_WIDTH = 6;

  return QString ("%1/%2")
      .arg (x, FIELD_WIDTH)
      .arg (y, FIELD_WIDTH);
}

int Pixels::indexCollapse (int row,
                           int col,
                           int width) const
{
  return row * width + col;
}

bool Pixels::pixelIsBlack (const QImage &image,
                           int x,
                           int y)
{
  QRgb rgb = image.pixel (x, y);
  return qGray (rgb) < 128;
}

