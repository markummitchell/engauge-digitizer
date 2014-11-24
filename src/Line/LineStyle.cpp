#include "LineStyle.h"

const int DEFAULT_LINE_WIDTH = 1;

LineStyle::LineStyle () :
  m_width (0),
  m_paletteColor (COLOR_PALETTE_TRANSPARENT)
{
}

LineStyle::LineStyle (unsigned int width,
                      ColorPalette paletteColor) :
  m_width (width),
  m_paletteColor (paletteColor)
{
}

QColor LineStyle::color () const
{
  return Qt::red;
}

LineStyle LineStyle::defaultAxesCurve ()
{
  return LineStyle (DEFAULT_LINE_WIDTH,
                    COLOR_PALETTE_RED); // Same default color as used for PointStyle axes curve default
}

LineStyle LineStyle::defaultGraphCurve (int /* index */)
{
  return LineStyle (DEFAULT_LINE_WIDTH,
                    COLOR_PALETTE_BLUE); // Same default color as used for PointStyle graph curves default
}

ColorPalette LineStyle::paletteColor() const
{
  return m_paletteColor;
}

unsigned int LineStyle::width () const
{
  return m_width;
}
