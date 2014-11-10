#ifndef LINE_STYLE_H
#define LINE_STYLE_H

#include <QColor>

/// Details for a specific Line.
class LineStyle
{
public:
  /// Single constructor.
  LineStyle (unsigned int width);

  /// Return the line color.
  QColor color () const;

  /// Width of line.
  unsigned int width () const;

private:
  LineStyle();

  unsigned int m_width;
};

#endif // LINE_STYLE_H
