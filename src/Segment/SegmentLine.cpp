#include "SegmentLine.h"

SegmentLine::SegmentLine(QGraphicsScene  &scene,
                         Segment *segment) :
  m_segment (segment)
{
}

Segment *SegmentLine::segment() const
{
  return m_segment;
}
