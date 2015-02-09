#ifndef GRAPHICS_LINE_H
#define GRAPHICS_LINE_H

#include <QGraphicsLineItem>

class QPointF;

class LineStyle;

/// This class draws one line between one pair of points, as a QGraphicsItem. There is no
/// counterpart inside the Document since the Points and Coordinates in the Document are all
/// that are needed to create all the GraphicsLines
///
/// Values that are dynamic, like point ordinals, are stored as QGraphicsItem data values
/// rather than member variables of this class.
class GraphicsLine : public QGraphicsLineItem
{
public:
  /// Single constructor
  GraphicsLine(const LineStyle &lineStyle);

  /// Move start point of this line.
  void moveStart (const QPointF &pos);

  /// Move end point of this line.
  void moveEnd (const QPointF &pos);

private:
  GraphicsLine();
};

#endif // GRAPHICS_LINE_H
