#include "Filter.h"
#include <QImage>

Filter::Filter()
{
}

bool Filter::colorCompare (QRgb rgb1,
                           QRgb rgb2)
{
  const long MASK = 0xf0f0f0f0;
  return (rgb1 & MASK) == (rgb2 & MASK);
}

QRgb Filter::marginColor(const QImage *image)
{
  // Add unique colors to colors list
  ColorList colorCounts;
  for (int x = 0; x < image->width (); x++) {
    mergePixelIntoColorCounts (image->pixel (x, 0), colorCounts);
    mergePixelIntoColorCounts (image->pixel (x, image->height () - 1), colorCounts);
  }
  for (int y = 0; y < image->height (); y++) {
    mergePixelIntoColorCounts (image->pixel (0, y), colorCounts);
    mergePixelIntoColorCounts (image->pixel (image->width () - 1, y), colorCounts);
  }

  // Margin color is the most frequent color
  FilterColorEntry entryMax;
  entryMax.count = 0;
  for (ColorList::const_iterator itr = colorCounts.begin (); itr != colorCounts.end (); itr++) {
    if ((*itr).count > entryMax.count) {
      entryMax = *itr;
    }
  }

  return entryMax.color.rgb();
}

void Filter::mergePixelIntoColorCounts (QRgb pixel,
                                        ColorList &colorCounts)
{
  FilterColorEntry entry;
  entry.color = pixel;
  entry.count = 0;

  // Look for previous entry
  bool found = false;
  for (ColorList::iterator itr = colorCounts.begin (); itr != colorCounts.end (); itr++) {
    if (colorCompare (entry.color.rgb(),
                      (*itr).color.rgb())) {
      found = true;
      ++(*itr).count;
      break;
    }
  }

  if (!found) {
    colorCounts.append (entry);
  }
}
