#ifndef SEGMENT_LINE_H
#define SEGMENT_LINE_H

#include <QGraphicsLineItem>

class Segment;

// This class is a special case of the standard QGraphicsLineItem for segments.
class SegmentLine : public QGraphicsLineItem
{
public:
  /// Single constructor.
  SegmentLine(QQGraphicsScene  &scene,
              Segment *segment);

  Segment *segment() const;

private:
  SegmentLine();

  Segment *m_segment;
};

#endif // SEGMENT_LINE_H
