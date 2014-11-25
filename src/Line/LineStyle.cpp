#include "LineStyle.h"

const int DEFAULT_LINE_WIDTH = 1;

LineStyle::LineStyle () :
  m_width (0),
  m_paletteColor (COLOR_PALETTE_TRANSPARENT),
  m_curveConnectAs (CONNECT_AS_FUNCTION)
{
}

LineStyle::LineStyle (unsigned int width,
                      ColorPalette paletteColor,
                      CurveConnectAs curveConnectAs) :
  m_width (width),
  m_paletteColor (paletteColor),
  m_curveConnectAs (curveConnectAs)
{
}

LineStyle::LineStyle (const LineStyle &other) :
  m_width (other.width ()),
  m_paletteColor (other.paletteColor()),
  m_curveConnectAs (other.curveConnectAs())
{
}

LineStyle &LineStyle::operator= (const LineStyle &other)
{
  m_width = other.width ();
  m_paletteColor = other.paletteColor();
  m_curveConnectAs = other.curveConnectAs();

  return *this;
}

QColor LineStyle::color () const
{
  return Qt::red;
}

CurveConnectAs LineStyle::curveConnectAs () const
{
  return m_curveConnectAs;
}

LineStyle LineStyle::defaultAxesCurve ()
{
  return LineStyle (DEFAULT_LINE_WIDTH,
                    COLOR_PALETTE_TRANSPARENT,
                    CONNECT_AS_FUNCTION); // Same default color as used for PointStyle axes curve default
}

LineStyle LineStyle::defaultGraphCurve (int /* index */)
{
  return LineStyle (DEFAULT_LINE_WIDTH,
                    COLOR_PALETTE_BLUE,
                    CONNECT_AS_FUNCTION); // Same default color as used for PointStyle graph curves default
}

ColorPalette LineStyle::paletteColor() const
{
  return m_paletteColor;
}

void LineStyle::setCurveConnectAs(CurveConnectAs curveConnectAs)
{
  m_curveConnectAs = curveConnectAs;
}

void LineStyle::setPaletteColor (ColorPalette paletteColor)
{
  m_paletteColor = paletteColor;
}

void LineStyle::setWidth (int width)
{
  m_width = width;
}

unsigned int LineStyle::width () const
{
  return m_width;
}
