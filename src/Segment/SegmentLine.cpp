#include "DataKey.h"
#include "GraphicsItemType.h"
#include "Logger.h"
#include "SegmentLine.h"

SegmentLine::SegmentLine(QGraphicsScene  & /* scene */,
                         Segment *segment) :
  m_segment (segment)
{
  LOG4CPP_INFO_S ((*mainCat)) << "SegmentLine::SegmentLine"
                              << " address=0x" << std::hex << (unsigned long) this;

  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, QVariant (GRAPHICS_ITEM_TYPE_SEGMENT));
}

SegmentLine::~SegmentLine ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "SegmentLine::~SegmentLine"
                              << " address=0x" << std::hex << (unsigned long) this;
}

Segment *SegmentLine::segment() const
{
  return m_segment;
}
