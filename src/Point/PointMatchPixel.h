#ifndef POINT_MATCH_PIXEL_H
#define POINT_MATCH_PIXEL_H

#include <QPoint>

/// Single on or off pixel out of the pixels that define the point match mode's candidate point
class PointMatchPixel
{
 public:
  /// Single basic constructor
  PointMatchPixel(int xOffset,
                  int yOffset,
                  bool pixelIsOn);

  /// Copy constructor
  PointMatchPixel (const PointMatchPixel &other);

  /// Assignment operator
  PointMatchPixel &operator= (const PointMatchPixel &other);

  /// True/false if pixel is on/off
  bool pixelIsOn () const;

  /// X position relative to the center of the point
  int xOffset () const;

  /// Y position relative to the center of the point
  int yOffset () const;

 private:
  PointMatchPixel();

  QPoint m_posOffset;
  bool m_pixelIsOn;
};

#endif // POINT_MATCH_PIXEL_H
