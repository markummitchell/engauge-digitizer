#include "DataKey.h"
#include "GraphicsItemType.h"
#include "SegmentLine.h"

SegmentLine::SegmentLine(QGraphicsScene  &scene,
                         Segment *segment) :
  m_segment (segment)
{
  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, QVariant (GRAPHICS_ITEM_TYPE_SEGMENT));
}

Segment *SegmentLine::segment() const
{
  return m_segment;
}
