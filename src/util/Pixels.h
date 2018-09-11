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

/// Utility class for pixel manipulation
class Pixels
{
public:
  /// Single constructor
  Pixels(const QImage &image);

  /// Fill triangle between these three points
  int countBlackPixelsAroundPoint (int x,
                                   int y,
                                   int stopCountAt);

  /// Return true if pixel is black in black and white image
  static bool pixelIsBlack (const QImage &image,
                            int x,
                            int y);
  
private:
  Pixels();
  
  QString hashForCoordinates (int x,
                              int y) const;

  const QImage &m_image;

  HashLookup m_hashLookup; // Prevents reprocessing of already-processed pixels

};

#endif // PIXELS_H
