#ifndef FILTER_H
#define FILTER_H

#include "FilterColorEntry.h"
#include <QList>
#include <QRgb>

class QImage;

/// Class for filtering image to remove unimportant information.
class Filter
{
public:
  /// Single constructor.
  Filter();

  /// Identify the margin color of the image, which is defined as the most common color in the four margins. For speed,
  /// only pixels in the four borders are examined, with the results from those borders safely representing the most
  /// common color of the entire margin areas.
  QRgb marginColor(const QImage *image);

private:

  typedef QList<FilterColorEntry> ColorList;

  bool colorCompare (QRgb rgb1,
                     QRgb rgb2);
  void mergePixelIntoColorCounts (QRgb pixel,
                                  ColorList &colorCounts);
};

#endif // FILTER_H
