#ifndef GRAPHICS_LINE_H
#define GRAPHICS_LINE_H

#include <QGraphicsLineItem>

class LineStyle;

/// This class draws one line between one pair of points, as a QGraphicsItem. There is no
/// counterpart inside the Document since the Points and Coordinates in the Document are all
/// that are needed to create all the GraphicsLines
class GraphicsLine : public QGraphicsLineItem
{
public:
  /// Single constructor
  GraphicsLine(const LineStyle &lineStyle);

private:
  GraphicsLine();
};

#endif // GRAPHICS_LINE_H
