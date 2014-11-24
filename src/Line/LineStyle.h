#ifndef LINE_STYLE_H
#define LINE_STYLE_H

#include "ColorPalette.h"
#include <QColor>

/// Details for a specific Line.
class LineStyle
{
public:
  /// Single constructor.
  LineStyle (unsigned int width,
             ColorPalette paletteColor);

  /// Return the line color.
  QColor color () const;

  /// Initial default for axes curve.
  static LineStyle defaultAxesCurve ();

  /// Initial default for index'th graph curve.
  static LineStyle defaultGraphCurve (int index);

  /// Line color.
  ColorPalette paletteColor() const;

  /// Width of line.
  unsigned int width () const;

private:
  LineStyle();

  unsigned int m_width;
  ColorPalette m_paletteColor;
};

#endif // LINE_STYLE_H
