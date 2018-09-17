/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef PIXELS_H
#define PIXELS_H

#include <QMap>
#include <QPoint>
#include <QQueue>
#include <QStack>
#include <QString>

class QImage;

/// Quick lookup table for pixel coordinate hashes processed so far
typedef QMap<QString, bool> HashLookup;

typedef QQueue<QPoint> QueuedPoints;

/// Each pixel transitions from unprocessed, to in-process, to processed
enum PixelFillState {
  PIXEL_FILL_STATE_UNPROCESSED,
  PIXEL_FILL_STATE_IN_PROCESS,
  PIXEL_FILL_STATE_PROCESSED
};

/// Utility class for pixel manipulation
class Pixels
{
public:
  /// Single constructor
  Pixels();

  /// Fill triangle between these three points
  int countBlackPixelsAroundPoint (const QImage &image,
                                   int x,
                                   int y,
                                   int stopCountAt);

  /// Fill white hole encompassing (row,col) if number of pixels in that hole is below the threshold
  void fillHole (QImage &image,
                 int row,
                 int col,
                 int thresholdCount) const;

  /// Fill in white holes, surrounded by black pixels, smaller than some threshold number of pixels. Originally
  /// this was recursive but the high recursion levels (for big regions) overflowed the stack
  void fillHoles (QImage &image,
                  int thresholdCount);

  /// Fill in white pixels surrounded by more black pixels than white pixels. This is much faster than
  /// fillHoles and effectively as good
  void fillIsolatedWhitePixels (QImage &image);

  /// Return true if pixel is black in black and white image
  static bool pixelIsBlack (const QImage &image,
                            int x,
                            int y);
  
private:

  enum FillIt {
    NO_FILL,
    YES_FILL
  };

  // Multiple pass algorithm
  int fillPass (QImage &image,
                QVector<PixelFillState> &states,
                int row,
                int col,
                PixelFillState stateFrom,
                PixelFillState stateTo,
                FillIt fillit);
  QString hashForCoordinates (int x,
                              int y) const;
  int indexCollapse (int row,
                     int col,
                     int width) const;
};

#endif // PIXELS_H
