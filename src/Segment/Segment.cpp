#include "DataKey.h"
#include "DocumentModelSegments.h"
#include "GraphicsItemType.h"
#include "Segment.h"

Segment::Segment() :
  QGraphicsPathItem(0)
{
  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, QVariant (GRAPHICS_ITEM_TYPE_SEGMENT));
}

void Segment::setDocumentModelSegments (const DocumentModelSegments &modelSegments)
{

}
