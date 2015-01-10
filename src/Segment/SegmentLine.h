#ifndef SEGMENT_LINE_H
#define SEGMENT_LINE_H

#include <QGraphicsLineItem>

class QGraphicsScene;
class Segment;

/// This class is a special case of the standard QGraphicsLineItem for segments.
class SegmentLine : public QGraphicsLineItem
{
public:
  /// Single constructor.
  SegmentLine(QGraphicsScene &scene,
              Segment *segment);

  /// Segment that owns this line
  Segment *segment() const;

private:
  SegmentLine();

  Segment *m_segment;
};

#endif // SEGMENT_LINE_H
