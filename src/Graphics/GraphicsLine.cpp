#include "EnumsToQt.h"
#include "GraphicsLine.h"
#include "LineStyle.h"
#include <QPen>

GraphicsLine::GraphicsLine(const LineStyle &lineStyle)
{
  // Line pen is set here. The line geometry is set later, after the constructor has finished
  QColor color (ColorPaletteToQColor (lineStyle.paletteColor ()));
  unsigned int width = lineStyle.width ();

  QPen pen (QBrush (color),
            width);
  setPen (pen);
}
