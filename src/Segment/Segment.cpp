#include "DataKey.h"
#include "DocumentModelSegments.h"
#include "GraphicsItemType.h"
#include <QGraphicsScene>
#include "Segment.h"
#include "SegmentLine.h"

Segment::Segment(QGraphicsScene &scene) :
  m_scene (scene)
{
  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, QVariant (GRAPHICS_ITEM_TYPE_SEGMENT));
}

void Segment::appendColumn(int x, int y, const DocumentModelSegments &modelSegments)
{
  SegmentLine* line = new SegmentLine(canvas, this);
  Q_CHECK_PTR(line);
  line->setPoints(x - 1, yLast, x, y);
  line->setPen(PointSetStyles::instance().pointSetPen(seg.lineColor, seg.lineSize));
  line->setZ(ZSegments);

  // Do not show this line or its segment. this is handled later

  m_lines.append(line);

  // Update total length using distance formula
  m_length += sqrt((1.0) * (1.0) + (y - yLast) * (y - yLast));

  yLast = y;
}

void Segment::setDocumentModelSegments (const DocumentModelSegments &modelSegments)
{

}
