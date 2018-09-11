/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Pixels.h"
#include <QImage>
#include <QRgb>

Pixels::Pixels (const QImage &image) :
  m_image (image)
{
}

int Pixels::countBlackPixelsAroundPoint (int x,
                                         int y,
                                         int stopCountAt)
{
  int count = 0;
  QueuedPoints m_queuedPoints;

  // First point
  if (pixelIsBlack (m_image, x, y)) {
    m_queuedPoints.push_back (QPoint (x, y));
  }

  while (m_queuedPoints.count () > 0) {
    
    // Pop off queue
    QPoint p = m_queuedPoints.front ();
    m_queuedPoints.pop_front ();

    QString hash = hashForCoordinates (p.x(),
                                       p.y());

    // Skip if out of bounds, processed already or not black
    bool inBounds = (0 <= p.x() &&
                     0 <= p.y() &&
                     p.x() < m_image.width () &&
                     p.y() < m_image.height ());
    if (inBounds &&
        !m_hashLookup.contains (hash) &&
        pixelIsBlack (m_image, p.x(), p.y())) {

      // Black pixel. Add to count, and remember to not reprocess later
      ++count;
      if (count == stopCountAt) {
        return count; // Reached limit. Stop immediately (probably for speed)
      }
      m_hashLookup [hash] = true;

      // Queue neighbors for processing
      for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
          if (dx != 0 || dy != 0) {
            m_queuedPoints.push_back (QPoint (p.x() + dx,
                                              p.y() + dy));
          }
        }
      }
    }
  }

  return count; // Did not reach limit
}

QString Pixels::hashForCoordinates (int x,
                                    int y) const
{
  const int FIELD_WIDTH = 6;

  return QString ("%1/%2")
      .arg (x, FIELD_WIDTH)
      .arg (y, FIELD_WIDTH);
}

bool Pixels::pixelIsBlack (const QImage &image,
                           int x,
                           int y)
{
  QRgb rgb = image.pixel (x, y);
  return qGray (rgb) < 128;
}

